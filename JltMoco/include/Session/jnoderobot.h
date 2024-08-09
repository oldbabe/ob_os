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
#ifndef JNODEROBOT_H
#define JNODEROBOT_H

#include <QObject>
#include "global.h"
#include "Core/jrobotarray.h"

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JNodeRobot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int type WRITE setType READ getType NOTIFY typeChanged)
    Q_PROPERTY(int robotV WRITE setRobotV READ getRobotV NOTIFY robotVChanged)
    Q_PROPERTY(int robotA WRITE setRobotA READ getRobotA NOTIFY robotAChanged)
    Q_PROPERTY(int pathV WRITE setPathV READ getPathV NOTIFY pathVChanged)
    Q_PROPERTY(int pathA WRITE setPathA READ getPathA NOTIFY pathAChanged)
    Q_PROPERTY(int tsValue WRITE setTsValue READ getTsValue NOTIFY tsValueChanged)
    Q_PROPERTY(int waiting WRITE setWaiting READ getWaiting NOTIFY waitingChanged)
    Q_PROPERTY(int assistCA WRITE setAssistCA READ getAssistCA NOTIFY assistCAChanged)

    Q_PROPERTY(bool enable READ getEnable NOTIFY enableChanged)
    Q_PROPERTY(JRobotArray* target READ getTarget CONSTANT)
    Q_PROPERTY(JRobotArray* assist READ getAssist CONSTANT)
    Q_PROPERTY(CartesianPose *tool READ getTool CONSTANT FINAL)
    Q_PROPERTY(CartesianPose *world READ getWorld CONSTANT FINAL)
    Q_PROPERTY(CartesianPoseLoad *load READ getLoad CONSTANT FINAL)
    Q_PROPERTY(int frames WRITE setFrames READ getFrames NOTIFY framesChanged)

public:
    explicit JNodeRobot(QObject *parent = nullptr);
    ~JNodeRobot();

    enum RobotType
    {
        RobotType_PTP = 1,
        RobotType_Line,
        RobotType_Arc
    };
    Q_ENUM(RobotType)

    void updateEnable();
    void setEnable(bool enable);
    void setType(int value);
    void setRobotV(int value);
    void setRobotA(int value);
    void setPathV(int value);
    void setPathA(int value);
    void setTsValue(int value);
    void setWaiting(int value);
    void setAssistCA(int value);
    void setFrames(int value);

    bool getEnable() const {return mEnable;}
    int getType() const {return mType;}
    int getRobotV() const {return mRobotV;}
    int getRobotA() const {return mRobotA;}
    int getPathV() const {return mPathV;}
    int getPathA() const {return mPathA;}
    int getTsValue() const {return mTsValue;}
    int getWaiting() const {return mWaiting;}
    int getAssistCA() const {return mAssistCA;}
    int getFrames() const {return mFrames;}

    JRobotArray* getTarget(){return &mTarget;}
    JRobotArray* getAssist(){return &mAssist;}
    CartesianPose *getTool(){return &mTool;};
    CartesianPose *getWorld(){return &mWorld;};
    CartesianPoseLoad *getLoad(){return &mLoad;};

    QJsonObject toParamJson();
    QList<double> centerCircle3d(double x1, double y1, double z1,
                                             double x2, double y2, double z2,
                                             double x3, double y3, double z3);

private:
    bool mEnable;
    int mType;
    int mRobotV,mRobotA;
    int mPathV,mPathA;
    int mTsValue;
    int mWaiting;
    int mAssistCA;
    JRobotArray mTarget;
    JRobotArray mAssist;
    CartesianPose mTool;
    CartesianPose mWorld;
    CartesianPoseLoad mLoad;
    int mFrames;

signals:
    void enableChanged();
    void typeChanged();
    void robotVChanged();
    void robotAChanged();
    void pathVChanged();
    void pathAChanged();
    void tsValueChanged();
    void waitingChanged();
    void assistCAChanged();
    void framesChanged();

};

}

#endif // JSCRIPTMODEL_H
