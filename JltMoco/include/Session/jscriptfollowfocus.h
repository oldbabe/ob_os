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
#ifndef JSCRIPTFOLLOWFOCUS_H
#define JSCRIPTFOLLOWFOCUS_H

#include "global.h"
#include <QObject>
#include <QJsonObject>

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JScriptFollowFocus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(FollowFocusMode focusMode WRITE setFocusMode READ getFocusMode NOTIFY focusModeChanged)
    Q_PROPERTY(FollowFocusMode zoomMode WRITE setZoomMode READ getZoomMode NOTIFY zoomModeChanged)
    Q_PROPERTY(FollowFocusMode irisMode WRITE setIrisMode READ getIrisMode NOTIFY irisModeChanged)

    Q_PROPERTY(int focusValue WRITE setFocusValue READ getFocusValue NOTIFY focusValueChanged)
    Q_PROPERTY(int zoomValue WRITE setZoomValue READ getZoomValue NOTIFY zoomValueChanged)
    Q_PROPERTY(int irisValue WRITE setIrisValue READ getIrisValue NOTIFY irisValueChanged)

public:
    explicit JScriptFollowFocus(QObject *parent = nullptr);
    ~JScriptFollowFocus();

    enum FollowFocusMode
    {
        FollowFocusMode_Coonstant = 0,  //恒定值
        FollowFocusMode_OnlyRemote, //仅遥控
        FollowFocusMode_PathRecord,  //路径记录
        FollowFocusMode_PathPlay,  //路径回放
        FollowFocusMode_TimeRecord,  //时间记录
        FollowFocusMode_TimePlay  //时间回放
    };
    Q_ENUM(FollowFocusMode)

    void setFocusMode(FollowFocusMode mode);
    void setZoomMode(FollowFocusMode mode);
    void setIrisMode(FollowFocusMode mode);
    void setFocusValue(int value);
    void setZoomValue(int value);
    void setIrisValue(int value);
    void setPathRecord(const QJsonObject &record);
    void setTimeRecord(const QJsonObject &record);

    FollowFocusMode getFocusMode() const {return mFocusMode;}
    FollowFocusMode getZoomMode() const {return mZoomMode;}
    FollowFocusMode getIrisMode() const {return mIrisMode;}
    int getFocusValue() const {return mFocusValue;}
    int getZoomValue() const {return mZoomValue;}
    int getIrisValue() const {return mIrisValue;}
    int getFocusPathFirst();
    int getZoomPathFirst();
    int getIrisPathFirst();
    int getFocusTimeFirst();
    int getZoomTimeFirst();
    int getIrisTimeFirst();

    QJsonObject toJson();

private slots:
    void onStateChanged();
    void onFrameCounterChanged();

private:
    FollowFocusMode mFocusMode;
    FollowFocusMode mZoomMode;
    FollowFocusMode mIrisMode;
    int mFocusValue;
    int mZoomValue;
    int mIrisValue;

    qint64 pathLength;
    void focusPlayOrRecord(int error,qint64 time);
    void zoomPlayOrRecord(int error,qint64 time);
    void irisPlayOrRecord(int error,qint64 time);

    QMap<int,int> focusPathRecord;
    QMap<int,int> zoomPathRecord;
    QMap<int,int> irisPathRecord;

    QMap<qint64,int> focusTimeRecord;
    QMap<qint64,int> zoomTimeRecord;
    QMap<qint64,int> irisTimeRecord;

signals:
    void focusValueChanged();
    void zoomValueChanged();
    void irisValueChanged();
    void focusModeChanged();
    void zoomModeChanged();
    void irisModeChanged();

};

}

#endif // JSCRIPTCAMERANODE_H
