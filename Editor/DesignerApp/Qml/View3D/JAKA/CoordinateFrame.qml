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

Node
{
    id: root

    //是否可以选中
    property bool pickable: false
    property double longZoom :1
    //x轴
    Model
    {
        id:redCylinder
        source: "#Cylinder"
        eulerRotation.z: 90
        scale: Qt.vector3d(0.1,2*longZoom,0.1)//缩放为圆柱体
        position: Qt.vector3d(100*longZoom, 0, 0)//由于缩放操作,需要移动
        pickable: root.pickable
        property bool checked: false//选中状态：鼠标选中后置true
        materials: [
            DefaultMaterial
            {
                //选中时更新颜色
                diffuseColor: (parent.checked||redCone.checked)?Qt.rgba(0.4, 0.2, 0.3, 1.0):Qt.rgba(1, 0, 0, 1.0)
                //关闭光照影响
                lighting: DefaultMaterial.NoLighting
            }
        ]
    }
    //x轴 箭头
    Model
    {
        id:redCone
        source: "#Cone"
        eulerRotation.z: -90
        position: Qt.vector3d(200*longZoom, 0, 0)
        scale: Qt.vector3d(0.5,1,0.5)
        pickable: root.pickable
        property bool checked: false
        materials: [
            DefaultMaterial
            {
                diffuseColor: (parent.checked||redCylinder.checked)?Qt.rgba(0.4, 0.2, 0.3, 1.0):Qt.rgba(1, 0, 0, 1.0)
                lighting: DefaultMaterial.NoLighting
            }
        ]
    }
    //y轴
    Model
    {
        id:greenCylinder
        source: "#Cylinder"
        position: Qt.vector3d(0, 100*longZoom, 0)
        scale: Qt.vector3d(0.1,2*longZoom,0.1)
        pickable: root.pickable
        property bool checked: false
        materials: [
            DefaultMaterial
            {
                diffuseColor: (parent.checked||greenCone.checked)?Qt.rgba(0.4, 0.2, 0.3, 1.0):Qt.rgba(0, 1, 0, 1.0)
                lighting: DefaultMaterial.NoLighting
            }
        ]
    }
    Model
    {
        id:greenCone
        source: "#Cone"
        position: Qt.vector3d(0, 200*longZoom, 0)
        pickable: root.pickable
        scale: Qt.vector3d(0.5,1,0.5)
        property bool checked: false
        materials: [
            DefaultMaterial
            {
                diffuseColor: (parent.checked||greenCylinder.checked)?Qt.rgba(0.4, 0.2, 0.3, 1.0):Qt.rgba(0, 1, 0, 1.0)
                lighting: DefaultMaterial.NoLighting
            }
        ]
    }
    //z轴
    Model
    {
        id:blueCylinder
        source: "#Cylinder"
        eulerRotation.x: 90
        position: Qt.vector3d(0, 0, 100*longZoom)
        scale: Qt.vector3d(0.1,2*longZoom,0.1)
        pickable: root.pickable
        property bool checked: false
        materials: [
            DefaultMaterial
            {
                diffuseColor: (parent.checked||blueCone.checked)?Qt.rgba(0.4, 0.2, 0.3, 1.0):Qt.rgba(0, 0, 1, 1.0)
                lighting: DefaultMaterial.NoLighting
            }
        ]
    }
    Model
    {
        id:blueCone
        source: "#Cone"
        eulerRotation.x: 90
        position: Qt.vector3d(0, 0, 200*longZoom)
        pickable: root.pickable
        scale: Qt.vector3d(0.5,1,0.5)
        property bool checked: false
        materials: [
            DefaultMaterial
            {
                diffuseColor: (parent.checked||blueCylinder.checked)?Qt.rgba(0.4, 0.2, 0.3, 1.0):Qt.rgba(0, 0, 1, 1.0)
                lighting: DefaultMaterial.NoLighting
            }
        ]
    }
    //球
    Model
    {
        id: sphere
        source: "#Sphere"
        pickable: root.pickable
        scale: Qt.vector3d(0.5,0.5,0.5)
        property bool checked: false
        materials: [
            DefaultMaterial
            {
                diffuseColor: parent.checked?Qt.rgba(0.4, 0.2, 0.3, 1.0):Qt.rgba(0.9, 0.9, 0.9, 1.0)
                lighting: DefaultMaterial.NoLighting
            }
        ]
    }
    //选中功能实现
    // MouseArea
    // {
    //     id: mouseArea
    //     anchors.fill: parent

    //     property Model checkNode: null

    //     onPressed:
    //     {
    //         //鼠标位置转换为相机远视口的空间位置
    //         var pos = mcamera.mapFromViewport(Qt.vector3d(mouseX/mView3D.width,mouseY/mView3D.height,mcamera.clipNear));
    //         //按下3d位置的方向
    //         var direction = Qt.vector3d(pos.x-mcamera.position.x,pos.y-mcamera.position.y,pos.z-mcamera.position.z);
    //         //查找从鼠标按下方向存在的首个模型
    //         var res = mView3D.rayPick(mcamera.position,direction);
    //         //查找成功
    //         if(res.objectHit !== null)
    //         {
    //             checkNode = res.objectHit;
    //             checkNode.checked = true;
    //         }
    //     }

    //     onReleased:
    //     {
    //         if(checkNode !== null)
    //         {
    //             checkNode.checked = false;
    //             checkNode = null;
    //         }
    //     }
    // }
}

