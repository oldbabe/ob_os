#include "Session/jnodecamera.h"
#include <QJsonObject>
#include <QDebug>

namespace jltmoco
{

JNodeCamera::JNodeCamera(QObject *parent)
    : QObject(parent)
{
    this->setImageInterval(0);
    this->setImageNum(1);
    this->setShootMode(1);
}

JNodeCamera::~JNodeCamera()
{
}

QJsonObject JNodeCamera::toJson()
{
    QJsonObject json;
    json["ImageInterval"] = getImageInterval();
    json["ImageNum"] = getImageNum();
    json["ShootMode"] = getShootMode();
    return json;
}

void JNodeCamera::setImageInterval(int value)
{
    if(mImageInterval != value)
    {
        this->mImageInterval = value;
        emit imageIntervalChanged();
    }
}

void JNodeCamera::setImageNum(int value)
{
    if(mImageNum != value)
    {
        this->mImageNum = value;
        emit imageNumChanged();
    }
}

void JNodeCamera::setShootMode(int value)
{
    if(mShootMode != value)
    {
        this->mShootMode = value;
        emit shootModeChanged();
    }
}

}
