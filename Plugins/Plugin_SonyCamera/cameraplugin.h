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
#ifndef CAMERAPLUGIN_H
#define CAMERAPLUGIN_H

#include "workerthread.h"
#include "abstractcamera.h"
#include <QObject>

namespace jltmoco
{

class CameraPlugin : public QObject, AbstractCamera
{
    Q_OBJECT
    Q_INTERFACES(jltmoco::AbstractCamera)
    Q_PLUGIN_METADATA(IID AbstractCamera_iid FILE "config.json")
signals:
    void deviceConnectedChanged(bool state);
    void deviceCompleteDownload(const QString &filename);
    void deviceContentsTransferChanged(int progress,const QString &filename);

public:
    CameraPlugin();

    virtual void registerFunc(std::function<void (const QJsonObject &)>);

    virtual void setup();
    virtual void uninstall();
    virtual void connect(bool flag = false);
    virtual bool isConnected();
    virtual void disconnect();
    virtual QJsonObject getStatusData();
    virtual void updatePropertys();
    virtual void parseUserCommand(const QJsonObject &cmd);

public slots:
    void mThreadCallbackChanged(const QJsonObject &data);

private:
    WorkerThread *mThread;
    std::function<void (const QJsonObject &)> cameraFunc;
};

}

#endif // CAMERAPLUGIN_H
