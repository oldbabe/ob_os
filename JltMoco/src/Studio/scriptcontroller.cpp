#include "Studio/scriptcontroller.h"

#include <QMutex>
#include <QDebug>

#include "NetWork/studioclient.h"

#include "Studio/jrobot.h"
#include "Studio/jcamera.h"
#include "Studio/jturnplate.h"
#include "Studio/jfollowfocus.h"

using namespace jltmoco;

ScriptController* ScriptController::handle = Q_NULLPTR;

ScriptController* ScriptController::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new ScriptController;
        mutex.unlock();
    }
    return handle;
}


ScriptController::ScriptController()
{
    this->setState(StudioCtrlCode_Remote);
    this->frameCode = ScriptCommandCode_Null;
    this->frameCounter = 0;
    this->execIndex = 0;
}

/**
 * @brief this->StudioController->Server->Client
 * @return QJsonObject
 */
QJsonObject ScriptController::getStatusData()
{
    QJsonObject root;
    root["deviceId"] = DeviceNumber::Device_ScriptController;
    root["state"] = getState();
    root["index"] = getExecIndex();
    root["frameCounter"] = QString::number(getFrameCounter());
    return root;
}

/**
 * @brief Server->Client->setStatusData
 * @param obj
 */
void ScriptController::setStatusData(const QJsonObject &obj)
{
    StudioClient *client = StudioClient::getInstance();
    client->setStudioCtrlState((StudioCtrlCode)obj["state"].toInt());
    this->setExecIndex(obj["index"].toInt());
    this->setState(obj["state"].toInt());
    this->setFrameCounter(obj["frameCounter"].toString().toLongLong());
}

/**
 * @brief Server->Client->设置静态数据
 * @param obj
 */
void ScriptController::setStaticData(const QJsonObject &obj)
{
}

/**
 * @brief 脚本运行索引
 * @param index
 */
void ScriptController::setExecIndex(int index)
{
    if(execIndex != index)
    {
        this->execIndex = index;
        emit indexChanged();
    }
}

/**
 * @brief server指令处理-数据验证
 * @param obj 指令包
 */
void ScriptController::commandProcessing(const QJsonObject &obj)
{
    int code = obj["code"].toInt();
    if(code == ScriptCommandCode_NodeReset && getFrameCode() == ScriptCommandCode_Null)
    {
        int index = obj["index"].toInt();
        QJsonObject data = obj["data"].toObject();
        QJsonObject robot = data[QString::number(Device_Robot)].toObject();
        robot["number"] = index;
        data[QString::number(Device_Robot)] = robot;
        this->nodeResetExec(index,data);
    }
    else if(code == ScriptCommandCode_ScriptExec && getFrameCode() == ScriptCommandCode_Null)
    {
        this->scriptExec(obj["data"].toObject(),obj["runmode"].toInt());
    }
    else
    {
        this->stopExec();
    }
}

/**
 * @brief 时间帧更新
 */
void ScriptController::frameUpdate()
{
    if(getFrameCode() == ScriptCommandCode_NodeReset)
        this->nodeResetProcessing();
    else if(getFrameCode() == ScriptCommandCode_ScriptExecImage)
        this->imgScriptExecProcessing();
    else if(getFrameCode() == ScriptCommandCode_ScriptExecMovie)
        this->movieScriptExecProcessing();
    else if(getFrameCode() == ScriptCommandCode_Stop)
        this->studioStop();
}

/**
 * @brief 节点复位执行
 * @param index 节点索引
 * @param startframe 启动帧
 * @param obj 执行数据
 */
void ScriptController::nodeResetExec(int index,const QJsonObject &nodeData)
{
    this->setFrameCounter(0);
    this->setExecIndex(index);
    this->frameCmdObj = nodeData;
    this->deviceList.clear();
    this->setFrameCode(ScriptCommandCode_NodeReset);
}

/**
 * @brief 脚本执行
 * @param obj 执行数据
 */
void ScriptController::scriptExec(const QJsonObject &scriptData,int runmode)
{
    this->setFrameCounter(0);
    this->execRunmode = runmode;
    this->frameCmdObj = scriptData;
    this->deviceList.clear();
    if(scriptData["CameraType"].toInt() == ScriptShootModeCode_Image)
        this->setFrameCode(ScriptCommandCode_ScriptExecImage);
    else
        this->setFrameCode(ScriptCommandCode_ScriptExecMovie);
}

/**
 * @brief 停止执行
 */
void ScriptController::stopExec()
{
    this->setFrameCounter(0);
    this->setFrameCode(ScriptCommandCode_Stop);
}

/**
 * @brief 设置计数器
 */
void ScriptController::setFrameCounter(quint64 value)
{
    if(frameCounter != value)
    {
        this->frameCounter = value;
        emit frameCounterChanged();
    }
}

/**
 * @brief 设置帧编码
 * @param code
 */
void ScriptController::setFrameCode(ScriptCommandCode code)
{
    if(frameCode != code)
    {
        if(code == ScriptCommandCode_ScriptExecMovie)
        {
            //初始化参数
            this->mFollowFocusMap.clear();
            //连接信号
            connect(JRobot::getInstance(),&JRobot::runNumberChanged,
                    this,&ScriptController::onRobotRunNumberChanged);
        }
        else if(code == ScriptCommandCode_Stop && frameCode == ScriptCommandCode_ScriptExecMovie)
        {
            //断开信号
            disconnect(JRobot::getInstance(),&JRobot::runNumberChanged,
                       this,&ScriptController::onRobotRunNumberChanged);
        }
        this->frameCode = code;
    }
}

/**
 * @brief 节点复位处理
 */
void ScriptController::nodeResetProcessing()
{
    //帧计数器
    this->setFrameCounter((getFrameCounter()+1));
    if(frameCounter == 1)
    {
        this->setState(StudioCtrlCode_NodeReset_Start);
    }

    //指令处理
    if(!frameCmdObj[QString::number(Device_Robot)].isNull())
    {
        this->nodeResetRobotEvent(frameCounter,frameCmdObj[QString::number(Device_Robot)].toObject());
    }
    if(!frameCmdObj[QString::number(Device_Turntable)].isNull())
    {
        this->nodeResetTurnplateEvent(frameCounter,frameCmdObj[QString::number(Device_Turntable)].toObject());
    }
    if(!frameCmdObj[QString::number(Device_FollowFocus)].isNull())
    {
        this->nodeResetFollowFocusEvent(frameCounter,frameCmdObj[QString::number(Device_FollowFocus)].toObject());
    }

    //最快完成时间是10帧-100ms
    if(deviceList.isEmpty() && frameCounter >= 10)
    {
        this->setFrameCode(ScriptCommandCode_Stop);
    }
}

/**
 * @brief 节点复位的机械臂设备事件
 * @param frameNumber
 */
void ScriptController::nodeResetRobotEvent(quint64 frameNumber,const QJsonObject &nodeData)
{
    JRobot *robot = JRobot::getInstance();
    if(frameNumber == 1 && !robot->isArrived(nodeData["target"].toObject(),nodeData["code"].toInt()))
    {
        this->deviceList.append(Device_Robot);
        robot->absPosMovement(nodeData);
    }
    else if(frameNumber > 1 && deviceList.contains(Device_Robot) && robot->isArrived(nodeData["target"].toObject(),nodeData["code"].toInt()))
    {
        this->deviceList.removeOne(Device_Robot);
    }
}

/**
 * @brief 节点复位的转盘设备事件
 * @param frameNumber
 */
void ScriptController::nodeResetTurnplateEvent(quint64 frameNumber,const QJsonObject &nodeData)
{
    JTurnplate *turnplate = JTurnplate::getInstance();
    if(frameNumber == 1 && !turnplate->isArrived(nodeData["target"].toString()))
    {
        this->deviceList.append(Device_Turntable);
    }
    else if(frameNumber > 1 && deviceList.contains(Device_Turntable) && turnplate->isArrived(nodeData["target"].toString()))
    {
        this->deviceList.removeOne(Device_Turntable);
    }
    turnplate->absMove(nodeData["target"].toString().toFloat(),nodeData["Speed"].toInt(),nodeData["Acc"].toInt(),nodeData["Acc"].toInt());

}

/**
 * @brief 节点复位：跟焦器时间
 * @param frameNumber
 * @param nodeData
 */
void ScriptController::nodeResetFollowFocusEvent(quint64 frameNumber,const QJsonObject &nodeData)
{
    if(frameNumber == 1 && !nodeData.isEmpty())
    {
        int focus = nodeData["FocusValue"].isUndefined()?JFollowfocus::getInstance()->getFocus():nodeData["FocusValue"].toInt();
        int zoom = nodeData["ZoomValue"].isUndefined()?JFollowfocus::getInstance()->getZoom():nodeData["ZoomValue"].toInt();
        int iris = nodeData["IrisValue"].isUndefined()?JFollowfocus::getInstance()->getIris():nodeData["IrisValue"].toInt();
        JFollowfocus::getInstance()->allRemote(focus,zoom,iris);
    }
}

/**
 * @brief 静态影像拍摄脚本
 */
void ScriptController::imgScriptExecProcessing()
{
    //帧计数器缓存
    static quint64 frameCounterBuffer = 0;
    //帧计数器
    this->setFrameCounter((getFrameCounter()+1));
    if(frameCounter == 1)
    {
        this->setState(StudioCtrlCode_ScriptExec_Image_Start);
        frameCounterBuffer = frameCounter-1;
    }

    this->setExecIndex(frameCmdObj["CurrentIndex"].toInt());
    QJsonArray nodes = frameCmdObj["Nodes"].toArray();
    if(getExecIndex() >= 0 && getExecIndex() < nodes.count())
    {
        QJsonObject node = nodes.at(getExecIndex()).toObject();
        this->nodeResetRobotEvent(frameCounter-frameCounterBuffer,node[QString::number(Device_Robot)].toObject());
        this->nodeResetTurnplateEvent(frameCounter-frameCounterBuffer,node[QString::number(Device_Turntable)].toObject());
        if(!deviceList.contains(Device_Robot)&&!deviceList.contains(Device_Turntable))
        {
            //运动帧是否完成
            if(execRunmode == ScriptRunModeCode_ShootAndMotion)
            {
                if(!deviceList.contains(Device_ScriptController)&&!deviceList.contains(Device_Camera))
                {
                    this->deviceList.append(Device_ScriptController);
                    frameCounterBuffer = frameCounter;
                }
            }
            //稳定帧50
            if(deviceList.contains(Device_ScriptController))
            {
                if((frameCounter-frameCounterBuffer) >= 50)
                {
                    this->deviceList.removeOne(Device_ScriptController);
                    this->deviceList.append(Device_Camera);
                    frameCounterBuffer = frameCounter;
                }
            }
            //拍摄帧
            if(deviceList.contains(Device_Camera))
            {
                QJsonObject nodeData = node[QString::number(Device_Camera)].toObject();
                double interval = nodeData["ImageInterval"].toDouble();
                int imageNum = nodeData["ImageNum"].toInt();
                //第一帧拍摄
                if((frameCounter-frameCounterBuffer) == 1)
                {
                    JCamera::getInstance()->shooting(nodeData["ShootMode"].toInt());
                }
                //第200帧拍摄完成
                else if((frameCounter-frameCounterBuffer) == 200)
                {
                    imageNum--;
                    nodeData["ImageNum"] = imageNum;
                    node[QString::number(Device_Camera)] = nodeData;
                    nodes[getExecIndex()] = node;
                    frameCmdObj["Nodes"] = nodes;
                }
                //记录间隔时间帧
                if((frameCounter-frameCounterBuffer) >= (200+interval*100))
                {
                    frameCounterBuffer = frameCounter;
                }
                //拍摄完成
                if(imageNum <= 0)
                {
                    this->deviceList.clear();
                }
            }
            //一个节点完成
            if(deviceList.isEmpty())
            {
                this->setExecIndex(execIndex+1);
                frameCmdObj["CurrentIndex"] = getExecIndex();
                frameCounterBuffer = frameCounter;
            }
        }
    }

    //最快完成时间是10帧-100ms
    if(deviceList.isEmpty() && frameCounter >= 10 && getExecIndex() >= nodes.count())
    {
        this->setFrameCode(ScriptCommandCode_Stop);
    }
}

/**
 * @brief 动态影像拍摄脚本
 */
void ScriptController::movieScriptExecProcessing()
{
    //帧计数器
    this->setFrameCounter((getFrameCounter()+1));
    if(getFrameCounter() == 1)
    {
        this->setState(StudioCtrlCode_ScriptExec_Movie_Start);
        if(execRunmode == ScriptRunModeCode_ShootAndMotion)
        {
            JCamera::getInstance()->filmRecording(true);
        }
    }
    //! 机械臂
    JRobot *robot = JRobot::getInstance();

    int recordingFrame = frameCmdObj["RecordingDuration"].toInt()*100;
    int delayFrame = frameCmdObj["MoveDelay"].toInt()*100;
    QJsonArray nodes = frameCmdObj["Nodes"].toArray();
    //运动准备时间
    if((delayFrame+1) == getFrameCounter())
    {
        int count = 0;
        while(!nodes.isEmpty() && count < 5)
        {
            count++;
            QJsonObject node = nodes.first().toObject();
            robot->continueMovement(node[QString::number(Device_Robot)].toObject());
            nodes.removeFirst();
        }
        //启动运行
        robot->continueMovementStart();
        frameCmdObj["Nodes"] = nodes;
    }

    //! 转盘
    QJsonObject turnplateJson = frameCmdObj["Turnplates"].toObject();
    int startTime = turnplateJson["StartTime"].toInt()*100;
    int duration = turnplateJson["Duration"].toInt()*100;
    if(getFrameCounter() >= startTime && getFrameCounter() <= (startTime+duration))
    {
        int orientation = turnplateJson["Ori"].toInt();
        orientation = ((orientation==1)?1:-1);
        int speed = turnplateJson["Speed"].toInt();
        int acc = turnplateJson["Acc"].toInt();
        int dec = turnplateJson["Dec"].toInt();
        JTurnplate::getInstance()->speedMove(orientation,speed,acc,dec);
    }
    else
    {
        JTurnplate::getInstance()->runStop();
    }

    //最快结束时间是10帧-100ms
    if(frameCounter >= 10 && frameCounter >= recordingFrame)
    {
        this->setFrameCode(ScriptCommandCode_Stop);
        if(execRunmode == ScriptRunModeCode_ShootAndMotion)
        {
            JCamera::getInstance()->filmRecording(false);
        }
    }
}

/**
 * @brief 影棚停止
 */
void ScriptController::studioStop()
{
    static int stopCounter = 0;
    //帧计数器
    stopCounter++;
    if(stopCounter == 1)
    {
        JRobot::getInstance()->runStop();
        if(JCamera::getInstance()->getRecordingState()->getValue() != "0")
            JCamera::getInstance()->filmRecording(false);
    }

    JTurnplate::getInstance()->runStop();

    //10帧后停止
    if(stopCounter >= 10)
    {
        this->setFrameCode(ScriptCommandCode_Null);
        this->setState(StudioCtrlCode_Remote);
        stopCounter = 0;
        JFollowfocus::getInstance()->setFocusEnable(true);
        JFollowfocus::getInstance()->setZoomEnable(true);
        JFollowfocus::getInstance()->setIrisEnable(true);
    }
}

/**
 * @brief 机械臂的运行变化改变(发送机械臂连续运动数据)
 */
void ScriptController::onRobotRunNumberChanged()
{
    if(getFrameCode() != ScriptCommandCode_ScriptExecMovie)
        return;

    JRobot *robot = JRobot::getInstance();
    this->setExecIndex(robot->getRunNumber());

    QJsonArray nodes = frameCmdObj["Nodes"].toArray();
    if(!nodes.isEmpty())
    {
        QJsonObject node = nodes.first().toObject();
        robot->continueMovement(node[QString::number(Device_Robot)].toObject());
        nodes.removeFirst();
        frameCmdObj["Nodes"] = nodes;
    }
}
