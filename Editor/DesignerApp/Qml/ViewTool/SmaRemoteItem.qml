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
import "../JltComponent"
import JMoco 1.0


Rectangle
{
    id: root
    radius: 3
    color: "#404040"
    implicitHeight: 40

    Component.onCompleted:
    {
        var node = JSession.currentScript.currentNode.next;
        if(node!==null)
        {
            node = node.next;
        }
        while(node!==null)
        {
            nodeComponent.createObject(row,{nodeData:node});
            node = node.next;
        }
        JSession.currentScript.currentNode.updateFrameCounts();
        control.to = Qt.binding(function(){
            if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                return 0;
            if(JSession.currentScript.currentNode.type !== JNode.NodeType_StopMotionAnimation)
                return 0;
            return JSession.currentScript.currentNode.frameCounts;
        });
        frameCountText.text = Qt.binding(function(){
            return control.to;
        });
        frameSetItem.valueItem.text = control.value;
    }

    function frameReset(value)
    {
        if(JSession.currentScript !== null && JSession.currentScript.currentNode !== null && JSession.currentScript.currentNode.type === JNode.NodeType_StopMotionAnimation)
        {
            JSession.currentScript.currentNode.frameMotion(value);
        }
    }

    Rectangle
    {
        id: frameCountRect
        radius: 3
        color: "#303030"
        height: 34
        width: 120
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        Text
        {
            id: nameText
            color: "aliceblue"
            text: "总帧数"
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
        }
        Text
        {
            id: frameCountText
            color: "aliceblue"
            text: qsTr("0")
            leftPadding: 5
            anchors.left: nameText.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
        }
    }

    RemoteButton
    {
        id: leftButton
        buttonType: 5
        toolText: "-1帧"
        anchors.leftMargin: 5
        anchors.left: frameCountRect.right
        anchors.verticalCenter: parent.verticalCenter
        onButtonClick:
        {
            var currentValue = Number(frameSetItem.valueItem.text);
            if((currentValue-1) >= 0)
            {
                control.value = currentValue-1;
                root.frameReset(control.value);
                frameSetItem.valueItem.text = control.value;
            }
        }
        Component.onCompleted:
        {
            enabled = Qt.binding(function(){
                if(control.value <= control.from)
                    return false;
                if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                    return false;
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return false;
                var node = JSession.currentScript.currentNode.next;
                while(node!==null)
                {
                    //存在未更新数据的节点
                    if(!node.robot.enable)
                        return false;
                    node = node.next;
                }
                return true;
            });
        }
    }

    Rectangle
    {
        id: frameSetRect
        radius: 3
        color: "#303030"
        height: 34
        width: 120
        anchors.leftMargin: 5
        anchors.left: leftButton.right
        anchors.verticalCenter: parent.verticalCenter
        IntShowInput
        {
            id: frameSetItem
            anchors.fill: parent
            anchors.leftMargin: 5
            titleText: "当前帧"
            onValueChanged: function(value)
            {
                if(Number(value) > JSession.currentScript.currentNode.frameCounts)
                    control.value = JSession.currentScript.currentNode.frameCounts;
                else if(Number(value) < 0)
                    control.value = 0;
                else
                    control.value = Number(value);
            }
        }
    }

    RemoteButton
    {
        id: rightButton
        toolText: "+1帧"
        anchors.left: frameSetRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        onButtonClick:
        {
            var currentValue = Number(frameSetItem.valueItem.text);
            if((currentValue+1) <= control.to)
            {
                control.value = currentValue+1;
                root.frameReset(control.value);
                frameSetItem.valueItem.text = control.value;
            }
        }
        Component.onCompleted:
        {
            enabled = Qt.binding(function(){
                if(control.value >= control.to)
                    return false;
                if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                    return false;
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return false;
                var node = JSession.currentScript.currentNode.next;
                while(node!==null)
                {
                    //存在未更新数据的节点
                    if(!node.robot.enable)
                        return false;
                    node = node.next;
                }
                return true;
            });
        }
    }

    Slider
    {
        id: control
        from: 0
        to: 100
        value: 0
        stepSize: 1
        height: 40
        snapMode: Slider.SnapAlways
        leftPadding: 10
        rightPadding: 10
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.left: rightButton.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        property var nodes: []

        onMoved:
        {
            frameSetItem.valueItem.text = control.value;
        }

        background: Item
        {
            Row
            {
                id: row
                anchors.fill: parent
            }

            Rectangle
            {
                x: control.leftPadding
                y: control.topPadding + control.availableHeight / 2 - height / 2
                implicitWidth: 200
                implicitHeight: 4
                width: control.availableWidth
                height: implicitHeight
                radius: 2
                color: "#bdbebf"

                Rectangle {
                    width: control.visualPosition * parent.width
                    height: parent.height
                    color: "#21be2b"
                    radius: 2
                }
            }
        }

        handle: Rectangle {
            x: control.leftPadding + control.visualPosition * (control.availableWidth) - width/2
            y: control.topPadding + control.availableHeight / 2 - height / 2
            radius: 1
            color: "dodgerblue"
            implicitWidth: 20
            implicitHeight: 38
            border.color: "steelblue"
        }

        Component
        {
            id: nodeComponent

            Rectangle
            {
                radius: 1
                color: "transparent"
                border.color: "steelblue"
                property JNode nodeData: null
                height: control.height
                Component.onCompleted:
                {
                    width = Qt.binding(function(){
                        return control.width*(nodeData.robot.frames/control.to);
                    });
                }
            }
        }
    }
}
