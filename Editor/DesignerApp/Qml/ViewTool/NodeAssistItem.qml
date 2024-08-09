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

//辅助点按钮
Rectangle
{
    radius:3
    color: "#444444"
    implicitHeight: 34
    width: row.width+20

    Row
    {
        id: row
        spacing: 10
        anchors.centerIn: parent

        UpdateButton
        {
            toolText: "更新圆弧辅助点数据"
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
                    if(JSession.currentScript.currentNode.robot.type !== 3)
                        return false;
                    return true;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.currentNode.updataRobotAssist();
                JSession.currentScript.changed=true;
            }
        }

        RemoteButton
        {
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
                    if(JSession.currentScript.currentNode.robot.type === 3)
                    {
                        var node = JSession.currentScript.currentNode;
                        if(node.robot.assist.a1==="0"&&node.robot.assist.a2==="0"&&node.robot.assist.a3==="0"&&
                                node.robot.assist.a4==="0"&&node.robot.assist.a5==="0"&&node.robot.assist.a6==="0")
                        {
                            return false;
                        }
                        return true;
                    }

                    return false;
                });
                resetFlag = Qt.binding(function(){
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    if(JSession.currentScript.currentNode.robot.type === 0)
                        return false;
                    var node = JSession.currentScript.currentNode;
                    var a1Error = Math.abs(Number(node.robot.assist.a1)-Number(JRobot.position.a1));
                    var a2Error = Math.abs(Number(node.robot.assist.a2)-Number(JRobot.position.a2));
                    var a3Error = Math.abs(Number(node.robot.assist.a3)-Number(JRobot.position.a3));
                    var a4Error = Math.abs(Number(node.robot.assist.a4)-Number(JRobot.position.a4));
                    var a5Error = Math.abs(Number(node.robot.assist.a5)-Number(JRobot.position.a5));
                    var a6Error = Math.abs(Number(node.robot.assist.a6)-Number(JRobot.position.a6));
                    if(a1Error<0.1&&a2Error<0.1&&a3Error<0.1&&a4Error<0.1&&a5Error<0.1&&a6Error<0.1)
                    {
                        return true;
                    }
                    return false;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.assistNodeReset(4);
            }
        }
        RemoteButton
        {
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
                    if(JSession.currentScript.currentNode.robot.type === 3)
                    {
                        var node = JSession.currentScript.currentNode;
                        if(node.robot.assist.x==="0"&&node.robot.assist.y==="0"&&node.robot.assist.z==="0"&&
                                node.robot.assist.rx==="0"&&node.robot.assist.ry==="0"&&node.robot.assist.rz==="0")
                        {
                            return false;
                        }
                        return true;
                    }

                    return false;
                });
                resetFlag = Qt.binding(function(){
                    if(JSession.currentScript === null)
                        return false;
                    if(JSession.currentScript.currentNode === null)
                        return false;
                    if(JSession.currentScript.currentNode.type !== JNode.NodeType_Move)
                        return false;
                    if(JSession.currentScript.currentNode.robot.type === 0)
                        return false;
                    var node = JSession.currentScript.currentNode;
                    var xError = Math.abs(Number(node.robot.assist.x)-Number(JRobot.position.x));
                    var yError = Math.abs(Number(node.robot.assist.y)-Number(JRobot.position.y));
                    var zError = Math.abs(Number(node.robot.assist.z)-Number(JRobot.position.z));
                    var rxError = Math.abs(Number(node.robot.assist.rx)-Number(JRobot.position.rx));
                    var ryError = Math.abs(Number(node.robot.assist.ry)-Number(JRobot.position.ry));
                    var rzError = Math.abs(Number(node.robot.assist.rz)-Number(JRobot.position.rz));
                    if(xError<0.1&&yError<0.1&&zError<0.1&&rxError<0.1&&ryError<0.1&&rzError<0.1)
                    {
                        return true;
                    }
                    return false;
                });
            }
            onButtonClick:
            {
                JSession.currentScript.assistNodeReset(5);
            }
        }
    }
}
