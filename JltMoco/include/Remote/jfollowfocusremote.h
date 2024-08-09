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
#ifndef JFOLLOWFOCUSREMOTE_H
#define JFOLLOWFOCUSREMOTE_H

#include <QObject>
#include "global.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JFollowfocusRemote : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ getConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString portName WRITE setPortName READ getPortName NOTIFY portNameChanged)
    Q_PROPERTY(int focus READ getFocus NOTIFY focusChanged)
    Q_PROPERTY(int zoom READ getZoom NOTIFY zoomChanged)
    Q_PROPERTY(int iris READ getIris NOTIFY irisChanged)

signals:
    void connectedChanged();
    void portNameChanged();
    void focusChanged();
    void zoomChanged();
    void irisChanged();

public:
    static JFollowfocusRemote* getInstance();

    Q_INVOKABLE void setup();
    Q_INVOKABLE void uninstall();

    void setPortName(const QString &name);
    void setFocus(int value);
    void setZoom(int value);
    void setIris(int value);

    bool getConnected() const;
    QString getPortName() const { return this->mPortName;}
    int getFocus() const { return this->mFocus;}
    int getZoom() const { return this->mZoom;}
    int getIris() const { return this->mIris;}

private slots:
    void onReadyRead();

private:
    static JFollowfocusRemote* handle;
    JFollowfocusRemote();
    QString mPortName;
    int mFocus;
    int mZoom;
    int mIris;

    QSerialPort *mPort;
    QByteArray dataBuffer;

    void parseDataBuffer();
    void parsePos(const QByteArray &array);

};
}

#endif // JFOLLOWFOCUSREMOTE_H
