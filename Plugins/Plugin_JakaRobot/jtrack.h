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
#ifndef JTRACK_H
#define JTRACK_H

#include <QTcpSocket>

namespace jltmoco
{
enum RaileMode
{
    RaileMode_Enable = 0x01,
    RaileMode_DisEnable, //下使能
    RaileMode_SetZero,  //设置零点
    RaileMode_SerZeroAbs,//绝对运动复位
    RaileMode_Reset,    //复位
    RaileMode_Motion    //运动
};

enum RaileMotionMode
{
    RaileMotionMode_Jog_Add = 0x01,    //手动前进
    RaileMotionMode_Jog_Sub,    //手动后退
    RaileMotionMode_Relative,   //相对运动
    RaileMotionMode_Absolute,   //绝对运动
    RaileMotionMode_Stop,   //停止
};

class JTrack : public QTcpSocket
{
    Q_OBJECT
public:
    static JTrack* getInstance();
    ~JTrack();

    QList<QJsonObject >dataList;
    void startMonitor();
    void stopMonitor();

    int railEnable;
    int railAbsState;
    int railTsState;
    float railPosition;
    float railTarget;
    float railContinueMoveError;

    void railAutoEnable();
    void railJogMove(float speed);
    void railAbsMove(const QJsonObject &dataObj);
    bool railContinueMoveResult();
    void railContinueMove(const QJsonObject &node);

    float arrayToFloat(const QByteArray &array,int index);
    QByteArray floatToArray(const float &value);
    void sendModeBuffer(quint8 mode);
    void sendMotionBuffer(quint8 mode,float pos = 0,float speed = 0,float tv = 0);

private:
    static JTrack* handle;
    JTrack();
    bool mMonitorState;
    double mSetPosition;
    void monitor();

private slots:
    void onReadyRead();

};

}

#endif // RAILSOCKET_H
