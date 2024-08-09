#include "kukaplugin.h"
#include <QDebug>
using namespace jltmoco;

KukaPlugin::KukaPlugin()
{
    this->mRobotSocket = NULL;
}


void KukaPlugin::registerFunc(std::function<void (const QJsonObject &)> func)
{
    this->mFunc = func;
}

/**
* @brief 安装服务
**/
void KukaPlugin::setup()
{
    this->mRobotSocket = new RobotSocket;
}

/**
* @brief 卸载服务
**/
void KukaPlugin::uninstall()
{
    this->mRobotSocket->disconnectFromHost();
    if(mRobotSocket->state() != QAbstractSocket::UnconnectedState)
        this->mRobotSocket->waitForDisconnected(1000);
    this->mRobotSocket->deleteLater();
}

/**
* @brief 连接
**/
bool KukaPlugin::connect(const QString &robotIp,const QString &railIp)
{
    this->mRobotSocket->connectToHost(robotIp,54600);
    return mRobotSocket->waitForConnected(200);
}

/**
* @brief 连接状态
**/
bool KukaPlugin::connected() const
{
    if(!mRobotSocket)
        return false;

    return this->mRobotSocket->state() == QAbstractSocket::ConnectedState;
}

/**
* @brief 断开
**/
void KukaPlugin::disconnect()
{
    this->mRobotSocket->disconnectFromHost();
    if(mRobotSocket->state() != QAbstractSocket::UnconnectedState)
        this->mRobotSocket->waitForDisconnected(1000);
}

/**
* @brief 保存用户指令 - 保存指令数据-在机械臂反馈器中解析
* @param code 指令编码
* @param dataJson 指令内容
**/
void KukaPlugin::parseUserCommand(const QJsonObject &obj)
{
    this->mRobotSocket->moveControl(obj);
}

/**
* @brief 返回机械臂状态数据
**/
QJsonObject KukaPlugin::getStatusData()
{
    QJsonObject root;
    root["code"] = 1;
    root["state"] = mRobotSocket->mRunMode;
    root["connected"] = mRobotSocket->state() == QAbstractSocket::ConnectedState ? true : false;
    root["railConnected"] = mRobotSocket->state() == QAbstractSocket::ConnectedState ? true : false;
    root["runNumber"] = mRobotSocket->mRunNumber;
    root["data"] = mRobotSocket->mPosition;
    root["tool"] = mRobotSocket->mTool;
    root["base"] = mRobotSocket->mWorld;
    root["load"] = mRobotSocket->mLoad;
    return root;
}

QJsonObject KukaPlugin::getStaticData()
{
    QJsonObject root;
    root["model"] = mRobotSocket->mModel;
    root["caEnable"] = true;
    return root;
}
