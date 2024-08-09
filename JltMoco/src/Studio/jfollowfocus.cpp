#include "Studio/jfollowfocus.h"
#include "Studio/studiocontroller.h"
#include "Interface/abstractfollowfocus.h"
#include <QMutex>
#include <QDebug>

#include "jltmoco.h"
#include "jconfig.h"

using namespace jltmoco;

JFollowfocus* JFollowfocus::handle = Q_NULLPTR;

JFollowfocus* JFollowfocus::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JFollowfocus;
        mutex.unlock();
    }
    return handle;
}

JFollowfocus::JFollowfocus()
{
    this->pluginHandle = nullptr;
    this->setConnected(false);
    this->mFocusEnable = true;
    this->mZoomEnable = true;
    this->mIrisEnable = true;
    this->mFocusValue = 3600;
    this->mZoomValue = 3600;
    this->mIrisValue = 3600;
}

/**
 * @brief 初始化
 */
void JFollowfocus::init()
{
    this->mPortName = JConfig::getInstance()->value("JFollowfocus/PortName").toString();
    QObject *obj = loadPlugin("Plugins/FocusDevice.dll");
    if(obj)
    {
        this->pluginHandle = qobject_cast<AbstractFllowFocus *>(obj);
        this->pluginHandle->setup();
        if(pluginHandle->connect(getPortName())){
            this->pluginHandle->calibrate();
        }
    }
}

/**
 * @brief 释放
 */
void JFollowfocus::release()
{
    if(pluginHandle)
        pluginHandle->uninstall();
}

/**
 * @brief 返回状态数据
 * @return QJsonObject
 */
QJsonObject JFollowfocus::getStatusData()
{
    QJsonObject root;
    if(pluginHandle){
        root = pluginHandle->getStatusData();
        this->setState(root["state"].toInt());
        this->setConnected(root["connected"].toBool());
    }
    root["deviceId"] = DeviceNumber::Device_FollowFocus;
    root["power"] = getPower();
    root["loaded"] = getLoaded();
    root["com"] = getPortName();
    root["focus"] = getFocus();
    root["zoom"] = getZoom();
    root["iris"] = getIris();
    return root;
}

/**
 * @brief Server->Client->setStatusData
 * @param obj
 */
void JFollowfocus::setStatusData(const QJsonObject &obj)
{
    this->setConnected(obj["connected"].toBool());
    this->setState(obj["state"].toInt());
    this->setLoaded(obj["loaded"].toBool());
    this->setPower(obj["power"].toInt());
    this->mPortName = obj["com"].toString();
    if(getConnected())
    {
        this->updateFocus(obj["focus"].toInt());
        this->updateZoom(obj["zoom"].toInt());
        this->updateIris(obj["iris"].toInt());
    }
}
/**
 * @brief Server->Client->设置静态数据
 * @param obj
 */
void JFollowfocus::setStaticData(const QJsonObject &obj)
{
    ;
}

/**
 * @brief 指令处理
 * @param obj
 */
void JFollowfocus::commandProcessing(const QJsonObject &obj)
{
    switch (obj["code"].toInt())
    {
    case 1:
    {
        this->calibrateDevice();
        break;
    }
    case 2:
    {
        this->setFocus(obj["data"].toInt());
        break;
    }
    case 3:
    {
        this->setZoom(obj["data"].toInt());
        break;
    }
    case 4:
    {
        QJsonObject data = obj["data"].toObject();
        this->setFocus(data["focus"].toInt());
        this->setZoom(data["zoom"].toInt());
        this->setIris(data["iris"].toInt());
        break;
    }
    case 5:
    {
        this->disconnectDevice();
        break;
    }
    case 6:
    {
        this->setPortName(obj["data"].toString());
        break;
    }
    case 7:
    {
        this->setIris(obj["data"].toInt());
        break;
    }
    default:
        break;
    }
}

void JFollowfocus::setPortName(const QString &name)
{
    if(name != mPortName)
    {
        this->mPortName = name;
        emit portNameChanged();
        JConfig::getInstance()->setValue("JFollowfocus/PortName",name);

        if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
        {
            QJsonObject cmd;
            cmd["deviceId"] = DeviceNumber::Device_FollowFocus;
            cmd["code"] = 6;
            cmd["data"] = name;
            emit dataChanged(cmd);
        }
        else
        {
            if(getConnected())
            {
                this->disconnectDevice();
            }
            this->connectDevice();
        }
    }
}

QString JFollowfocus::getPortName() const
{
    return mPortName;
}

void JFollowfocus::connectDevice()
{
    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_Connect);
    }
    else
    {
        if(getLoaded() && pluginHandle)
        {
            pluginHandle->connect(getPortName());
        }
    }
}

void JFollowfocus::disconnectDevice()
{
    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_Disonnect);
    }
    else
    {
        if(getLoaded() && pluginHandle)
        {
            this->pluginHandle->disconnect();
        }
    }
}

void JFollowfocus::calibrateDevice()
{
    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_Init);
    }
    else
    {
        if(getLoaded() && pluginHandle)
        {
            this->pluginHandle->calibrate();
        }
    }
}

void JFollowfocus::remoteValues(int f,int z,int i)
{
    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        if(getFocusEnable())
            this->sendFocus(f);
        if(getZoomEnable())
            this->sendZoom(z);
        if(getIrisEnable())
            this->sendIris(i);
    }
    else
    {
        this->allRemote(f,z,i);
    }
}

void JFollowfocus::allRemote(int f,int z,int i)
{
    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        QJsonObject root;
        root["deviceId"] = DeviceNumber::Device_FollowFocus;
        root["code"] = 4;
        QJsonObject data;
        data["focus"] = f;
        data["zoom"] = z;
        data["iris"] = i;
        root["data"] = data;
        emit dataChanged(root);
    }
    else
    {
        if(pluginHandle)
        {
            this->pluginHandle->setValues(f,z,i);
            this->updateFocus(f);
            this->updateZoom(z);
            this->updateIris(i);
        }
    }
}

void JFollowfocus::setFocus(int value)
{
    if(!getFocusEnable())
        return;

    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_FocusRemote,value);
    }
    else
    {
        if(pluginHandle)
        {
            this->pluginHandle->setFocus(value);
            this->updateFocus(value);
        }
    }
}

void JFollowfocus::setZoom(int value)
{
    if(!getZoomEnable())
        return;

    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_ZoomRemote,value);
    }
    else
    {
        if(pluginHandle)
        {
            this->pluginHandle->setZoom(value);
            this->updateZoom(value);
        }
    }
}

void JFollowfocus::setIris(int value)
{
    if(!getIrisEnable())
        return;

    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_IrisRemote,value);
    }
    else
    {
        if(pluginHandle)
        {
            this->pluginHandle->setIris(value);
            this->updateIris(value);
        }
    }
}

void JFollowfocus::sendFocus(int value)
{
    this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_FocusRemote,value);
}

void JFollowfocus::sendZoom(int value)
{
    this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_ZoomRemote,value);
}

void JFollowfocus::sendIris(int value)
{
    this->sendRemoteValue(FollowfocusCommand::FollowfocusCommand_IrisRemote,value);
}

void JFollowfocus::updateFocus(int value)
{
    if(mFocusValue != value)
    {
        this->mFocusValue = value;
        emit focusChanged();
    }
}

void JFollowfocus::updateZoom(int value)
{
    if(mZoomValue != value)
    {
        this->mZoomValue = value;
        emit zoomChanged();
    }
}

void JFollowfocus::updateIris(int value)
{
    if(mIrisValue != value)
    {
        this->mIrisValue = value;
        emit irisChanged();
    }
}

void JFollowfocus::setFocusEnable(bool value)
{
    // if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    // {
    //     this->sendValueEnable(FollowfocusCommand::FollowfocusCommand_FocusEnable,value);
    // }
    // else
    // {
        this->updateFocusEnable(value);
    // }
}

void JFollowfocus::setZoomEnable(bool value)
{
    // if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    // {
    //     this->sendValueEnable(FollowfocusCommand::FollowfocusCommand_ZoomEnable,value);
    // }
    // else
    // {
        this->updateZoomEnable(value);
    // }
}

void JFollowfocus::setIrisEnable(bool value)
{
    // if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    // {
    //     this->sendValueEnable(FollowfocusCommand::FollowfocusCommand_IrisEnable,value);
    // }
    // else
    // {
        this->updateIrisEnable(value);
    // }
}

void JFollowfocus::updateFocusEnable(bool value)
{
    if(mFocusEnable != value)
    {
        this->mFocusEnable = value;
        emit focusEnableChanged();
    }
}

void JFollowfocus::updateZoomEnable(bool value)
{
    if(mZoomEnable != value)
    {
        this->mZoomEnable = value;
        emit zoomEnableChanged();
    }
}

void JFollowfocus::updateIrisEnable(bool value)
{
    if(mIrisEnable != value)
    {
        this->mIrisEnable = value;
        emit irisEnableChanged();
    }
}

void JFollowfocus::setConnected(bool value)
{
    if(mConnected != value)
    {
        this->mConnected = value;
        emit connectedChanged();
    }
}

void JFollowfocus::sendRemoteValue(int code,int value)
{
    QJsonObject data;
    data["deviceId"] = DeviceNumber::Device_FollowFocus;
    data["code"] = code;
    data["data"] = value;
    emit dataChanged(data);
}

void JFollowfocus::sendValueEnable(int code,bool enable)
{
    QJsonObject data;
    data["deviceId"] = DeviceNumber::Device_FollowFocus;
    data["code"] = code;
    data["data"] = enable;
    emit dataChanged(data);
}
