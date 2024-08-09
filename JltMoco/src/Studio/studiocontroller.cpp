#include "Studio/studiocontroller.h"

#include <QDebug>
#include <QMutex>
#include <QTimerEvent>
#include <QHostInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QtSerialPort/QSerialPortInfo>

#include "NetWork/studioclient.h"
#include "NetWork/studioserver.h"

#include "Studio/jfreed.h"
#include "Studio/jcamera.h"
#include "Studio/jrobot.h"
#include "Studio/jfollowfocus.h"
#include "Studio/jturnplate.h"
#include "Studio/scriptcontroller.h"

using namespace jltmoco;

StudioController* StudioController::handle = Q_NULLPTR;

StudioController* StudioController::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new StudioController;
        mutex.unlock();
    }
    return handle;
}

StudioController::StudioController()
{
    this->loopTimerId = 0;
    this->mControllerType = StudioController::LocalControllerOnly;
}

/**
 * @brief 初始化
 */
void StudioController::init()
{
    if(getControllerType() == StudioController::LocalControllerOnly || getControllerType() == StudioController::LocalControllerServer)
    {
        //设备初始化
        JRobot::getInstance()->init();
        JCamera::getInstance()->init();
        JFollowfocus::getInstance()->init();
        JTurnplate::getInstance()->init();
        JFreed::getInstance()->init();

        //启动帧状态监控计时器
        if(loopTimerId == 0)
            this->loopTimerId = startTimer(10,Qt::PreciseTimer);

        //启动服务器
        if(getControllerType() == StudioController::LocalControllerServer)
        {
            StudioServer *server = StudioServer::getInstance();
            connect(this,&StudioController::frameStatusDataChanged,
                    server,&StudioServer::onSendData);
            connect(server,&StudioServer::socketStatusChanged,
                    this,&StudioController::onStudioServerProcessing);
            connect(server,&StudioServer::socketCountChanged,
                    this,&StudioController::onStudioServerSocketChanged);
            connect(JCamera::getInstance(),&JCamera::dataChanged,
                    server,&StudioServer::onSendData);
            connect(JRobot::getInstance(),&JRobot::dataChanged,
                    server,&StudioServer::onSendData);
            connect(ScriptController::getInstance(),&ScriptController::dataChanged,
                    server,&StudioServer::onSendData);

            server->startServer();
        }
    }
    else if(getControllerType() == StudioController::RemoteControllerOnly)
    {
        StudioClient *client = StudioClient::getInstance();
        connect(client,&StudioClient::disconnected,
                this,&StudioController::onStudioClientDisconnected);
        connect(client,&StudioClient::statusChanged,
                this,&StudioController::onStudioClientProcessing);
        connect(JCamera::getInstance(),&JCamera::dataChanged,
                client,&StudioClient::onSendData);
        connect(JFollowfocus::getInstance(),&JFollowfocus::dataChanged,
                client,&StudioClient::onSendData);
        connect(JRobot::getInstance(),&JRobot::dataChanged,
                client,&StudioClient::onSendData);
        connect(JTurnplate::getInstance(),&JTurnplate::dataChanged,
                client,&StudioClient::onSendData);
        client->init();
    }
}

/**
 * @brief 释放
 */
void StudioController::release()
{
    if(getControllerType() == StudioController::LocalControllerOnly || getControllerType() == StudioController::LocalControllerServer)
    {
        //关闭帧计时器
        if(loopTimerId != 0){
            this->killTimer(loopTimerId);
            this->loopTimerId = 0;
        }
        //设备释放
        JRobot::getInstance()->release();
        JCamera::getInstance()->release();
        JFollowfocus::getInstance()->release();
        JTurnplate::getInstance()->release();
        JFreed::getInstance()->release();
        //关闭服务器
        if(getControllerType() == StudioController::LocalControllerServer){
            StudioServer::getInstance()->stopServer();
        }
    }
    else if(getControllerType() == StudioController::RemoteControllerOnly){
        StudioClient::getInstance()->release();
    }
}

/**
* @brief 可连接端口号列表
**/
QStringList StudioController::ports()
{
    QStringList porNames;
    porNames.append("");
    QList<QSerialPortInfo> list  = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo & info, list)
    {
        porNames.append(info.portName());
    }
    return porNames;
}

/**
 * @brief 返回本地的IP地址
 * @return
 */
QString StudioController::localHostName()
{
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }

    return "";
}

void StudioController::sendCommandData(const QJsonObject &data)
{
    StudioController *controller = StudioController::getInstance();
    if(controller->getControllerType() == StudioController::RemoteControllerOnly)
    {
        StudioClient::getInstance()->sendRemoteCommand(data);
    }
    else if(controller->getControllerType() == StudioController::LocalControllerOnly ||
             controller->getControllerType() == StudioController::LocalControllerServer)
    {
        ;
    }
}

/**
 * @brief 遥控控制器使能/禁用
 * @param enable=true启动=false禁用(默认false)
 */
void StudioController::setControllerType(ControllerType type)
{
    if(mControllerType != type)
    {
        this->mControllerType = type;
        emit controllerTypeChanged();
    }
}

/**
 * @brief 影棚客户端断开时的设备处理
 */
void StudioController::onStudioClientDisconnected()
{
    JRobot::getInstance()->setLoaded(false);
    JRobot::getInstance()->setConnected(false);
    JCamera::getInstance()->setLoaded(false);
    JCamera::getInstance()->setConnected(false);
    JFollowfocus::getInstance()->setLoaded(false);
    JFollowfocus::getInstance()->setConnected(false);
    JTurnplate::getInstance()->setLoaded(false);
}

/**
 * @brief 服务端 -> 客户端数据处理
 * @param obj 数据内容
 */
void StudioController::onStudioClientProcessing(const QJsonObject &obj)
{
    int code = obj["code"].toInt();
    //影棚时间轴监控数据
    if(code == 0x1000)
    {
        QJsonArray devs = obj["data"].toArray();
        for(int i = 0; i < devs.count(); i++)
        {
            QJsonObject data = devs[i].toObject();
            int deviceId = data["deviceId"].toInt();
            switch (deviceId)
            {
            case DeviceNumber::Device_Robot:JRobot::getInstance()->setStatusData(data);break;
            case DeviceNumber::Device_Camera:JCamera::getInstance()->setStatusData(data);break;
            case DeviceNumber::Device_FollowFocus:JFollowfocus::getInstance()->setStatusData(data);break;
            case DeviceNumber::Device_Turntable:JTurnplate::getInstance()->setStatusData(data);break;
            case DeviceNumber::Device_ScriptController:ScriptController::getInstance()->setStatusData(data);break;
            default:break;
            }
        }
    }
    //影棚动态回调数据
    else if(code == 0x2000)
    {
        QJsonObject data = obj["data"].toObject();
        int deviceId = data["deviceId"].toInt();
        switch (deviceId)
        {
        case DeviceNumber::Device_Robot:JRobot::getInstance()->setStaticData(data);break;
        case DeviceNumber::Device_Camera:JCamera::getInstance()->setStatusData(data);break;
        case DeviceNumber::Device_FollowFocus:JFollowfocus::getInstance()->setStatusData(data);break;
        case DeviceNumber::Device_Turntable:JTurnplate::getInstance()->setStatusData(data);break;
        case DeviceNumber::Device_ScriptController:ScriptController::getInstance()->setStaticData(data);break;
        default:break;
        }
    }
    //影棚静态数据
    else if(code == 0x2001)
    {
        QJsonArray datas = obj["data"].toArray();
        for(int i = 0; i < datas.count(); i++)
        {
            QJsonObject item = datas.at(i).toObject();
            int deviceId = item["deviceId"].toInt();
            switch (deviceId)
            {
            case DeviceNumber::Device_Robot:JRobot::getInstance()->setStaticData(item);break;
            case DeviceNumber::Device_Camera:JCamera::getInstance()->setStaticData(item);break;
            case DeviceNumber::Device_FollowFocus:JFollowfocus::getInstance()->setStaticData(item);break;
            case DeviceNumber::Device_Turntable:JTurnplate::getInstance()->setStaticData(item);break;
            case DeviceNumber::Device_ScriptController:ScriptController::getInstance()->setStaticData(item);break;
            default:break;
            }
        }
    }
}

/**
 * @brief 客户端 -> 服务端数据处理
 * @param obj 数据内容
 */
void StudioController::onStudioServerProcessing(const QJsonObject &obj)
{
    int deviceId = obj["deviceId"].toInt();
    switch (deviceId)
    {
    case DeviceNumber::Device_Robot:
        JRobot::getInstance()->commandProcessing(obj);
        break;
    case DeviceNumber::Device_Camera:
        JCamera::getInstance()->commandProcessing(obj);
        break;
    case DeviceNumber::Device_FollowFocus:
        JFollowfocus::getInstance()->commandProcessing(obj);
        break;
    case DeviceNumber::Device_Turntable:
        JTurnplate::getInstance()->commandProcessing(obj);
        break;
    case DeviceNumber::Device_ScriptController:
        ScriptController::getInstance()->commandProcessing(obj);
        break;
    default:break;
    }
}

/**
 * @brief 服务端用户改变(新增)
 * @param index
 */
void StudioController::onStudioServerSocketChanged(int index)
{
    JCamera::getInstance()->reloadProperties();

    {
        QJsonObject root;
        root["code"] = 0x2000;

        QJsonObject data;
        data["deviceId"] = 2;
        data["code"] = 2;
        data["cameraName"] = JCamera::getInstance()->getCameraName();
        root["data"] = data;
        emit frameStatusDataChanged(root,index);
    }
    {
        QJsonObject root;
        root["code"] = 0x2000;

        QJsonObject data;
        data["deviceId"] = 2;
        data["code"] = 3;
        data["result"] = true;
        data["downloadDir"] = JCamera::getInstance()->getDownloadDir();
        root["data"] = data;
        emit frameStatusDataChanged(root,index);
    }

    {
        //静态数据
        QJsonObject root;
        root["code"] = 0x2001;
        QJsonArray datas;
        datas.append(JRobot::getInstance()->getStaticData());
        root["data"] = datas;
        emit frameStatusDataChanged(root,index);
    }
}

/**
 * @brief 计时器
 */
void StudioController::timerEvent(QTimerEvent *event)
{
    if(event->timerId() != loopTimerId)
        return;

    QJsonObject root;
    root["code"] = 0x1000;
    QJsonArray devs;
    devs.append(JRobot::getInstance()->getStatusData());
    devs.append(JCamera::getInstance()->getStatusData());
    devs.append(JFollowfocus::getInstance()->getStatusData());
    devs.append(JTurnplate::getInstance()->getStatusData());
    devs.append(ScriptController::getInstance()->getStatusData());
    root["data"] = devs;
    emit frameStatusDataChanged(root);
    //脚本控制帧刷新
    ScriptController::getInstance()->frameUpdate();
}
