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
#ifndef JSCRIPTCAMERA_H
#define JSCRIPTCAMERA_H

#include "global.h"
#include <QObject>

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JScriptCamera : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int recordingDuration WRITE setRecordingDuration READ getRecordingDuration NOTIFY recordingDurationChanged)
    Q_PROPERTY(int moveDelay WRITE setMoveDelay READ getMoveDelay NOTIFY moveDelayChanged)

public:
    explicit JScriptCamera(QObject *parent = nullptr);
    ~JScriptCamera();

    void setRecordingDuration(int duration);
    void setMoveDelay(int mesc);

    int getMoveDelay() const {return mMoveDelay;}
    int getRecordingDuration() const {return mRecordingDuration;}

private:
    int mRecordingDuration;
    int mMoveDelay;

signals:
    void recordingDurationChanged();
    void moveDelayChanged();

};

}

#endif // JNODECAMERA_H