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
#ifndef STUDIOCLIENT_H
#define STUDIOCLIENT_H

#include "jltmoco.h"
#include "NetWork/studiosocket.h"
#include "../global.h"
#include <QJsonObject>

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT StudioClient : public StudioSocket
{
    Q_OBJECT
    Q_PROPERTY(int connected READ getConnected NOTIFY connectedChanged)
    Q_PROPERTY(StudioCtrlCode studioCtrlState READ getStudioCtrlState NOTIFY studioCtrlStateChanged)

    Q_PROPERTY(QString serverAddr WRITE setServerAddr READ getServerAddr NOTIFY serverAddrChanged)
    Q_PROPERTY(int number WRITE setNumber READ getNumber NOTIFY numberChanged)
    Q_PROPERTY(int type WRITE setType READ getType NOTIFY typeChanged)

signals:
    void typeChanged();
    void numberChanged();
    void serverAddrChanged();
    void connectedChanged();
    void studioCtrlStateChanged();
    void followFoucsTimerChanged();

public:
    static StudioClient* getInstance();

    Q_INVOKABLE void init();
    Q_INVOKABLE void release();
    Q_INVOKABLE void connectServer(const QString &addr);
    Q_INVOKABLE void disConnectServer();
    int getConnected();

    void setServerAddr(const QString &addr);
    QString getServerAddr();
    void setNumber(int value);
    int getNumber() const;
    void setType(int value);
    int getType() const;

    void setStudioCtrlState(StudioCtrlCode);
    StudioCtrlCode getStudioCtrlState() const;

    Q_INVOKABLE bool isTargetPos(const QJsonObject &nodeItem);
    Q_INVOKABLE int nodeReset(int number,const QJsonObject &obj);
    Q_INVOKABLE int scriptRun(const QJsonObject &obj,int runmode = 1,int followfocusmode = 1);
    Q_INVOKABLE void studioRunJogStop();

    Q_INVOKABLE void setJsonConfig(const QString &key,const QJsonObject &obj);
    Q_INVOKABLE QJsonObject getJsonConfig(const QString &key) const;

    Q_INVOKABLE void sendRemoteCommand(const QJsonObject &jsobject);

public slots:
    void onSendData(const QJsonObject &data);

private slots:
    void onSocketStateChanged(int );

private:
    static StudioClient* handle;
    StudioClient();
    int connected;
    void setConnected(int value);

    StudioCtrlCode studioCtrlState;
};


}


#endif // STUDIOCLIENT_H
