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
import "../../../JS/VisibleData.js" as VisibData
Node
{
    id: joint6_obj
    //是否为脚本展示结点
    property int simulation: 0

    Model
    {
        id: defaultobject
        source: "file:///"+VisibData.appirt()+"/JAKA/Joint6.mesh"

        materials: PrincipledMaterial
        {
            baseColor: simulation === 1? "#8080FF":(simulation === 0? "#778899":"#E68616")  //材质基础色
            roughness:0.2          //模型表面反射光线的强度
            metalness:0.2          //金属质感程度
        }
    }
}
