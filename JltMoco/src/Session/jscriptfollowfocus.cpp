#include "Session/jscriptfollowfocus.h"
#include "Studio/scriptcontroller.h"
#include "Studio/jrobot.h"
#include "Studio/jfollowfocus.h"
#include <QJsonObject>

namespace jltmoco
{

JScriptFollowFocus::JScriptFollowFocus(QObject *parent)
    : QObject(parent)
{
    this->setFocusValue(3600);
    this->setZoomValue(3600);
    this->setIrisValue(3600);
    this->setFocusMode(FollowFocusMode_OnlyRemote);
    this->setZoomMode(FollowFocusMode_OnlyRemote);
    this->setIrisMode(FollowFocusMode_OnlyRemote);
    connect(ScriptController::getInstance(),&ScriptController::frameCounterChanged,
            this,&JScriptFollowFocus::onFrameCounterChanged);
    connect(ScriptController::getInstance(),&ScriptController::stateChanged,
            this,&JScriptFollowFocus::onStateChanged);
}

JScriptFollowFocus::~JScriptFollowFocus()
{
}

void JScriptFollowFocus::setFocusValue(int value)
{
    if(mFocusValue != value)
    {
        this->mFocusValue = value;
        emit focusValueChanged();
    }
}

void JScriptFollowFocus::setZoomValue(int value)
{
    if(mZoomValue != value)
    {
        this->mZoomValue = value;
        emit zoomValueChanged();
    }
}

void JScriptFollowFocus::setIrisValue(int value)
{
    if(mIrisValue != value)
    {
        this->mIrisValue = value;
        emit irisValueChanged();
    }
}

void JScriptFollowFocus::setPathRecord(const QJsonObject &record)
{
    {
        this->focusPathRecord.clear();
        QJsonArray focus = record["focus"].toArray();
        for(int i = 0;i < focus.count(); i++)
        {
            QString data = focus[i].toString();
            QStringList list = data.split("_");
            if(list.length() == 2)
                this->focusPathRecord.insert(list[0].toInt(),list[1].toInt());
        }
    }
    {
        this->zoomPathRecord.clear();
        QJsonArray zoom = record["zoom"].toArray();
        for(int i = 0;i < zoom.count(); i++)
        {
            QString data = zoom[i].toString();
            QStringList list = data.split("_");
            if(list.length() == 2)
                this->zoomPathRecord.insert(list[0].toInt(),list[1].toInt());
        }
    }
    {
        this->irisPathRecord.clear();
        QJsonArray iris = record["iris"].toArray();
        for(int i = 0;i < iris.count(); i++)
        {
            QString data = iris[i].toString();
            QStringList list = data.split("_");
            if(list.length() == 2)
                this->irisPathRecord.insert(list[0].toInt(),list[1].toInt());
        }
    }
}

void JScriptFollowFocus::setTimeRecord(const QJsonObject &record)
{
    {
        this->focusTimeRecord.clear();
        QJsonArray focus = record["focus"].toArray();
        for(int i = 0;i < focus.count(); i++)
        {
            QString data = focus[i].toString();
            QStringList list = data.split("_");
            if(list.length() == 2)
                this->focusTimeRecord.insert(list[0].toLongLong(),list[1].toInt());
        }
    }
    {
        this->zoomTimeRecord.clear();
        QJsonArray zoom = record["zoom"].toArray();
        for(int i = 0;i < zoom.count(); i++)
        {
            QString data = zoom[i].toString();
            QStringList list = data.split("_");
            if(list.length() == 2)
                this->zoomTimeRecord.insert(list[0].toLongLong(),list[1].toInt());
        }
    }
    {
        this->irisTimeRecord.clear();
        QJsonArray iris = record["iris"].toArray();
        for(int i = 0;i < iris.count(); i++)
        {
            QString data = iris[i].toString();
            QStringList list = data.split("_");
            if(list.length() == 2)
                this->irisTimeRecord.insert(list[0].toLongLong(),list[1].toInt());
        }
    }
}

void JScriptFollowFocus::setFocusMode(FollowFocusMode mode)
{
    if(mFocusMode != mode)
    {
        this->mFocusMode = mode;
        emit focusModeChanged();
    }
}

void JScriptFollowFocus::setZoomMode(FollowFocusMode mode)
{
    if(mZoomMode != mode)
    {
        this->mZoomMode = mode;
        emit zoomModeChanged();
    }
}

void JScriptFollowFocus::setIrisMode(FollowFocusMode mode)
{
    if(mIrisMode != mode)
    {
        this->mIrisMode = mode;
        emit irisModeChanged();
    }
}


int JScriptFollowFocus::getFocusPathFirst()
{
    if(focusPathRecord.isEmpty())
        return -1;
    return focusPathRecord.first();
}

int JScriptFollowFocus::getZoomPathFirst()
{
    if(zoomPathRecord.isEmpty())
        return -1;
    return zoomPathRecord.first();
}

int JScriptFollowFocus::getIrisPathFirst()
{
    if(irisPathRecord.isEmpty())
        return -1;
    return irisPathRecord.first();
}

int JScriptFollowFocus::getFocusTimeFirst()
{
    if(focusTimeRecord.isEmpty())
        return -1;
    return focusTimeRecord.first();
}

int JScriptFollowFocus::getZoomTimeFirst()
{
    if(zoomTimeRecord.isEmpty())
        return -1;
    return zoomTimeRecord.first();
}

int JScriptFollowFocus::getIrisTimeFirst()
{
    if(irisTimeRecord.isEmpty())
        return -1;
    return irisTimeRecord.first();
}

QJsonObject JScriptFollowFocus::toJson()
{
    QJsonObject followFocus;
    followFocus["FocusMode"] = getFocusMode();
    followFocus["ZoomMode"] = getZoomMode();
    followFocus["IrisMode"] = getIrisMode();
    QJsonObject constant;
    constant["focus"] = getFocusValue();
    constant["zoom"] = getZoomValue();
    constant["iris"] = getIrisValue();
    followFocus["Constant"] = constant;

    QJsonObject pathObj;
    {
        QJsonArray fPaths;
        QMapIterator<int, int> i(focusPathRecord);
        while (i.hasNext())
        {
            i.next();
            fPaths.append(QString::number(i.key())+"_"+QString::number(i.value()));
        }
        pathObj["focus"] = fPaths;

        QJsonArray zPaths;
        i = zoomPathRecord;
        while (i.hasNext())
        {
            i.next();
            zPaths.append(QString::number(i.key())+"_"+QString::number(i.value()));
        }
        pathObj["zoom"] = zPaths;

        QJsonArray iPaths;
        i = irisPathRecord;
        while (i.hasNext())
        {
            i.next();
            iPaths.append(QString::number(i.key())+"_"+QString::number(i.value()));
        }
        pathObj["iris"] = iPaths;
    }
    followFocus["PathRecord"] = pathObj;

    QJsonObject timeObj;
    {
        QJsonArray fTimes;
        QMapIterator<qint64, int> j(focusTimeRecord);
        while (j.hasNext())
        {
            j.next();
            fTimes.append(QString::number(j.key())+"_"+QString::number(j.value()));
        }
        timeObj["focus"] = fTimes;

        QJsonArray zTimes;
        j = zoomTimeRecord;
        while (j.hasNext())
        {
            j.next();
            zTimes.append(QString::number(j.key())+"_"+QString::number(j.value()));
        }
        timeObj["zoom"] = zTimes;

        QJsonArray iTimes;
        j = irisTimeRecord;
        while (j.hasNext())
        {
            j.next();
            iTimes.append(QString::number(j.key())+"_"+QString::number(j.value()));
        }
        timeObj["iris"] = iTimes;
    }
    followFocus["TimeRecord"] = timeObj;

    return followFocus;
}

void JScriptFollowFocus::onStateChanged()
{
    JFollowfocus *followfocus = JFollowfocus::getInstance();
    if(ScriptController::getInstance()->getState() == 800)//视频脚本
    {
        if(mFocusMode == FollowFocusMode_Coonstant || mFocusMode == FollowFocusMode_PathPlay || mFocusMode == FollowFocusMode_TimePlay)
            followfocus->setFocusEnable(false);
        if(mZoomMode == FollowFocusMode_Coonstant || mZoomMode == FollowFocusMode_PathPlay || mZoomMode == FollowFocusMode_TimePlay)
            followfocus->setZoomEnable(false);
        if(mIrisMode == FollowFocusMode_Coonstant || mIrisMode == FollowFocusMode_PathPlay || mIrisMode == FollowFocusMode_TimePlay)
            followfocus->setIrisEnable(false);
    }
    else if(ScriptController::getInstance()->getState() == 784)//平面脚本
    {
        followfocus->setFocusEnable(false);
        followfocus->setZoomEnable(false);
        followfocus->setIrisEnable(false);
    }
    else if(ScriptController::getInstance()->getState() == 513)//就位
    {
        followfocus->setFocusEnable(false);
        followfocus->setZoomEnable(false);
        followfocus->setIrisEnable(false);
    }
    else
    {
        followfocus->setFocusEnable(true);
        followfocus->setZoomEnable(true);
        followfocus->setIrisEnable(true);
    }
}

//513就位 //0 256挂起
void JScriptFollowFocus::onFrameCounterChanged()
{
    static double startX = 0;
    static double startY = 0;
    static double startZ = 0;

    //800视频脚本运行启动
    if(ScriptController::getInstance()->getState() != 800)
        return;

    JRobot *robot = JRobot::getInstance();
    if(ScriptController::getInstance()->getFrameCounter() == 1)
    {
        this->pathLength = 0;
        startX = robot->getPosition()->getX().toDouble();
        startY = robot->getPosition()->getY().toDouble();
        startZ = robot->getPosition()->getZ().toDouble();
    }

    int error = qSqrt(qPow(robot->getPosition()->getX().toDouble()-startX,2)+
                              qPow(robot->getPosition()->getY().toDouble()-startY,2)+
                              qPow(robot->getPosition()->getZ().toDouble()-startZ,2));
    if(error>0)
    {
        this->pathLength += error;
        startX = robot->getPosition()->getX().toDouble();
        startY = robot->getPosition()->getY().toDouble();
        startZ = robot->getPosition()->getZ().toDouble();
    }

    this->focusPlayOrRecord(error,ScriptController::getInstance()->getFrameCounter());
    this->zoomPlayOrRecord(error,ScriptController::getInstance()->getFrameCounter());
    this->irisPlayOrRecord(error,ScriptController::getInstance()->getFrameCounter());
}

/**
 * @brief 对焦回放或记录
 * @param error 路径增量
 * @param time 帧编号
 */
void JScriptFollowFocus::focusPlayOrRecord(int error,qint64 time)
{
    JFollowfocus *followfocus = JFollowfocus::getInstance();
    if(mFocusMode == FollowFocusMode_PathRecord)
    {
        if(time == 1)
        {
            focusPathRecord.clear();
        }
        if(error > 0)
        {
            if(!focusPathRecord.isEmpty())
            {
                if(focusPathRecord.last() != followfocus->getFocus())
                    this->focusPathRecord.insert(pathLength,followfocus->getFocus());
            }
            else
            {
                this->focusPathRecord.insert(pathLength,followfocus->getFocus());
            }
        }
    }
    else if(mFocusMode == FollowFocusMode_PathPlay)
    {
        if(error > 0)
        {
            QMap<int,int>::iterator it = focusPathRecord.lowerBound(pathLength);
            if(it == focusPathRecord.end())
            {
                if(!focusPathRecord.isEmpty())
                    followfocus->sendFocus((--it).value());
            }
            else
            {
                followfocus->sendFocus(it.value());
            }
        }
        else
        {
            if(pathLength == 0)
                followfocus->sendFocus(getFocusPathFirst());
        }
    }
    else if(mFocusMode == FollowFocusMode_TimeRecord)
    {
        if(time == 1)
        {
            focusTimeRecord.clear();
        }
        if(!focusTimeRecord.isEmpty())
        {
            if(focusTimeRecord.last() != followfocus->getFocus())
                this->focusTimeRecord.insert(time,followfocus->getFocus());
        }
        else
        {
            this->focusTimeRecord.insert(time,followfocus->getFocus());
        }
    }
    else if(mFocusMode == FollowFocusMode_TimePlay)
    {
        QMap<qint64,int>::iterator i = focusTimeRecord.find(time);
        if(i != focusTimeRecord.end())
            followfocus->sendFocus(i.value());
    }
}

/**
 * @brief 变焦回放或记录
 * @param error 路径增量
 * @param time 帧编号
 */
void JScriptFollowFocus::zoomPlayOrRecord(int error,qint64 time)
{
    JFollowfocus *followfocus = JFollowfocus::getInstance();
    if(mZoomMode == FollowFocusMode_PathRecord)
    {
        if(time == 1)
        {
            zoomPathRecord.clear();
        }
        if(error > 0)
        {
            if(!zoomPathRecord.isEmpty())
            {
                if(zoomPathRecord.last() != followfocus->getZoom())
                    this->zoomPathRecord.insert(pathLength,followfocus->getZoom());
            }
            else
            {
                this->zoomPathRecord.insert(pathLength,followfocus->getZoom());
            }
        }
    }
    else if(mZoomMode == FollowFocusMode_PathPlay)
    {
        if(error > 0)
        {
            QMap<int,int>::iterator it = zoomPathRecord.lowerBound(pathLength);
            if(it == zoomPathRecord.end())
            {
                if(!zoomPathRecord.isEmpty())
                    followfocus->sendZoom((--it).value());
            }
            else
            {
                followfocus->sendZoom(it.value());
            }
        }
        else
        {
            if(pathLength == 0)
                followfocus->sendZoom(getZoomPathFirst());
        }
    }
    else if(mZoomMode == FollowFocusMode_TimeRecord)
    {
        if(time == 1)
        {
            zoomTimeRecord.clear();
        }
        if(!zoomTimeRecord.isEmpty())
        {
            if(zoomTimeRecord.last() != followfocus->getZoom())
                this->zoomTimeRecord.insert(time,followfocus->getZoom());
        }
        else
        {
            this->zoomTimeRecord.insert(time,followfocus->getZoom());
        }
    }
    else if(mZoomMode == FollowFocusMode_TimePlay)
    {
        QMap<qint64,int>::iterator i = zoomTimeRecord.find(time);
        if(i != zoomTimeRecord.end())
            followfocus->sendZoom(i.value());
    }
}

/**
 * @brief 光圈回放或记录
 * @param error 路径增量
 * @param time 帧编号
 */
void JScriptFollowFocus::irisPlayOrRecord(int error,qint64 time)
{
    JFollowfocus *followfocus = JFollowfocus::getInstance();
    if(mIrisMode == FollowFocusMode_PathRecord && error > 0)
    {
        if(time == 1)
        {
            irisPathRecord.clear();
        }
        if(error > 0)
        {
            if(!irisPathRecord.isEmpty())
            {
                if(irisPathRecord.last() != followfocus->getIris())
                    this->irisPathRecord.insert(pathLength,followfocus->getIris());
            }
            else
            {
                this->irisPathRecord.insert(pathLength,followfocus->getIris());
            }
        }
    }
    else if(mIrisMode == FollowFocusMode_PathPlay)
    {
        if(error > 0)
        {
            QMap<int,int>::iterator it = irisPathRecord.lowerBound(pathLength);
            if(it == irisPathRecord.end())
            {
                if(!irisPathRecord.isEmpty())
                    followfocus->sendIris((--it).value());
            }
            else
            {
                followfocus->sendIris(it.value());
            }
        }
        else
        {
            if(pathLength == 0)
                followfocus->sendIris(getIrisPathFirst());
        }
    }
    else if(mIrisMode == FollowFocusMode_TimeRecord)
    {
        if(time == 1)
        {
            irisTimeRecord.clear();
        }
        if(!irisTimeRecord.isEmpty())
        {
            if(irisTimeRecord.last() != followfocus->getIris())
                this->irisTimeRecord.insert(time,followfocus->getIris());
        }
        else
        {
            this->irisTimeRecord.insert(time,followfocus->getIris());
        }
    }
    else if(mIrisMode == FollowFocusMode_TimePlay)
    {
        QMap<qint64,int>::iterator i = irisTimeRecord.find(time);
        if(i != irisTimeRecord.end())
            followfocus->sendIris(i.value());
    }
}


}
