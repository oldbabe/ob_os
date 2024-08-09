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
import QtMultimedia 6.2
import QtQuick.Controls 6.2
import JMoco 1.0

Rectangle
{
    id:root
    color: "#363636"
    focus: true

    property var keyData: []
    property bool keyRemoteEnable: false

    Keys.onPressed:function(event)
    {
        if(!event.isAutoRepeat)
        {
            switch(event.key)
            {
            case Qt.Key_W:
            case Qt.Key_A:
            case Qt.Key_S:
            case Qt.Key_D:
            case Qt.Key_R:
            case Qt.Key_F:
            case Qt.Key_Up:
            case Qt.Key_Down:
            case Qt.Key_Left:
            case Qt.Key_Right:
            case Qt.Key_Less:
            case Qt.Key_Greater:
            {
                keyData.push(event.key)
                sendKeyRemoteData();
                break;
            }
            case Qt.Key_Shift:
            {
                sendKeyRemoteData(Qt.Key_Shift);
                break;
            }
            default:
                break;
            }
        }
    }
    Keys.onReleased:function(event)
    {
        if(!event.isAutoRepeat)
        {
            switch(event.key)
            {
            case Qt.Key_W:
            case Qt.Key_A:
            case Qt.Key_S:
            case Qt.Key_D:
            case Qt.Key_R:
            case Qt.Key_F:
            case Qt.Key_Up:
            case Qt.Key_Down:
            case Qt.Key_Left:
            case Qt.Key_Right:
            case Qt.Key_Less:
            case Qt.Key_Greater:
            {
                keyData.pop(event.key)
                sendKeyRemoteData();
                break;
            }
            case Qt.Key_Shift:
            {
                sendKeyRemoteData(Qt.Key_Shift);
                break;
            }
            default:break;
            }
        }
    }

    function sendKeyRemoteData(key = -1)
    {
        var flag = false;
        if(!keyRemoteEnable && key === Qt.Key_Shift)
        {
            keyRemoteEnable = true;
            flag = true;
        }
        else if(keyRemoteEnable && key === -1)
        {
            flag = true;
        }
        else if(keyRemoteEnable && key === Qt.Key_Shift)
        {
            keyRemoteEnable = false;
            JRobot.runStop();
        }
        if(flag)
        {
            //读取机械臂运动方向数据
            var dir = [];
            dir = JRobot.getRemoteDirection();
            //[0]前-后 [1]左-右 [2]上-下 [3]左转-右转 [4]抬头-低头 [5]左翻转-右翻转
            var data = {"P1":"0","P2":"0","P3":"0","P4":"0","P5":"0","P6":"0","P7":"0"};
            //前-后
            var dataKey = "P"+String(Math.abs(dir[0]));
            if(keyData.lastIndexOf(Qt.Key_R) !== -1)
                data[dataKey] = dir[0]>0?"0.1":"-0.1";
            else if(keyData.lastIndexOf(Qt.Key_F) !== -1)
                data[dataKey] = dir[0]>0?"-0.1":"0.1";
            //上-下
            dataKey = "P"+String(Math.abs(dir[2]));
            if(keyData.lastIndexOf(Qt.Key_S) !== -1)
                data[dataKey] = dir[2]>0?"0.1":"-0.1";
            else if(keyData.lastIndexOf(Qt.Key_W) !== -1)
                data[dataKey] = dir[2]>0?"-0.1":"0.1";
            //左-右
            dataKey = "P"+String(Math.abs(dir[1]));
            if(keyData.lastIndexOf(Qt.Key_D) !== -1)
                data[dataKey] = dir[1]>0?"0.1":"-0.1";
            else if(keyData.lastIndexOf(Qt.Key_A) !== -1)
                data[dataKey] = dir[1]>0?"-0.1":"0.1";
            //抬头-低头
            dataKey = "P"+String(Math.abs(dir[4]));
            if(keyData.lastIndexOf(Qt.Key_Up) !== -1)
                data[dataKey] = dir[4]>0?"0.05":"-0.05";
            else if(keyData.lastIndexOf(Qt.Key_Down) !== -1)
                data[dataKey] = dir[4]>0?"-0.05":"0.05";
            //左转-右转
            dataKey = "P"+String(Math.abs(dir[3]));
            if(keyData.lastIndexOf(Qt.Key_Right) !== -1)
                data[dataKey] = dir[3]>0?"0.05":"-0.05";
            else if(keyData.lastIndexOf(Qt.Key_Left) !== -1)
                data[dataKey] = dir[3]>0?"-0.05":"0.05";
            //左翻转-右翻转
            dataKey = "P"+String(Math.abs(dir[5]));
            if(keyData.lastIndexOf(Qt.Key_Greater) !== -1)
                data[dataKey] = dir[5]>0?"0.05":"-0.05";
            else if(keyData.lastIndexOf(Qt.Key_Less) !== -1)
                data[dataKey] = dir[5]>0?"-0.05":"0.05";
            //发送指令
            JRobot.jogMovement(9,data);
        }
    }

    Component.onCompleted:
    {
        JCameraDevice.videoSink = videoOutput.videoSink;
    }
    Component.onDestruction:
    {
        JCameraDevice.stop();
    }
    Text
    {
        font.pixelSize: 16
        color: "aliceblue"
        text: qsTr("无视频输入")
        visible: JCameraDevice.currentIndex === -1 ? true : false
        anchors.centerIn: parent
    }
    MouseArea
    {
        anchors.fill: parent
        onPressed: root.forceActiveFocus();

            // var pos = parent.mapToItem(videoOutput.contentRect,mouseX,mouseY);
            // console.log(mouseX,mouseY,pos,videoOutput.contentRect.x,
            //             videoOutput.contentRect.y,
            //             videoOutput.contentRect.width,
            //             videoOutput.contentRect.height)
        // }
    }
    VideoOutput
    {
        id: videoOutput
        anchors.fill: parent
        visible: JCameraDevice.currentIndex > -1 ? true : false
        MouseArea
        {
            x:videoOutput.contentRect.x
            y:videoOutput.contentRect.y
            width:videoOutput.contentRect.width
            height:videoOutput.contentRect.height
            onPressed:
            {
                root.forceActiveFocus();
                if(JCameraDevice.controlFlag === JCameraDevice.ControlFlags_NULL)
                    return;
                var setX = 0,setY = 0;
                if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_0)
                {
                    setX = mouseX/videoOutput.contentRect.width;
                    setY = mouseY/videoOutput.contentRect.height;
                }
                else if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_90)
                {
                    setX = mouseY/videoOutput.contentRect.height;
                    setY = (videoOutput.contentRect.width-mouseX)/videoOutput.contentRect.width;;
                }
                else if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_180)
                {
                    setX = (videoOutput.contentRect.width-mouseX)/videoOutput.contentRect.width;;
                    setY = (videoOutput.contentRect.height-mouseY)/videoOutput.contentRect.height;
                }
                else if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_270)
                {
                    setX = (videoOutput.contentRect.height-mouseY)/videoOutput.contentRect.height;;
                    setY = mouseX/videoOutput.contentRect.width;
                }
                if(JCameraDevice.controlFlag === JCameraDevice.ControlFlags_Focus)
                    JCamera.setFocusPosition(setX,setY,1);
                else if(JCameraDevice.controlFlag === JCameraDevice.ControlFlags_FocusShoot)
                    JCamera.setFocusPosition(setX,setY,2);
            }
        }
    }
    //底部焦点指示器
    Rectangle
    {
        height: 4
        radius: 1
        color: "darkgrey"
        visible: parent.focus
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: parent.width/4
        anchors.rightMargin: parent.width/4
    }
}
