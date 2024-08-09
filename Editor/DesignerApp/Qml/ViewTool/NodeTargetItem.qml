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
import "../JltComponent"

//目标点按钮
Rectangle
{
    radius: 3
    color: "#444444"
    width: targetRow.width+4
    height: 34
    Row
    {
        id: targetRow
        spacing: 5
        anchors.centerIn: parent
        RemoteButton
        {
            buttonType: 4
            toolText: "反向执行"
            Component.onCompleted:
            {
                enabled = Qt.binding(function(){
                    if(!axisRemoteButton.resetFlag || !xyzRemoteButton.resetFlag)
                        return false;
                    if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                        return false;
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null )
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    //遍历后续节点是否存在未使能的节点
                    var node = JSession.currentScript.currentNode;
                    while(node !== null)
                    {
                        if(node.robot.type !== 0 && !node.robot.enable)
                            return false;
                        node = node.last;
                    }
                    return true;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.scriptRun(0,false);
            }
        }
        RemoteButton
        {
            buttonType: 2
            toolText: "反向执行1个节点"
            Component.onCompleted:
            {
                enabled = Qt.binding(function(){
                    if(!axisRemoteButton.resetFlag || !xyzRemoteButton.resetFlag)
                        return false;
                    if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                        return false;
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    if(JSession.currentScript.currentNode.last === null)
                        return false;
                    var lastNode = JSession.currentScript.currentNode.last;
                    if(lastNode.robot.target.x==="0"&&lastNode.robot.target.y==="0"&&lastNode.robot.target.z==="0"&&
                            lastNode.robot.target.rx==="0"&&lastNode.robot.target.ry==="0"&&lastNode.robot.target.rz==="0")
                    {
                        return false;
                    }
                    return true;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.scriptRun(-1);
            }
        }
        UpdateButton
        {
            toolText: "更新目标点数据"
            Component.onCompleted:
            {
                enabled = Qt.binding(function(){
                    if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                        return false;
                    if(JSession.currentScript === null)
                        return false;
                    if(!JSession.currentScript.editEnable)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    return true;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.currentNode.updataRobotTarget();
                JSession.currentScript.changed=true;
            }
        }
        RemoteButton
        {
            id: axisRemoteButton
            setText: "A"
            toolText: "以轴旋转的方式就位"
            Component.onCompleted:
            {
                enabled = Qt.binding(function(){
                    if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                        return false;
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    var node = JSession.currentScript.currentNode;
                    if(node.robot.target.a1==="0"&&node.robot.target.a2==="0"&&node.robot.target.a3==="0"&&
                            node.robot.target.a4==="0"&&node.robot.target.a5==="0"&&node.robot.target.a6==="0")
                    {
                        return false;
                    }
                    return true;
                });
                resetFlag = Qt.binding(function(){
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    var node = JSession.currentScript.currentNode;
                    var a1Error = Math.abs(Number(node.robot.target.a1)-Number(JRobot.position.a1));
                    var a2Error = Math.abs(Number(node.robot.target.a2)-Number(JRobot.position.a2));
                    var a3Error = Math.abs(Number(node.robot.target.a3)-Number(JRobot.position.a3));
                    var a4Error = Math.abs(Number(node.robot.target.a4)-Number(JRobot.position.a4));
                    var a5Error = Math.abs(Number(node.robot.target.a5)-Number(JRobot.position.a5));
                    var a6Error = Math.abs(Number(node.robot.target.a6)-Number(JRobot.position.a6));
                    if(a1Error<0.1&&a2Error<0.1&&a3Error<0.1&&a4Error<0.1&&a5Error<0.1&&a6Error<0.1)
                    {
                        return true;
                    }
                    return false;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.targetNodeReset(4);
            }
        }
        RemoteButton
        {
            id: xyzRemoteButton
            setText: "T"
            toolText: "以空间移动(xyz)的方式就位"
            Component.onCompleted:
            {
                enabled = Qt.binding(function(){
                    if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                        return false;
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    var node = JSession.currentScript.currentNode;
                    if(node.robot.target.x==="0"&&node.robot.target.y==="0"&&node.robot.target.z==="0"&&
                            node.robot.target.rx==="0"&&node.robot.target.ry==="0"&&node.robot.target.rz==="0")
                    {
                        return false;
                    }
                    return true;
                });
                resetFlag = Qt.binding(function(){
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    var node = JSession.currentScript.currentNode;
                    var xError = Math.abs(Number(node.robot.target.x)-Number(JRobot.position.x));
                    var yError = Math.abs(Number(node.robot.target.y)-Number(JRobot.position.y));
                    var zError = Math.abs(Number(node.robot.target.z)-Number(JRobot.position.z));
                    var rxError = Math.abs(Number(node.robot.target.rx)-Number(JRobot.position.rx));
                    var ryError = Math.abs(Number(node.robot.target.ry)-Number(JRobot.position.ry));
                    var rzError = Math.abs(Number(node.robot.target.rz)-Number(JRobot.position.rz));
                    if(xError<0.1&&yError<0.1&&zError<0.1&&rxError<0.1&&ryError<0.1&&rzError<0.1)
                    {
                        return true;
                    }
                    return false;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.targetNodeReset(5);
            }
        }
        RemoteButton
        {
            buttonType: 1
            toolText: "正向执行1个节点"
            Component.onCompleted:
            {
                enabled = Qt.binding(function(){
                    if(!xyzRemoteButton.resetFlag)
                        return false;
                    if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                        return false;
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    if(JSession.currentScript.currentNode.next === null)
                        return false;
                    var nextNode = JSession.currentScript.currentNode.next;
                    if(nextNode.robot.target.x==="0"&&nextNode.robot.target.y==="0"&&nextNode.robot.target.z==="0"&&
                            nextNode.robot.target.rx==="0"&&nextNode.robot.target.ry==="0"&&nextNode.robot.target.rz==="0")
                    {
                        return false;
                    }
                    return true;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.scriptRun(1);
            }
        }
        RemoteButton
        {
            buttonType: 3
            toolText: "正向执行"
            Component.onCompleted:
            {
                enabled = Qt.binding(function(){
                    if(!xyzRemoteButton.resetFlag)
                        return false;
                    if(!JRobot.connected || JScriptController.state === 513 || JScriptController.state === 784 || JScriptController.state === 800)
                        return false;
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    //遍历后续节点是否存在未使能的节点
                    var node = JSession.currentScript.currentNode;
                    while(node !== null)
                    {
                        //存在未更新数据的机械臂节点
                        if(node.robot.type !== 0 && !node.robot.enable)
                            return false;
                        node = node.next;
                    }
                    return true;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.scriptRun();
            }
        }
    }
}

