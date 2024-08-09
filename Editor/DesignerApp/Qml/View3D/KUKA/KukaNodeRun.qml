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
import QtQuick
import QtQuick3D

import JMoco 1.0
//滑台
SlidingTable
{
    id: slidingTable
    simulation: isScriptNode
    // position.z:(JSession.opened && JRobot.connected) ? Number(JSession.script.get(JScriptController.index).robot.target.a7) : 67.5
    //是否为节点机械臂
    property int isScriptNode: 2

    Component.onCompleted:
    {
        slidingTable.position.z = Qt.binding(function(){
            if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                return false;
            if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
            {
                if(JSession.currentScript.currentNode.robot.type===3)
                {
                    return Number(JSession.currentScript.currentNode.robot.assist.a7);
                }
            }
            return 67.5;
        });
        joint2.eulerRotation.y = Qt.binding(function(){
            if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                return false;
            if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
            {
                if(JSession.currentScript.currentNode.robot.type===3)
                {
                    return -Number(JSession.currentScript.currentNode.robot.assist.a1);
                }
            }
            return 0;
        });
        joint3.eulerRotation.x = Qt.binding(function(){
            if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                return false;
            if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
            {
                if(JSession.currentScript.currentNode.robot.type===3)
                {
                    return Number(JSession.currentScript.currentNode.robot.assist.a2);
                }
            }
            return -90;
        });
        joint4.eulerRotation.x = Qt.binding(function(){
            if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                return false;
            if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
            {
                if(JSession.currentScript.currentNode.robot.type===3)
                {
                    return Number(JSession.currentScript.currentNode.robot.assist.a3);
                }
            }
            return 90;
        });
        joint5.eulerRotation.z = Qt.binding(function(){
            if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                return false;
            if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
            {
                if(JSession.currentScript.currentNode.robot.type===3)
                {
                    return -Number(JSession.currentScript.currentNode.robot.assist.a4);
                }
            }
            return 0;
        });
        joint6.eulerRotation.x = Qt.binding(function(){
            if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                return false;
            if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
            {
                if(JSession.currentScript.currentNode.robot.type===3)
                {
                    return Number(JSession.currentScript.currentNode.robot.assist.a5);
                }
            }
            return 90;
        });
        joint7.eulerRotation.z = Qt.binding(function(){
            if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                return false;
            if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
            {
                if(JSession.currentScript.currentNode.robot.type===3)
                {
                    return -Number(JSession.currentScript.currentNode.robot.assist.a6);
                }
            }
            return 0;
        });
    }

    Joint1
    {
        id: joint1
        simulation: isScriptNode
        position: Qt.vector3d(0, 932.5, 193.58)
        Joint2
        {
            id: joint2
            simulation: isScriptNode
            // eulerRotation.y:(JSession.opened && JRobot.connected) ? Number(-JSession.script.get(JScriptController.index).robot.target.a1) : 0
            position: Qt.vector3d(0, 274.47, 0)
            Joint3
            {
                id: joint3
                simulation: isScriptNode
                // eulerRotation.x:(JSession.opened && JRobot./*connected*/) ? Number(JSession.script.get(JScriptController.index).robot.target.a2) : -90
                position: Qt.vector3d(0, 245.53, 160)
                Joint4
                {
                    id: joint4
                    simulation: isScriptNode
                    // eulerRotation.x:(JSession.opened && JRobot.connected) ? Number(JSession.script.get(JScriptController.index).robot.target.a3) : 90
                    position: Qt.vector3d(-20.3, 0, 780.04)
                    Joint5
                    {
                        id: joint5
                        simulation: isScriptNode
                        position: Qt.vector3d(115.1, 149.98, 299.96)
                        // eulerRotation.z:(JSession.opened && JRobot.connected) ? Number(-JSession.script.get(JScriptController.index).robot.target.a4) : 0
                        Joint6
                        {
                            id: joint6
                            simulation: isScriptNode
                            // eulerRotation.x:(JSession.opened && JRobot.connected) ? Number(JSession.script.get(JScriptController.index).robot.target.a5) : 90
                            position: Qt.vector3d(-42, 0, 560)
                            Joint7
                            {
                                id: joint7
                                simulation: isScriptNode
                                // eulerRotation.z:(JSession.opened && JRobot.connected) ? Number(-JSession.script.get(JScriptController.index).robot.target.a6) : 0
                                position: Qt.vector3d(42, 0, 139)

                            }
                        }
                    }
                }
            }
        }
    }
}
