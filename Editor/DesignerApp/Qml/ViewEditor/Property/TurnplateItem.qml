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

    DeviceValueItem
    {
        id: targetItem
        tagText: "目标位置"
        width: parent.width

        onButttonClick:
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.trunplate.target = JTurnplate.angle;
            JSession.currentScript.changed=true;
        }
        onTextInput:function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.trunplate.target = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                        return true;
                }
                return false;
            });
            textItem.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                        {
                            return JSession.currentScript.currentNode.trunplate.target;
                        }
                    }
                }
                return 0;
            });
        }
    }

    SliderInputItem
    {
        id: speedItem
        width: parent.width
        tagText: "速度"
        titleText: "V"

        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.trunplate.speed = value;
            JSession.currentScript.changed=true;
        }

        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                        return true;
                }
                return false;
            });
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    {
                        if(JSession.currentScript.currentNode !== null)
                        {
                            return JSession.currentScript.currentNode.trunplate.speed;
                        }
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
        id: accItem
        width: parent.width
        tagText: "加速度"
        titleText: "A"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.trunplate.acc = value;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                        return true;
                }
                return false;
            });
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    {
                        if(JSession.currentScript.currentNode !== null)
                        {
                            return JSession.currentScript.currentNode.trunplate.acc;
                        }
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
        id: speedVItem
        width: parent.width
        tagText: "速度"
        titleText: "V"

        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glTurnplate.speed = value;
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
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                        return JSession.currentScript.glTurnplate.speed;
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
        id: accVItem
        width: parent.width
        tagText: "加速度"
        titleText: "A"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glTurnplate.acc = value;
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
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                        return JSession.currentScript.glTurnplate.acc;
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
        id: decVItem
        width: parent.width
        tagText: "减速度"
        titleText: "A"
        onHandleMove: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glTurnplate.dec = value;
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
            newValue = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                        return JSession.currentScript.glTurnplate.dec;
                }
                return 0;
            });
            slideritem.enabled = Qt.binding(function(){
                return JSession.currentScript!==null?JSession.currentScript.editEnable:false
            });
        }
    }

    ComboxItem
    {
        id: runDirectionItem
        tagText: "运动方向";
        comboxArray:["顺时针","逆时针"]
        width: parent.width
        comboxAlias.width: 180
        onIndexActivated: function(index)
        {
            if(!JSession.currentScript.editEnable)
                return;

            if(index === 0)
                JSession.currentScript.glTurnplate.direction = 1;
            else
                JSession.currentScript.glTurnplate.direction = -1;

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
            comboxAlias.currentIndex = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    {
                        if(JSession.currentScript.glTurnplate.direction === 1)
                            return 0;
                        else if(JSession.currentScript.glTurnplate.direction === -1)
                            return 1;
                    }
                }
                return 0;
            });
            comboxAlias.enabled = Qt.binding(function(){
                return JSession.currentScript!==null?JSession.currentScript.editEnable:false
            });
        }
    }

    TextInputItem
    {
        id: runTimeItem
        width: parent.width
        tagText:"运动时间"
        suffixText: "秒"
        enteText:"输入值0-600"
        maxCount: 600
        minCount: 0
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glTurnplate.duration = value;
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
            dataItem.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    {
                        return JSession.currentScript.glTurnplate.duration;
                    }
                }
                return 0;
            });
        }
    }

    TextInputItem
    {
        id: startTimeItem
        width: parent.width
        tagText:"起始时间"
        suffixText: "秒"
        enteText:"输入值0-600"
        maxCount: 600
        minCount: 0
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glTurnplate.startTime = value;
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
            dataItem.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    {
                        return JSession.currentScript.glTurnplate.startTime;
                    }
                }
                return 0;
            });
        }
    }
}

