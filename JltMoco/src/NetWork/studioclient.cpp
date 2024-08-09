#include "NetWork/studioclient.h"
#include <QMutex>
#include <QDebug>

#include "jconfig.h"
#include "Studio/jrobot.h"
#include "Studio/jturnplate.h"

using namespace jltmoco;

StudioClient* StudioClient::handle = Q_NULLPTR;

StudioClient* StudioClient::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new StudioClient;
        mutex.unlock();
    }
    return handle;
}


StudioClient::StudioClient()
{
}

void StudioClient::init()
{
    this->setConnected(QAbstractSocket::UnconnectedState);
    this->setStudioCtrlState(StudioCtrlCode_None);

    QObject::connect(this,&QTcpSocket::stateChanged,
                     this,&StudioClient::onSocketStateChanged);
}

void StudioClient::release()
{
    this->disconnectFromHost();
    if (state() != QAbstractSocket::UnconnectedState)
        this->waitForDisconnected(300);
}


void StudioClient::connectServer(const QString &ip)
{
    if(ip.isEmpty())
        return;

    if(connected == QAbstractSocket::ConnectingState)
        this->disconnectFromHost();
    else if(connected == QAbstractSocket::UnconnectedState)
        this->connectToHost(ip,10000);
}


void StudioClient::disConnectServer()
{
    if(connected != QAbstractSocket::UnconnectedState)
        this->disconnectFromHost();
}

void StudioClient::setConnected(int value)
{
    if(connected != value)
    {
        this->connected = value;
        emit connectedChanged();

        if(connected == 3)
            this->setStudioCtrlState(StudioCtrlCode_Remote);
        else
            this->setStudioCtrlState(StudioCtrlCode_None);
    }
}

int StudioClient::getConnected()
{
    return connected;
}

void StudioClient::setServerAddr(const QString &addr)
{
    JConfig::getInstance()->setServerAddr(addr);
    emit serverAddrChanged();
}

QString StudioClient::getServerAddr()
{
    return JConfig::getInstance()->getServerAddr();
}

void StudioClient::setNumber(int value)
{
    JConfig::getInstance()->setNumber(value);
    emit numberChanged();
}

int StudioClient::getNumber() const
{
    return JConfig::getInstance()->getNumber();
}

void StudioClient::setType(int value)
{
    JConfig::getInstance()->setType(value);
    emit typeChanged();
}

int StudioClient::getType() const
{
    return JConfig::getInstance()->getType();
}


/**
 * @brief 设置影棚控制状态
 * @param code
 */
void StudioClient::setStudioCtrlState(StudioCtrlCode code)
{
    if(studioCtrlState != code)
    {
        this->studioCtrlState = code;
        emit studioCtrlStateChanged();
    }
}

/**
 * @brief 返回影棚控制状态
 * @return
 */
StudioCtrlCode StudioClient::getStudioCtrlState() const
{
    return studioCtrlState;
}

/**
 * @brief StudioClient::isTargetPos
 * @param nodeItem 脚本节点数据
 * @return 是否在目标位置
 */
bool StudioClient::isTargetPos(const QJsonObject &nodeItem)
{
    bool res1 = JRobot::getInstance()->isArrived(nodeItem["1"].toObject()["target"].toObject());
    bool res2 = JTurnplate::getInstance()->isArrived(nodeItem["4"].toObject()["target"].toString());
    return (res1&&res2);
}

/**
 * @brief 节点复位
 * @return =0成功返回
 */
int StudioClient::nodeReset(int index,const QJsonObject &obj)
{
    if(obj.isEmpty() && index < 0)
        return 1;

    QJsonObject root;
    root["deviceId"] = Device_ScriptController;
    root["code"] = ScriptCommandCode_NodeReset;
    root["index"] = index;
    root["data"] = obj;
    if(connected == 3)
        return sendData(root);
    return -1;
}

/**
 * @brief 脚本运行启动
 * @param obj
 * @param mode =0仅运动=1录制且运动
 */
int StudioClient::scriptRun(const QJsonObject &obj,int runmode,int followfocusmode)
{
    if(obj.isEmpty())
        return 1;//指令错误

    QJsonObject root;
    root["deviceId"] = Device_ScriptController;
    root["code"] = ScriptCommandCode_ScriptExec;
    root["data"] = obj;
    root["runmode"] = runmode;
    root["followfocusmode"] = followfocusmode;
    if(connected == 3)
        return sendData(root);
    return -1;
}

/**
 * @brief 脚本运行完成
 */
void StudioClient::studioRunJogStop()
{
    QJsonObject root;
    root["deviceId"] = Device_ScriptController;
    root["code"] = ScriptCommandCode_Stop;
    if(connected == 3)
        sendData(root);
}

/**
 * @brief 连接状态改变
 * @param socketState
 */
void StudioClient::onSocketStateChanged(int socketState)
{
    this->setConnected(socketState);
}

/**
 * @brief 设置遥控速度
 * @param type 挡位
 * @param num 轴编号
 * @param value 值
 */
void StudioClient::setJsonConfig(const QString &key,const QJsonObject &obj)
{
    JConfig::getInstance()->setJsonConfig(key,obj);
}

/**
 * @brief 返回遥控速度
 * @param type 挡位
 * @param num 轴编号
 * @return 值 默认返回 "1"
 */
QJsonObject StudioClient::getJsonConfig(const QString &key) const
{
    return JConfig::getInstance()->getJsonConfig(key);
}

//发送指令数据
void StudioClient::sendRemoteCommand(const QJsonObject &cmd)
{
    if(connected == 3)
    {
        this->sendData(cmd);
    }
}

void StudioClient::onSendData(const QJsonObject &data)
{
    if(connected == 3)
    {
        this->sendData(data);
    }
}
