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
#ifndef JSCRIPTTURNPLATE_H
#define JSCRIPTTURNPLATE_H

#include "global.h"
#include <QObject>

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JScriptTurnplate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int acc WRITE setAcc READ getAcc NOTIFY accChanged)
    Q_PROPERTY(int dec WRITE setDec READ getDec NOTIFY decChanged)
    Q_PROPERTY(int speed WRITE setSpeed READ getSpeed NOTIFY speedChanged)
    Q_PROPERTY(int duration WRITE setDuration READ getDuration NOTIFY durationChanged)
    Q_PROPERTY(int direction WRITE setDirection READ getDirection NOTIFY directionChanged)
    Q_PROPERTY(int startTime WRITE setStartTime READ getStartTime NOTIFY startTimeChanged)


public:
    explicit JScriptTurnplate(QObject *parent = nullptr);
    ~JScriptTurnplate();

    void setAcc(int value);
    void setDec(int value);
    void setSpeed(int value);
    void setDuration(int value);
    void setDirection(int value);
    void setStartTime(int value);

    int getAcc() const {return mAcc;}
    int getDec() const {return mDec;}
    int getSpeed() const {return mSpeed;}
    int getDuration() const {return mDuration;}
    int getDirection() const {return mDirection;}
    int getStartTime() const {return mStartTime;}

private:
    //转盘全局视频参数
    int mAcc;
    int mDec;
    int mSpeed;
    int mDuration;
    int mDirection;
    int mStartTime;

signals:
    //转盘全局视频参数
    void accChanged();
    void decChanged();
    void speedChanged();
    void durationChanged();
    void directionChanged();
    void startTimeChanged();
};

}

#endif // JSCRIPTCAMERANODE_H
