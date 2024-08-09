#include "jrobot.h"
#include "jtrack.h"
#include "jakaplugin.h"
#include "jroboterrortext.h"
#include <QMutex>
#include <QDebug>
#include <QThread>
#include <QJsonObject>

using namespace jltmoco;

JRobot* JRobot::handle = Q_NULLPTR;

void errorFunction(int code)
{
    JRobot::getInstance()->robotCallback(code);
}

JRobot* JRobot::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JRobot;
        mutex.unlock();
    }
    return handle;
}

JRobot::JRobot()
{
    this->robotPlugin = NULL;
    this->mRunLine = 0;
    this->connected = false;
    this->monitorRunning = false;
    this->mServoState = FALSE;
    this->mJogType = 0;
    mJakaRobot.set_error_handler(errorFunction);
    QObject::connect(this,&JRobot::taskChanged,
                     this,&JRobot::onTaskChanged);
}

JRobot::~JRobot()
{

}

void JRobot::closeRobot()
{
    if(connected)
        mJakaRobot.login_out();
}

void JRobot::onTaskChanged(const QJsonObject &task)
{
    int code = task["code"].toInt();
    if(code == -1)
    {
        //连接
        errno_t ret = mJakaRobot.login_in(task["ip"].toString().toStdString().c_str());
        if(ret != ERR_SUCC)
        {
            qDebug() << "jaka robot login_in failed:" << ret;
            return;
        }
        //上电
        QThread::msleep(500);
        ret = mJakaRobot.power_on();
        if(ret != ERR_SUCC)
        {
            qDebug() << "jaka robot power_on failed:" << ret;
            return;
        }
        //使能
        QThread::msleep(500);
        ret = mJakaRobot.enable_robot();
        if(ret != ERR_SUCC)
        {
            qDebug() << "jaka robot enable_robot failed:" << ret;
            return;
        }
        //参数初始化设置
        mJakaRobot.set_collision_level(5);
        mJakaRobot.set_status_data_update_time_interval(8);
        if(mJakaRobot.set_user_frame_id(1) == ERR_SUCC)
            mJakaRobot.get_user_frame_data(1,&mWorld);
        if(mJakaRobot.set_tool_id(1) == ERR_SUCC)
            mJakaRobot.get_tool_data(1,&mTool);
        mJakaRobot.get_payload(&mLoad);
        this->connected = true;
    }
    else if(code == 1)
    {
        jogLoop();
    }
    else if(code == 7)
    {
        monitorLoop();
    }
}

QJsonObject JRobot::getStatus()
{
    QJsonObject status;
    status["code"] = 1;
    status["state"] = 1;
    status["connected"] = connected;
    status["railConnected"] = (JTrack::getInstance()->state()==QAbstractSocket::ConnectedState)?true:false;
    status["runNumber"] = mRunLine;
    QJsonObject data;
    data["E1"] = QString::number(JTrack::getInstance()->railPosition);
    RobotStatus robotStatus;
    if(connected && mJakaRobot.get_robot_status(&robotStatus) == ERR_SUCC)
    {
        mPosition.tran.x = robotStatus.cartesiantran_position[0];
        mPosition.tran.y = robotStatus.cartesiantran_position[1];
        mPosition.tran.z = robotStatus.cartesiantran_position[2];
        mPosition.rpy.rx = robotStatus.cartesiantran_position[3];
        mPosition.rpy.ry = robotStatus.cartesiantran_position[4];
        mPosition.rpy.rz = robotStatus.cartesiantran_position[5];
        data["X"] = QString::number(mPosition.tran.x);
        data["Y"] = QString::number(mPosition.tran.y);
        data["Z"] = QString::number(mPosition.tran.z);
        data["A"] = QString::number(qRadiansToDegrees(mPosition.rpy.rx));
        data["B"] = QString::number(qRadiansToDegrees(mPosition.rpy.ry));
        data["C"] = QString::number(qRadiansToDegrees(mPosition.rpy.rz));
        data["A1"] = QString::number(qRadiansToDegrees(robotStatus.joint_position[0]));
        data["A2"] = QString::number(qRadiansToDegrees(robotStatus.joint_position[1]));
        data["A3"] = QString::number(qRadiansToDegrees(robotStatus.joint_position[2]));
        data["A4"] = QString::number(qRadiansToDegrees(robotStatus.joint_position[3]));
        data["A5"] = QString::number(qRadiansToDegrees(robotStatus.joint_position[4]));
        data["A6"] = QString::number(qRadiansToDegrees(robotStatus.joint_position[5]));
    }
    status["data"] = data;
    //工具坐标系
    QJsonObject obj;
    obj["X"] = mTool.tran.x;
    obj["Y"] = mTool.tran.y;
    obj["Z"] = mTool.tran.z;
    obj["A"] = qRadiansToDegrees(mTool.rpy.rx);
    obj["B"] = qRadiansToDegrees(mTool.rpy.ry);
    obj["C"] = qRadiansToDegrees(mTool.rpy.rz);
    status["tool"] = obj;
    //基坐标系
    obj["X"] = mWorld.tran.x;
    obj["Y"] = mWorld.tran.y;
    obj["Z"] = mWorld.tran.z;
    obj["A"] = qRadiansToDegrees(mWorld.rpy.rx);
    obj["B"] = qRadiansToDegrees(mWorld.rpy.ry);
    obj["C"] = qRadiansToDegrees(mWorld.rpy.rz);
    status["base"] = obj;
    //负载数据
    QJsonObject load;
    load["mass"] = mLoad.mass;
    load["X"] = mLoad.centroid.x;
    load["Y"] = mLoad.centroid.y;
    load["Z"] = mLoad.centroid.z;
    load["A"] = 0;
    load["B"] = 0;
    load["C"] = 0;
    load["JX"] = 0;
    load["JY"] = 0;
    load["JZ"] = 0;
    status["load"] = load;
    return status;
}

void JRobot::setRobotPlugin(JakaPlugin *plugin)
{
    this->robotPlugin = plugin;
}

void JRobot::moveStop()
{
    monitorRunning = false;
    if(mServoState == TRUE)
    {
        mServoState = FALSE;
    }
    else
    {
        mJakaRobot.motion_abort();
    }
}

void JRobot::jogDataUpdate(int type,const QJsonObject &obj)
{
    mJogType = type;
    // 单轴
    if(mJogType==1)
    {
        mJogAxisData.jVal[0] = qDegreesToRadians(obj["P1"].toString().toDouble());
        mJogAxisData.jVal[1] = qDegreesToRadians(obj["P2"].toString().toDouble());
        mJogAxisData.jVal[2] = qDegreesToRadians(obj["P3"].toString().toDouble());
        mJogAxisData.jVal[3] = qDegreesToRadians(obj["P4"].toString().toDouble());
        mJogAxisData.jVal[4] = qDegreesToRadians(obj["P5"].toString().toDouble());
        mJogAxisData.jVal[5] = qDegreesToRadians(obj["P6"].toString().toDouble());
    }
    // 基座坐标
    else
    {
        mJogPosData.tran.x = obj["P1"].toString().toDouble()*10;
        mJogPosData.tran.y = obj["P2"].toString().toDouble()*10;
        mJogPosData.tran.z = obj["P3"].toString().toDouble()*10;
        mJogPosData.rpy.rx = qDegreesToRadians(obj["P4"].toString().toDouble())*2;
        mJogPosData.rpy.ry = qDegreesToRadians(obj["P5"].toString().toDouble())*2;
        mJogPosData.rpy.rz = qDegreesToRadians(obj["P6"].toString().toDouble())*2;
    }
    if(mServoState == FALSE)
    {
        mJakaRobot.servo_move_use_joint_LPF(0.5);
        if(mJakaRobot.servo_move_enable(TRUE) == ERR_SUCC)
        {
            mServoState = TRUE;
            QJsonObject task;
            task["code"] = 1;
            emit taskChanged(task);
        }
    }
}

void JRobot::jogLoop()
{
    while (mServoState == TRUE)
    {
        // 单轴
        if(mJogType==1)
        {
            mJakaRobot.servo_j(&mJogAxisData,INCR);
        }
        // 基座坐标
        else if(mJogType==2)
        {
            mJakaRobot.servo_p(&mJogPosData,INCR);
        }
        // 工具坐标
        else if(mJogType==3)
        {
            RotMatrix matrix;
            mJakaRobot.rpy_to_rot_matrix(&mPosition.rpy,&matrix);
            CartesianPose setPos;
            setPos.tran.x = matrix.x.x*mJogPosData.tran.x+matrix.x.y*mJogPosData.tran.y+matrix.x.z*mJogPosData.tran.z;
            setPos.tran.y = matrix.y.x*mJogPosData.tran.x+matrix.y.y*mJogPosData.tran.y+matrix.y.z*mJogPosData.tran.z;
            setPos.tran.z = matrix.z.x*mJogPosData.tran.x+matrix.z.y*mJogPosData.tran.y+matrix.z.z*mJogPosData.tran.z;
            setPos.rpy.rx = matrix.x.x*mJogPosData.rpy.rx+matrix.x.y*mJogPosData.rpy.ry+matrix.x.z*mJogPosData.rpy.rz;
            setPos.rpy.ry = matrix.y.x*mJogPosData.rpy.rx+matrix.y.y*mJogPosData.rpy.ry+matrix.y.z*mJogPosData.rpy.rz;
            setPos.rpy.rz = matrix.z.x*mJogPosData.rpy.rx+matrix.z.y*mJogPosData.rpy.ry+matrix.z.z*mJogPosData.rpy.rz;
            mJakaRobot.servo_p(&setPos,INCR);
        }
        else
        {
            break;
        }
        QThread::msleep(50);
    }
    if(mJakaRobot.servo_move_enable(FALSE) != ERR_SUCC)
    {
        qDebug() << "JPluginRobot servo_move_enable FALSE failed!";
    }
}

void JRobot::absPosMove(const QJsonObject &dataObj)
{
    QJsonObject target = dataObj["target"].toObject();
    CartesianPose cart;
    cart.tran.x = target["X"].toString().toDouble();
    cart.tran.y = target["Y"].toString().toDouble();
    cart.tran.z = target["Z"].toString().toDouble();
    cart.rpy.rx = qDegreesToRadians(target["A"].toString().toDouble());
    cart.rpy.ry = qDegreesToRadians(target["B"].toString().toDouble());
    cart.rpy.rz = qDegreesToRadians(target["C"].toString().toDouble());

    QJsonObject paramJson = dataObj["param"].toObject();
    double prgV = (double)paramJson["PrgV"].toInt() / 100.0;
    //设置程序速度
    if(mJakaRobot.set_rapidrate(prgV) == ERR_SUCC)
    {
        double rapid_rate = 0;
        mJakaRobot.get_rapidrate(&rapid_rate);
        double speedMax = (double)paramJson["RobotV"].toInt()/100.0*1800.0;//   mm/s
        double accMax = (double)paramJson["RobotA"].toInt()/100.0*2000.0;// mm/s
        errno_t ret = mJakaRobot.linear_move(&cart,ABS,FALSE,speedMax,accMax,0,NULL);
        if(ret != ERR_SUCC)
        {
            ErrorCode errorCode;
            mJakaRobot.get_last_error(&errorCode);
            qDebug() << "JRobot::absPosMove error:" << errorCode.code << errorCode.message;
        }
    }
}

void JRobot::absAxisMove(const QJsonObject &dataObj)
{
    QJsonObject param = dataObj["param"].toObject();
    QJsonObject target = dataObj["target"].toObject();

    JointValue joint_pos;
    joint_pos.jVal[0] = qDegreesToRadians(target["A1"].toString().toDouble());
    joint_pos.jVal[1] = qDegreesToRadians(target["A2"].toString().toDouble());
    joint_pos.jVal[2] = qDegreesToRadians(target["A3"].toString().toDouble());
    joint_pos.jVal[3] = qDegreesToRadians(target["A4"].toString().toDouble());
    joint_pos.jVal[4] = qDegreesToRadians(target["A5"].toString().toDouble());
    joint_pos.jVal[5] = qDegreesToRadians(target["A6"].toString().toDouble());

    //设置程序速度
    double prgV = (double)param["PrgV"].toInt()/100.0;
    if(mJakaRobot.set_rapidrate(prgV) == ERR_SUCC)
    {
        double speed = qDegreesToRadians(((double)param["RobotV"].toInt())/100.0*180.0);
        double acc = qDegreesToRadians(((double)param["RobotA"].toInt())/100.0*400.0);
        errno_t ret = mJakaRobot.joint_move(&joint_pos,ABS,FALSE,speed,acc,0,nullptr);
        if(ret != ERR_SUCC)
        {
            ErrorCode errorCode;
            mJakaRobot.get_last_error(&errorCode);
            qDebug() << "JRobot::absAxisMove error:" << errorCode.code << errorCode.message;
        }
    }
}

void JRobot::setToolCoord(const QJsonObject &dataObj)
{
    if(connected)
    {
        CartesianPose buffer;
        buffer.tran.x=dataObj["X"].toDouble();
        buffer.tran.y=dataObj["Y"].toDouble();
        buffer.tran.z=dataObj["Z"].toDouble();
        buffer.rpy.rx=qDegreesToRadians(dataObj["A"].toDouble());
        buffer.rpy.ry=qDegreesToRadians(dataObj["B"].toDouble());
        buffer.rpy.rz=qDegreesToRadians(dataObj["C"].toDouble());
        if(mJakaRobot.set_tool_data(1,&buffer,"jltapp") == ERR_SUCC)
        {
            mTool = buffer;
        }
        else
        {
            qDebug() << "JRobot::setToolCoord failed";
        }
    }
}

void JRobot::setBaseCoord(const QJsonObject &dataObj)
{
    if(connected)
    {
        CartesianPose buffer;
        buffer.tran.x = dataObj["X"].toDouble();
        buffer.tran.y = dataObj["Y"].toDouble();
        buffer.tran.z = dataObj["Z"].toDouble();
        buffer.rpy.rx = qDegreesToRadians(dataObj["A"].toDouble());
        buffer.rpy.ry = qDegreesToRadians(dataObj["B"].toDouble());
        buffer.rpy.rz = qDegreesToRadians(dataObj["C"].toDouble());
        if(mJakaRobot.set_user_frame_data(1,&buffer,"jltapp") == ERR_SUCC)
        {
            mWorld = buffer;
        }
        else
        {
            qDebug() << "JRobot::setBaseCoord failed";
        }
    }
}

void JRobot::setPayload(const QJsonObject &dataObj)
{
    if(connected)
    {
        PayLoad pay;
        pay.mass = dataObj["M"].toDouble();
        pay.centroid.x = dataObj["X"].toDouble();
        pay.centroid.y = dataObj["Y"].toDouble();
        pay.centroid.z = dataObj["Z"].toDouble();
        if(mJakaRobot.set_payload(&pay) == ERR_SUCC)
        {
            mLoad = pay;
        }
        else
        {
            qDebug() << "JRobot::setPayload failed";
        }
    }
}

/**
 * @brief 连续运动的循环监视器
 */
void JRobot::monitorLoop()
{
    int startLine = 0;
    errno_t ret = mJakaRobot.get_current_line(&startLine);
    if(ret != ERR_SUCC)
    {
        mJakaRobot.get_current_line(&startLine);
    }
    this->mStopInterval = 0;//毫秒
    this->mRunLine = 0;
    this->mMonitorLine = startLine;
    this->monitorRunning = true;
    //初始化全局参数
    if(!dataList.isEmpty())
    {
        QJsonObject firstNode = dataList.first();
        QJsonObject param = firstNode["param"].toObject();
        double prgV = (double)param["PrgV"].toInt()/100.0;
        if(mJakaRobot.set_rapidrate(prgV) != ERR_SUCC)
            qDebug() << "void JRobotPlugin::sendNodeFirst() set_rapidrate failed!";
    }
    //循环监视
    while (monitorRunning)
    {
        //当前是停止状态时,进行连发任务
        BOOL stopFlag = 0;
        mJakaRobot.is_in_pos(&stopFlag);
        if(stopFlag == TRUE)
        {
            //节点暂停时间
            if(mStopInterval>0)
            {
                QThread::msleep(mStopInterval);
                mStopInterval = 0;
            }
            //暂停时间结束后,发送剩余节点
            for (int i = 0; i < 5; ++i)
            {
                if(dataList.isEmpty())
                    break;
                this->sendNodeFirst();
                if(mStopInterval != 0)
                    break;
            }
        }
        //监控
        int line;
        errno_t ret = mJakaRobot.get_current_line(&line);
        if(ret != ERR_SUCC)
        {
            mJakaRobot.get_current_line(&line);
        }
        this->setRunLine(startLine,line);
        QThread::msleep(100);
    }
    dataList.clear();
    mJakaRobot.motion_abort();
}

void JRobot::sendNodeFirst()
{
    QJsonObject node = dataList.takeFirst();
    QJsonObject param = node["param"].toObject();
    QJsonObject target = node["target"].toObject();

    mStopInterval = param["Waiting"].toInt()*1000;
    int type = node["type"].toInt();
    if(type == 1)
    {

        JointValue joint_pos;
        joint_pos.jVal[0] = qDegreesToRadians(target["A1"].toString().toDouble());
        joint_pos.jVal[1] = qDegreesToRadians(target["A2"].toString().toDouble());
        joint_pos.jVal[2] = qDegreesToRadians(target["A3"].toString().toDouble());
        joint_pos.jVal[3] = qDegreesToRadians(target["A4"].toString().toDouble());
        joint_pos.jVal[4] = qDegreesToRadians(target["A5"].toString().toDouble());
        joint_pos.jVal[5] = qDegreesToRadians(target["A6"].toString().toDouble());

        double max = (double)param["PrgV"].toInt()/100.0;
        double v = (double)param["RobotV"].toInt()/100.0;
        double speedMax = qDegreesToRadians(max*v*180.0);
        double accMax = qDegreesToRadians((double)param["RobotA"].toInt()/100.0*400.0);
        double tsValue = (double)param["TsValue"].toInt();

        if(mJakaRobot.joint_move(&joint_pos,ABS,FALSE,speedMax,accMax,tsValue,nullptr) != ERR_SUCC)
            qDebug() << "void JRobotPlugin::sendNodeFirst() joint_move failed!";
    }
    else if(type == 2)
    {
        CartesianPose cart;
        cart.tran.x = target["X"].toString().toDouble();
        cart.tran.y = target["Y"].toString().toDouble();
        cart.tran.z = target["Z"].toString().toDouble();
        cart.rpy.rx = qDegreesToRadians(target["A"].toString().toDouble());
        cart.rpy.ry = qDegreesToRadians(target["B"].toString().toDouble());
        cart.rpy.rz = qDegreesToRadians(target["C"].toString().toDouble());

        double max = (double)param["PrgV"].toInt()/100.0;
        double v = (double)param["RobotV"].toInt()/100.0;
        double accMax = (double)param["RobotA"].toInt()/100.0*2000.0;// mm/s
        double tsValue = (double)param["TsValue"].toInt();
        if(mJakaRobot.linear_move(&cart,ABS,FALSE,(max*v*1800.0),accMax,tsValue,NULL) != ERR_SUCC)
            qDebug() << "void JRobotPlugin::sendNodeFirst() linear_move failed!";
    }
    else if(type == 3)
    {
        QJsonObject assist = node["assist"].toObject();
        //目标位置
        CartesianPose cart;
        cart.tran.x = target["X"].toString().toDouble();
        cart.tran.y = target["Y"].toString().toDouble();
        cart.tran.z = target["Z"].toString().toDouble();
        cart.rpy.rx = qDegreesToRadians(target["A"].toString().toDouble());
        cart.rpy.ry = qDegreesToRadians(target["B"].toString().toDouble());
        cart.rpy.rz = qDegreesToRadians(target["C"].toString().toDouble());
        //辅助位置
        CartesianPose fCart;
        fCart.tran.x = assist["X"].toString().toDouble();
        fCart.tran.y = assist["Y"].toString().toDouble();
        fCart.tran.z = assist["Z"].toString().toDouble();
        fCart.rpy.rx = qDegreesToRadians(assist["A"].toString().toDouble());
        fCart.rpy.ry = qDegreesToRadians(assist["B"].toString().toDouble());
        fCart.rpy.rz = qDegreesToRadians(assist["C"].toString().toDouble());

        //参数
        double max = (double)param["PrgV"].toInt()/100.0;
        double v = (double)param["RobotV"].toInt()/100.0;
        double accMax = (double)param["RobotA"].toInt()/100.0*2000.0;// mm/s
        double tsValue = (double)param["TsValue"].toInt();
        if(mJakaRobot.circular_move(&cart,&fCart,ABS,FALSE,(max*v*1800.0),accMax,tsValue,NULL) != ERR_SUCC)
            qDebug() << "void JRobotPlugin::sendNodeFirst() circular_move failed!";
    }
    QThread::msleep(100);
}

void JRobot::setRunLine(int startLine,int line)
{
    if(mMonitorLine != line)
    {
        this->mMonitorLine = line;
        if(startLine>mMonitorLine)
            this->mRunLine = mMonitorLine-1;
        else
            this->mRunLine = mMonitorLine-startLine-1;

        if(!dataList.isEmpty() && mStopInterval == 0)
        {
            this->sendNodeFirst();
        }
    }
}

void JRobot::robotCallback(int code)
{
    QJsonObject callbackJson;
    callbackJson["code"] = 0x2000;
    callbackJson["data"] = getErrorData(code);
    if(robotPlugin && robotPlugin->mFunc)
    {
        robotPlugin->mFunc(callbackJson);
    }
}
