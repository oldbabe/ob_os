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

Canvas
{
    id: control

    implicitHeight: 30
    implicitWidth: 30

    property string toolText: "数据更新"
    property color runColor: "lawngreen"
    property color runHoverColor: "honeydew"
    property color disableColor: "#303030"

    signal buttonClick();

    ToolTip.visible: enabled&&mouseArea.containsMouse
    ToolTip.text: toolText

    onEnabledChanged: requestPaint();

    onPaint:
    {
        var ctx = getContext("2d");
        ctx.clearRect(0,0,width,height);
        ctx.lineWidth = 2;
        ctx.strokeStyle = (!control.enabled)?disableColor:mouseArea.containsMouse?runHoverColor:runColor;
        ctx.beginPath();
        ctx.moveTo(5,height/2);
        ctx.lineTo(7,height/2);
        ctx.lineTo(5,height/2-4);
        ctx.lineTo(3,height/2);
        ctx.lineTo(5,height/2);
        ctx.stroke();
        ctx.beginPath();
        ctx.arc(width/2,height/2,10,0.78,3.14,false);
        ctx.stroke();
        ctx.moveTo(width/2+10,height/2);
        ctx.lineTo(width/2+12,height/2);
        ctx.lineTo(width/2+10,height/2+4);
        ctx.lineTo(width/2+8,height/2);
        ctx.lineTo(width/2+10,height/2);
        ctx.stroke();
        ctx.beginPath();
        ctx.arc(width/2,height/2,10,3.93,6.28,false);
        ctx.stroke();
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onContainsMouseChanged: control.requestPaint();
        onClicked: control.buttonClick();
    }
}
