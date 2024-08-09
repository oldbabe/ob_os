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
import "../../Component"
import "../Property"
import JMoco 1.0

//运动节点属性页面
Rectangle
{
    id: root
    color: "#202020"
    state: "robot"
    //顶部
    TabBar
    {
        id: tabBar
        width: parent.width
        height: 24
        background: Item{}
        TabButton
        {
            text: "机械臂"
            implicitHeight: parent.height
            implicitWidth: 60
            width: implicitWidth
            height: implicitHeight
            contentItem: Text
            {
                text: parent.text
                font: parent.font
                color: parent.checked ? "aliceblue" : "gainsboro"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            background: Rectangle
            {
                color: parent.checked ? "steelblue" : "#363636"
            }
            onClicked: root.state = "robot";
        }
        TabButton
        {
            text: "相机"
            implicitHeight: parent.height
            implicitWidth: 60
            width: implicitWidth
            height: implicitHeight
            contentItem: Text
            {
                text: parent.text
                font: parent.font
                color: parent.checked ? "aliceblue" : "gainsboro"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            background: Rectangle
            {
                color: parent.checked ? "steelblue" : "#363636"
            }
            onClicked: root.state = "camera";
        }

        // TabButton
        // {
        //     text: "跟焦器"
        //     implicitHeight: parent.height
        //     implicitWidth: 60
        //     width: implicitWidth
        //     height: implicitHeight
        //     contentItem: Text
        //     {
        //         text: parent.text
        //         font: parent.font
        //         color: parent.checked ? "aliceblue" : "gainsboro"
        //         horizontalAlignment: Text.AlignHCenter
        //         verticalAlignment: Text.AlignVCenter
        //         elide: Text.ElideRight
        //     }
        //     background: Rectangle
        //     {
        //         color: parent.checked ? "steelblue" : "#363636"
        //     }
        //     onClicked: root.state = "followFocus";
        // }
        // TabButton
        // {
        //     text: "转盘"
        //     implicitHeight: parent.height
        //     implicitWidth: 60
        //     width: implicitWidth
        //     height: implicitHeight
        //     contentItem: Text
        //     {
        //         text: parent.text
        //         font: parent.font
        //         color: parent.checked ? "aliceblue" : "gainsboro"
        //         horizontalAlignment: Text.AlignHCenter
        //         verticalAlignment: Text.AlignVCenter
        //         elide: Text.ElideRight
        //     }
        //     background: Rectangle
        //     {
        //         color: parent.checked ? "steelblue" : "#363636"
        //     }
        //     onClicked: root.state = "turnplate";
        // }
    }

    Flickable
    {
        id: flickable
        anchors.top: tabBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        boundsMovement :Flickable.StopAtBounds

        contentWidth: width
        contentHeight: column.height

        clip: true
        ScrollBar.vertical: ScrollBar
        {
            policy:ScrollBar.AlwaysOff
        }

        Column
        {
            id: column
            width: parent.width
            spacing: 1
            RobotItem
            {
                id: robotItem
                width: column.width
                visible: root.state === "robot" ? true : false
            }
            CameraItem
            {
                id: cameraItem
                width: column.width
                visible: root.state === "camera" ? true : false
            }
            FollowFocusItem
            {
                id: followFocusItem
                width: column.width
                visible: root.state === "followFocus" ? true : false
            }
            TurnplateItem
            {
                id: turnplateItem
                width: column.width
                visible: root.state === "turnplate" ? true : false
            }
        }
    }

    //蒙版
    Rectangle
    {
        id:textRect
        anchors.fill: parent
        color: "#202020"
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript!==null&&JSession.currentScript.currentNode===null&&JSession.currentScript.currentNode.type===JNode.NodeType_Move)
                    return true;
                return false;
            });
            titleText.text = Qt.binding(function(){
                if(JSession.currentScript===null)
                    return "请打开脚本!";
                if(JSession.currentScript.currentNode===null)
                    return "请选择节点!";
                if(JSession.currentScript.currentNode.type!==JNode.NodeType_Move)
                    return "请选择运动节点!";
                return "";
            });
        }
        Text
        {
            id:titleText
            anchors.centerIn: parent
            color: "aliceblue"
            font.pixelSize: 20
        }
    }

}
