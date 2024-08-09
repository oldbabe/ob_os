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
#ifndef JGLOBALREMOTEPARAM_H
#define JGLOBALREMOTEPARAM_H

#include <QObject>
#include <QVector3D>
#include "../global.h"

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JGlobalRemoteParam : public QObject
{
    Q_OBJECT
    //脚本遥控数据
    Q_PROPERTY(int robotPrgV WRITE setRobotPrgV READ getRobotPrgV NOTIFY robotPrgVChanged)
    Q_PROPERTY(int robotV WRITE setRobotV READ getRobotV NOTIFY robotVChanged)
    Q_PROPERTY(int robotA WRITE setRobotA READ getRobotA NOTIFY robotAChanged)
    Q_PROPERTY(int railV WRITE setRailV READ getRailV NOTIFY railVChanged)
    Q_PROPERTY(int railA WRITE setRailA READ getRailA NOTIFY railAChanged)
    Q_PROPERTY(int turnplateV WRITE setTurnplateV READ getTurnplateV NOTIFY turnplateVChanged)
    Q_PROPERTY(int turnplateA WRITE setTurnplateA READ getTurnplateA NOTIFY turnplateAChanged)
    Q_PROPERTY(QVector3D cameraPosition WRITE setCameraPosition READ getCameraPosition NOTIFY cameraPositionChanged)
    Q_PROPERTY(QVector3D cameraEulerRotation WRITE setCameraEulerRotation READ getCameraEulerRotation NOTIFY cameraEulerRotationChanged)

signals:
    void robotPrgVChanged();
    void robotVChanged();
    void robotAChanged();
    void railVChanged();
    void railAChanged();
    void turnplateVChanged();
    void turnplateAChanged();
    void cameraPositionChanged();
    void cameraEulerRotationChanged();

public:
    static JGlobalRemoteParam* getInstance();
    ~JGlobalRemoteParam(){}

    QJsonObject toRobotParamJson();

    void setCameraPosition(const QVector3D &vec);
    void setCameraEulerRotation(const QVector3D &vec);
    QVector3D getCameraPosition() const {return mCameraPosition;}
    QVector3D getCameraEulerRotation() const {return mCameraEulerRotation;}

    void setRobotPrgV(int value);
    void setRobotV(int value);
    void setRobotA(int value);
    void setRailV(int value);
    void setRailA(int value);
    void setTurnplateV(int value);
    void setTurnplateA(int value);

    int getRobotPrgV() {return mRobotPrgV;}
    int getRobotV() {return mRobotV;}
    int getRobotA() {return mRobotA;}
    int getRailV() {return mRailV;}
    int getRailA() {return mRailA;}
    int getTurnplateV() {return mTurnplateV;}
    int getTurnplateA() {return mTurnplateA;}

private:
    static JGlobalRemoteParam* handle;
    JGlobalRemoteParam();
    QVector3D mCameraPosition;
    QVector3D mCameraEulerRotation;

    int mRobotPrgV;
    int mRobotV;
    int mRobotA;
    int mRailV;
    int mRailA;
    int mTurnplateV;
    int mTurnplateA;

};

}

#endif // JROBOTARRAY_H
