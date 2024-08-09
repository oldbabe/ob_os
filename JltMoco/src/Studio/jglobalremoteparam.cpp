#include "Studio/jglobalremoteparam.h"
#include <QMutex>
#include <QDebug>
#include "jconfig.h"

namespace jltmoco
{

JGlobalRemoteParam* JGlobalRemoteParam::handle = Q_NULLPTR;

JGlobalRemoteParam* JGlobalRemoteParam::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JGlobalRemoteParam;
        mutex.unlock();
    }
    return handle;
}

JGlobalRemoteParam::JGlobalRemoteParam()
{
    this->mRobotPrgV = JConfig::getInstance()->value("RobotPrgV",30).toInt();
    this->mRobotV = JConfig::getInstance()->value("RobotV",30).toInt();
    this->mRobotA = JConfig::getInstance()->value("RobotA",30).toInt();
    this->mRailV = JConfig::getInstance()->value("RailV",30).toInt();
    this->mRailA = JConfig::getInstance()->value("RailA",30).toInt();
    this->mTurnplateV = JConfig::getInstance()->value("TurnplateV",30).toInt();
    this->mTurnplateA = JConfig::getInstance()->value("TurnplateA",30).toInt();
    this->mCameraPosition.setX(JConfig::getInstance()->value("CameraPositionX",0).toDouble());
    this->mCameraPosition.setY(JConfig::getInstance()->value("CameraPositionY",1200).toDouble());
    this->mCameraPosition.setZ(JConfig::getInstance()->value("CameraPositionZ",2700).toDouble());
    this->mCameraEulerRotation.setX(JConfig::getInstance()->value("CameraEulerRotationX",0).toDouble());
    this->mCameraEulerRotation.setY(JConfig::getInstance()->value("CameraEulerRotationY",0).toDouble());
    this->mCameraEulerRotation.setZ(JConfig::getInstance()->value("CameraEulerRotationZ",0).toDouble());
}

void JGlobalRemoteParam::setCameraPosition(const QVector3D &vec)
{
    this->mCameraPosition = vec;
    JConfig::getInstance()->setValue("CameraPositionX",mCameraPosition.x());
    JConfig::getInstance()->setValue("CameraPositionY",mCameraPosition.y());
    JConfig::getInstance()->setValue("CameraPositionZ",mCameraPosition.z());
    emit cameraPositionChanged();
}

void JGlobalRemoteParam::setCameraEulerRotation(const QVector3D &vec)
{
    this->mCameraEulerRotation = vec;
    JConfig::getInstance()->setValue("CameraEulerRotationX",mCameraEulerRotation.x());
    JConfig::getInstance()->setValue("CameraEulerRotationY",mCameraEulerRotation.y());
    JConfig::getInstance()->setValue("CameraEulerRotationZ",mCameraEulerRotation.z());
    emit cameraEulerRotationChanged();
}

QJsonObject JGlobalRemoteParam::toRobotParamJson()
{
    QJsonObject json;
    json["PrgV"] = getRobotPrgV();
    json["RobotV"] = getRobotV();
    json["RobotA"] = getRobotA();
    json["PathV"] = getRailV();
    json["PathA"] = getRailA();
    json["AssistCA"] = 0;
    json["TsValue"] = 0;
    json["Waiting"] = 0;
    return json;
}

void JGlobalRemoteParam::setRobotPrgV(int value)
{
    if(value <= 0 || value > 100)
        return;

    if(mRobotPrgV != value)
    {
        this->mRobotPrgV = value;
        emit robotPrgVChanged();
        JConfig::getInstance()->setValue("RobotPrgV",value);
    }
}

void JGlobalRemoteParam::setRobotV(int value)
{
    if(value <= 0 || value > 100)
        return;

    if(mRobotV != value)
    {
        this->mRobotV = value;
        emit robotVChanged();
        JConfig::getInstance()->setValue("RobotV",value);
    }
}

void JGlobalRemoteParam::setRobotA(int value)
{
    if(value <= 0 || value > 100)
        return;
    if(mRobotA != value)
    {
        this->mRobotA = value;
        emit robotAChanged();
        JConfig::getInstance()->setValue("RobotA",value);
    }
}

void JGlobalRemoteParam::setRailV(int value)
{
    if(value <= 0 || value > 100)
        return;

    if(mRailV != value)
    {
        this->mRailV = value;
        emit railVChanged();
        JConfig::getInstance()->setValue("RailV",value);
    }
}

void JGlobalRemoteParam::setRailA(int value)
{
    if(value <= 0 || value > 100)
        return;

    if(mRailA != value)
    {
        this->mRailA = value;
        emit railAChanged();
        JConfig::getInstance()->setValue("RailA",value);
    }
}

void JGlobalRemoteParam::setTurnplateV(int value)
{
    if(value <= 0 || value > 100)
        return;

    if(mTurnplateV != value)
    {
        this->mTurnplateV = value;
        emit turnplateVChanged();
        JConfig::getInstance()->setValue("TurnplateV",value);
    }
}

void JGlobalRemoteParam::setTurnplateA(int value)
{
    if(value <= 0 || value > 100)
        return;

    if(mTurnplateA != value)
    {
        this->mTurnplateA = value;
        emit turnplateAChanged();
        JConfig::getInstance()->setValue("TurnplateA",value);
    }
}


}
