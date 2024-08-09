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
#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "cameradefined.h"
#include <QJsonObject>
#include <QThread>

namespace jltmoco
{

class CameraDevice;
class WorkerThread : public QThread
{
    Q_OBJECT
signals:
    void callbackChanged(const QJsonObject &data);

public:
    WorkerThread();

    void runStart();
    void runStop();
    void appendCommand(const QJsonObject &cmd);
    void callbackMsg(QJsonObject &data);
    QJsonObject getStatusData() const{return statusJson;};

    void setTransferState(int state,const QString &fileName);

protected:
    virtual void run();

private:
    bool runFlag;
    bool connected;
    int connectedMode;
    QJsonObject statusJson;
    QList<QJsonObject> commandList;
    QString downloadDir;
    int mTransferState;
    bool realTimeImageEnable;

    void setDataState(DeviceStatus state);

    void execCommand(CameraDevice *camera);
    void execPropSetting(CameraDevice *camera,const QJsonObject &obj);
    void execSetDownloadDirectory(CameraDevice *camera,const QString &dir);
    void execShooting(CameraDevice *camera,int mode);
    void execDownloadEndFile(CameraDevice *camera);
    void execRealTimeImageDownload(CameraDevice *camera,const QString &fileName);
    void execSetFocusPosition(CameraDevice *camera,qreal x,qreal y,int mode);
    void execGetRealTimeImage(CameraDevice *camera);
};

}

#endif // WORKERTHREAD_H
