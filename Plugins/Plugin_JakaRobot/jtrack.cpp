#include "jtrack.h"

#include <QJsonObject>

#include <QMutex>
#include <QDebug>

using namespace jltmoco;

JTrack* JTrack::handle = Q_NULLPTR;

JTrack* JTrack::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JTrack;
        mutex.unlock();
    }
    return handle;
}

JTrack::JTrack()
{
    this->mMonitorState = false;
    this->railPosition = 0;
    this->railEnable = 0;
    this->railTarget = 0;
    this->railContinueMoveError = 0;

    QAbstractSocket::connect(this,&QTcpSocket::readyRead,
                             this,&JTrack::onReadyRead);
}

JTrack::~JTrack()
{

}

void JTrack::startMonitor()
{
    this->mSetPosition = 0;
    this->mMonitorState = true;
}

void JTrack::stopMonitor()
{
    this->mMonitorState = false;
}

void JTrack::monitor()
{
    if(!mMonitorState)
        return;
    if(dataList.isEmpty())
        return;

    // QJsonObject target = dataList.first()["target"].toObject();
    // //脚本给定的目标位置
    // double e1 = target["E1"].toString().toDouble();
}

void JTrack::onReadyRead()
{
    //socket 缓存中无数据，则返回.
    if(this->bytesAvailable() <= 0)
        return;

    //全部读入，会产生半包、粘包问题
    QByteArray buffer = this->readAll();
    //读取缓存
    if(buffer.size() == 16)
    {
        if(buffer[0]=='#'&&buffer[15]=='$')
        {
            //使能状态 =0未使能 =1使能 =2报错
            this->railEnable = buffer[1];
            this->railAutoEnable();
            //位置
            this->railPosition = arrayToFloat(buffer,4);
            this->monitor();
            //绝对运动状态 =0停止中 =1运动中
            this->railAbsState = buffer[2];
            //是否过渡 =0禁止 =1可以过渡（停止之前一直接收）
            //            this->railTsState = buffer[3];
            //            qDebug() << "railTsState: " << railTsState;
            //    quint8 absG = buffer[3];
            //速度
            //    float speed = this->arrayToFloat(buffer,8);

            //归零错误
            //    quint8 zeroError = buffer[12];
            ////   //消息错误
            //    quint8 msgError = buffer[13];
            ////    //运动错误
            //    quint8 motionError = buffer[14];
            //            qDebug() << enable << pos << zeroError<< msgError<< motionError;
        }
    }
}

/**
 * @brief 轨道使能
 */
void JTrack::railAutoEnable()
{
    static int frameCounter = 0;
    if(railEnable != 1)
    {
        frameCounter++;
        if(frameCounter>=30)
        {
            this->sendModeBuffer(RaileMode_Enable);
            frameCounter = 0;
        }
    }
}

/**
 * @brief 轨道速度控制
 * @param speed
 */
void JTrack::railJogMove(float speed)
{
    static bool isRunning = false;
    if(speed!=0 && !isRunning)
    {
        if(speed > 0)
            this->sendMotionBuffer(RaileMotionMode_Jog_Add,0,qAbs(speed));
        else if(speed < 0)
            this->sendMotionBuffer(RaileMotionMode_Jog_Sub,0,qAbs(speed));

        isRunning = true;
    }
    else if(speed==0)
    {
        isRunning = false;
        this->sendMotionBuffer(RaileMotionMode_Stop);
    }
}

/**
 * @brief 轨道位置控制
 * @param dataObj
 */
void JTrack::railAbsMove(const QJsonObject &dataObj)
{
    float maxSpeed = 666.0f;

    QJsonObject targetJson = dataObj["target"].toObject();
    float target = targetJson["E1"].toString().toFloat();

    QJsonObject paramJson = dataObj["param"].toObject();
    float prgV = ((float)paramJson["PrgV"].toInt())*0.01f;
    float speed = ((float)paramJson["PathV"].toInt())*0.01f*maxSpeed*prgV;

    this->sendMotionBuffer(RaileMotionMode_Absolute,target,speed);
}

/**
 * @brief 轨道连续运动结果
 * @return
 */
bool JTrack::railContinueMoveResult()
{
    if(railEnable != 1 || state() != QAbstractSocket::ConnectedState)
        return true;

    if(qAbs(railPosition-railTarget) > (railContinueMoveError+0.1))
        return false;

    return true;
}

/**
 * @brief 轨道连续运动指令
 * @param targetAngle
 */
void JTrack::railContinueMove(const QJsonObject &node)
{
    float maxSpeed = 666.0f;

    QJsonObject targetJson = node["target"].toObject();

    this->railTarget = targetJson["E1"].toString().toFloat();
    QJsonObject paramJson = node["param"].toObject();
    float prgV = ((float)paramJson["PrgV"].toInt())*0.01f;
    float speed = ((float)paramJson["PathV"].toInt())*0.01f*maxSpeed*prgV;
    this->railContinueMoveError = ((float)paramJson["TsValue"].toInt());

    this->sendMotionBuffer(RaileMotionMode_Absolute,railTarget,speed,railContinueMoveError);
}

/**
 * @brief array 转 轨道Float
 */
float JTrack::arrayToFloat(const QByteArray &array,int index)
{
    float data = 0;
    unsigned char bytes[4];
    //32位
    bytes[0]=array[index+3];
    bytes[1]=array[index+2];
    bytes[2]=array[index+1];
    bytes[3]=array[index];
    memcpy_s(&data,sizeof(float),bytes,4);

    return data;
}


/**
 * @brief Float 转 轨道array
 * @param value 输入转换的值
 * @param array 修改的内存
 * @param index 其实索引
 */
QByteArray JTrack::floatToArray(const float &value)
{
    QByteArray rArray(4,0x00);
    unsigned char vs[4];
    memcpy_s(&vs,4,&value,4);

    rArray[0] = vs[3];
    rArray[1] = vs[2];
    rArray[2] = vs[1];
    rArray[3] = vs[0];

    return rArray;
}

/**
 * @brief 模式指令发送
 * @param mode 指令模式
 */
void JTrack::sendModeBuffer(quint8 mode)
{
    if(state() != QAbstractSocket::ConnectedState)
        return;

    QByteArray buffer(20,0x00);
    buffer[0] = 0x23;
    buffer[1] = mode;
    buffer[2] = 0x00;
    buffer[3] = 0x24;

    this->write(buffer,buffer.length());
}


/**
 * @brief 运动指令发送
 * @param mode 运动模式 =1前进 2后退 3相对位移 4绝对位移 5停止
 * @param pos 位置
 * @param speed 速度
 * @param tv 过渡值
 */
void JTrack::sendMotionBuffer(quint8 mode,float pos,float speed,float tv)
{
    if(state() != QAbstractSocket::ConnectedState)
        return;

    QByteArray buffer(20,0x00);
    buffer[0] = 0x23;
    buffer[1] = 0x06;
    buffer[2] = mode;
    buffer[3] = 0x24;

    //位置 0~
    QByteArray posA = this->floatToArray(pos);
    buffer[4] = posA[0];
    buffer[5] = posA[1];
    buffer[6] = posA[2];
    buffer[7] = posA[3];

    //速度 0~370mm/s
    QByteArray speedA = this->floatToArray(speed);
    buffer[8] = speedA[0];
    buffer[9] = speedA[1];
    buffer[10] = speedA[2];
    buffer[11] = speedA[3];

    //过渡距离 0~100mm
    QByteArray tvA = this->floatToArray(tv);
    buffer[12] = tvA[0];
    buffer[13] = tvA[1];
    buffer[14] = tvA[2];
    buffer[15] = tvA[3];

    this->write(buffer,buffer.length());
    this->flush();
}
