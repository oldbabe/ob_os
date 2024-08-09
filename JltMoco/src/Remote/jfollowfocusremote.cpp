#include "Remote/jfollowfocusremote.h"
#include "jconfig.h"

#include <QMutex>
#include <QDebug>
#include <QTimerEvent>
#include "Studio/jfollowfocus.h"

using namespace jltmoco;

JFollowfocusRemote* JFollowfocusRemote::handle = Q_NULLPTR;

JFollowfocusRemote* JFollowfocusRemote::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JFollowfocusRemote;
        mutex.unlock();
    }
    return handle;
}

JFollowfocusRemote::JFollowfocusRemote()
{
    this->setFocus(3600);
    this->setZoom(3600);
    this->setIris(3600);
    this->mPort = NULL;
}

void JFollowfocusRemote::setup()
{
    this->mPortName = JConfig::getInstance()->value("JFollowfocusRemote/PortName").toString();
    this->mPort = new QSerialPort;
    this->mPort->setBaudRate(38400);//波特率
    this->mPort->setDataBits(QSerialPort::Data8);//数据位
    this->mPort->setParity(QSerialPort::NoParity);//无检验
    this->mPort->setStopBits(QSerialPort::OneStop);//1位停止位
    this->mPort->setFlowControl(QSerialPort::NoFlowControl);//无硬件控制
    this->mPort->setPortName(mPortName);//设置端口名
    connect(mPort,&QSerialPort::readyRead,
            this,&JFollowfocusRemote::onReadyRead);
    //初始化连接
    if(!mPortName.isEmpty())
    {
        if(mPort->open(QIODeviceBase::ReadOnly))
        {
            emit connectedChanged();
        }
    }
}

void JFollowfocusRemote::uninstall()
{
    if(mPort->isOpen())
    {
        this->mPort->close();
    }
    if(mPort)
    {
        this->mPort->deleteLater();
        this->mPort = nullptr;
    }
}


bool JFollowfocusRemote::getConnected() const
{
    if(mPort)
        return mPort->isOpen();

    return false;
}

void JFollowfocusRemote::onReadyRead()
{
    //socket 缓存中无数据，则返回.
    if(mPort->bytesAvailable() <= 0)
        return;

    this->dataBuffer.append(mPort->readAll());
    this->parseDataBuffer();
}

void JFollowfocusRemote::parseDataBuffer()
{
    int headIndex = dataBuffer.indexOf('@');
    int endIndex = dataBuffer.indexOf('\n');
    if(headIndex != -1 && endIndex != -1)
    {
        if(endIndex > headIndex)
        {
            QByteArray datas = dataBuffer.mid(headIndex,endIndex-1);
            this->dataBuffer.remove(0,endIndex+1);

            //自动校准指令
            if(datas == "@0FF70")
            {
                JFollowfocus::getInstance()->calibrateDevice();
            }
            //点击运行到指定位置
            else if(datas[1] == 0x031)
            {
                this->parsePos(datas);
            }

            this->parseDataBuffer();
        }
        else
        {
            this->dataBuffer.remove(0,headIndex+1);
        }
    }
}

void JFollowfocusRemote::setPortName(const QString &name)
{
    if(mPortName != name)
    {
        this->mPortName = name;
        this->mPort->setPortName(name);
        JConfig::getInstance()->setValue("JFollowfocusRemote/PortName",mPortName);

        if(mPort->isOpen())
        {
            this->mPort->close();
            emit connectedChanged();
        }

        if(!mPortName.isEmpty())
        {
            if(mPort->open(QIODeviceBase::ReadOnly))
            {
                emit connectedChanged();
            }
        }
    }
}

void JFollowfocusRemote::setFocus(int value)
{
    if(mFocus != value)
    {
        this->mFocus = value;
        emit focusChanged();
    }
}

void JFollowfocusRemote::setZoom(int value)
{
    if(mZoom != value)
    {
        this->mZoom = value;
        emit focusChanged();
    }
}

void JFollowfocusRemote::setIris(int value)
{
    if(mIris != value)
    {
        this->mIris = value;
        emit irisChanged();
    }
}

/**
 * @brief 运动指令解析
 * @param array
 */
void JFollowfocusRemote::parsePos(const QByteArray &array)
{
    int f = mFocus,z = mZoom,i = mIris;
    bool result = false,sendEnable = true;
    QByteArray pos = array.mid(4,array.size()-6);
    if(array[2] == 0x30 && array[3] == 0x31)
    {
        f = QByteArray(pos.right(2)+pos.left(2)).toInt(&result,16);
    }
    else if(array[2] == 0x30 && array[3] == 0x32)
    {
        z = QByteArray(pos.right(2)+pos.left(2)).toInt(&result,16);
    }
    else if(array[2] == 0x30 && array[3] == 0x34)
    {
        i = QByteArray(pos.right(2)+pos.left(2)).toInt(&result,16);
    }
    else if(array[2] == 0x30 && array[3] == 0x33)
    {
        QByteArray focusArray = pos.left(4);
        QByteArray zoomArray = pos.right(4);
        f = QByteArray(focusArray.right(2)+focusArray.left(2)).toInt(&result,16);
        z = QByteArray(zoomArray.right(2)+zoomArray.left(2)).toInt(&result,16);
    }
    else if(array[2] == 0x30 && array[3] == 0x35)
    {
        QByteArray focusArray = pos.left(4);
        QByteArray zoomArray = pos.right(4);
        f = QByteArray(focusArray.right(2)+focusArray.left(2)).toInt(&result,16);
        i = QByteArray(zoomArray.right(2)+zoomArray.left(2)).toInt(&result,16);
    }
    else if(array[2] == 0x30 && array[3] == 0x36)
    {
        QByteArray focusArray = pos.left(4);
        QByteArray zoomArray = pos.right(4);
        z = QByteArray(focusArray.right(2)+focusArray.left(2)).toInt(&result,16);
        i = QByteArray(zoomArray.right(2)+zoomArray.left(2)).toInt(&result,16);
    }
    else if(array[2] == 0x30 && array[3] == 0x37)
    {
        QByteArray focusArray = pos.left(4);
        QByteArray zoomArray = pos.mid(4,4);
        QByteArray irisArray = pos.right(4);
        f = QByteArray(focusArray.right(2)+focusArray.left(2)).toInt(&result,16);
        z = QByteArray(zoomArray.right(2)+zoomArray.left(2)).toInt(&result,16);
        i = QByteArray(irisArray.right(2)+irisArray.left(2)).toInt(&result,16);
    }
    else
    {
        sendEnable = false;
    }
    if(sendEnable)
    {
        this->setFocus(f);
        this->setZoom(z);
        this->setIris(i);
        JFollowfocus::getInstance()->remoteValues(f,z,i);
    }
}
