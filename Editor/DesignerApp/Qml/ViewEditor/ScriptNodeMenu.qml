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

JltMenu
{
    property JltScriptScene scene: null
    delegate: JltMenuItem{}
    //初始化禁用/使能状态
    onAboutToShow:
    {
        if(scene.currentNode !== null)
            deleteNodeAction.enabled = true;
        else
            deleteNodeAction.enabled = false;
        if(scene.currentNode !== null)
        {
            if(scene.currentNode.inputConnector !== null && scene.currentNode.inputConnector.bindConnector !== null)
                disconnectAction.enabled = true;
            else if(scene.currentNode.outputConnector !== null && scene.currentNode.outputConnector.bindConnector !== null)
                disconnectAction.enabled = true;
            else
                disconnectAction.enabled = false;
        }
        else
        {
            disconnectAction.enabled = false;
        }
        if(scene.currentNode !== null&&scene.currentNode.inputConnector !== null && scene.currentNode.inputConnector.bindConnector !== null)
            disconnectLeftAction.enabled = true;
        else
            disconnectLeftAction.enabled = false;
        if(scene.currentNode !== null && scene.currentNode.outputConnector.bindConnector !== null)
            disconnectRightAction.enabled = true;
        else
            disconnectRightAction.enabled = false;
    }
    Action
    {
        id: deleteNodeAction
        text: qsTr("删除")
        shortcut: "Delete";
        icon.source: ""
        onTriggered:
        {
            scene.removeNode(scene.currentNode);
            scene.currentNode = null;
        }
    }
    Action
    {
        id: disconnectAction
        text: qsTr("断开连接线")
        shortcut: "";
        icon.source: ""
        onTriggered:
        {
            if(scene.currentNode !== null)
            {
                scene.currentNode.disconnectInputConnector();
                scene.currentNode.disconnectOutputConnector();
                if(scene.currentNode.nodeData.last)
                {
                    scene.currentNode.nodeData.last.next = null;
                    scene.currentNode.nodeData.last = null;
                }
                if(scene.currentNode.nodeData.next)
                {
                    scene.currentNode.nodeData.next.last = null;
                    scene.currentNode.nodeData.next = null;
                }

                JSession.currentScript.changed = true;
            }
        }
    }
    Action
    {
        id: disconnectLeftAction
        text: qsTr("断开左连接线")
        shortcut: "";
        icon.source: ""
        onTriggered:
        {
            if(scene.currentNode !== null)
            {
                if(scene.currentNode.nodeData.last)
                {
                    scene.currentNode.nodeData.last.next = null;
                    scene.currentNode.nodeData.last = null;
                }
                scene.currentNode.nodeData.last = null;
                scene.currentNode.disconnectInputConnector();
                JSession.currentScript.changed = true;
            }
        }
    }
    Action
    {
        id: disconnectRightAction
        text: qsTr("断开右连接线")
        shortcut: "";
        icon.source: ""
        onTriggered:
        {
            if(scene.currentNode !== null)
            {
                if(scene.currentNode.nodeData.next)
                {
                    scene.currentNode.nodeData.next.last = null;
                    scene.currentNode.nodeData.next = null;
                }
                scene.currentNode.disconnectOutputConnector();
                JSession.currentScript.changed = true;
            }
        }
    }
}
