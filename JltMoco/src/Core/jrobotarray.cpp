#include "Core/jrobotarray.h"
#include <QJsonObject>

namespace jltmoco
{

JRobotArray::JRobotArray()
{
    this->setX("0");
    this->setY("0");
    this->setZ("0");
    this->setRx("0");
    this->setRy("0");
    this->setRz("0");
    this->setA1("0");
    this->setA2("0");
    this->setA3("0");
    this->setA4("0");
    this->setA5("0");
    this->setA6("0");
    this->setA7("0");
}

void JRobotArray::setX(const QString &value)
{
    if(value.isEmpty())
        return;
    if(posX != value)
    {
        this->posX = value;
        emit posXChanged();
    }
}
void JRobotArray::setY(const QString &value)
{
    if(value.isEmpty())
        return;
    if(posY != value)
    {
        this->posY = value;
        emit posYChanged();
    }
}
void JRobotArray::setZ(const QString &value)
{
    if(value.isEmpty())
        return;
    if(posZ != value)
    {
        this->posZ = value;
        emit posZChanged();
    }
}
void JRobotArray::setRx(const QString &value)
{
    if(value.isEmpty())
        return;
    if(posRx != value)
    {
        this->posRx = value;
        emit posRxChanged();
    }
}
void JRobotArray::setRy(const QString &value)
{
    if(value.isEmpty())
        return;
    if(posRy != value)
    {
        this->posRy = value;
        emit posRyChanged();
    }
}
void JRobotArray::setRz(const QString &value)
{
    if(value.isEmpty())
        return;
    if(posRz != value)
    {
        this->posRz = value;
        emit posRzChanged();
    }
}
void JRobotArray::setA1(const QString &value)
{
    if(value.isEmpty())
        return;
    if(axis1 != value)
    {
        this->axis1 = value;
        emit axis1Changed();
    }
}
void JRobotArray::setA2(const QString &value)
{
    if(value.isEmpty())
        return;
    if(axis2 != value)
    {
        this->axis2 = value;
        emit axis2Changed();
    }
}
void JRobotArray::setA3(const QString &value)
{
    if(value.isEmpty())
        return;
    if(axis3 != value)
    {
        this->axis3 = value;
        emit axis3Changed();
    }
}
void JRobotArray::setA4(const QString &value)
{
    if(value.isEmpty())
        return;
    if(axis4 != value)
    {
        this->axis4 = value;
        emit axis4Changed();
    }
}
void JRobotArray::setA5(const QString &value)
{
    if(value.isEmpty())
        return;
    if(axis5 != value)
    {
        this->axis5 = value;
        emit axis5Changed();
    }
}
void JRobotArray::setA6(const QString &value)
{
    if(value.isEmpty())
        return;
    if(axis6 != value)
    {
        this->axis6 = value;
        emit axis6Changed();
    }
}
void JRobotArray::setA7(const QString &value)
{
    if(value.isEmpty())
        return;
    if(axis7 != value)
    {
        this->axis7 = value;
        emit axis7Changed();
    }
}

QJsonObject JRobotArray::toJson()
{
    QJsonObject root;
    root["X"] = getX();
    root["Y"] = getY();
    root["Z"] = getZ();
    root["A"] = getRx();
    root["B"] = getRy();
    root["C"] = getRz();
    root["A1"] = getA1();
    root["A2"] = getA2();
    root["A3"] = getA3();
    root["A4"] = getA4();
    root["A5"] = getA5();
    root["A6"] = getA6();
    root["E1"] = getA7();
    return root;
}

/***********************************************************/

void CartesianTran::setX(qreal value)
{
    this->mx = value;
    emit xChanged();
}

void CartesianTran::setY(qreal value)
{
    this->my = value;
    emit yChanged();
}

void CartesianTran::setZ(qreal value)
{
    this->mz = value;
    emit zChanged();
}

void Rpy::setRx(qreal value)
{
    this->mrx = value;
    emit rxChanged();
}

void Rpy::setRy(qreal value)
{
    this->mry = value;
    emit ryChanged();
}

void Rpy::setRz(qreal value)
{
    this->mrz = value;
    emit rzChanged();
}

void CartesianPoseLoad::setMass(qreal value)
{
    this->mMass = value;
    emit massChanged();
}

QJsonObject CartesianPose::toJson()
{
    QJsonObject root;
    root["X"] = getTran()->getX();
    root["Y"] = getTran()->getY();
    root["Z"] = getTran()->getZ();
    root["A"] = getRpy()->getRx();
    root["B"] = getRpy()->getRy();
    root["C"] = getRpy()->getRz();
    return root;
}

QJsonObject CartesianPoseLoad::toJson()
{
    QJsonObject root;
    root["mass"] = getMass();
    root["X"] = getTran()->getX();
    root["Y"] = getTran()->getY();
    root["Z"] = getTran()->getZ();
    root["A"] = getRpy()->getRx();
    root["B"] = getRpy()->getRy();
    root["C"] = getRpy()->getRz();
    root["JX"] = getInertia()->getX();
    root["JY"] = getInertia()->getY();
    root["JZ"] = getInertia()->getZ();
    return root;
}

}
