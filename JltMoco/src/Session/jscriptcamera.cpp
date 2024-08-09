#include "Session/jscriptcamera.h"


namespace jltmoco
{

JScriptCamera::JScriptCamera(QObject *parent)
    : QObject(parent)
{
    this->setRecordingDuration(30);
    this->setMoveDelay(3);
}

JScriptCamera::~JScriptCamera()
{
}

void JScriptCamera::setRecordingDuration(int duration)
{
    if(mRecordingDuration != duration)
    {
        this->mRecordingDuration = duration;
        emit recordingDurationChanged();
    }
}

void JScriptCamera::setMoveDelay(int mesc)
{
    if(mMoveDelay != mesc)
    {
        this->mMoveDelay = mesc;
        emit moveDelayChanged();
    }
}
}
