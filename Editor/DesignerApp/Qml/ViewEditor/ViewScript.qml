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

import "./ScriptList"

Item
{
    id:root

    //左边工具栏区域
    Rectangle
    {
        id: toolBarItem
        width: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        color: "#363636"
        Button
        {
            id: editorButton
            height: parent.width
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            flat: true; down:false
            icon.width: 25
            icon.height: 25
            icon.color: (hovered||selected) ?"white":"gainsboro"
            icon.source: "qrc:/Image/icon_save_as_script.png"
            property bool selected: true
            background: Item {
                Rectangle
                {
                    width: 4;height: parent.height
                    color: "dodgerblue"
                    visible: editorButton.selected
                }
            }
            onClicked:selected = !selected;
        }
    }
    //右边工具箱区域
    SplitView
    {
        id: toolBoxItem
        width: 50
        anchors.top: parent.top
        anchors.left: toolBarItem.right
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        orientation: Qt.Horizontal
        handle: Rectangle
        {
            implicitWidth: 2
            color: (SplitHandle.pressed||SplitHandle.hovered) ? "steelblue" : "transparent"
        }

        //会话的脚本文件列表
        SessionView
        {
            id: sessionView
            color: toolBarItem.color
            height: parent.height
            SplitView.minimumWidth: 250
            SplitView.preferredWidth: 250
            visible: editorButton.selected
        }
        Row
        {
            spacing: 2
            //脚本页面
            StackView
            {
                id: stackView
                initialItem: sceneComponent
                width: parent.width-scriptDataLoader.width-parent.spacing
                height: parent.height
            }

            //脚本属性页面
            Loader
            {
                id: scriptDataLoader
                focus: true
                width: 320
                height: parent.height
                asynchronous: true
                source: "qrc:/Qml/ViewEditor/Property/EmptyPropPage.qml"
                Component.onCompleted:
                {
                    source = Qt.binding(function(){
                        if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                            return "qrc:/Qml/ViewEditor/Property/EmptyPropPage.qml";
                        else if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
                            return "qrc:/Qml/ViewEditor/Property/NodePropPage.qml";
                        else if(JSession.currentScript.currentNode.type === JNode.NodeType_Erp)
                            return "qrc:/Qml/ViewEditor/Property/ErpPropPage.qml";
                        else if(JSession.currentScript.currentNode.type === JNode.NodeType_StopMotionAnimation)
                            return "qrc:/Qml/ViewEditor/Property/SmaPropPage.qml";
                        else
                            return "qrc:/Qml/ViewEditor/Property/EmptyPropPage.qml";
                    });
                }
            }
        }
    }

    Component
    {
        id: sceneComponent
        ScriptScene
        {
            id: scriptSceneView
        }
    }
}
