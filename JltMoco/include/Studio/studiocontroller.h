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
#ifndef STUDIOCONTROLLER_H
#define STUDIOCONTROLLER_H

#include <QObject>
#include "global.h"

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT StudioController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ControllerType controllerType WRITE setControllerType READ getControllerType NOTIFY controllerTypeChanged)
signals:
    void controllerTypeChanged();
    void frameStatusDataChanged(const QJsonObject &status,int index = -1);

public:
    static StudioController* getInstance();

    Q_INVOKABLE void init();
    Q_INVOKABLE void release();

    Q_INVOKABLE QStringList ports();
    Q_INVOKABLE QString localHostName();

    enum ControllerType{
        LocalControllerOnly = 0,//仅本地控制器
        LocalControllerServer,//本地控制器+服务器
        RemoteControllerOnly //仅远程控制器
    };
    Q_ENUM(ControllerType)
    void sendCommandData(const QJsonObject &data);
    void setControllerType(ControllerType type);
    ControllerType getControllerType() const {return mControllerType;};

public slots:
    void onStudioClientDisconnected();
    void onStudioClientProcessing(const QJsonObject &obj);
    void onStudioServerProcessing(const QJsonObject &obj);
    void onStudioServerSocketChanged(int index);

protected:
    virtual void timerEvent(QTimerEvent *event) override;

private:
    static StudioController* handle;
    StudioController();

    ControllerType mControllerType;
    int loopTimerId;

};

}

#endif // STUDIOCONTROLLER_H
