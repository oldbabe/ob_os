#include "Session/jnoderobot.h"
#include <QJsonObject>
#include <QDebug>

namespace jltmoco
{

JNodeRobot::JNodeRobot(QObject *parent)
    : QObject(parent)
{
    this->mEnable = false;
    this->mType = RobotType_PTP;
    this->mRobotV = 30;
    this->mRobotA = 30;
    this->mPathV = 30;
    this->mPathA = 30;
    this->mTsValue = 0;
    this->mWaiting = 0;
    this->mAssistCA = 0;
    this->mFrames = 0;
}

JNodeRobot::~JNodeRobot()
{
}

void JNodeRobot::updateEnable()
{
    bool enable = true;
    if(getTarget()->getA1()=="0"&&
        getTarget()->getA2()=="0"&&
        getTarget()->getA3()=="0"&&
        getTarget()->getA4()=="0"&&
        getTarget()->getA5()=="0"&&
        getTarget()->getA6()=="0"&&
        getTarget()->getA7()=="0")
    {
        enable = false;
    }
    if(enable && getType() == 3)
    {
        if(getAssist()->getA1()=="0"&&
            getAssist()->getA2()=="0"&&
            getAssist()->getA3()=="0"&&
            getAssist()->getA4()=="0"&&
            getAssist()->getA5()=="0"&&
            getAssist()->getA6()=="0"&&
            getAssist()->getA7()=="0")
        {
            enable = false;
        }
    }
    this->setEnable(enable);
}

void JNodeRobot::setEnable(bool enable)
{
    if(mEnable != enable)
    {
        this->mEnable = enable;
        emit enableChanged();
    }
}

void JNodeRobot::setType(int value)
{
    if(mType != value)
    {
        this->mType = value;
        emit typeChanged();
    }
}

void JNodeRobot::setRobotV(int value)
{
    if(mRobotV != value)
    {
        this->mRobotV = value;
        emit robotVChanged();
    }
}

void JNodeRobot::setRobotA(int value)
{
    if(mRobotA != value)
    {
        this->mRobotA = value;
        emit robotAChanged();
    }
}

void JNodeRobot::setPathV(int value)
{
    if(mPathV != value)
    {
        this->mPathV = value;
        emit pathVChanged();
    }
}

void JNodeRobot::setPathA(int value)
{
    if(mPathA != value)
    {
        this->mPathA = value;
        emit pathAChanged();
    }
}

void JNodeRobot::setTsValue(int value)
{
    if(mTsValue != value)
    {
        this->mTsValue = value;
        emit tsValueChanged();
    }
}

void JNodeRobot::setWaiting(int value)
{
    if(mWaiting != value)
    {
        this->mWaiting = value;
        emit waitingChanged();
    }
}

void JNodeRobot::setAssistCA(int value)
{
    if(mAssistCA != value)
    {
        this->mAssistCA = value;
        emit assistCAChanged();
    }
}

void JNodeRobot::setFrames(int value)
{
    if(mFrames != value)
    {
        this->mFrames = value;
        emit framesChanged();
    }
}

QJsonObject JNodeRobot::toParamJson()
{
    QJsonObject param;
    param["RobotV"] = getRobotV();
    param["RobotA"] = getRobotA();
    param["PathV"] = getPathV();
    param["PathA"] = getPathA();
    param["AssistCA"] = getAssistCA();
    param["TsValue"] = getTsValue();
    param["Waiting"] = getWaiting();
    return param;
}

/**
 * @brief 圆心角计算
 * @param x1 起点x
 * @param y1 起点y
 * @param z1 起点z
 * @param x2 辅助点x
 * @param y2 辅助点y
 * @param z2 辅助点z
 * @param x3 目标点x
 * @param y3 目标点y
 * @param z3 目标点z
 * @return [圆心点x,圆心点y,圆心点z,半径,圆心角]
 */
QList<double> JNodeRobot::centerCircle3d(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    double a1 = (y1*z2 - y2*z1 - y1*z3 + y3*z1 + y2*z3 - y3*z2),
        b1 = -(x1*z2 - x2*z1 - x1*z3 + x3*z1 + x2*z3 - x3*z2),
        c1 = (x1*y2 - x2*y1 - x1*y3 + x3*y1 + x2*y3 - x3*y2),
        d1 = -(x1*y2*z3 - x1*y3*z2 - x2*y1*z3 + x2*y3*z1 + x3*y1*z2 - x3*y2*z1);

    double a2 = 2 * (x2 - x1),
        b2 = 2 * (y2 - y1),
        c2 = 2 * (z2 - z1),
        d2 = x1*x1 + y1*y1 + z1*z1 - x2*x2 - y2*y2 - z2*z2;

    double a3 = 2 * (x3 - x1),
        b3 = 2 * (y3 - y1),
        c3 = 2 * (z3 - z1),
        d3 = x1*x1 + y1*y1 + z1*z1 - x3*x3 - y3*y3 - z3*z3;

    double x = -(b1*c2*d3 - b1*c3*d2 - b2*c1*d3 + b2*c3*d1 + b3*c1*d2 - b3*c2*d1)
               / (a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
    double y = (a1*c2*d3 - a1*c3*d2 - a2*c1*d3 + a2*c3*d1 + a3*c1*d2 - a3*c2*d1)
               / (a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
    double z = -(a1*b2*d3 - a1*b3*d2 - a2*b1*d3 + a2*b3*d1 + a3*b1*d2 - a3*b2*d1)
               / (a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
    double radius = qSqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y) + (z1 - z)*(z1 - z));

    double arclength1 = qSqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));
    double angle1 = qRadiansToDegrees(qAsin((arclength1/2)/radius));
    double arclength2 = qSqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)+(z3-z2)*(z3-z2));
    double angle2 = qRadiansToDegrees(qAsin((arclength2/2)/radius));
    double angle = angle1*2+angle2*2;

    return QList<double>()<<x<<y<<z<<radius<<angle;
}

}
