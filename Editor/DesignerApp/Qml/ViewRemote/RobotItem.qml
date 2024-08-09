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
import "../Component"
import JMoco 1.0


Column
{
    id: root
    spacing: 1

    Component.onCompleted:
    {
        state = Qt.binding(function(){
            if(JRobot.remoteType === JRobot.RemoteType_World)
                return "world";
            else if(JRobot.remoteType === JRobot.RemoteType_Tool)
                return "tool";
            else
                return "axis";
        });
        tagItem.tagText = Qt.binding(function(){
            if(JRobot.remoteType === JRobot.RemoteType_Axis)
                return "单轴";
            else if(JRobot.remoteType === JRobot.RemoteType_World)
                return "基坐标";
            else if(JRobot.remoteType === JRobot.RemoteType_Tool)
                return "工具坐标";
            else
                return "-";
        });
    }

    function senRemoteData(index,speed)
    {
        var json = {
            "P1": String(itemP1.jogValue),
            "P2": String(itemP2.jogValue),
            "P3": String(itemP3.jogValue),
            "P4": String(itemP4.jogValue),
            "P5": String(itemP5.jogValue),
            "P6": String(itemP6.jogValue),
            "P7": String(itemP7.jogValue)
        };
        JRobot.jogMovement(JRobot.remoteType,json);
    }

    states: [
        State {
            name: "world"
            PropertyChanges {
                target: itemP1
                dataTitleText: "X"
                dataText: parseFloat(JRobot.position.x).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP2
                dataTitleText: "Y"
                dataText: parseFloat(JRobot.position.y).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP3
                dataTitleText: "Z"
                dataText: parseFloat(JRobot.position.z).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP4
                dataTitleText: "A"
                dataText: parseFloat(JRobot.position.rx).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP5
                dataTitleText: "B"
                dataText: parseFloat(JRobot.position.ry).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP6
                dataTitleText: "C"
                dataText: parseFloat(JRobot.position.rz).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP7
                leftTitleText: "-"
                rightTitleText: "+"
            }
        },
        State {
            name: "tool"
            PropertyChanges {
                target: itemP1
                dataTitleText: "X"
                dataText: parseFloat(JRobot.position.x).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP2
                dataTitleText: "Y"
                dataText: parseFloat(JRobot.position.y).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP3
                dataTitleText: "Z"
                dataText: parseFloat(JRobot.position.z).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP4
                dataTitleText: "A"
                dataText: parseFloat(JRobot.position.rx).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP5
                dataTitleText: "B"
                dataText: parseFloat(JRobot.position.ry).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP6
                dataTitleText: "C"
                dataText: parseFloat(JRobot.position.rz).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP7
                leftTitleText: "-"
                rightTitleText: "+"
            }
        },
        State {
            name: "axis"
            PropertyChanges {
                target: itemP1
                dataTitleText: "A1"
                dataText: parseFloat(JRobot.position.a1).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP2
                dataTitleText: "A2"
                dataText: parseFloat(JRobot.position.a2).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP3
                dataTitleText: "A3"
                dataText: parseFloat(JRobot.position.a3).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP4
                dataTitleText: "A4"
                dataText: parseFloat(JRobot.position.a4).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP5
                dataTitleText: "A5"
                dataText: parseFloat(JRobot.position.a5).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP6
                dataTitleText: "A6"
                dataText: parseFloat(JRobot.position.a6).toFixed(3)
                leftTitleText: "-"
                rightTitleText: "+"
            }
            PropertyChanges {
                target: itemP7
                leftTitleText: "-"
                rightTitleText: "+"
            }
        }
    ]

    TagItem
    {
        id: tagItem
        tagText: "手动遥控"
        zoomFlag: true
        width: parent.width
        Row
        {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 3
            layoutDirection:Qt.RightToLeft
            spacing: 5
            ToolButtonNoClick
            {
                id:rightTB3
                width: 25
                height: 25
                checkable:true
                checked: JRobot.remoteType === JRobot.RemoteType_Axis ? true : false
                icon: "qrc:/Image/icon_Robot.png"
                enterText: "单轴"
                onButtonEntered: rightTB3.entered = true;
                onButtonExited: rightTB3.entered = false;
                onButtonClicked: JRobot.remoteType = JRobot.RemoteType_Axis;
            }
            ToolButtonNoClick
            {
                id:rightTB1
                width: 25
                height: 25
                checkable:true
                checked: JRobot.remoteType === JRobot.RemoteType_Tool ? true : false
                icon: "qrc:/Image/icon_tool_bottom.png"
                enterText: "工具坐标系"
                onButtonEntered: rightTB1.entered = true;
                onButtonExited: rightTB1.entered = false;
                onButtonClicked: JRobot.remoteType = JRobot.RemoteType_Tool;
            }
            ToolButtonNoClick
            {
                id:rightTB0
                width: 25
                height: 25
                checkable:true
                checked: JRobot.remoteType === JRobot.RemoteType_World ? true : false
                icon: "qrc:/Image/icon_world_bottom.png"
                enterText: "世界坐标系"
                onButtonEntered: rightTB0.entered = true;
                onButtonExited: rightTB0.entered = false;
                onButtonClicked: JRobot.remoteType = JRobot.RemoteType_World;
            }
        }
    }

    RobotRemoteItem
    {
        id: itemP1
        visible: tagItem.zoomFlag
        width: parent.width
        onJogMoved: root.senRemoteData();
        onJogStop: JRobot.runStop();
    }
    RobotRemoteItem
    {
        id: itemP2
        visible: tagItem.zoomFlag
        width: parent.width
        onJogMoved: root.senRemoteData();
        onJogStop: JRobot.runStop();
    }
    RobotRemoteItem
    {
        id: itemP3
        visible: tagItem.zoomFlag
        width: parent.width
        onJogMoved: root.senRemoteData();
        onJogStop: JRobot.runStop();
    }
    RobotRemoteItem
    {
        id: itemP4
        visible: tagItem.zoomFlag
        width: parent.width
        onJogMoved: root.senRemoteData();
        onJogStop: JRobot.runStop();
    }
    RobotRemoteItem
    {
        id: itemP5
        visible: tagItem.zoomFlag
        width: parent.width
        onJogMoved: root.senRemoteData();
        onJogStop: JRobot.runStop();
    }
    RobotRemoteItem
    {
        id: itemP6
        visible: tagItem.zoomFlag
        width: parent.width
        onJogMoved: root.senRemoteData();
        onJogStop: JRobot.runStop();
    }
    RobotRemoteItem
    {
        id: itemP7
        visible: tagItem.zoomFlag
        width: parent.width
        dataTitleText: "E1"
        dataText: parseFloat(JRobot.position.a7).toFixed(3)
        onJogMoved: root.senRemoteData();
        onJogStop: JRobot.runStop();
    }
}
