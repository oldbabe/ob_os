#include "Session/jnodeturnplate.h"
#include <QJsonObject>

namespace jltmoco
{

JNodeTurnplate::JNodeTurnplate(QObject *parent)
    : QObject(parent)
{
    this->setTarget("0");
    this->setAcc(30);
    this->setSpeed(30);

}

JNodeTurnplate::~JNodeTurnplate()
{
}

QJsonObject JNodeTurnplate::toJson()
{
    QJsonObject json;
    json["Acc"] = getAcc();
    json["Speed"] = getSpeed();
    json["target"] = getTarget();
    return json;
}

void JNodeTurnplate::setAcc(int value)
{
    if(mAcc != value)
    {
        this->mAcc = value;
        emit accChanged();
    }
}

void JNodeTurnplate::setSpeed(int value)
{
    if(mSpeed != value)
    {
        this->mSpeed = value;
        emit speedChanged();
    }
}

void JNodeTurnplate::setTarget(const QString &value)
{
    if(mTarget != value)
    {
        this->mTarget = value;
        emit targetChanged();
    }
}


}
