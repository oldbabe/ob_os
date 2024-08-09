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

import JMoco 1.0

Rectangle
{
    id:root
    color: "#363636"
    implicitHeight: 50
    GamePadItem
    {
        id: gamePadItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
    }
    StudioRobotItem
    {
        id: studioRobotItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: gamePadItem.right
        anchors.leftMargin: 10
    }
    StudioCameraItem
    {
        id: studioCameraItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: studioRobotItem.right
        anchors.leftMargin: 10
    }
    Rectangle
    {
        id: separateItem
        width: 2
        height: parent.height
        color: "#202020"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: studioCameraItem.right
        anchors.leftMargin: 10
    }
    ConnectButton
    {
        id: connectButton
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: separateItem.right
        anchors.leftMargin: 10
    }
    StudioResetButton
    {
        id: studioResetButton
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: connectButton.right
        anchors.leftMargin: 10
    }
    DownloadButton
    {
        id: downloadButton
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: studioResetButton.right
        anchors.leftMargin: 10
    }
    StopButton
    {
        id: stopButton
        height: 34
        width: 120
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: downloadButton.right
        anchors.leftMargin: 10
    }
    Loader
    {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: stopButton.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        Component.onCompleted:
        {
            source = Qt.binding(function(){
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return "";
                if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
                    return "qrc:/Qml/ViewTool/NodeItem.qml";
                else if(JSession.currentScript.currentNode.type === JNode.NodeType_StopMotionAnimation)
                    return "qrc:/Qml/ViewTool/SmaRemoteItem.qml";
                else
                    return "";
            });
        }
    }
}
