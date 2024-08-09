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
#ifndef JCAMERAINSTALL_H
#define JCAMERAINSTALL_H

#include "global.h"
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JCameraInstall : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex WRITE setCurrentIndex READ getCurrentIndex NOTIFY currentIndexChanged)

public:
    static JCameraInstall* getInstance();

    void release();
    void setCurrentIndex(int index);
    int getCurrentIndex() const {return mCurrentIndex;};

    Q_INVOKABLE int count(const QString &cameaName) const;
    Q_INVOKABLE void init(const QString &cameaName);
    Q_INVOKABLE QJsonObject get(const QString &cameaName,int index);
    Q_INVOKABLE void setTitle(const QString &cameaName,int index,const QString &title);
    Q_INVOKABLE void setProperty(const QString &cameaName,int index,int key,int writable,const QString &value);
    Q_INVOKABLE QJsonArray getProperty(const QString &cameaName,int index);
    Q_INVOKABLE void apply(const QString &cameaName,int index);
    Q_INVOKABLE QStringList getDownLoadList();
    Q_INVOKABLE void setDownLoadList(const QStringList &list);
    Q_INVOKABLE bool pathExists(const QString &path);

private slots:
    void onTimeout();

private:
    static JCameraInstall* handle;
    JCameraInstall();

    int mCurrentIndex;
    QTimer *mTimer;
    QJsonArray mProps;

signals:
    void currentIndexChanged();
    void finished();
    void started();

};



}

#endif // DEVICEMANAGER_H
