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

    TextInputItem
    {
        id: imageCountItem
        width: parent.width
        tagText:"拍摄次数"
        suffixText: "次"
        enteText: "输入0-30"
        maxCount: 30
        minCount: 0
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.camera.imageNum = Number(value);
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return false;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return true;
                return false;
            });
            dataItem.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.camera.imageNum;
                    }
                }
                return 0;
            });
        }
    }
    TextInputItem
    {
        id: interItem
        width: parent.width
        tagText:"间隔时间"
        suffixText: "秒"
        enteText: "输入0-100"
        maxCount: 100
        minCount: 0
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.camera.imageInterval = Number(value);
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return false;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return true;
                return false;
            });
            dataItem.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.camera.imageInterval;
                    }
                }
                return 0;
            });
        }
    }

    ComboxItem
    {
        id: shootTypeItem
        tagText: "拍摄模式";
        comboxAlias.width: 180
        comboxArray:["直接拍摄","自动AF"]
        width: parent.width
        onIndexActivated: function(index)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.currentNode.camera.shootMode = index;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return false;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return true;
                return false;
            });
            comboxAlias.currentIndex = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.currentNode.camera.shootMode;
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
        id: recordingTimeItem
        width: parent.width
        tagText:"录制时长"
        suffixText: "秒"
        maxCount: 600
        minCount: 0
        enteText: "输入0-600"
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glCamera.recordingDuration = Number(value);
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return false;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return true;
                return false;
            });
            dataItem.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.glCamera.recordingDuration;
                    }
                }
                return 0;
            });
        }
    }
    TextInputItem
    {
        id: moveDelay
        width: parent.width
        tagText:"运动开始时间"
        suffixText: "秒"
        maxCount: 600
        minCount: 0
        enteText: "输入0-600"
        dataItem.width: 180
        onTextInput: function(value)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glCamera.moveDelay = Number(value);
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            visible = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return false;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return true;
                return false;
            });
            dataItem.valueText = Qt.binding(function(){
                if(JSession.currentScript !== null)
                {
                    if(JSession.currentScript.currentNode !== null)
                    {
                        return JSession.currentScript.glCamera.moveDelay;
                    }
                }
                return 0;
            });
        }
    }
}

