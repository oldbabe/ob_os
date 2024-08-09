#include "NetWork/studioserver.h"

#include <QDebug>
#include <QMutex>
#include <QTcpSocket>

using namespace jltmoco;

StudioServer* StudioServer::handle = Q_NULLPTR;

StudioServer* StudioServer::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new StudioServer;
        mutex.unlock();
    }
    return handle;
}

StudioServer::StudioServer()
{
}

/**
 * @brief 安装服务
 */
void StudioServer::init()
{
    this->startServer();
}

/**
 * @brief 卸载服务
 */
void StudioServer::release()
{
    this->stopServer();
}

void StudioServer::startServer()
{
    this->socketList.clear();
    this->listen(QHostAddress::Any,10000);
}

void StudioServer::stopServer()
{
    this->close();
    this->deleteLater();
}

/**
 * @brief 向所有用户反馈数据
 * @param obj 发送的内容
 * @param index 发送的socket索引(默认-1向全部socket发送)
 */
void StudioServer::onSendData(const QJsonObject &obj,int index)
{
    if(!isRunning())
        return;

    if(socketList.count() > 0)
    {
        if(index == -1)
        {
            for(int i = 0; i < socketList.count(); i++)
                socketList[i]->sendData(obj);
        }
        else
        {
            if(index < socketList.count()){
                socketList[index]->sendData(obj);
            }
        }
    }
}

/**
 * @brief 新连接
 * @param socketDescriptor
 */
void StudioServer::incomingConnection(qintptr socketDescriptor)
{
    StudioSocket *socket = new StudioSocket;
    socket->setSocketType(StudioSocket::SocketType_Server);
    socket->setSocketDescriptor(socketDescriptor);
    //!添加到队列
    this->socketList.append(socket);
    //!断开连接时销毁
    connect(socket,&StudioSocket::disconnected,socket,&StudioSocket::deleteLater);
    connect(socket,&StudioSocket::statusChanged,this,&StudioServer::socketStatusChanged);
    //!销毁后移出队列
    connect(socket,&StudioSocket::destroyed,this,[&](QObject *obj){
        for(int i = 0; i < socketList.size(); i++)
        {
            disconnect(socketList[i],&StudioSocket::statusChanged,this,&StudioServer::socketStatusChanged);
            if(obj == socketList[i])
                socketList.removeAt(i);
        }
    });
    //!更新回调数据
    emit socketCountChanged(socketList.indexOf(socket));
}

