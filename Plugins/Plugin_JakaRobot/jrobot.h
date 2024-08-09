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

#include <QObject>
#include <JAKAZuRobot.h>

namespace jltmoco
{

class JakaPlugin;
class JRobot : public QObject
{
    Q_OBJECT
signals:
    void taskChanged(const QJsonObject &task);

public:
    static JRobot* getInstance();
    ~JRobot();

    void closeRobot();
    bool connected;
    QJsonObject getStatus();
    JAKAZuRobot *getRobot(){return&mJakaRobot;}
    void setRobotPlugin(JakaPlugin *plugin);
    void robotCallback(int code);

    void moveStop();
    void jogDataUpdate(int type,const QJsonObject &obj);

    void absPosMove(const QJsonObject &dataObj);
    void absAxisMove(const QJsonObject &dataObj);
    void setToolCoord(const QJsonObject &dataObj);
    void setBaseCoord(const QJsonObject &dataObj);
    void setPayload(const QJsonObject &dataObj);

    QList<QJsonObject >dataList;

public slots:
    void onTaskChanged(const QJsonObject &task);

private:
    static JRobot* handle;
    JRobot();

    JakaPlugin *robotPlugin;

    QList<QJsonObject> mTaskList;
    JAKAZuRobot mJakaRobot;
    CartesianPose mWorld,mTool;
    PayLoad mLoad;
    CartesianPose mPosition;

    int mServoState;
    int mJogType;
    CartesianPose mJogPosData;
    JointValue mJogAxisData;
    void jogLoop();

    bool monitorRunning;
    int mRunLine;
    int mMonitorLine;
    int mStopInterval;

    void monitorLoop();
    void sendNodeFirst();
    void setRunLine(int startLine,int line);

};

}

#endif // JROBOT_H
