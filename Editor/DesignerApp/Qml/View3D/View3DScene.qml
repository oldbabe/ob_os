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
import QtQuick3D.Helpers 6.2
import QtQuick.Controls 6.2
import JMoco 1.0

//! 3D场景
View3D
{
    id: mainView
    anchors.fill: parent

    DirectionalLight{}
    PerspectiveCamera
    {
        id:pCamera
        clipFar:100000.0
        position: JGlobalRemoteParam.cameraPosition
        eulerRotation: JGlobalRemoteParam.cameraEulerRotation
    }
    //地面
    Model
    {
        source: "#Cube"
        scale: Qt.vector3d(200, 0.01, 200);
        materials: [ PrincipledMaterial
            {
                metalness:0.1
                roughness:0.2
                baseColor:"#CCCCCC"
            }
        ]
    }
    //场景加载
    Loader3D
    {
        id: root3D
        Component.onCompleted:
        {
            source = Qt.binding(function (){
                if(JRobot.model === "JAKA_Zu12")
                    return "qrc:/Qml/View3D/JAKA/JakaScene.qml";
                else if(JRobot.model === "KUKA-KR20-R3100")
                    return "qrc:/Qml/View3D/XRKUKA3130/kuka3130Scene.qml";
                else if(JRobot.model === "KUKA-KR20-R1810")
                    return "qrc:/Qml/View3D/KUKA/KukaScene.qml";
                else
                    return "";
            })
        }
    }
    //! [导入场景]

    //! [environment]
    environment: SceneEnvironment

    {
        backgroundMode: SceneEnvironment.Color
        clearColor:"skyblue"
    }

    //! [environment]
    //! [网格线]
//            AxisHelper
//            {
//                gridColor: Qt.rgba(0.5, 0.5, 0.5, 0.5)
//            }
    //! [网格线]
    //! [主相机控制器]
    //灯光
    DirectionalLight
    {
        ambientColor: "#EEEEEE"
        brightness: 1.5
        castsShadow: true
    }
    WasdController
    {
        id:wasdCtrl
        controlledObject: pCamera
        acceptedButtons: Qt.RightButton
        onInputsNeedProcessingChanged:
        {
            if(!inputsNeedProcessing)
            {
                JGlobalRemoteParam.cameraPosition = pCamera.position;
                JGlobalRemoteParam.cameraEulerRotation = pCamera.eulerRotation;
            }
        }
    }
    //! [主相机控制器]
    Image
    {
        width: 80
        height: 80
        source: "qrc:/Image/icon_coordinate.png"
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
    }
}
