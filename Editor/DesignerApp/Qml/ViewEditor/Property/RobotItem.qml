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
import "../../Component"
import JMoco 1.0

Column
{
    id: column
    spacing: 1
    topPadding: 2

    SliderInputItem
    {
        id: prgVItem
        width: parent.width
        tagText: "最大速度"
        titleText: "V"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glRobot.prgV = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.glRobot.prgV;
                    }
                }
                return 0;
            });
            slideritem.enabled = Qt.binding(function(){
                return JSession.currentScript!==null?JSession.currentScript.editEnable:false
            });
        }
    }

    DeviceValuesItem
    {
        id: targetItem
        tagText: "目标位置"
        width: parent.width
        bindButton.visible: false
        onButttonClick:
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.updataRobotTarget();
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            posX.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.target.x;
                    }
                }
                return 0;
            });
            posY.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.target.y;
                    }
                }
                return 0;
            });
            posZ.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.target.z;
                    }
                }
                return 0;
            });
            posA.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.target.rx;
                    }
                }
                return 0;
            });
            posB.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.target.ry;
                    }
                }
                return 0;
            });
            posC.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.target.rz;
                    }
                }
                return 0;
            });
            posE1.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.target.a7;
                    }
                }
                return 0;
            });
        }
    }
    DeviceValuesItem
    {
        id: assistItem
        tagText: "辅助位置"
        width: parent.width
        bindButton.visible: false
        onButttonClick:
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.updataRobotAssist();
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return false;
                if(JSession.currentScript.currentNode.robot.type === 3)
                    return true;
                return false;
            });
            posX.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assist.x;
                    }
                }
                return 0;
            });
            posY.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assist.y;
                    }
                }
                return 0;
            });
            posZ.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assist.z;
                    }
                }
                return 0;
            });
            posA.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assist.rx;
                    }
                }
                return 0;
            });
            posB.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assist.ry;
                    }
                }
                return 0;
            });
            posC.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assist.rz;
                    }
                }
                return 0;
            });
            posE1.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assist.a7;
                    }
                }
                return 0;
            });
        }
    }
    TextInputDoubleItem
    {
        id: angleMoveItem
        width: parent.width
        tagText:"圆心角"
        suffixText: "度"
        enteText: "输入0-360"
        maxCount: 360
        minCount: 0
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.robot.assistCA = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(!JRobot.caEnable)
                    return false;
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return false;
                if(JSession.currentScript.currentNode.robot.type === 3)
                    return true;
                return false;
            });
            inputText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.assistCA;
                    }
                }
                return 0;
            });
        }

        //刷新按钮
        ToolButton
        {
            id: updateBt

            width: 20
            height: 20
            icon: "qrc:/Image/icon_data_refresh.png"

            anchors.left: angleMoveItem.left
            anchors.leftMargin: 190
            anchors.verticalCenter: parent.verticalCenter

            onButtonClicked:
            {
                if(!JSession.currentScript.editEnable)
                    return;
                if(JSession.currentScript === null)
                    return;
                if(JSession.currentScript.currentNode === null)
                    return;
                JSession.currentScript.currentNode.updateCenterCircle();
            }
        }
    }

    TextInputItem
    {
        id: motionDelay
        width: parent.width
        tagText:"过渡值"
        suffixText: "mm"
        maxCount: 500
        minCount: 0
        enteText: "输入0-500"
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.robot.tsValue = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                        return true;
                }
                return false;
            });

            inputText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.tsValue;
                    }
                }
                return 0;
            });
        }
    }
    TextInputDoubleItem
    {
        id: waitingTimeInput
        width: parent.width
        tagText:"停留"
        suffixText: "秒"
        enteText: "输入0-600"
        maxCount: 600
        minCount: 0
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.robot.waiting = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                        return true;
                }
                return false;
            });
            inputText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.waiting;
                    }
                }
                return 0;
            });
        }
    }

    SliderInputItem
    {
        id: robotVItem
        width: parent.width
        tagText: "机械臂速度"
        titleText: "V"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.robot.robotV = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.robotV;
                    }
                }
                return 0;
            });
            slideritem.enabled = Qt.binding(function(){
                return JSession.currentScript!==null?JSession.currentScript.editEnable:false
            });
        }
    }
    SliderInputItem
    {
        id: robotAItem
        width: parent.width
        tagText: "机械臂加速度"
        titleText: "A"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.robot.robotA = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.robotA;
                    }
                }
                return 0;
            });
            slideritem.enabled = Qt.binding(function(){
                return JSession.currentScript!==null?JSession.currentScript.editEnable:false
            });
        }
    }
    SliderInputItem
    {
        id: railVItem
        width: parent.width
        tagText: "轨道速度"
        titleText: "V"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.robot.pathV = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.pathV;
                    }
                }
                return 0;
            });
            slideritem.enabled = Qt.binding(function(){
                return JSession.currentScript!==null?JSession.currentScript.editEnable:false
            });
        }
    }
    SliderInputItem
    {
        id: railAItem
        width: parent.width
        tagText: "轨道加速度"
        titleText: "A"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.robot.pathA = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.robot.pathA;
                    }
                }
                return 0;
            });
            slideritem.enabled = Qt.binding(function(){
                return JSession.currentScript!==null?JSession.currentScript.editEnable:false
            });
        }
    }
}

