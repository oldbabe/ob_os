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
    //是否为节点机械臂
    property int isScriptNode: 1
    //复位位置显示状态声明
    property bool resetButtonEnable: windowRoot.rest3dValue

    Component.onCompleted:
    {
        slidingTable.position.z = Qt.binding(function(){
            if(slidingTable.resetButtonEnable)
                return Number(JRobot.installGet(JRobot.installIndex).reset.a7);
            if(JSession.currentScript===null || JSession.currentScript.currentNode === null)
                return 0;
            return Number(JSession.currentScript.currentNode.robot.target.a7);
        });
        joint2.eulerRotation.y = Qt.binding(function(){
            if(slidingTable.resetButtonEnable)
                return -Number(JRobot.installGet(JRobot.installIndex).reset.a1);
            if(JSession.currentScript===null || JSession.currentScript.currentNode === null)
                return 0;
            return -Number(JSession.currentScript.currentNode.robot.target.a1);
        });
        joint3.eulerRotation.x = Qt.binding(function(){
            if(slidingTable.resetButtonEnable)
                return Number(JRobot.installGet(JRobot.installIndex).reset.a2);
            if(JSession.currentScript===null || JSession.currentScript.currentNode === null)
                return -90;
            return Number(JSession.currentScript.currentNode.robot.target.a2);
        });
        joint4.eulerRotation.x = Qt.binding(function(){
            if(slidingTable.resetButtonEnable)
                return Number(JRobot.installGet(JRobot.installIndex).reset.a3);
            if(JSession.currentScript===null || JSession.currentScript.currentNode === null)
                return 90;
            return Number(JSession.currentScript.currentNode.robot.target.a3);
        });
        joint5.eulerRotation.z = Qt.binding(function(){
            if(slidingTable.resetButtonEnable)
                return -Number(JRobot.installGet(JRobot.installIndex).reset.a4);
            if(JSession.currentScript===null || JSession.currentScript.currentNode === null)
                return 0;
            return -Number(JSession.currentScript.currentNode.robot.target.a4);
        });
        joint6.eulerRotation.x = Qt.binding(function(){
            if(slidingTable.resetButtonEnable)
                return Number(JRobot.installGet(JRobot.installIndex).reset.a5);
            if(JSession.currentScript===null || JSession.currentScript.currentNode === null)
                return 90;
            return Number(JSession.currentScript.currentNode.robot.target.a5);
        });
        joint7.eulerRotation.z = Qt.binding(function(){
            if(slidingTable.resetButtonEnable)
                return -Number(JRobot.installGet(JRobot.installIndex).reset.a6);
            if(JSession.currentScript===null || JSession.currentScript.currentNode === null)
                return 0;
            return -Number(JSession.currentScript.currentNode.robot.target.a6);
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
            position: Qt.vector3d(0, 274.47, 0)
            Joint3
            {
                id: joint3
                simulation: isScriptNode
                position: Qt.vector3d(0, 245.53, 160)
                Joint4
                {
                    id: joint4
                    simulation: isScriptNode
                    position: Qt.vector3d(-20.3, 0, 780.04)
                    Joint5
                    {
                        id: joint5
                        simulation: isScriptNode
                        position: Qt.vector3d(115.1, 149.98, 299.96)
                        Joint6
                        {
                            id: joint6
                            simulation: isScriptNode
                            position: Qt.vector3d(-42, 0, 560)
                            Joint7
                            {
                                id: joint7
                                simulation: isScriptNode
                                position: Qt.vector3d(42, 0, 139)
                            }
                        }
                    }
                }
            }
        }
    }
}
