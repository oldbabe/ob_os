#include "Studio/jturnplate.h"
#include "Studio/studiocontroller.h"
#include "Interface/abstractturnplate.h"
#include <QMutex>
#include <QDebug>

#include "jltmoco.h"
#include "jconfig.h"

using namespace jltmoco;

JTurnplate* JTurnplate::handle = Q_NULLPTR;

JTurnplate* JTurnplate::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JTurnplate;
        mutex.unlock();
    }
    return handle;
}

JTurnplate::JTurnplate()
{
    this->connected = false;
    this->angle = "0";
    this->mPortName.clear();
}

/**
 * @brief 初始化
 */
void JTurnplate::init()
{
    this->mPortName = JConfig::getInstance()->value("JTurnplate/PortName").toString();
    QObject *obj = loadPlugin("Plugins/TurnplateDevice.dll");
    if(obj)
    {
        this->pluginHandle = qobject_cast<AbstractTurnplate *>(obj);
        this->pluginHandle->setup();
        if(!mPortName.isEmpty())
        {
            this->pluginHandle->connect(mPortName);
        }
    }
}

/**
 * @brief 释放
 */
void JTurnplate::release()
{
    if(pluginHandle)
        this->pluginHandle->uninstall();
}

/**
 * @brief 返回状态数据
 * @return QJsonObject
 */
QJsonObject JTurnplate::getStatusData()
{
    QJsonObject root;
    if(pluginHandle){
        root = pluginHandle->getStatusData();
    }
    root["loaded"] = getLoaded();
    root["power"] = getPower();
    root["deviceId"] = DeviceNumber::Device_Turntable;
    root["com"] = mPortName;
    this->setConnected(root["connected"].toBool());
    this->setState(root["state"].toInt());
    this->setAngle(root["angle"].toString("0"));
    root["angle"] = getAngle().isEmpty()?"0":getAngle();
    return root;
}

/**
 * @brief Server->Client->设置静态数据
 * @param obj
 */
void JTurnplate::setStaticData(const QJsonObject &obj)
{
    ;
}

/**
 * @brief Server->Client->setStatusData
 * @param obj
 */
void JTurnplate::setStatusData(const QJsonObject &obj)
{
    this->setConnected(obj["connected"].toBool());
    this->setLoaded(obj["loaded"].toBool());
    this->setState(obj["state"].toInt());
    this->setAngle(obj["angle"].toString());
    this->setPower(obj["power"].toInt());
    this->mPortName = obj["com"].toString();
}

bool JTurnplate::getConnected() const
{
    return this->connected;
}

void JTurnplate::setConnected(bool value)
{
    if(value != connected)
    {
        this->connected = value;
        emit connectedChanged();
    }
}

void JTurnplate::sendData(const QJsonObject &data)
{
    StudioController *studioController = StudioController::getInstance();
    if(studioController->getControllerType() == StudioController::RemoteControllerOnly)
    {
        emit dataChanged(data);
    }
    else
    {
        this->commandProcessing(data);
    }
}


/**
 * @brief 指令处理
 * @param obj
 */
void JTurnplate::commandProcessing(const QJsonObject &obj)
{
    if(obj["code"].toInt() == 10)
    {
        this->setPortName(obj["data"].toString());
    }
    else
    {
        if(pluginHandle)
            pluginHandle->parseUserCommand(obj);
    }
}


bool JTurnplate::isArrived(const QString &target)
{
    if(!getLoaded() || !getConnected())
        return true;

    bool isSendFlag = true;
    if(qAbs(target.toDouble()-getAngle().toDouble()) > 0.5f)
        isSendFlag = false;

    return isSendFlag;
}

void JTurnplate::runStop()
{
    QJsonObject root;
    root["deviceId"] = Device_Turntable;
    root["code"] = TurnplateOperationCode_Stop;
    this->sendData(root);
}

void JTurnplate::absMove(float target,int spped,int acc,int dec)
{
    QJsonObject root;
    root["deviceId"] = Device_Turntable;
    root["code"] = TurnplateOperationCode_PosMode;
    root["angle"] = target;
    root["speed"] = spped;
    root["acc"] = acc;
    root["dec"] = dec;
    this->sendData(root);
}

void JTurnplate::speedMove(int direction,int spped,int acc,int dec)
{
    QJsonObject root;
    root["deviceId"] = Device_Turntable;
    root["code"] = TurnplateOperationCode_SpeedMode;
    root["direction"] = direction;
    root["speed"] = spped;
    root["acc"] = acc;
    root["dec"] = dec;
    this->sendData(root);
}

void JTurnplate::setAngle(const QString &value)
{
    if(value != angle)
    {
        this->angle = value;
        emit angleChanged();
    }
}

void JTurnplate::setPortName(const QString &name)
{
    if(mPortName != name)
    {
        this->mPortName = name;
        emit portNameChanged();

        StudioController *studioController = StudioController::getInstance();
        if(studioController->getControllerType() == StudioController::RemoteControllerOnly)
        {
            QJsonObject cmd;
            cmd["deviceId"] = Device_Turntable;
            cmd["code"] = TurnplateOperationCode_PortName;
            cmd["data"] = name;
            emit dataChanged(cmd);
        }
        else
        {
            if(!pluginHandle)
                return;
            if(getConnected())
            {
                pluginHandle->disconnect();
            }
            if(!mPortName.isEmpty())
            {
                pluginHandle->connect(mPortName);
            }
        }
    }
}
