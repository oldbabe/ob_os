#include "focusplugin.h"
#include <QJsonObject>
#include <QTimer>

namespace jltmoco
{

FocusPlugin::FocusPlugin()
{
    this->mPort = nullptr;
}

/**
* @brief 安装服务
**/
void FocusPlugin::setup()
{
    this->mPort = new QSerialPort;
    this->mPort->setBaudRate(38400);//波特率
    this->mPort->setDataBits(QSerialPort::Data8);//数据位
    this->mPort->setParity(QSerialPort::NoParity);//无检验
    this->mPort->setStopBits(QSerialPort::OneStop);//1位停止位
    this->mPort->setFlowControl(QSerialPort::NoFlowControl);//无硬件控制
}
/**
* @brief 卸载服务
**/
void FocusPlugin::uninstall()
{
    if(mPort)
    {
        this->disconnect();
        this->mPort->deleteLater();
    }
}

/**
* @brief 跟焦器连接
* @param 连接的端口名
**/
bool FocusPlugin::connect(const QString &port)
{
    if(!mPort)
    {
        return false;
    }
    if(mPort->isOpen())
    {
//        qDebug() << "mPort->close()";
        this->mPort->close();
        return false;
    }
    if(port.isEmpty())
    {
//        qDebug() << "mPort->isEmpty()";
        return false;
    }
    this->mPort->setPortName(port);
    return mPort->open(QIODeviceBase::WriteOnly);
}

/**
* @brief 是否连接
**/
bool FocusPlugin::connected() const
{
    if(!mPort)
        return false;

    return mPort->isOpen();
}
/**
* @brief 跟焦器断开
**/
void FocusPlugin::disconnect()
{
    if(mPort->isOpen())
        this->mPort->close();
}

/**
    * @brief 获得设备状态数据
    **/
QJsonObject FocusPlugin::getStatusData()
{
    QJsonObject root;
    root["code"] = 1;//状态数据
    root["connected"] = this->connected();
    //=0初始状态 =1遥控状态 =2校准状态 =3绝对运动状态
    root["state"] = -1;
    return root;
}

/**
* @brief 跟焦器校准
**/
void FocusPlugin::calibrate()
{
    unsigned char dataBuff[8];//数据位

    dataBuff[0] = 0x40;
    dataBuff[1] = 0x30;
    dataBuff[2] = 0x46;
    dataBuff[3] = 0x46;
    dataBuff[4] = 0x37;
    dataBuff[5] = 0x30;
    dataBuff[6] = 0x0D;
    dataBuff[7] = 0x0A;

    this->mPort->write(reinterpret_cast<const char *>(dataBuff), 8);//发送数据
    this->mPort->flush();//让数据立刻从串口发送出去,不要在缓冲区里墨迹
}

void FocusPlugin::setFocus(int value)
{
    this->controlAmotor(value,0x31);
}

void FocusPlugin::setZoom(int value)
{
    this->controlAmotor(value,0x32);
}

void FocusPlugin::setIris(int value)
{
    this->controlAmotor(value,0x33);
}

void FocusPlugin::setValues(int focus, int zoom, int iris)
{
    QByteArray sendBuff;//数据位
    sendBuff.append(0x40);//头
    sendBuff.append(0x31);//位置模式
    //! 电机
    sendBuff.append(0x30);
    sendBuff.append(0x37);
    //! 位置
    sendBuff.append(toValue(focus).toLatin1());
    sendBuff.append(toValue(zoom).toLatin1());
    sendBuff.append(toValue(iris).toLatin1());
    //!BCC校验
    char bcc = sendBuff.at(0);
    for(int i = 1; i < sendBuff.size(); i++)
    {
        bcc ^= sendBuff.at(i);
    }

    QByteArray bccArray;
    bccArray.append(bcc);
    sendBuff.append(QString(bccArray).toLatin1().toHex());

    //换行符
    sendBuff.append(0x0D);
    sendBuff.append(0x0A);

    if(mPort->isOpen())
    {
        this->mPort->write(sendBuff.constData(), qstrlen(sendBuff.constData()));//发送数据
        this->mPort->flush();//让数据立刻从串口发送出去
    }
}

/**
 * @brief 将给定值转换为跟焦器位置信息
 */
QString FocusPlugin::toValue(int value)
{
    QString total = "0000";
    QString target16 = QString::number(value,16);
    target16 = target16.toUpper();//转换为大写
    total = total.replace(4-target16.size(),target16.size(),target16);
    target16.clear();
    target16 = total.right(2) + total.left(2);
    return  target16;
}

/**
* @brief 设置目标值zoom
* @param value 变焦值 0~7200
* @param number =0x31对焦=0x32变焦=0x33光圈焦
**/
void FocusPlugin::controlAmotor(int value,char number)
{
    QByteArray sendBuff;//数据位
    sendBuff.append(0x40);//头
    sendBuff.append(0x31);//位置模式
    //! 电机
    sendBuff.append(0x30);
    sendBuff.append(number);//对焦
    //! 位置
    sendBuff.append(toValue(value).toLatin1());
    //!BCC校验
    char bcc = sendBuff.at(0);
    for(int i = 1; i < sendBuff.size(); i++)
    {
        bcc ^= sendBuff.at(i);
    }
    QByteArray bccArray;
    bccArray.append(bcc);
    sendBuff.append(QString(bccArray).toLatin1().toHex());

    //换行符
    sendBuff.append(0x0D);
    sendBuff.append(0x0A);
    bool res = mPort->isOpen();
    if(res)
    {
        this->mPort->write(sendBuff.constData(), qstrlen(sendBuff.constData()));//发送数据
        this->mPort->flush();//让数据立刻从串口发送出去
    }
}

/**
* @brief 写数据
**/
void FocusPlugin::writeData(const QByteArray &array)
{
    if(mPort->isOpen())
    {
        this->mPort->write(array.constData(), qstrlen(array.constData()));//发送数据
        this->mPort->flush();//让数据立刻从串口发送出去
    }
}

}

