#include "Studio/jfreed.h"
#include "Studio/jrobot.h"
#include "Studio/jfollowfocus.h"
#include "jconfig.h"

#include <QMutex>
#include <QTimerEvent>


using namespace jltmoco;

JFreed* JFreed::handle = Q_NULLPTR;

JFreed* JFreed::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JFreed;
        mutex.unlock();
    }
    return handle;
}

JFreed::JFreed()
{
    this->freedTimerId = 0;
    this->mUdpSocket = new QUdpSocket;
}

/**
 * @brief 安装服务
 */
void JFreed::init()
{
    JConfig *config = JConfig::getInstance();

    this->setAutoFlag(config->value("JFreed/AutoFlag").toBool(),false);

    this->setIpAddress(config->value("JFreed/UDP_IPV4").toString(),false);
    this->setPort(config->value("JFreed/UDP_Port").toInt(),false);
    this->setFrame(config->value("JFreed/UDP_Frame").toInt(),false);
    this->setZoomDeleyFrame(config->value("JFreed/ZoomDeleyFrame").toInt(),false);
    this->setFocusDeleyFrame(config->value("JFreed/FocusDeleyFrame").toInt(),false);

    this->focusMaxValue = config->value("JFreed/focusMaxValue").toFloat();
    this->focusMinValue = config->value("JFreed/focusMinValue").toFloat();
    this->zoomMaxValue = config->value("JFreed/zoomMaxValue").toFloat();
    this->zoomMinValue = config->value("JFreed/zoomMinValue").toFloat();

    QList<QVariant> var = config->value("JFreed/CameraRotate").toList();
    if(var.isEmpty())
        this->setCameraRotate(0,0,0);//默认旋转0度
    else
        this->setCameraRotate(var[0].toFloat(),var[1].toFloat(),var[2].toFloat(),false);

    var = config->value("JFreed/CameraTransform").toList();
    if(var.isEmpty())
        this->setCameraTransform(3,4,2);//默认A=>-A B=>-B C=>C
    else
        this->setCameraTransform(var[0].toInt(),var[1].toInt(),var[2].toInt(),false);

    var = config->value("JFreed/CoordinateOffset").toList();
    if(var.isEmpty())
        this->setCoordinateOffset(0,0,0);//默认偏移为0mm
    else
        this->setCoordinateOffset(var[0].toFloat(),var[1].toFloat(),var[2].toFloat(),false);

    var = config->value("JFreed/CoordinateUnits").toList();
    if(var.isEmpty())
        this->setCoordinateUnity(10,10,10);//默认单位cm
    else
        this->setCoordinateUnity(var[0].toFloat(),var[1].toFloat(),var[2].toFloat(),false);

    var = config->value("JFreed/CoordinateTransform").toList();
    if(var.isEmpty())
        this->setCoordinateTransform(4,0,2);//默认X=>Y Y=>X Z=>Z
    else
        this->setCoordinateTransform(var[0].toInt(),var[1].toInt(),var[2].toInt(),false);

    if(focusMaxValue <= 0)
        this->setFocusMaxValue(7200);

    if(zoomMaxValue <= 0)
        this->setZoomMaxValue(7200);

    for(int i = 0; i < 29; i++)
        this->freedBuffer.append(0x30);

    /***************************************/
    for(int i = 0; i < 29; i++)
        this->focusZoomBuffer.append(0x30);

    focusZoomBuffer[0] = 0xD1;
    focusZoomBuffer[1] = 0x02;
    this->delayBuffer.clear();
    this->delayZoomList.clear();
    this->delayFoucsList.clear();

    /***************************************/

    if(getAutoFlag())
    {
        this->startServer();
    }
}

/**
 * @brief 卸载服务
 */
void JFreed::release()
{
    this->stopServer();
    this->mUdpSocket->deleteLater();
}

void JFreed::setIpAddress(const QString &ip,bool flag)
{
    QString address = ip.isEmpty()?"127.0.0.1":ip;
    this->udpAddress = address;
    if(flag || ip.isEmpty())
    {
        JConfig::getInstance()->setValue("JFreed/UDP_IPV4",address);
    }
}

void JFreed::setPort(int port,bool flag)
{
    int totalPort = (port<=0)?40000:port;
    this->udpPort = totalPort;
    if(flag || port<=0)
    {
        JConfig::getInstance()->setValue("JFreed/UDP_Port",totalPort);
    }
}

void JFreed::setFrame(int value,bool flag)
{
    int frame = (value<24)?24:value;
    this->freedFrame = frame;
    if(flag || value<24)
    {
        JConfig::getInstance()->setValue("JFreed/UDP_Frame",frame);
    }
}

void JFreed::setFocusDeleyFrame(int count,bool flag)
{
    this->delayFoucsFrame = count>0?count:0;
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/FocusDeleyFrame",delayFoucsFrame);
        //重新计算帧缓存
        this->delayFoucsList.clear();
    }
}

void JFreed::setZoomDeleyFrame(int count,bool flag)
{
    this->delayZoomFrame = count>0?count:0;
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/ZoomDeleyFrame",delayZoomFrame);
        //重新计算帧缓存
        this->delayZoomList.clear();
    }
}

void JFreed::setFocusMinValue(float min)
{
    this->focusMinValue = min;
    JConfig::getInstance()->setValue("JFreed/focusMinValue",min);
}

void JFreed::setFocusMaxValue(float max)
{
    this->focusMaxValue = max;
    JConfig::getInstance()->setValue("JFreed/focusMaxValue",max);
}

void JFreed::setZoomMinValue(float min)
{
    this->zoomMinValue = min;
    JConfig::getInstance()->setValue("JFreed/zoomMinValue",min);
}

void JFreed::setZoomMaxValue(float max)
{
    this->zoomMaxValue = max;
    JConfig::getInstance()->setValue("JFreed/zoomMaxValue",max);
}

void JFreed::setCameraRotate(float x,float y,float z,bool flag)
{
    this->cameraRotate.swap(QVector<float>()<<x<<y<<z);
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/CameraRotate",QVector<QVariant>()<<x<<y<<z);
    }
}

void JFreed::setCameraTransform(int a,int b,int c,bool flag)
{
    this->cameraTransform.swap(QVector<int>()<<a<<b<<c);
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/CameraTransform",QVector<QVariant>()<<a<<b<<c);
    }
}

void JFreed::setCoordinateOffset(float x,float y,float z,bool flag)
{
    this->coordinateOffset.swap(QVector<float>()<<x<<y<<z);
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/CoordinateOffset",QVector<QVariant>()<<x<<y<<z);
    }
}

void JFreed::setCoordinateUnity(float x,float y,float z,bool flag)
{
    this->coordinateUnits.swap(QVector<float>()<<x<<y<<z);
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/CoordinateUnits",QVector<QVariant>()<<x<<y<<z);
    }
}

void JFreed::setCoordinateTransform(int x,int y,int z,bool flag)
{
    this->coordinateTransform.swap(QVector<int>()<<x<<y<<z);
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/CoordinateTransform",QVector<QVariant>()<<x<<y<<z);
    }
}

QString JFreed::getIpAddress() const
{
    return this->udpAddress;
}

int JFreed::getPort() const
{
    return this->udpPort;
}

int JFreed::getFrame() const
{
    return this->freedFrame;
}

int JFreed::getFocusDeleyFrame() const
{
    return this->delayFoucsFrame;
}

int JFreed::getZoomDeleyFrame() const
{
    return this->delayZoomFrame;
}

float JFreed::getFocusMinValue() const
{
    return this->focusMinValue;
}

float JFreed::getFocusMaxValue() const
{
    return this->focusMaxValue;
}

float JFreed::getZoomMinValue() const
{
    return this->zoomMinValue;
}

float JFreed::getZoomMaxValue() const
{
    return this->zoomMaxValue;
}

QVector<float> JFreed::getCameraRotate() const
{
    return this->cameraRotate;
}

QVector<int> JFreed::getCameraTransform() const
{
    return this->cameraTransform;
}

QVector<float> JFreed::getCoordinateOffset() const
{
    return this->coordinateOffset;
}

QVector<float> JFreed::getCoordinateUnity() const
{
    return this->coordinateUnits;
}

QVector<int> JFreed::getCoordinateTransform() const
{
    return this->coordinateTransform;
}

/**
 * @brief 启动服务
 * @param fps 帧率
 */
void JFreed::startServer()
{
    if(freedTimerId == 0)
    {
        this->freedTimerId = startTimer(1000/freedFrame,Qt::PreciseTimer);
    }
}

/**
 * @brief 停止服务
 */
void JFreed::stopServer()
{
    if(freedTimerId != 0)
    {
        this->killTimer(freedTimerId);
        this->freedTimerId = 0;
    }
}

void JFreed::setAutoFlag(bool enable,bool flag)
{
    this->autoFlag = enable;
    if(flag)
    {
        JConfig::getInstance()->setValue("JFreed/AutoFlag",enable);
    }
}

bool JFreed::getAutoFlag() const
{
    return autoFlag;
}

bool JFreed::isRunning() const
{
    return freedTimerId>0?true:false;
}

void JFreed::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == freedTimerId)
    {
        //msg type
        freedBuffer[0] = 0xD1;
        //camera id
        freedBuffer[1] = 0x01;

        JRobot *robot = JRobot::getInstance();
        this->transformCameraBuffer(freedBuffer,cameraTransform[0],robot->getPosition()->getRx().toDouble());
        this->transformCameraBuffer(freedBuffer,cameraTransform[1],robot->getPosition()->getRy().toDouble());
        this->transformCameraBuffer(freedBuffer,cameraTransform[2],robot->getPosition()->getRz().toDouble());
        this->transformCoordinateBuffer(freedBuffer,coordinateTransform[0],robot->getPosition()->getX().toDouble());
        this->transformCoordinateBuffer(freedBuffer,coordinateTransform[1],robot->getPosition()->getY().toDouble());
        this->transformCoordinateBuffer(freedBuffer,coordinateTransform[2],robot->getPosition()->getZ().toDouble());

        JFollowfocus *followfocus = JFollowfocus::getInstance();
        float focusValue = followfocus->getFocus();
        float zoomValue = followfocus->getZoom();
        float focusPercent = focusValue/7200.0f;
        float zoomPercent = zoomValue/7200.0f;

        this->delayZoomList.push_back(zoomPercent);
        if(delayZoomList.size() > delayZoomFrame)
        {
            this->freedBuffer.replace(20,3,generateZoom(delayZoomList.first()));
            this->delayZoomList.removeFirst();
        }

        this->delayFoucsList.push_back(focusPercent);
        if(delayFoucsList.size() > delayFoucsFrame)
        {
            this->freedBuffer.replace(23,3,generateFocus(delayFoucsList.first()));
            this->delayFoucsList.removeFirst();
        }

        //custom byte
        freedBuffer[26] = '0';
        freedBuffer[27] = '0';
        //ck
        freedBuffer[28] = generateCheckSum(freedBuffer.left(28));

        this->mUdpSocket->writeDatagram(freedBuffer.data(),freedBuffer.size(),QHostAddress(udpAddress),udpPort);
        this->mUdpSocket->flush();
    }
    else
    {
        this->killTimer(event->timerId());
    }
}


void JFreed::transformCameraBuffer(QByteArray &buffer,int axis,float value)
{
    //结果 = (源数据+偏移)/单位计算
    switch (axis)
    {
    case 0:buffer.replace(2,3,generatePan(value+cameraRotate[0]));break;
    case 1:buffer.replace(5,3,generateTile(value+cameraRotate[1]));break;
    case 2:buffer.replace(8,3,generateRoll(value+cameraRotate[2]));break;
    case 3:buffer.replace(2,3,generatePan(-value+cameraRotate[0]));break;
    case 4:buffer.replace(5,3,generateTile(-value+cameraRotate[1]));break;
    case 5:buffer.replace(8,3,generateRoll(-value+cameraRotate[2]));break;
    default:
        break;
    }
}

void JFreed::transformCoordinateBuffer(QByteArray &buffer,int axis,float value)
{
    switch (axis)
    {
    case 0:buffer.replace(11,3,generatePos((value+coordinateOffset[0])/coordinateUnits[0]));break;
    case 1:buffer.replace(14,3,generatePos((value+coordinateOffset[1])/coordinateUnits[1]));break;
    case 2:buffer.replace(17,3,generatePos((value+coordinateOffset[2])/coordinateUnits[2]));break;
    case 3:buffer.replace(11,3,generatePos(-(value+coordinateOffset[0])/coordinateUnits[0]));break;
    case 4:buffer.replace(14,3,generatePos(-(value+coordinateOffset[1])/coordinateUnits[1]));break;
    case 5:buffer.replace(17,3,generatePos(-(value+coordinateOffset[2])/coordinateUnits[2]));break;
    default:
        break;
    }
}

/**
 * @brief 转换Pan角
 * @param angle 输入角度
 * @return 3个字节
 */
QByteArray JFreed::generatePan(float angle)
{
    //角度范围转换(-180~180)
    if(qAbs(angle) > 180)
    {
        if (angle < -180)
            angle += 360;
        else
            angle -= 360;
    }
    return this->angleToByte(angle);
}
/**
 * @brief 转换Tile角
 * @param angle 输入角度
 * @return 3个字节
 */
QByteArray JFreed::generateTile(float angle)
{
    //角度范围转换(-90~90)
    if(qAbs(angle) > 90)
    {
        if (angle < -90)
            angle += 180;
        else
            angle -= 180;
    }
    return this->angleToByte(angle);
}
/**
 * @brief 转换Roll角
 * @param angle 输入角度
 * @return 3个字节
 */
QByteArray JFreed::generateRoll(float angle)
{
    //角度范围转换(-180~180)
    if(qAbs(angle) > 180)
    {
        if (angle < -180)
            angle += 360;
        else
            angle -= 360;
    }
    return this->angleToByte(angle);
}

/**
 * @brief 角度值转换位字节 (freed格式)
 * @param angle 输入角度
 * @return 3个字节
 */
QByteArray JFreed::angleToByte(float angle)
{
    QByteArray buffer;
    //数值转换 以1/32768度为单位的带符号整型值(二进制)
    int absAngle = angle*32768;
    //<*L>
    buffer.append(absAngle&0x000000ff);
    //<*M>
    absAngle >>= 8;
    buffer.insert(0,absAngle&0x000000ff);
    //<*H>
    absAngle >>= 8;
    buffer.insert(0,absAngle&0x000000ff);

    return buffer;
}

/**
 * @brief JFreed::generatePos
 * @param pos
 * @return
 */
QByteArray JFreed::generatePos(float pos)
{
    //发送缓存
    QByteArray buffer;

    //范围限制 (-131072~131072)mm
    if (pos <= -131071)
        pos = -131071;
    else if (pos >= 131071)
        pos = 131071;

    //数值转换
    int axis = pos*640;
    //<*L>
    buffer.append(axis&0xff);
    //<*M>
    axis >>= 8;
    buffer.insert(0,axis&0xff);
    //<*H>
    axis >>= 8;
    buffer.insert(0,axis&0xff);

    return buffer;
}


/**
 * @brief 变焦值创建
 * @param value
 * @return
 */
QByteArray JFreed::generateZoom(float value)
{
    //发送缓存
    QByteArray buffer;
    //数值转换
    int zoomValue = value*4095;
    //<*L>
    buffer.append(zoomValue&0xff);
    //<*M>
    zoomValue >>= 8;
    buffer.insert(0,zoomValue&0xff);
    //<*H>
    zoomValue >>= 8;
    buffer.insert(0,zoomValue&0xff);

    return buffer;
}

/**
 * @brief 对焦值创建
 * @param value
 * @return
 */
QByteArray JFreed::generateFocus(float value)
{
    //发送缓存
    QByteArray buffer;
    //数值转换
    int focusValue = value*4095;
    //<*L>
    buffer.append(focusValue&0xff);
    //<*M>
    focusValue >>= 8;
    buffer.insert(0,focusValue&0xff);
    //<*H>
    focusValue >>= 8;
    buffer.insert(0,focusValue&0xff);

    return buffer;
}

/**
 * @brief 总和检验码
 * @param buffer
 * @return
 */
char JFreed::generateCheckSum(const QByteArray &buffer)
{
    char ck = 0x40;

    for(int i = 0; i < buffer.length(); i++)
        ck -= buffer[i];

    return ck;
}

