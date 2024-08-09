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
    position: Qt.vector3d(0, 0, 0)

    //是否为节点机械臂
    property int isScriptNode: 0
    //末端透视相机引用别名
//    property alias tcpCamera: camera

    Joint1
    {
        id: joint1
        simulation: isScriptNode
        position: Qt.vector3d(0, 575,0)
        //世界坐标系初始化
        HyaloplasmicSphere
        {
            id: coodWorldSphere
            position: Qt.vector3d(0,0, 0)
            eulerRotation.x:-90

            CoordinateFrame
            {
                id: coodWorld
                longZoom:4
            }

        }
        Joint2
        {
            id: joint2
            simulation: isScriptNode
            eulerRotation.y:Number(-JRobot.position.a1)
            position: Qt.vector3d(0, 170, 0)
            Joint3
            {
                id: joint3
                simulation: isScriptNode
                eulerRotation.z:Number(-JRobot.position.a2)
                position: Qt.vector3d(175,405, 106.5)
                Joint4
                {
                    id: joint4
                    simulation: isScriptNode
                    eulerRotation.z:Number(-JRobot.position.a3)
                    position: Qt.vector3d(1282.05, 0, 72)
                    Joint5
                    {
                        id: joint5
                        simulation: isScriptNode
                        eulerRotation.x:Number(-JRobot.position.a4)
                        position: Qt.vector3d(1421.51, 50, -189.5)
                        Joint6
                        {
                            id: joint6
                            eulerRotation.z:Number(-JRobot.position.a5)
                            simulation: isScriptNode
                            position: Qt.vector3d(213.5, 0, 48.8)
                            Joint7
                            {
                                id: joint7
                                simulation: isScriptNode
                                eulerRotation.x:Number(-JRobot.position.a6)
                                position: Qt.vector3d(130.5, 0, -44.1)
                                 //坐标系初始化
                                HyaloplasmicSphere
                                {
                                    id: coodToolSphere
                                    position: Qt.vector3d(40,0,0)
                                    eulerRotation.z:-90
                                    eulerRotation.y:90

                                    CoordinateFrame
                                    {
                                        id: coodTool
                                        // visible: JRobotInstall.currentIndex !== -1
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

