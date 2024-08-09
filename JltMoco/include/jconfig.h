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
#ifndef JCONFIG_H
#define JCONFIG_H


#include <QSettings>
#include <QJsonObject>
#include "global.h"


namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JConfig : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(QString serverAddr WRITE setServerAddr READ getServerAddr NOTIFY serverAddrChanged)
    Q_PROPERTY(QString robotAddr WRITE setRobotAddr READ getRobotAddr NOTIFY robotAddrChanged)
    Q_PROPERTY(QString railAddr WRITE setRailAddr READ getRailAddr NOTIFY railAddrChanged)
    Q_PROPERTY(int number WRITE setNumber READ getNumber NOTIFY numberChanged)
    Q_PROPERTY(int type WRITE setType READ getType NOTIFY typeChanged)
    Q_PROPERTY(QString turnplatePortName WRITE setTurnplatePortName READ getTurnplatePortName NOTIFY turnplatePortNameChanged)
    Q_PROPERTY(QString railDeviceAddr WRITE setRailDeviceAddr READ getRailDeviceAddr NOTIFY railDeviceAddrChanged)

signals:
    void typeChanged();
    void numberChanged();
    void serverAddrChanged();
    void robotAddrChanged();
    void railAddrChanged();
    void railDeviceAddrChanged();
    void turnplatePortNameChanged();

public:
    static JConfig* getInstance();
    ~JConfig(){};

    void setServerAddr(const QString &addr,bool enable = true);
    QString getServerAddr();
    void setRobotAddr(const QString &addr,bool enable = true);
    QString getRobotAddr();
    void setRailAddr(const QString &addr,bool enable = true);
    QString getRailAddr();
    void setRailDeviceAddr(const QString &,bool enable = true);
    QString getRailDeviceAddr() const;

    void setNumber(int value,bool enable = true);
    int getNumber() const;
    void setType(int value,bool enable = true);
    int getType() const;

    void setTurnplatePortName(const QString &,bool enable = true);
    QString getTurnplatePortName() const;

    Q_INVOKABLE void setJsonConfig(const QString &key,const QJsonObject &obj);
    Q_INVOKABLE QJsonObject getJsonConfig(const QString &key) const;

private:
    static JConfig* handle;
    JConfig(const QString &fileName, QSettings::Format format, QObject *parent = nullptr);

    QString mServerAddr;
    QString mRobotAddr;
    QString mRailAddr;
    QString mRailDeviceAddr;
    int mNumber;
    int mType;

    QString mFollowfocusPortName;
    QString mTurnplatePortName;

};


}


#endif // JConfig_H
