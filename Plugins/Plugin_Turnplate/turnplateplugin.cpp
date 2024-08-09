#include "turnplateplugin.h"

#include <QDebug>
//#include <QThread>

namespace jltmoco
{


TurnplatePlugin::TurnplatePlugin()
{
    this->mPort = nullptr;
}

/**
* @brief 安装服务
**/
void TurnplatePlugin::setup()
{
    //配置端口号
    this->mPort = new QSerialPort;
    this->mPort->setBaudRate(115200);//波特率
    this->mPort->setDataBits(QSerialPort::Data8);//数据位
    this->mPort->setParity(QSerialPort::NoParity);//无检验
    this->mPort->setStopBits(QSerialPort::OneStop);//1位停止位
    this->mPort->setFlowControl(QSerialPort::NoFlowControl);//无硬件控制
    QObject::connect(mPort,&QSerialPort::readyRead,
                     this,&TurnplatePlugin::onPortDataParse);
};

/**
* @brief 卸载服务
**/
void TurnplatePlugin::uninstall()
{
    this->mPort->deleteLater();
}

/**
* @brief 轨道连接
* @brief value 1.轨道名
**/
bool TurnplatePlugin::connect(const QString &portName)
{
    if(portName.isEmpty())
        return false;

    this->mPort->setPortName(portName);
    return this->mPort->open(QIODeviceBase::ReadWrite);
}

void TurnplatePlugin::disconnect()
{
    this->mPort->close();
}

/**
* @brief 轨道是否连接
* @brief value 1.轨道名
**/
bool TurnplatePlugin::connected() const
{
    if(!mPort)
        return false;
    return mPort->isOpen();
}

/**
* @brief 端口数据处理
**/
void TurnplatePlugin::onPortDataParse()
{
    //socket 缓存中无数据，则返回.
    if(mPort->bytesAvailable() <= 0)
        return;

    //全部读入，会产生半包、粘包问题
    QByteArray buffer = mPort->readAll();
    this->recvBuffer.append(buffer);
    this->parseRecvBuffer();
}

/**
* @brief 解析数据缓存
**/
void TurnplatePlugin::parseRecvBuffer()
{
    int headIndex = -1,lastIndex = -1;
    for(int i = 0; i < recvBuffer.length(); i++)
    {
        //查找头'#'
        if(recvBuffer.at(i) == '@')
            headIndex = i;
        else if(recvBuffer.at(i) == '$')
            lastIndex = i;
        //查找结束
        if(headIndex != -1 && lastIndex != -1)
            break;
    }
    //存在一包数据
    if(headIndex != -1 && lastIndex != -1)
    {
        //数据出错
        if(headIndex > lastIndex)
        {
            recvBuffer.remove(0,headIndex);
        }
        else
        {
            QByteArray datas = recvBuffer.mid(headIndex+1,lastIndex-1);
            if(datas.length() > 2 && datas[1] == '#')
            {
                this->motorState = datas.mid(0,1).toInt();
                this->motorAngle = QString::number(datas.mid(2,10).toFloat());
            }
            recvBuffer.remove(0,lastIndex+1);
        }
        //粘包,递归处理
        if(!recvBuffer.isEmpty())
        {
            this->parseRecvBuffer();
        }
    }
    //数据出错
    else if(headIndex == -1 && lastIndex != -1)
    {
        recvBuffer.remove(0,lastIndex+1);
    }
}

/**
* @brief 返回设备状态
**/
QJsonObject TurnplatePlugin::getStatusData()
{
    QJsonObject root;
    root["code"] = 1;//状态数据
    root["connected"] = this->connected();
    root["state"] = motorState;
    root["angle"] = motorAngle;

    return root;
}


/**
    * @brief 解析用户指令
    * @param cmd 指令内容
    **/
void TurnplatePlugin::parseUserCommand(const QJsonObject &cmd)
{
    if(connected())
    {
        QString recvData;
        //mode
        recvData.append('@');
        recvData.append(QString::number(cmd["code"].toInt()));
        //目标角度
        recvData.append('#');
        recvData.append(QString::number(cmd["angle"].toDouble()));
        //方向
        recvData.append('#');
        recvData.append(QString::number(cmd["direction"].toInt()));
        //速度
        recvData.append('#');
        recvData.append(QString::number(cmd["speed"].toInt()));
        //加速度
        recvData.append('#');
        recvData.append(QString::number(cmd["acc"].toInt()));
        //减速度
        recvData.append('#');
        recvData.append(QString::number(cmd["dec"].toInt()));
        recvData.append('#');

        //发送数据
        QByteArray array = recvData.toLocal8Bit();
        array.append(0x0D);
        array.append(0x0A);

        this->mPort->write(array,array.length());//发送数据
        this->mPort->flush();//让数据立刻从串口发送出去
    }
}



/**
 * @brief 返回可连接端口号列表
 */
//QStringList TurnplatePlugin::getPorts()
//{
//    QStringList strlist;
//    QList<QSerialPortInfo> list  = QSerialPortInfo::availablePorts();
//    foreach (const QSerialPortInfo & info, list)
//    {
//        strlist.append(info.portName());
//    }
//    return strlist;
//}


/**
 * @brief int 转 轨道array
 */
//QByteArray TurnplatePlugin::intToArray(const int &value)
//{
//    QByteArray rArray(4,0x00);
//    unsigned char vs[4];
//    memcpy_s(&vs,4,&value,4);

//    rArray[0] = vs[3];
//    rArray[1] = vs[2];
//    rArray[2] = vs[1];
//    rArray[3] = vs[0];

//    return rArray;
//}


///**
// * @brief arrat 转long
// */
//long TurnplatePlugin::arrayToLong(const QByteArray &array)
//{
//    long data = 0;

//    unsigned char bytes[4];

//    bytes[0]=array[0];
//    bytes[1]=array[1];
//    bytes[2]=array[2];
//    bytes[3]=array[3];

//    memcpy_s(&data,sizeof(long),bytes,sizeof(long));

//    return data;
//}

}
