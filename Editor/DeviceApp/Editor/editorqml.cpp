#include "editorqml.h"

#include <QMutex>
#include <QSettings>
#include <QJsonArray>
#include <livelinkfreed.h>
#include <devicecontroller.h>
#include "Interface/enumdefine.h"

EditorQml* EditorQml::handle = Q_NULLPTR;

EditorQml* EditorQml::getInstance()
{
    static QMutex mutex;
    if(handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new EditorQml;
        mutex.unlock();
    }

    return handle;
}

EditorQml::EditorQml()
{
#ifdef QT_DEBUG
    this->debugFlag = true;
#else
    this->debugFlag = false;
#endif
    this->setRobotConnected(false);
    this->setCameraConnected(false);
    this->setFollowfocusConnected(false);
    this->setTurnplateConnected(false);
}


void EditorQml::setup()
{
    QSettings settings;
    bool enable = settings.value("Editor/FirstOpenFlag").toBool();
    //第一次启动时初始化配置文化
    if(!enable)
    {
        settings.setValue("Editor/StudioType",0);
        settings.setValue("Editor/RobotIp","0.0.0.0");
        settings.setValue("Editor/RailIp","0.0.0.0");
        settings.setValue("Editor/RailDriveIp","0.0.0.0");
        settings.setValue("Editor/FollowFocuCom","");
        settings.setValue("Editor/TurnplateCom","");
        settings.setValue("Editor/CameraRotate","0");

        settings.setValue("Editor/FreedAutoStart",false);
        settings.setValue("Editor/FreeDIp","127.0.0.0");
        settings.setValue("Editor/FreeDPort",40000);
        settings.setValue("Editor/FreeD_Frame",30);
        settings.setValue("Editor/FreeD_CRx",0);
        settings.setValue("Editor/FreeD_CRy",0);
        settings.setValue("Editor/FreeD_CRz",0);
        settings.setValue("Editor/FreeD_Wx",0);
        settings.setValue("Editor/FreeD_Wy",0);
        settings.setValue("Editor/FreeD_Wz",0);

        settings.setValue("Editor/FirstOpenFlag",true);
    }

    this->setRobotIp(settings.value("Editor/RobotIp").toString());
    this->setRailIp(settings.value("Editor/RailIp").toString());
    this->setStudioType(settings.value("Editor/StudioType").toInt());
    this->setCameraRotate(settings.value("Editor/CameraRotate").toString());
    this->setRailDriveIp(settings.value("Editor/RailDriveIp").toString());
    this->setFollowFocuCom(settings.value("Editor/FollowFocuCom").toString());
    this->setTurnplateCom(settings.value("Editor/TurnplateCom").toString());

//    this->setFreeAutoEnable(settings.value("Editor/FreedAutoStart").toBool());
//    this->setFreeDIp(settings.value("Editor/FreeDIp").toString());
//    this->setFreeDPort(settings.value("Editor/FreeDPort").toInt());
//    this->setFreeDFrame(settings.value("Editor/FreeD_Frame").toInt());

//    if(getFreeAutoEnable())
//        LiveLinkFreeD::getInstance()->startServer();
}


void EditorQml::uninstall()
{
}

/**
 * @brief 设置影棚类型
 * @param type
 */
void EditorQml::setStudioType(const int &type)
{
    if(studioType != type)
    {
        this->studioType = type;
        this->setConfigValue("Editor/StudioType",type);
        emit studioTypeChanged();
    }
}

/**
 * @brief 返回影棚类型
 * @param type
 */
int EditorQml::getStudioType() const
{
    return this->studioType;
}

/**
 * @brief 设置相机视图的旋转角度
 * @param angle
 */
void EditorQml::setCameraRotate(const QString &angle)
{
    if(cameraRotate != angle)
    {
        this->cameraRotate = angle;
        this->setConfigValue("Editor/CameraRotate",angle);
        emit cameraRotateChanged();
    }
}


/**
 * @brief 返回相机视图的旋转角度
 * @param angle
 */
QString EditorQml::getCameraRotate() const
{
    return this->cameraRotate;
}

/**
 * @brief 设置机械臂IP
 * @param ip
 */
void EditorQml::setRobotIp(const QString &ip)
{
    if(robotIp != ip)
    {
        this->robotIp = ip;
        emit robotIpChanged();
        this->setConfigValue("Editor/RobotIp",ip);
        DEVICE::DeviceController::getInstance()->setRobotIp(ip);
    }
}

/**
 * @brief 返回机械臂P
 */
QString EditorQml::getRobotIp() const
{
    return this->robotIp;
}

/**
 * @brief 设置轨道Ip
 * @param ip
 */
void EditorQml::setRailIp(const QString &ip)
{
    if(railIp != ip)
    {
        this->railIp = ip;
        emit railIpChanged();
        this->setConfigValue("Editor/RailIp",ip);
        DEVICE::DeviceController::getInstance()->setRailIp(ip);
    }
}

/**
 * @brief 返回轨道IP
 */
QString EditorQml::getRailIp() const
{
    return this->railIp;
}

/**
 * @brief 设置轨道驱动IP
 */
void EditorQml::setRailDriveIp(const QString &ip)
{
    if(ip!=railDriveIp)
    {
        this->railDriveIp = ip;
        emit railDriveIpChanged();
        this->setConfigValue("Editor/RailDriveIp",ip);
    }
}

/**
 * @brief 返回轨道驱动IP
 */
QString EditorQml::getRailDriveIp() const
{
    return railDriveIp;
}

/**
 * @brief 设置跟焦器端口号
 * @param com
 */
void EditorQml::setFollowFocuCom(const QString &com)
{
    if(com!=followFocuCom)
    {
        this->followFocuCom = com;
        emit followFocuComChanged();
        this->setConfigValue("Editor/FollowFocuCom",com);
        DEVICE::DeviceController::getInstance()->setFollowfocusPortName(com);
    }
}

/**
 * @brief 返回跟焦器端口号
 * @param com
 */
QString EditorQml::getFollowFocuCom() const
{
    return followFocuCom;
}

/**
 * @brief 设置转盘端口号
 * @param com
 */
void EditorQml::setTurnplateCom(const QString &com)
{
    if(com!=turnplateCom)
    {
        this->turnplateCom = com;
        emit turnplateComChanged();
        this->setConfigValue("Editor/TurnplateCom",com);
        DEVICE::DeviceController::getInstance()->setTurnplatePortName(com);
    }
}

/**
 * @brief 返回转盘端口号
 * @param com
 */
QString EditorQml::getTurnplateCom() const
{
    return turnplateCom;
}

//void EditorQml::setFreeAutoEnable(bool enable)
//{
//    QSettings settings;
//    settings.setValue("Editor/FreedAutoStart",enable);
//}

//bool EditorQml::getFreeAutoEnable() const
//{
//    QSettings settings;
//    return settings.value("Editor/FreedAutoStart").toBool();
//}

//void EditorQml::setFreeState(bool state)
//{
//    if(state)
//        LiveLinkFreeD::getInstance()->startServer();
//    else
//        LiveLinkFreeD::getInstance()->stopServer();
//}

//bool EditorQml::getFreeState() const
//{
//    return LiveLinkFreeD::getInstance()->isRunning();
//}

//void EditorQml::setFreeDIp(const QString &ip)
//{
//    this->setConfigValue("Editor/FreeDIp",ip);
//    LiveLinkFreeD::getInstance()->setIpAddress(ip);
//}

//QString EditorQml::getFreeDIp() const
//{
//    return LiveLinkFreeD::getInstance()->getIpAddress();
//}

//void EditorQml::setFreeDPort(int port)
//{
//    this->setConfigValue("Editor/FreeDPort",port);
//    LiveLinkFreeD::getInstance()->setPort(port);
//}

//int EditorQml::getFreeDPort() const
//{
//    return LiveLinkFreeD::getInstance()->getPort();
//}


//void EditorQml::setFreeDFrame(int value)
//{
//    this->setConfigValue("Editor/FreeD_Frame",value);
//    LiveLinkFreeD::getInstance()->setFrame(value);
//}

//int EditorQml::getFreeDFrame() const
//{
//    return LiveLinkFreeD::getInstance()->getFrame();
//}

/**
 * @brief 返回可用的端口号列表
 * @return com
 */
QStringList EditorQml::ports()
{
    return DEVICE::DeviceController::getInstance()->ports();
}

bool EditorQml::getDebugFlag() const
{
    return this->debugFlag;
}

QString EditorQml::getLocalHostName()
{
    return DEVICE::DeviceController::getInstance()->localHostName();
}

/**
 * @brief 设置状态数据
 * @param obj
 */
void EditorQml::onStudioDevicesPropertiesChanged(const QJsonObject &obj)
{
    int code = obj["code"].toInt();
    if(code == 0x1000)
    {
        QJsonArray devs = obj["data"].toArray();
        for(int i = 0; i < devs.count(); i++)
        {
            QJsonObject dev = devs.at(i).toObject();
            int devId = dev["deviceId"].toInt();
            this->setDevConnected(devId,dev["connected"].toBool());
        }
    }
    else if(code == 0x2000)
    {
        QJsonObject devData;
        devData = obj["data"].toObject();

        if(devData["deviceId"].toInt() == 6)//openCv Data
        {
            int value = devData["data"].toInt();
            if(value != 0)
                DEVICE::DeviceController::robotPlugin->jog(1,0,((double)value*2),0,0,0,0);
            else
                DEVICE::DeviceController::robotPlugin->jogStop();
        }
    }
}

/**
 * @brief 跟随指令
 */
void EditorQml::onAutoFollowStateChanged(bool flag)
{
    emit cameraFrameImgUpdate(flag);
}

/**
 * @brief 设置设备的连接状态
 */
void EditorQml::setDevConnected(int deviceID,bool state)
{
    switch (deviceID)
    {
    case DEVICE::DeviceNumber::EquipmentNumber_Robot:
        this->setRobotConnected(state);
        break;
    case DEVICE::DeviceNumber::EquipmentNumber_Camera:
        this->setCameraConnected(state);
        break;
    case DEVICE::DeviceNumber::EquipmentNumber_FollowFocus:
        this->setFollowfocusConnected(state);
        break;
    case DEVICE::DeviceNumber::EquipmentNumber_Turntable:
        this->setTurnplateConnected(state);
        break;
    default:
        break;
    }
}
bool EditorQml::getRobotConnected() const
{
    return this->robotConnected;
}
bool EditorQml::getCameraConnected() const
{
    return this->cameraConnected;
}
bool EditorQml::getFollowfocusConnected() const
{
    return this->followfocusConnected;
}
bool EditorQml::getTurnplateConnected() const
{
    return this->turnplateConnected;
}

//void EditorQml::videoFrameUpdate(QVideoFrame &frame)
//{
//    QImage img = frame.toImage();
//    DEVICE::DeviceController::getInstance()->setCameraFrameImg(img.scaled(img.width()/4,img.height()/4));
//}

/**
 * @brief 设置机械臂&轨道的连接状态
 */
void EditorQml::setRobotConnected(bool res)
{
    if(res != robotConnected)
    {
        this->robotConnected = res;
        emit deviceStateChanged(DEVICE::DeviceNumber::EquipmentNumber_Robot,res);
    }
}
/**
 * @brief 设置相机的连接状态
 */
void EditorQml::setCameraConnected(bool res)
{
    if(res != cameraConnected)
    {
        this->cameraConnected = res;
        emit deviceStateChanged(DEVICE::DeviceNumber::EquipmentNumber_Camera,res);
    }
}
/**
 * @brief 设置跟焦器的连接状态
 */
void EditorQml::setFollowfocusConnected(bool res)
{
    if(res != followfocusConnected)
    {
        this->followfocusConnected = res;
        emit deviceStateChanged(DEVICE::DeviceNumber::EquipmentNumber_FollowFocus,res);
    }
}
/**
 * @brief 设置转盘的连接状态
 */
void EditorQml::setTurnplateConnected(bool res)
{
    if(res != turnplateConnected)
    {
        this->turnplateConnected = res;
        emit deviceStateChanged(DEVICE::DeviceNumber::EquipmentNumber_Turntable,res);
    }
}

/**
 * @brief 设置配置文件的值
 * @param key
 * @param value
 */
void EditorQml::setConfigValue(const QString &key,const QString &value)
{
    QSettings settings;
    settings.setValue(key,value);
}

void EditorQml::setConfigValue(const QString &key,const int &value)
{
    QSettings settings;
    settings.setValue(key,value);
}
