#include "NetWork/studiosocket.h"

#include <QJsonObject>
#include <QJsonDocument>

using namespace jltmoco;

StudioSocket::StudioSocket(QObject *parent) :
    QTcpSocket(parent)
{
    this->recvBuffer.clear();
    this->setSocketType(SocketType_Client);
    connect(this,&QTcpSocket::readyRead,this,&StudioSocket::onReadyRead);
}

/**
 * @brief 数据发送
 */
qint64 StudioSocket::sendData(const QJsonObject &obj)
{
    QJsonDocument doc(obj);
    QByteArray sendByte = doc.toJson();
    sendByte.insert(0,'#');
    sendByte.append('$');

    return write(sendByte,sendByte.length());
}

/**
 * @brief 设置socket类型
 * @param type
 */
void StudioSocket::setSocketType(SocketType type)
{
    this->socketType = type;
}

/**
 * @brief 返回socket类型
 * @return SocketType
 *
 */
StudioSocket::SocketType StudioSocket::getSocketType()
{
    return this->socketType;
}

/**
 * @brief 数据解析
 */
void StudioSocket::onReadyRead()
{
    //读数据
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    //socket 缓存中无数据，则返回.
    if(socket->bytesAvailable() <= 0)
        return;

    //全部读入，会产生半包、粘包问题
    QByteArray buffer = socket->readAll();
    this->recvBuffer.append(buffer);

    //数据解析
    this->dataParse();
}

/**
 * @brief 递归处理数据缓存
 * @param dataByte
 */
void StudioSocket::dataParse()
{
    int headIndex = -1,lastIndex = -1;
    for(int i = 0; i < recvBuffer.length(); i++)
    {
        //查找头'#'
        if(recvBuffer.at(i) == '#')
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
            //接收的数据改变
            emit statusChanged(QJsonDocument::fromJson(recvBuffer.mid(headIndex+1,lastIndex-1)).object());
            recvBuffer.remove(0,lastIndex+1);
        }
        //粘包,递归处理
        if(!recvBuffer.isEmpty())
        {
            this->dataParse();
        }
    }
    //数据出错
    else if(headIndex == -1 && lastIndex != -1)
    {
        recvBuffer.remove(0,lastIndex+1);
    }
}
