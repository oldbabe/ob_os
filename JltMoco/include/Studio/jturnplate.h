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
#ifndef JTURNPLATE_H
#define JTURNPLATE_H

#include "Studio/deviceabstrcat.h"
#include "global.h"

namespace jltmoco
{

class AbstractTurnplate;
class DEVICECONTROLLER_EXPORT JTurnplate : public DeviceAbstract
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ getConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString angle READ getAngle NOTIFY angleChanged)
    Q_PROPERTY(QString portName WRITE setPortName READ getPortName NOTIFY portNameChanged)

signals:
    void connectedChanged();
    void angleChanged();
    void portNameChanged();
    void dataChanged(const QJsonObject &data,int index = -1);

public:
    static JTurnplate* getInstance();

    void init();
    void release();

    QJsonObject getStatusData();
    void setStatusData(const QJsonObject &obj);
    void setStaticData(const QJsonObject &obj);
    bool getConnected() const;

    void commandProcessing(const QJsonObject &obj);
    bool isArrived(const QString &target);
    void runStop();
    void absMove(float target,int spped,int acc,int dec);
    void speedMove(int direction,int spped,int acc,int dec);

    void setAngle(const QString &value);
    QString getAngle() const {return angle;};
    void setPortName(const QString &name);
    QString getPortName() const {return mPortName;};

private:
    static JTurnplate* handle;
    JTurnplate();

    AbstractTurnplate *pluginHandle;
    bool connected;
    QString mPortName;
    QString angle;
    void setConnected(bool value);
    void sendData(const QJsonObject &data);
};

}

#endif // DEVICEMANAGER_H
