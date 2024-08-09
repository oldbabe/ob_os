#include "Session/jscriptturnplate.h"
#include <QJsonObject>

namespace jltmoco
{

JScriptTurnplate::JScriptTurnplate(QObject *parent)
    : QObject(parent)
{
    this->setAcc(30);
    this->setDec(30);
    this->setSpeed(30);
    this->setDuration(10);
    this->setDirection(1);
    this->setStartTime(0);
}

JScriptTurnplate::~JScriptTurnplate()
{
}

void JScriptTurnplate::setAcc(int value)
{
    if(mAcc != value)
    {
        this->mAcc = value;
        emit accChanged();
    }
}

void JScriptTurnplate::setSpeed(int value)
{
    if(mSpeed != value)
    {
        this->mSpeed = value;
        emit speedChanged();
    }
}

void JScriptTurnplate::setDec(int value)
{
    if(mDec != value)
    {
        this->mDec = value;
        emit decChanged();
    }
}

void JScriptTurnplate::setDuration(int value)
{
    if(mDuration != value)
    {
        this->mDuration = value;
        emit durationChanged();
    }
}

void JScriptTurnplate::setDirection(int value)
{
    if(mDirection != value)
    {
        this->mDirection = value == 1 ? 1 : -1;
        emit directionChanged();
    }
}

void JScriptTurnplate::setStartTime(int value)
{
    if(mStartTime != value)
    {
        this->mStartTime = value;
        emit startTimeChanged();
    }
}

}
