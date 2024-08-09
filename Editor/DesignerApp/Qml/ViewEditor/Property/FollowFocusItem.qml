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

    DeviceTextItem
    {
        id: focusItem
        tagText: "对焦值"
        titleText: "F"
        width: parent.width
        onModelClick: function(mode)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glFollowFocus.focusMode = mode;
            JSession.currentScript.changed=true;
        }
        onButttonClick:
        {
            if(!JSession.currentScript.editEnable)
                return;
            if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                JSession.currentScript.currentNode.followfocus.focusValue = JFollowfocus.focus;
            else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                JSession.currentScript.glFollowFocus.focusValue = JFollowfocus.focus;
            JSession.currentScript.changed=true;
        }
        onEditFinished:function(textData)
        {
            if(!JSession.currentScript.editEnable)
                return;
            if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                JSession.currentScript.currentNode.followfocus.focusValue = textData;
            else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                JSession.currentScript.glFollowFocus.focusValue = textData;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            state = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return "photo";
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return "photo";
                else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return "video";
                return "photo";
            });
            showText = Qt.binding(function(){
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return 0;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return JSession.currentScript.currentNode.followfocus.focusValue;
                else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return JSession.currentScript.glFollowFocus.focusValue;
                return 0;
            });
            valueModel = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return 0;
                return  JSession.currentScript.glFollowFocus.focusMode;
            });
        }
    }

    DeviceTextItem
    {
        id: zoomItem
        tagText: "变焦值"
        titleText: "Z"
        width: parent.width

        onModelClick: function(mode)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glFollowFocus.zoomMode = mode;
            JSession.currentScript.changed=true;
        }
        onButttonClick:
        {
            if(!JSession.currentScript.editEnable)
                return;
            if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                JSession.currentScript.currentNode.followfocus.zoomValue = JFollowfocus.focus;
            else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                JSession.currentScript.glFollowFocus.zoomValue = JFollowfocus.focus;
            JSession.currentScript.changed=true;
        }
        onEditFinished:function(textData)
        {
            if(!JSession.currentScript.editEnable)
                return;
            if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                JSession.currentScript.currentNode.followfocus.zoomValue = textData;
            else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                JSession.currentScript.glFollowFocus.zoomValue = textData;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            state = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return "photo";
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return "photo";
                else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return "video";
                return "photo";
            });
            showText = Qt.binding(function(){
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return 0;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return JSession.currentScript.currentNode.followfocus.zoomValue;
                else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return JSession.currentScript.glFollowFocus.zoomValue;
                return 0;
            });
            valueModel = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return 0;
                return  JSession.currentScript.glFollowFocus.zoomMode;
            });
        }
    }

    DeviceTextItem
    {
        id: irisItem
        tagText: "光圈"
        titleText: "I"
        width: parent.width

        onModelClick: function(mode)
        {
            if(!JSession.currentScript.editEnable)
                return;
            JSession.currentScript.glFollowFocus.irisMode = mode;
            JSession.currentScript.changed=true;
        }
        onButttonClick:
        {
            if(!JSession.currentScript.editEnable)
                return;
            if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                JSession.currentScript.currentNode.followfocus.irisValue = JFollowfocus.focus;
            else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                JSession.currentScript.glFollowFocus.irisValue = JFollowfocus.focus;
            JSession.currentScript.changed=true;
        }
        onEditFinished:function(textData)
        {
            if(!JSession.currentScript.editEnable)
                return;
            if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                JSession.currentScript.currentNode.followfocus.irisValue = textData;
            else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                JSession.currentScript.glFollowFocus.irisValue = textData;
            JSession.currentScript.changed=true;
        }
        Component.onCompleted:
        {
            state = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return "photo";
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return "photo";
                else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return "video";
                return "photo";
            });
            showText = Qt.binding(function(){
                if(JSession.currentScript === null || JSession.currentScript.currentNode === null)
                    return 0;
                if(JSession.currentScript.scriptType === JScript.ScriptType_Image)
                    return JSession.currentScript.currentNode.followfocus.irisValue;
                else if(JSession.currentScript.scriptType === JScript.ScriptType_Video)
                    return JSession.currentScript.glFollowFocus.irisValue;
                return 0;
            });
            valueModel = Qt.binding(function(){
                if(JSession.currentScript === null)
                    return 0;
                return  JSession.currentScript.glFollowFocus.irisMode;
            });
        }
    }
}

