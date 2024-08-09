#include "Session/jnodefollowfocus.h"
#include <QJsonObject>

namespace jltmoco
{

JNodeFollowFocus::JNodeFollowFocus(QObject *parent)
    : QObject(parent)
{
    this->setFocusValue(3600);
    this->setZoomValue(3600);
    this->setIrisValue(3600);
}

JNodeFollowFocus::~JNodeFollowFocus()
{
}

QJsonObject JNodeFollowFocus::toJson()
{
    QJsonObject json;
    json["FocusValue"] = getFocusValue();
    json["ZoomValue"] = getZoomValue();
    json["IrisValue"] = getIrisValue();
    return json;
}

void JNodeFollowFocus::setFocusValue(int value)
{
    if(mFocusValue != value)
    {
        this->mFocusValue = value;
        emit focusValueChanged();
    }
}

void JNodeFollowFocus::setZoomValue(int value)
{
    if(mZoomValue != value)
    {
        this->mZoomValue = value;
        emit zoomValueChanged();
    }
}

void JNodeFollowFocus::setIrisValue(int value)
{
    if(mIrisValue != value)
    {
        this->mIrisValue = value;
        emit irisValueChanged();
    }
}

}
