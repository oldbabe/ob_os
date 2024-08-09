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
#ifndef JGAMEPAD_H
#define JGAMEPAD_H

#include <QObject>
#include "global.h"

#include <qt_windows.h>
#include <XInput.h>


typedef DWORD (__stdcall *XInputGetStateEx_t) (DWORD, XINPUT_STATE*);
typedef DWORD (__stdcall *XInputSetState_t) (DWORD, XINPUT_VIBRATION *);

namespace jltmoco
{


class DEVICECONTROLLER_EXPORT JGamepad : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ getConnected NOTIFY connectedChanged)
signals:
    //! 连接状态改变
    void connectedChanged();
    //! 状态数据改变
    void statusChanged(const QJsonObject &obj);

public:
    static JGamepad* getInstance();

    Q_INVOKABLE void init();
    Q_INVOKABLE void release();

    void setConnected(bool value);
    bool getConnected() const;


protected:
    virtual void timerEvent(QTimerEvent *event);

private:
    static JGamepad* handle;
    JGamepad();

    XInputGetStateEx_t XInputGetStateEx;
    XInputSetState_t XInputSetState;

    bool connected;
    int gamepadTimerId;
    QList<double> cmdList;
    double thumbRange(double value);
    double thumbRangeLow(double value);
    void setButtonY(bool state);
    void setButtonB(bool state);
    void setButtonA(bool state);
    void setCmdList(const QList<double> &cmd);

    double deadzoneX = 0.10f;//死区
    double deadzoneY = 0.10f;//死区
    void sendButtonPressedSignals(int number);
    void LeftThumbStick(double LX, double LY);
    void RightThumbStick(double RX, double RY);
    void VibrateController(short uID, WORD LeftMotorSpeed, WORD RightMotorSpeed);

    enum GamePad_ButtonCode
    {
        GamePad_up = 1,
        GamePad_down = 2,
        GamePad_left = 4,
        GamePad_right = 8,
        GamePad_start = 16,
        GamePad_back = 32,
        GamePad_ltdown = 64,
        GamePad_rtdown = 128,
        GamePad_lbump = 256,
        GamePad_rbump = 512,
        GamePad_guide = 1024,

        GamePad_a = 4096,
        GamePad_b = 8192,
        GamePad_x = 16384,
        GamePad_y = 32768
    };

    double axisLeftX;
    double axisLeftY;
    double axisRightX;
    double axisRightY;

    bool   buttonL1;
    double buttonL2;
    bool   buttonL3;

    bool   buttonR1;
    double buttonR2;
    bool   buttonR3;

    bool buttonA;
    bool buttonB;
    bool buttonX;
    bool buttonY;

    bool buttonBack;
    bool buttonStart;

    bool buttonDown;
    bool buttonLeft;
    bool buttonRight;
    bool buttonUp;
};

}

#endif // JGAMEPAD_H
