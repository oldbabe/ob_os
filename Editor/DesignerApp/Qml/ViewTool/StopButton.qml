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
import JMoco 1.0

Rectangle
{
    id: root
    radius: 3
    opacity: 0.9
    implicitHeight: 30
    implicitWidth: 100

    Component.onCompleted:
    {
        root.color = Qt.binding(function(){
            if(JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
            {
                return mouseArea.containsMouse?"darkred":"brown";
            }
            else
            {
                return "#595959";
            }
        });
    }

    Text
    {
        anchors.centerIn: parent
        text: qsTr("停止运行")
        color: "black"
        font.pixelSize: 16
        font.bold: true
    }
    MouseArea
    {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked:
        {
            if(JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
            {
                JSession.currentScript.stopRun();
            }
        }
    }
}
