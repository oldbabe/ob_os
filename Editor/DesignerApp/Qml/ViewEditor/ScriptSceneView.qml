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
import JltView 1.0
import JMoco 1.0
import "../JltComponent"

Item
{
    property JltScriptScene scene: null
    implicitWidth: 100
    implicitHeight: 40

    //复位按钮
    Button
    {
        id: sceneResetButton
        down:false;flat: true
        width: 30;height: 30
        icon.source: "qrc:/Image/icon_center.png"
        icon.color: hovered?"white":"gainsboro"
        icon.width: 20
        icon.height: 20
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        background: Rectangle
        {
            radius: 3
            opacity: 0.8
            color: "#202020"
            border.color: "#444444"
        }
        onClicked:
        {
            if(JSession.currentScript === null)
            {
                scene.originX = 0;
                scene.originY = 0;
            }
            else if(JSession.currentScript.currentNode === null)
            {
                var nodes = JSession.currentScript.getNodes();
                if(nodes.length > 0)
                {
                    scene.originX = -nodes[0].x*scene.gridWidth+scene.width/5;
                    scene.originY = -nodes[0].y*scene.gridWidth+scene.height/3;
                }
                else
                {
                    scene.originX = 0;
                    scene.originY = 0;
                }
            }
            else
            {
                scene.originX = -JSession.currentScript.currentNode.x*scene.gridWidth+scene.width/5;
                scene.originY = -JSession.currentScript.currentNode.y*scene.gridWidth+scene.height/3;
            }
        }
    }

    //相机操作类型
    TextButtonItem
    {
        id: cameraShotButton
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: sceneResetButton.right
        anchors.leftMargin: 10
        iconWidth: 20
        iconHeight: 20
        showText: "平面"
        checkedText: "启用"
        iconSource: "qrc:/Image/icon_pictures.png"
        Component.onCompleted:
        {
            showText = Qt.binding(function(){
                if(JSession.currentScript===null)
                    return "空";
                if(JSession.currentScript.scriptType===JScript.ScriptType_Image)
                    return "平面";
                else
                    return "视频";
            });
            iconSource = Qt.binding(function(){
                if(JSession.currentScript===null)
                    return "";
                if(JSession.currentScript.scriptType===JScript.ScriptType_Image)
                    return "qrc:/Image/icon_pictures.png";
                else
                    return "qrc:/Image/icon_Videos.png";
            });
        }
        onButtonClicked:
        {
            if(JSession.currentScript===null || !JSession.currentScript.editEnable)
                return;

            if(JSession.currentScript.scriptType===JScript.ScriptType_Image)
                JSession.currentScript.scriptType=JScript.ScriptType_Video;
            else
                JSession.currentScript.scriptType=JScript.ScriptType_Image;
        }
    }

    //相机启用或禁用按钮
    TextButtonItem
    {
        id: cameraEnableButton
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: cameraShotButton.right
        anchors.leftMargin: 10
        showText: "禁用"
        checkedText: "启用"
        iconSource: "qrc:/Image/icon_camera.png"
        Component.onCompleted:
        {
            checked = Qt.binding(function(){
                if(JSession.currentScript===null)
                    return false;
                if(JSession.currentScript.remoteMode===JScript.RemoteMode_MoveOnly)
                    return false;
                return true;
            });
        }
        onButtonClicked:
        {
            if(JSession.currentScript===null || !JSession.currentScript.editEnable)
                return;
            if(JSession.currentScript.remoteMode===JScript.RemoteMode_MoveOnly)
                JSession.currentScript.remoteMode=JScript.RemoteMode_MoveShooting;
            else
                JSession.currentScript.remoteMode=JScript.RemoteMode_MoveOnly;
        }
    }
}
