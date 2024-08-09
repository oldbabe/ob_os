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
#ifndef JROBOT_H
#define JROBOT_H

#include "Core/jrobotarray.h"
#include "Studio/deviceabstrcat.h"
#include "global.h"

namespace jltmoco
{

//机械臂设备类
class AbstractRobot;
class DEVICECONTROLLER_EXPORT JRobot : public DeviceAbstract
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ getConnected NOTIFY connectedChanged)
    Q_PROPERTY(int runNumber READ getRunNumber NOTIFY runNumberChanged)
    Q_PROPERTY(JRobotArray* position READ getPosition CONSTANT)
    Q_PROPERTY(QString model READ getModel NOTIFY modelChanged)
    Q_PROPERTY(QString address WRITE setAddress READ getAddress NOTIFY addressChanged)
    Q_PROPERTY(QString railAddress WRITE setRailAddress READ getRailAddress NOTIFY railAddressChanged)

    Q_PROPERTY(bool caEnable READ getCaEnable NOTIFY caEnableChanged)
    Q_PROPERTY(CartesianPose *tool READ getTool CONSTANT FINAL)
    Q_PROPERTY(CartesianPose *world READ getWorld CONSTANT FINAL)
    Q_PROPERTY(CartesianPoseLoad *load READ getLoad CONSTANT FINAL)
    Q_PROPERTY(int installIndex WRITE setInstallIndex READ getInstallIndex NOTIFY installIndexChanged)
    Q_PROPERTY(int remoteType WRITE setRemoteType READ getRemoteType NOTIFY remoteTypeChanged)

signals:
    void addressChanged();
    void railAddressChanged();
    void connectedChanged();
    void runNumberChanged();
    void modelChanged();
    void railConnectedChanged(bool);
    void dataChanged(const QJsonObject &data,int index = -1);
    void coordinateChanged();
    void installIndexChanged();
    void caEnableChanged();
    void pluginMsgChanged(const QJsonObject &data);
    void remoteTypeChanged();

public:
    static JRobot* getInstance();
    ~JRobot();

    void init();
    void release();

    Q_INVOKABLE bool isArrived(const QJsonObject &target,int code = 5);
    Q_INVOKABLE void jogMovement(int code,const QJsonObject &data);
    Q_INVOKABLE void absPosMovement(const QJsonObject &data);
    Q_INVOKABLE void continueMovement(const QJsonObject &data);
    Q_INVOKABLE void continueMovementStart();
    Q_INVOKABLE void runStop();

    QJsonObject getStatusData();
    void setStatusData(const QJsonObject &obj);
    Q_INVOKABLE QJsonObject getStaticData();
    void setStaticData(const QJsonObject &obj);
    void pluginCallBack(const QJsonObject &obj);
    void setPluginConfig(const QJsonObject &metaData);

    void setConnected(bool value);
    void setModel(const QString &str);
    void setRunNumber(int value);
    void setAddress(const QString &str);
    void setRailAddress(const QString &str);

    bool getConnected() const{ return mConnected;}
    int getRunNumber() const{ return this->runNumber;}
    JRobotArray *getPosition() {return &mPosition;};
    QString getModel() {return mModel;}
    QString getAddress() {return mAddress;}
    QString getRailAddress() {return mRailAddress;}
    void pluginCommand(const QJsonObject &root);

    Q_INVOKABLE int installCount() const{return mInstallList.size();}
    Q_INVOKABLE JRobotInstall* installGet(int index){return mInstallList[index];}
    Q_INVOKABLE void installSave();
    Q_INVOKABLE void installUpdate(int index);
    Q_INVOKABLE void installApply(int index);
    Q_INVOKABLE void installReset(int index);
    QJsonObject installToJson(int index);
    void setInstallIndex(int index);
    int getInstallIndex(){return mInstallIndex;};
    CartesianPose *getTool(){return &mTool;};
    CartesianPose *getWorld(){return &mWorld;};
    CartesianPoseLoad *getLoad(){return &mLoad;};
    bool getCaEnable() const{return mCaEnable;};

    enum RemoteType
    {
        RemoteType_Axis = 2,
        RemoteType_World,
        RemoteType_Tool = 9
    };
    Q_ENUM(RemoteType)
    int getRemoteType() const {return mRemoteType;}
    void setRemoteType(int type);
    Q_INVOKABLE QList<int> getRemoteDirection();
    Q_INVOKABLE void saveRemoteDirection(QList<int> list);

public slots:
    void commandProcessing(const QJsonObject &obj);

private:
    static JRobot* handle;
    JRobot();

    void setCaEnable(bool value);
    void setRailConnected(bool value);
    void updateData(const QJsonObject &data);
    void sendData(const QJsonObject &data);

    AbstractRobot *pluginHandle;

    QString mAddress;
    QString mRailAddress;
    bool mCaEnable;
    bool mConnected;
    bool railConnected;
    int runNumber;
    int runNumberLast;
    JRobotArray mPosition;
    QString mModel;
    CartesianPose mTool;
    CartesianPose mWorld;
    CartesianPoseLoad mLoad;

    int mInstallIndex;
    QList<JRobotInstall* >mInstallList;
    int mRemoteType;
    QList<int> mDirectionList;
};

}

#endif // DEVICEMANAGER_H
