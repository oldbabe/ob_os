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

Item
{
    implicitHeight: 40
    implicitWidth: remoteItem.width+studioTimerItem.width+interval.width+scriptTimerItem.width+10

    Rectangle
    {
        id: remoteItem
        radius: 3
        color: "#303030"
        height: parent.height
        width: nodeAssistItem.width+nodeTargetItem.width+15
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        NodeAssistItem
        {
            id: nodeAssistItem
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
        }
        NodeTargetItem
        {
            id: nodeTargetItem
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: nodeAssistItem.right
            anchors.leftMargin: 5
        }
    }
    StudioTimerItem
    {
        id: studioTimerItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: remoteItem.right
        anchors.leftMargin: 5
        Connections
        {
            target: JScriptController
            function onFrameCounterChanged()
            {
                var msec = JScriptController.frameCounter*10;
                var hours = Math.floor(msec / 3600000);
                studioTimerItem.hourItem.text = hours < 10 ? "0" + hours : hours;
                var minutes = Math.floor((msec % 3600000) / 60000);
                studioTimerItem.minuteItem.text = minutes < 10 ? "0" + minutes : minutes;
                var seconds = Math.floor(((msec % 3600000) % 60000) / 1000);
                studioTimerItem.secItem.text = seconds < 10 ? "0" + seconds : seconds;
                var mseconds = Math.floor(msec/10%100);
                studioTimerItem.msecItem.text = mseconds < 10 ? "0" + mseconds : mseconds;
            }
        }
    }
    Text
    {
        id: interval
        color: "aliceblue"
        text: qsTr("/")
        font.pixelSize: 24
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: studioTimerItem.right
        anchors.leftMargin: 5
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return false;
                if(JSession.currentScript.scriptType !== JScript.ScriptType_Video)
                    return false;
                return true;
            });
        }
    }
    StudioTimerItem
    {
        id: scriptTimerItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: interval.right
        anchors.leftMargin: 5
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return false;
                if(JSession.currentScript.scriptType !== JScript.ScriptType_Video)
                    return false;
                return true;
            });
            hourItem.text = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return "00";
                if(JSession.currentScript.scriptType !== JScript.ScriptType_Video)
                    return "00";
                var msec = JSession.currentScript.glCamera.recordingDuration*1000;
                var hours = Math.floor(msec / 3600000);
                return hours < 10 ? "0" + hours : hours;
            });
            minuteItem.text = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return "00";
                if(JSession.currentScript.scriptType !== JScript.ScriptType_Video)
                    return "00";
                var msec = JSession.currentScript.glCamera.recordingDuration*1000;
                var minutes = Math.floor((msec % 3600000) / 60000);
                return minutes < 10 ? "0" + minutes : minutes;
            });
            secItem.text = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return "00";
                if(JSession.currentScript.scriptType !== JScript.ScriptType_Video)
                    return "00";
                var msec = JSession.currentScript.glCamera.recordingDuration*1000;
                var seconds = Math.floor(((msec % 3600000) % 60000) / 1000);
                return seconds < 10 ? "0" + seconds : seconds;
            });
            msecItem.text = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return "00";
                if(JSession.currentScript.scriptType !== JScript.ScriptType_Video)
                    return "00";
                var msec = JSession.currentScript.glCamera.recordingDuration*1000;
                var mseconds = Math.floor(msec/10%100);
                return mseconds < 10 ? "0" + mseconds : mseconds;
            });
        }
    }

}
