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
    // position.z:(JRobot.loaded && JRobot.connected) ? Number(JRobot.position.a7) : 67.5
    //是否为节点机械臂
    property int isScriptNode: 0
    //末端透视相机引用别名
    Component.onCompleted:
    {
        position.z = Qt.binding(function(){return Number(JRobot.position.a7);});
        joint2.eulerRotation.y = Qt.binding(function(){return -Number(JRobot.position.a1)})
        joint3.eulerRotation.x = Qt.binding(function(){return Number(JRobot.position.a2)})
        joint4.eulerRotation.x = Qt.binding(function(){return Number(JRobot.position.a3)})
        joint5.eulerRotation.z = Qt.binding(function(){return -Number(JRobot.position.a4)})
        joint6.eulerRotation.x = Qt.binding(function(){return Number(JRobot.position.a5)})
        joint7.eulerRotation.z = Qt.binding(function(){return -Number(JRobot.position.a6)})
    }

    //设置世界坐标系
    function setCoodWorld(x,y,z,a,b,c)
    {
        coodWorld.position.x= x
        coodWorld.position.y= y
        coodWorld.position.z= z
        coodWorld.eulerRotation=Qt.vector3d(0,0,0)
        coodWorld.rotate(c,Qt.vector3d(0,0,1),Node.LocalSpace);
        coodWorld.rotate(b,Qt.vector3d(0,1,0),Node.LocalSpace);
        coodWorld.rotate(a,Qt.vector3d(1,0,0),Node.LocalSpace);
    }
    //设置工具坐标系
    function setCoodTool(x,y,z,a,b,c)
    {
        coodTool.position.x= -x
        coodTool.position.y= -y
        coodTool.position.z= z
        coodTool.eulerRotation=Qt.vector3d(0,0,0)
        coodTool.rotate(c,Qt.vector3d(0,0,1),Node.LocalSpace);
        coodTool.rotate(b,Qt.vector3d(0,1,0),Node.LocalSpace);
        coodTool.rotate(a,Qt.vector3d(1,0,0),Node.LocalSpace);
    }

    function updataTool()
    {
        // if(JRobotInstall.currentIndex !== -1)
        // {
        //     coodTool.position.x= Number(JRobotInstall.toolModel.get(JRobotInstall.currentIndex)["X"])
        //     coodTool.position.y= Number(JRobotInstall.toolModel.get(JRobotInstall.currentIndex)["Y"])
        //     coodTool.position.z= Number(JRobotInstall.toolModel.get(JRobotInstall.currentIndex)["Z"])
        //     coodTool.eulerRotation=Qt.vector3d(0,0,0)
        //     coodTool.rotate(Number(JRobotInstall.toolModel.get(JRobotInstall.currentIndex)["A"]),Qt.vector3d(0,0,1),Node.LocalSpace);
        //     coodTool.rotate(Number(JRobotInstall.toolModel.get(JRobotInstall.currentIndex)["B"]),Qt.vector3d(0,1,0),Node.LocalSpace);
        //     coodTool.rotate(Number(JRobotInstall.toolModel.get(JRobotInstall.currentIndex)["C"]),Qt.vector3d(1,0,0),Node.LocalSpace);
        // }
    }

    Joint1
    {
        id: joint1
        simulation: isScriptNode
        position: Qt.vector3d(0, 932.5, 193.58)
        //世界坐标系初始化
        HyaloplasmicSphere
        {
            id: coodWorldSphere
            eulerRotation.z:-90
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
            // eulerRotation.y:(JRobot.loaded && JRobot.connected) ? Number(-JRobot.position.a1) : 0
            position: Qt.vector3d(0, 274.47, 0)
            Joint3
            {
                id: joint3
                simulation: isScriptNode
                // eulerRotation.x:(JRobot.loaded && JRobot.connected) ? Number(JRobot.position.a2) : -90
                position: Qt.vector3d(0, 245.53, 160)
                Joint4
                {
                    id: joint4
                    simulation: isScriptNode
                    // eulerRotation.x:(JRobot.loaded && JRobot.connected) ? Number(JRobot.position.a3) :90
                    position: Qt.vector3d(-20.3, 0, 780.04)
                    Joint5
                    {
                        id: joint5
                        simulation: isScriptNode
                        // eulerRotation.z:(JRobot.loaded && JRobot.connected) ? Number(-JRobot.position.a4) : 0
                        position: Qt.vector3d(115.1, 149.98, 299.96)
                        Joint6
                        {
                            id: joint6
                            simulation: isScriptNode
                            // eulerRotation.x:(JRobot.loaded && JRobot.connected) ? Number(JRobot.position.a5) : 90
                            position: Qt.vector3d(-42, 0, 560)
                            Joint7
                            {
                                id: joint7
                                simulation: isScriptNode
                                // eulerRotation.z:(JRobot.loaded && JRobot.connected) ? Number(-JRobot.position.a6) : 0
                                position: Qt.vector3d(42, 0, 139)
                                //坐标系初始化
                                HyaloplasmicSphere
                                {
                                    id: coodToolSphere
                                    position: Qt.vector3d(0,0,40)
                                    eulerRotation.z:-90
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
