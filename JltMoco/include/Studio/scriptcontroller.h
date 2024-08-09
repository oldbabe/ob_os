/*
* 软件名称   BOBS 操作系统
* 版权所有   上海倔老头智能科技有限公司
* 本软件由上海倔老头智能科技有限公司开发并且开源 使用GPL V3（GNU General Public License） 开源协议
* 如收费请告知他人本软件可免费获得并说明收费缘由（如服务费）
* 联系方式
* vx 号    z1273305587
* 电话号   15536506659
* bilibili： 倔老头的会议室  UID: 3546726275221982
* 软件开源地址 https://github.com/oldbabe/ob_os
*
* Software name BOBS Operating system
*
* Copyright (C) 2024  Shanghai OldBaby technology Co., LTD
*
* This program is free software;you can redistribute it and/or modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation;either version 3 of the License, or (at your option) any later version.
*
* If there is a charge, please inform others that the software is available free of charge and explain the reason for the charge (e.g. service fee).
* Contact information
* Open source address https://github.com/oldbabe/ob_os
*/
#ifndef SCRIPTCONTROLLER_H
#define SCRIPTCONTROLLER_H

#include "jltmoco.h"
#include "Studio/deviceabstrcat.h"
#include "global.h"
#include <QJsonObject>
#include <QJsonArray>

namespace jltmoco
{

class FollowFocusBuffer
{
public:
    FollowFocusBuffer(double x = 0,double y = 0,double z = 0){
        this->mLength = 0;
        this->mX = x;
        this->mY = y;
        this->mZ = z;
        this->mUpdateEnable = false;
        this->mFocusValue = 3000;
        this->mZoomValue = 3000;
        this->mFocusMode = -1;
        this->mZoomMode = -1;
        this->mFocusMap.clear();
        this->mZoomMap.clear();
    }

    bool updateLength(double x,double y,double z)
    {
        if(!mUpdateEnable)
            return false;

        int len = mLength+qSqrt(qPow(x-mX,2)+qPow(y-mY,2)+qPow(z-mZ,2));
        if(len != mLength)
        {
            this->mLength = len;
            this->mX = x;
            this->mY = y;
            this->mZ = z;
            return true;
        }
        return false;
    }
    void insertFocusValue(int length,int value)
    {
        this->mFocusMap.insert(length,value);
    }
    void insertFocusValue(int value)
    {
        if(mUpdateEnable)
        {
            this->mFocusMap.insert(mLength,value);
        }
    }
    void insertZoomValue(int value)
    {
        if(mUpdateEnable)
        {
            this->mZoomMap.insert(mLength,value);
        }
    }
    void insertZoomValue(int length,int value)
    {
        this->mZoomMap.insert(length,value);
    }
    void insertIrisValue(int length,int value)
    {
        this->mIrisMap.insert(length,value);
    }
    void inserIrisValue(int value)
    {
        if(mUpdateEnable)
        {
            this->mIrisMap.insert(mLength,value);
        }
    }

    bool mUpdateEnable;
    int mLength;
    double mX,mY,mZ;
    int mFocusValue,mZoomValue,mFocusMode,mZoomMode,mIrisValue,mIrisMode;
    QMap<int,int> mFocusMap,mZoomMap,mIrisMap;
};

class DEVICECONTROLLER_EXPORT ScriptController : public DeviceAbstract
{
    Q_OBJECT
    Q_PROPERTY(quint64 frameCounter READ getFrameCounter NOTIFY frameCounterChanged)
    Q_PROPERTY(int index READ getExecIndex NOTIFY indexChanged)
signals:
    void frameCounterChanged();
    void indexChanged();
    void dataChanged(const QJsonObject &data,int index = -1);

public:
    static ScriptController* getInstance();

    QJsonObject getStatusData();
    void setStatusData(const QJsonObject &obj);
    void setStaticData(const QJsonObject &obj);
    void setExecIndex(int index);
    int getExecIndex() const {return execIndex;}

    void commandProcessing(const QJsonObject &obj);
    void frameUpdate();

    Q_INVOKABLE void nodeResetExec(int index,const QJsonObject &nodeData);
    Q_INVOKABLE void scriptExec(const QJsonObject &scriptData,int runmode = 1);
    Q_INVOKABLE void stopExec();

    void setFrameCounter(quint64 value);
    quint64 getFrameCounter() const{return frameCounter;}
    ScriptCommandCode getFrameCode() const{return frameCode;}

private:
    static ScriptController* handle;
    ScriptController();

    ScriptCommandCode frameCode;
    quint64 frameCounter;

    QJsonObject frameCmdObj;
    QList<DeviceNumber> deviceList;
    QMap<int,FollowFocusBuffer> mFollowFocusMap;

    int execIndex;
    int execRunmode;

    void setFrameCode(ScriptCommandCode code);
    void nodeResetProcessing();
    void nodeResetRobotEvent(quint64 frameNumber,const QJsonObject &nodeData);
    void nodeResetTurnplateEvent(quint64 frameNumber,const QJsonObject &nodeData);
    void nodeResetFollowFocusEvent(quint64 frameNumber,const QJsonObject &nodeData);
    void imgScriptExecProcessing();
    void movieScriptExecProcessing();
    void studioStop();

public slots:
    void onRobotRunNumberChanged();

};

}

#endif
