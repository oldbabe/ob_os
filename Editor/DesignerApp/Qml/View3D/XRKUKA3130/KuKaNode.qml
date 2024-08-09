﻿/*
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
    // eulerRotation.y:(JSession.opened) ? Number(JSession.script.currentNode.robot.target.a7) : 0
    //是否为节点机械臂
    property int isScriptNode: 1
    //末端透视相机引用别名
//    property alias tcpCamera: camera

    Joint1
    {
        id: joint1
        simulation: isScriptNode
        position: Qt.vector3d(0, 575,0)
        Joint2
        {
            id: joint2
            simulation: isScriptNode
            // eulerRotation.y: windowRoot.rest3dValue ? Number(-JRobotInstall.resetModel.get(JRobotInstall.currentIndex)["A1"]):
            //                                           ((JSession.opened) ? Number(-JSession.script.currentNode.robot.target.a1) : 0)

            position: Qt.vector3d(0, 170, 0)
            Joint3
            {
                id: joint3
                simulation: isScriptNode
                // eulerRotation.z: windowRoot.rest3dValue ? Number(-JRobotInstall.resetModel.get(JRobotInstall.currentIndex)["A2"]):
                //                                           ((JSession.opened) ? Number(-JSession.script.currentNode.robot.target.a2) : 90)

                position: Qt.vector3d(175,405, 106.5)
                Joint4
                {
                    id: joint4
                    simulation: isScriptNode
                    // eulerRotation.z: windowRoot.rest3dValue ? Number(-JRobotInstall.resetModel.get(JRobotInstall.currentIndex)["A3"]):
                    //                                           ((JSession.opened) ? Number(-JSession.script.currentNode.robot.target.a3) : -120)

                    position: Qt.vector3d(1282.05, 0, 72)
                    Joint5
                    {
                        id: joint5
                        simulation: isScriptNode
                        // eulerRotation.x: windowRoot.rest3dValue ? Number(-JRobotInstall.resetModel.get(JRobotInstall.currentIndex)["A4"]):
                        //                                           ((JSession.opened) ? Number(-JSession.script.currentNode.robot.target.a4) : 0)

                        position: Qt.vector3d(1421.51, 50, -189.5)
                        Joint6
                        {
                            id: joint6
                            // eulerRotation.z: windowRoot.rest3dValue ? Number(-JRobotInstall.resetModel.get(JRobotInstall.currentIndex)["A5"]):
                            //                                           ((JSession.opened) ? Number(-JSession.script.currentNode.robot.target.a5) : -60)

                            simulation: isScriptNode
                            position: Qt.vector3d(213.5, 0, 48.8)
                            Joint7
                            {
                                id: joint7
                                // eulerRotation.x: windowRoot.rest3dValue ? Number(-JRobotInstall.resetModel.get(JRobotInstall.currentIndex)["A6"]):
                                //                                           ((JSession.opened) ? Number(-JSession.script.currentNode.robot.target.a6) : 0)

                                simulation: isScriptNode
                                position: Qt.vector3d(130.5, 0, -44.1)
                            }
                        }
                    }
                }
            }
        }
    }
}
