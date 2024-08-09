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
import "../Component"
import JMoco 1.0

Item
{

    id:root
    implicitHeight: tagItem.height + dataColumn.height + 1
    implicitWidth: 200

    Component.onCompleted:
    {
        tagItem.zoomFlag = true;
    }

    TagItem
    {
        id: tagItem
        tagText: "相机"
        norColor: "#000000"
        hovColor: "#303030"
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        onZoomFlagChanged:
        {
            cameraItem.visible = zoomFlag;
        }
    }
    Column
    {
        id: dataColumn
        spacing: 1
        anchors.top: tagItem.bottom
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right


        Rectangle
        {
            id:cameraItem
            width: parent.width
            height: 200
            color: "#202020"

            Text
            {
                id:camText
                text: "设备"
                color: "#EEEEEE"
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: 10
            }
            Text
            {
                text: JCamera.loaded && JCamera.connected ? JCamera.cameraName :"未获取到相机名称"
                color: "#EEEEEE"
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: camText.right
                anchors.leftMargin: 2
            }

            Item {
                id: electric
                width: 60
                height: 40
                anchors.right: parent.right
                anchors.rightMargin: 2
                anchors.top: parent.top
                anchors.topMargin: 2
                property color textColor:"#000000"

                state: Number(JCamera.batteryRemaining.value)>50 ? "high" :(Number(JCamera.batteryRemaining.value)<20?"low":"half")
                Text
                {
                    anchors.centerIn: electric.Center
                    text:"电量"+JCamera.batteryRemaining.value + "%"
                    color:electric.textColor
                }

                states:[
                    State
                    {
                        name: "high"
                        PropertyChanges {
                            target: electric ;
                            textColor:"#66EE55" ;
                        }
                    },
                    State
                    {
                        name: "half"
                        PropertyChanges {
                            target: electric
                            textColor:"#DDBB55" ;
                        }
                    },
                    State {
                        name: "low"
                        PropertyChanges {
                            target: electric
                            textColor:"#DD3636" ;
                        }
                    }
                ]
            }

            Text
            {
                id:downCameraTablt
                text: "相机下载地址:"
                color: "#EEEEEE"
                anchors.top: camText.bottom
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: 10
            }
            Text
            {
                id:downCameraText
                text: JCamera.connected ? JCamera.downloadDir : "相机未连接"
                color: "#EEEEEE"
                elide: Text.ElideMiddle
                anchors.left: downCameraTablt.right
                anchors.leftMargin: 5
                anchors.verticalCenter: downCameraTablt.verticalCenter
            }
            ToolButton
            {
                id:downButton
                width: 50
                height: downCameraTablt.height
                anchors.verticalCenter: downCameraTablt.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 5
                showText: "设置"
                onButtonClicked: windowRoot.showCameraDownloadSetWindow();
            }

            //左框
            Rectangle
            {
                id:showRect
                width: parent.width/5*3-7
                height: 150
                color: "#151515"
                radius: 10
                anchors.left: parent.left
                anchors.leftMargin: 7
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                border.width: 2
                border.color: "#050505"

                //对焦模式
                Text
                {
                    text: JCamera.loaded && JCamera.connected ? JCamera.focusMode.value : "MF"
                    color: JCamera.focusMode.writable ===1 ? "#EEEEEE":"#666666"
                    font.pointSize: 20
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }

                //ISO
                Text
                {
                    id:isotext
                    text: JCamera.loaded && JCamera.connected ? JCamera.isoSensitivity.value : "1600"
                    color: JCamera.isoSensitivity.writable ===1 ? "#EEEEEE":"#666666"
                    font.pointSize: 20
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Text
                {
                    text: ("ISO")
                    color: JCamera.isoSensitivity.writable ===1 ? "#EEEEEE":"#666666"
                    font.pointSize: 14
                    anchors.left: isotext.left
                    anchors.bottom: isotext.top
                    anchors.bottomMargin: 2
                }
                //光圈-右下
                Text
                {
                    id:fnumberText
                    text: JCamera.loaded && JCamera.connected ? JCamera.fNumber.value : "2.8"
                    color: JCamera.fNumber.writable ===1 ? "#EEEEEE":"#666666"
                    font.pointSize: 20
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                }
                Text
                {
                    text:  "F"
                    color: JCamera.fNumber.writable ===1 ? "#EEEEEE":"#666666"
                    font.pointSize: 20
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.right: fnumberText.left
                    anchors.rightMargin: 2
                }
                //快门-右上
                Text
                {
                    text: JCamera.loaded && JCamera.connected ? JCamera.shutterSpeed.value : "1/50"
                    color: JCamera.shutterSpeed.writable ===1 ? "#EEEEEE":"#666666"
                    font.pointSize: 20
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                }
            }
            //右框
            Rectangle
            {
                id:funRect
                width: parent.width/5*2-14
                height: 50
                color: "#151515"
                radius: 10
                anchors.right: parent.right
                anchors.rightMargin: 7
                anchors.top: showRect.top
                border.width: 2
                border.color: "#050505"

                ToolButton
                {
                    anchors.centerIn: parent
                    enable: JCamera.loaded && JCamera.connected
                    width: 30
                    height: 30
                    icon: "qrc:/Image/icon_node_del.png"
                    opacityIMG: enable? 1.0 : 0.5
                    enterText: "相机储存卡1快速格式化"
                    onButtonEntered: entered = true;
                    onButtonExited: entered = false;
                    onButtonClicked: JCamera.quickFormat();
                }
            }
            //拍摄按钮
            Item
            {
                width: parent.width/5*2-14
                height: 100
                anchors.horizontalCenter: funRect.horizontalCenter
                anchors.bottom: showRect.bottom
                anchors.bottomMargin: 15

                ToolButton
                {
                    id:photoButton
                    width: 50
                    height: 50
                    padding:0
                    enterText: "拍照"
                    icon:"qrc:/Image/icon_Camera_Photo.png"
                    backAdius: width/2
                    anchors.bottom: parent.bottom
                    anchors.left: parent.horizontalCenter
                    anchors.leftMargin: 1
                    opacityIMG: 0.7
                    onButtonEntered: photoButton.entered = true;
                    onButtonExited: photoButton.entered = false;
                    onButtonLeftClicked:
                    {
                        JCamera.shooting(1)
                    }
                }

                ToolButton
                {
                    id:videoButton
                    width: 30
                    height: 30
                    padding:0
                    enterText: "录像"
                    icon:"qrc:/Image/icon_Camera_Video.png"
                    backAdius: width/2
                    anchors.bottom: parent.bottom
                    anchors.right: parent.horizontalCenter
                    anchors.rightMargin: 9
                    opacityIMG: 0.7
                    onButtonEntered: videoButton.entered = true;
                    onButtonExited: videoButton.entered = false;
                    state: JCamera.recordingState.value === "1" ? "run" : "stop"
                    states: [
                        State
                        {
                            name: "run"
                            PropertyChanges
                            {
                               target: videoButton; icon: "qrc:/Image/icon_Camera_Video_run.png"
                            }
                        },
                        State
                        {
                            name: "stop"
                            PropertyChanges
                            {
                               target: videoButton; icon: "qrc:/Image/icon_Camera_Video.png"
                            }
                        }
                    ]
                    onButtonClicked:
                    {
                        if(videoButton.state === "stop")
                        {
                            JCamera.filmRecording(true);
                        }
                        else if(videoButton.state === "run")
                        {
                            JCamera.filmRecording(false);
                        }

                    }

                }

                ToolButton
                {
                    id:focusButton
                    width: 30
                    height: 30
                    padding:0
                    enterText: "对焦"
                    icon:"qrc:/Image/icon_FollowFocus.png"
                    backAdius: width/2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 40
                    anchors.right: parent.horizontalCenter
                    anchors.rightMargin: 9
                    opacityIMG: 0.7
                    onButtonEntered: focusButton.entered = true;
                    onButtonExited: focusButton.entered = false;
                    onButtonPressed: JCamera.s1Shooting(true)
                    onButtonRelease: JCamera.s1Shooting(false)
                }
            }
        }
    }
}
