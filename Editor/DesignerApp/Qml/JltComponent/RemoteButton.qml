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
import QtQuick 6.2
import QtQuick.Controls 6.2

Control
{
    id: control

    implicitHeight: 30
    implicitWidth: 30

    property int buttonType: 0//=0
    property string toolText: ""
    property string setText: ""
    property color runColor: "lawngreen"
    property color runHoverColor: "honeydew"
    property color disableColor: "#303030"
    property bool resetFlag: false

    signal buttonClick();
    signal containsChanged(bool state);

    ToolTip.visible: enabled&&mouseArea.containsMouse
    ToolTip.text: toolText

    onEnabledChanged: canvas.requestPaint();
    onResetFlagChanged: canvas.requestPaint();

    background: Canvas
    {
        id: canvas
        onPaint:
        {
            var ctx = getContext("2d");
            ctx.lineCap = "square";
            ctx.clearRect(0,0,width,height);

            if(control.buttonType === 0)
            {
                ctx.beginPath();
                ctx.moveTo(5, 5);
                ctx.lineTo(5, height-5);
                ctx.lineTo(width-5, height/2);
                ctx.lineTo(5, 5);
                if(control.resetFlag)
                {
                    ctx.arc(width/6*5,height/6*5,width/12,0,6.28,false);
                }
                ctx.closePath();
            }
            else if(control.buttonType === 1)
            {
                ctx.beginPath();
                ctx.moveTo(5, 5);
                ctx.lineTo(5, height-5);
                ctx.lineTo(12, height-10);
                ctx.lineTo(12, height-5);
                ctx.lineTo(width-5, height/2);
                ctx.lineTo(12, 5);
                ctx.lineTo(12, 10);
                ctx.lineTo(5, 5);
                ctx.closePath();
            }
            else if(control.buttonType === 2)
            {
                ctx.beginPath();
                ctx.moveTo(width-5, 5);
                ctx.lineTo(width-5, height-5);
                ctx.lineTo(width-12, height-10);
                ctx.lineTo(width-12, height-5);
                ctx.lineTo(5, height/2);
                ctx.lineTo(width-12, 5);
                ctx.lineTo(width-12, 10);
                ctx.lineTo(width-5, 5);
                ctx.closePath();
            }
            else if(control.buttonType === 3)
            {
                ctx.beginPath();
                ctx.moveTo(5, 5);
                ctx.lineTo(5, height-5);
                ctx.lineTo(width-10, height/2);
                ctx.lineTo(5, 5);
                ctx.closePath();
                ctx.rect(width-8,5,3,height-10);
            }
            else if(control.buttonType === 4)
            {
                ctx.beginPath();
                ctx.moveTo(width-5, 5);
                ctx.lineTo(width-5, height-5);
                ctx.lineTo(10, height/2);
                ctx.lineTo(width-5, 5);
                ctx.closePath();
                ctx.rect(5,5,3,height-10);
            }
            else if(control.buttonType === 5)
            {
                ctx.beginPath();
                ctx.moveTo(width-5, 5);
                ctx.lineTo(width-5, height-5);
                ctx.lineTo(5, height/2);
                ctx.lineTo(width-5, 5);
                ctx.closePath();
            }
            ctx.fillStyle = (!control.enabled)?disableColor:mouseArea.containsMouse?runHoverColor:runColor;
            ctx.fill();

        }
    }
    contentItem: Text
    {
        text: setText
        color: control.enabled?"floralwhite":disableColor
        font.pixelSize: 7
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignRight
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onContainsMouseChanged: canvas.requestPaint();
        onEntered: control.containsChanged(true);
        onExited: control.containsChanged(false);
        onPositionChanged: control.containsChanged(true);
        onClicked: control.buttonClick();
    }
}
