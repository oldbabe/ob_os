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

Window
{
    id: window
    width: 400
    height: 260
    flags: Qt.Dialog
    modality: Qt.WindowModal
    title: popupType===2?"机械臂(错误消息)":"机械臂(报警消息)"

    Connections
    {
        target: window
        function onClosing()
        {
            window.destroy()
        }
    }

    //描述号
    property int errKey: 2
    //描述2报错 3警告
    property int popupType: 2
    //描述
    property string errDescribe: ""
    //原因
    property string errCause: ""
    //解决办法
    property string errSolution: ""

    Control
    {
        id: control
        padding: 10
        anchors.fill: parent
        background: Rectangle
        {
            color: "#303030"
        }
        contentItem: Column
        {
            spacing:10
            Control
            {
                width: parent.width
                height: 60
                topPadding:20
                background: Text
                {
                    text:"描述"+errKey
                    color: "aliceblue"
                    font.pixelSize: 12
                }
                contentItem: Rectangle
                {
                    radius: 5
                    color: "#303030"
                    border.width: 1
                    border.color: "#444444"
                    Text
                    {
                        text: window.errDescribe
                        color: "aliceblue"
                        font.pixelSize: 12
                        wrapMode: Text.WordWrap
                        anchors.fill: parent
                        leftPadding: 3
                        topPadding: 3
                    }
                }
            }
            Control
            {
                width: parent.width
                height: 60
                topPadding:20
                background: Text
                {
                    text:"原因"
                    color: "aliceblue"
                    font.pixelSize: 12
                }
                contentItem: Rectangle
                {
                    radius: 5
                    color: "#303030"
                    border.width: 1
                    border.color: "#444444"
                    Text
                    {
                        text: window.errCause
                        color: "aliceblue"
                        font.pixelSize: 12
                        wrapMode: Text.WordWrap
                        anchors.fill: parent
                        leftPadding: 3
                        topPadding: 3
                    }
                }
            }
            Control
            {
                width: parent.width
                height: 100
                topPadding:20
                background: Text
                {
                    text:"解决办法"
                    color: "aliceblue"
                    font.pixelSize: 12
                }
                contentItem: Rectangle
                {
                    radius: 5
                    color: "#303030"
                    border.width: 1
                    border.color: "#444444"
                    Text
                    {
                        text: window.errSolution
                        color: "aliceblue"
                        font.pixelSize: 12
                        wrapMode: Text.WordWrap
                        anchors.fill: parent
                        leftPadding: 3
                        topPadding: 3
                    }
                }
            }
        }
    }


}
