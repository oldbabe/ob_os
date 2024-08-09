#include "jconfig.h"
#include <QMutex>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>

using namespace jltmoco;

JConfig* JConfig::handle = Q_NULLPTR;

JConfig* JConfig::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();

        QDir dir;
        QString jltPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp";
        if(!dir.exists(jltPath))
            dir.mkpath(jltPath);

        handle = new JConfig(jltPath+"/JConfig.ini", QSettings::IniFormat);
        mutex.unlock();
    }
    return handle;
}

JConfig::JConfig(const QString &fileName, QSettings::Format format, QObject *parent)
    : QSettings(fileName,format,parent)
{
    this->setServerAddr(value("StudioConfig/ServerAddr").toString(),false);
    this->setRobotAddr(value("StudioConfig/RobotAddr").toString(),false);
    this->setRailAddr(value("StudioConfig/RailAddr").toString(),false);
    this->setRailDeviceAddr(value("StudioConfig/RailDeviceAddr").toString(),false);
    this->setTurnplatePortName(value("StudioConfig/TurnplatePortName").toString(),false);
    this->setNumber(value("StudioConfig/Number").toInt(),false);
    this->setType(value("StudioConfig/Type").toInt(),false);
}

void JConfig::setServerAddr(const QString &addr,bool enable)
{
    QString total = addr.isEmpty() ? "127.0.0.1" : addr;
    if(total != mServerAddr)
    {
        this->mServerAddr = total;
        emit serverAddrChanged();
        if(enable)
        {
            this->setValue("StudioConfig/ServerAddr",total);
        }
    }
}

QString JConfig::getServerAddr()
{
    return mServerAddr;
}

void JConfig::setRobotAddr(const QString &addr,bool enable)
{
    QString total = addr.isEmpty() ? "127.0.0.1" : addr;
    if(total != mRobotAddr)
    {
        this->mRobotAddr = total;
        emit robotAddrChanged();
        if(enable)
        {
            this->setValue("StudioConfig/RobotAddr",total);
        }
    }
}

QString JConfig::getRobotAddr()
{
    return this->mRobotAddr;
}

void JConfig::setRailAddr(const QString &addr,bool enable)
{
    QString total = addr.isEmpty() ? "127.0.0.1" : addr;
    if(total != mRailAddr)
    {
        this->mRailAddr = total;
        emit railAddrChanged();
        if(enable)
        {
            this->setValue("StudioConfig/RailAddr",total);
        }
    }
}

QString JConfig::getRailAddr()
{
    return mRailAddr;
}

void JConfig::setRailDeviceAddr(const QString &addr,bool enable)
{
    QString total = addr.isEmpty() ? "127.0.0.1" : addr;
    if(total != mRailDeviceAddr)
    {
        this->mRailDeviceAddr = total;
        emit railDeviceAddrChanged();
        if(enable)
        {
            this->setValue("StudioConfig/RailDeviceAddr",total);
        }
    }
}

QString JConfig::getRailDeviceAddr() const
{
    return mRailDeviceAddr;
}

void JConfig::setNumber(int value,bool enable)
{
    int total = value < 1 ? 1 : value;
    if(mNumber != total)
    {
        this->mNumber = total;
        emit numberChanged();
        if(enable)
        {
            this->setValue("StudioConfig/Number",total);
        }
    }
}

int JConfig::getNumber() const
{
    return this->mNumber;
}

void JConfig::setType(int value,bool enable)
{
    if(mType != value)
    {
        this->mType = value;
        emit typeChanged();
        if(enable)
        {
            this->setValue("StudioConfig/Type",value);
        }
    }
}

int JConfig::getType() const
{
    return this->mType;
}

void JConfig::setTurnplatePortName(const QString &value,bool enable)
{
    if(value != mTurnplatePortName)
    {
        this->mTurnplatePortName = value;
        emit turnplatePortNameChanged();
        if(enable)
        {
            this->setValue("StudioConfig/TurnplatePortName",value);
        }
    }
}

QString JConfig::getTurnplatePortName() const
{
    return this->mTurnplatePortName;
}

/**
 * @brief 设置遥控速度
 * @param type 挡位
 * @param num 轴编号
 * @param value 值
 */
void JConfig::setJsonConfig(const QString &key,const QJsonObject &obj)
{
    this->setValue("StudioClient/"+key,obj);
}

/**
 * @brief 返回遥控速度
 * @param type 挡位
 * @param num 轴编号
 * @return 值 默认返回 "1"
 */
QJsonObject JConfig::getJsonConfig(const QString &key) const
{
    return value("StudioClient/"+key).toJsonObject();
}

