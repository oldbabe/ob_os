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

import "./ViewCamera"
import "./View3D"
import "./ViewEditor"
import "./ViewRemote"
import "./ViewTool"
import "./ChildWindow"
import "./JltComponent"

JltWindow
{
    id: windowRoot
    width: 1600
    height: 900
    visible: true

    property bool rest3dValue: false //[3D视图目标位置显示类型]=true显示复位位置 =false显示节点位置
    property bool saveWindowFlag: true  //关闭窗口时是否需要打开保存窗口

    Component.onCompleted:
    {
        //影棚设备初始化(必须)
        JStudioController.controllerType = JStudioController.RemoteControllerOnly;
        JStudioController.init();
        JFollowfocusRemote.setup();//跟焦器初始化
        JGamepad.init();
        JSession.init();
        windowRoot.y = (windowRoot.Screen.height-height)/2
        windowRoot.x = (windowRoot.Screen.width-width)/2
    }

    Connections
    {
        target: windowRoot
        function onClosing(event)
        {
            if(saveWindowFlag)
            {
                var saveFlag = false;
                for(var i = 0; i < JSession.model.count(); i++)
                {
                    if(JSession.model.getScript(i).changed)
                    {
                        saveFlag = true;
                        break;
                    }
                }
                if(saveFlag)
                {
                    event.accepted = false;
                    var component = Qt.createComponent("qrc:/Qml/ChildWindow/CloseMainWindow.qml");
                    //提取对象
                    if(component.status === Component.Ready)
                    {
                        var objWindow = component.createObject(windowRoot);
                        objWindow.quitWindow.connect(windowRoot.closeWindow);
                        objWindow.show();
                        return;
                    }
                }
            }

            //窗口退出
            // jCameraLayou.closedCamera();
            JGamepad.release();
            JFollowfocusRemote.uninstall();
            JStudioController.release();
            JRobot.installSave();
            event.accepted = true;
        }
    }

    function closeWindow()
    {
        saveWindowFlag = false;
        closeTimer.start();
    }

    Timer
    {
        id:closeTimer
        interval: 50
        onTriggered:windowRoot.close();
    }

    toolItem: Item
    {
        Item
        {
            id: logoItem
            width: parent.height
            height: width
            Image
            {
                width: parent.width/3*2
                height: parent.height/3*2
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:/Image/icon_logo.png"
            }
        }

        MainMenuBar
        {
            anchors.left: logoItem.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    customItem: Item
    {
        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true
            onClicked:parent.forceActiveFocus();
        }

        ViewTool
        {
            id: viewTool
            width: parent.width
            anchors.centerIn: parent
        }

        SplitView
        {
            id: topSplitView
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: viewTool.top
            anchors.bottomMargin: 2
            orientation: Qt.Horizontal
            handle: Rectangle
            {
                implicitWidth: 2
                color: (SplitHandle.pressed||SplitHandle.hovered) ? "steelblue" : "transparent"
            }
            //相机页面
            ViewCamera
            {
                id: jCameraLayou
                SplitView.preferredWidth: windowRoot.width/2-166
            }
            //3D页面
            View3D
            {
                id:jThreeD
                SplitView.preferredWidth: windowRoot.width/2-166
            }
            //遥控页面
            ViewRemote
            {
                id:jremoteLayout
            }
        }
        //底部
        ViewScript
        {
            id: bottomSplitView
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: viewTool.bottom
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
        }
    }

    //机械臂安装方式
    Connections
    {
        target: JRobot
        function onConnectedChanged()
        {
            if(!JRobot.connected)
                return;
            var install = JRobot.installGet(JRobot.installIndex);
            if(install.model.length === 0)//没有机械臂型号数据则直接更新
            {
                JRobot.installUpdate(JRobot.installIndex);
            }
            else//当机械臂数据与安装方式不一致时,需要重新选择
            {
                robotWindowTimer.start();
            }
        }
        function onPluginMsgChanged(msg)
        {
            if(msg.popup === true)
            {
                var component = Qt.createComponent("qrc:/Qml/ChildWindow/RobotMsgWindow.qml");
                if (component.status === Component.Ready)
                {
                    var window = component.createObject(windowRoot,{errKey:msg.key,popupType:msg.code,errDescribe:msg.describe,errCause:msg.cause,errSolution:msg.solution});
                    window.show();
                }
                else
                {
                    console.log("failed:",component.errorString());
                }
            }
        }
    }

    Timer
    {
        id: robotWindowTimer
        interval: 100
        onTriggered:
        {
            var install = JRobot.installGet(JRobot.installIndex);
            var error = Math.abs(install.world.tran.x-JRobot.world.tran.x)+
                    Math.abs(install.world.tran.y-JRobot.world.tran.y)+
                    Math.abs(install.world.tran.z-JRobot.world.tran.z)+
                    Math.abs(install.world.rpy.rx-JRobot.world.rpy.rx)+
                    Math.abs(install.world.rpy.ry-JRobot.world.rpy.ry)+
                    Math.abs(install.world.rpy.rz-JRobot.world.rpy.rz)+
                    Math.abs(install.tool.tran.x-JRobot.tool.tran.x)+
                    Math.abs(install.tool.tran.y-JRobot.tool.tran.y)+
                    Math.abs(install.tool.tran.z-JRobot.tool.tran.z)+
                    Math.abs(install.tool.rpy.rx-JRobot.tool.rpy.rx)+
                    Math.abs(install.tool.rpy.ry-JRobot.tool.rpy.ry)+
                    Math.abs(install.tool.rpy.rz-JRobot.tool.rpy.rz)+
                    Math.abs(install.load.mass-JRobot.load.mass)+
                    Math.abs(install.load.tran.x-JRobot.load.tran.x)+
                    Math.abs(install.load.tran.y-JRobot.load.tran.y)+
                    Math.abs(install.load.tran.z-JRobot.load.tran.z)+
                    Math.abs(install.load.rpy.rx-JRobot.load.rpy.rx)+
                    Math.abs(install.load.rpy.ry-JRobot.load.rpy.ry)+
                    Math.abs(install.load.rpy.rz-JRobot.load.rpy.rz)+
                    Math.abs(install.load.inertia.x-JRobot.load.inertia.x)+
                    Math.abs(install.load.inertia.y-JRobot.load.inertia.y)+
                    Math.abs(install.load.inertia.z-JRobot.load.inertia.z);
            if(error>=0.1)
            {
                var component = Qt.createComponent("qrc:/Qml/ChildWindow/RobotInstallInit.qml");
                if (component.status === Component.Ready)
                {
                    var window = component.createObject(windowRoot);
                    window.show();
                }
            }
        }
    }

    //相机下载目录设置
    Connections
    {
        target: JCamera
        function onShowDownloadDirWindow()
        {
            windowRoot.showCameraDownloadSetWindow();
        }
    }

    Connections
    {
        target: JSession
        function onDirNameChanged()
        {
           if(!JCamera.connected && JSession.dirName!==JCamera.downloadDir)
                return;
            if(JSession.dirName !== JCamera.downloadDir)
            {
                windowRoot.showCameraDownloadSetWindow();
            }
        }
    }
    //打开新建下载目录设置窗口
    function showCameraDownloadSetWindow()
    {
        var component = Qt.createComponent("qrc:/Qml/ChildWindow/CameraDownloadSet.qml");
        if (component.status === Component.Ready)
        {
            var window = component.createObject(windowRoot);
            window.show();
        }
    }
    //切换会话
    function switchSession()
    {
        var path = JSession.getExistingDirectory("选择会话");
        if(path.length === 0)
            return;
        var res = JSession.openSession(path);
        if(res !== 0)
        {
            console.log("switchSession failed: ",res);
        }
    }

}
