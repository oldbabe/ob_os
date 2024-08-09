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
#ifndef JFOLLOWFOCUS_H
#define JFOLLOWFOCUS_H

#include "Studio/deviceabstrcat.h"
#include "global.h"

namespace jltmoco
{

class AbstractFllowFocus;
class DEVICECONTROLLER_EXPORT JFollowfocus : public DeviceAbstract
{
    Q_OBJECT
    Q_PROPERTY(QString portName WRITE setPortName READ getPortName NOTIFY portNameChanged)
    Q_PROPERTY(bool connected READ getConnected NOTIFY connectedChanged)
    Q_PROPERTY(int focus WRITE setFocus READ getFocus NOTIFY focusChanged)
    Q_PROPERTY(int zoom WRITE setZoom READ getZoom NOTIFY zoomChanged)
    Q_PROPERTY(int iris WRITE setIris READ getIris NOTIFY irisChanged)
    Q_PROPERTY(bool focusEnable WRITE setFocusEnable READ getFocusEnable NOTIFY focusEnableChanged)
    Q_PROPERTY(bool zoomEnable WRITE setZoomEnable READ getZoomEnable NOTIFY zoomEnableChanged)
    Q_PROPERTY(bool irisEnable WRITE setIrisEnable READ getIrisEnable NOTIFY irisEnableChanged)

signals:
    void portNameChanged();
    void connectedChanged();
    void focusChanged();
    void zoomChanged();
    void irisChanged();
    void focusEnableChanged();
    void zoomEnableChanged();
    void irisEnableChanged();

    void dataChanged(const QJsonObject &data,int index = -1);

public:
    static JFollowfocus* getInstance();

    void init();
    void release();

    QJsonObject getStatusData();
    void setStatusData(const QJsonObject &obj);
    void setStaticData(const QJsonObject &obj);
    bool getConnected() const{return mConnected;}

    void commandProcessing(const QJsonObject &obj);

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();
    Q_INVOKABLE void calibrateDevice();
    Q_INVOKABLE void remoteValues(int f,int z = -1,int i = -1);
    void allRemote(int f,int z,int i);

    void setConnected(bool value);
    void setPortName(const QString &name);
    QString getPortName() const;
    void setFocus(int value);
    void setZoom(int value);
    void setIris(int value);
    void updateFocus(int value);
    void updateZoom(int value);
    void updateIris(int value);
    void setFocusEnable(bool value);
    void setZoomEnable(bool value);
    void setIrisEnable(bool value);
    void updateFocusEnable(bool value);
    void updateZoomEnable(bool value);
    void updateIrisEnable(bool value);

    int getFocus() const{return mFocusValue;};
    int getZoom() const{return mZoomValue;};
    int getIris() const{return mIrisValue;};
    bool getFocusEnable() const{return mFocusEnable;};
    bool getZoomEnable() const{return mZoomEnable;};
    bool getIrisEnable() const{return mIrisEnable;};


    void sendFocus(int value);
    void sendZoom(int value);
    void sendIris(int value);

private:
    static JFollowfocus* handle;
    JFollowfocus();

    AbstractFllowFocus *pluginHandle;
    int mFocusValue,mZoomValue,mIrisValue;
    bool mFocusEnable,mZoomEnable,mIrisEnable;

    QString mPortName;
    bool mConnected;
    void sendRemoteValue(int code,int value = -1);
    void sendValueEnable(int code,bool enable);
};

}

#endif // DEVICEMANAGER_H
