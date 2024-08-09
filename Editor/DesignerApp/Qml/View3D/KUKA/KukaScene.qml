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
import QtQuick3D 6.2

import JMoco 1.0
//模型加载节点
Node
{
    id: root
    Connections
    {
        target: JRobot
        function onCoordinateChanged()
        {
            kukaNode.setCoodTool(JRobot.tool.tran.x,JRobot.tool.tran.y,JRobot.tool.tran.z,
                                 JRobot.tool.rpy.rx,JRobot.tool.rpy.ry,JRobot.tool.rpy.rz);
            kukaNode.setCoodWorld(JRobot.world.tran.x,JRobot.world.tran.y,JRobot.world.tran.z,
                                  JRobot.world.rpy.rx,JRobot.world.rpy.ry,JRobot.world.rpy.rz);
        }
    }
    //轨道
    Railway
    {
        id: railWay
        eulerRotation.y: 90
        //圆弧关键帧辅助位置显示
        KukaNodeRun
        {
            id: assistNode
            Component.onCompleted:
            {
                visible = Qt.binding(function(){
                    if(targetNode.resetButtonEnable)
                        return false;
                    if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                        return false;
                    if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
                    {
                        if(JSession.currentScript.currentNode.robot.type===3)
                            return true;
                    }
                    return false;
                });
            }
        }
        //圆弧关键帧目标位置显示
        KuKaNode
        {
            id: targetNode
            Component.onCompleted:
            {
                visible = Qt.binding(function(){
                    if(targetNode.resetButtonEnable)
                        return true;
                    if(JSession.currentScript===null || JSession.currentScript.currentNode===null)
                        return false;
                    if(JSession.currentScript.currentNode.type === JNode.NodeType_Move)
                        return true;
                    return false;
                });
            }
        }
        //同步机械臂节点
        KukaNodeRealy
        {
            id: kukaNode
        }
    }
}
