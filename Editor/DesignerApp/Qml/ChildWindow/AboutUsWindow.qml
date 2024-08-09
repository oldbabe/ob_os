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

Window
{
    id: window
    width: 400
    height: 300
    maximumHeight: height
    minimumHeight: height
    minimumWidth: width
    maximumWidth: width
    title: "关于我们"
    modality: Qt.WindowModal
    flags: Qt.Dialog

    Connections
    {
        target: window
        function onClosing()
        {
            window.destroy()
        }
    }

    Rectangle
    {
        anchors.fill: parent
        color: "#404040"

        Item
        {
            anchors.fill: parent
            anchors.margins: 10

            Column
            {
                spacing: 10
                Row
                {
                    spacing: 20
                    Item
                    {
                        width: 80
                        height: 30
                        Text
                        {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 13
                            color: "aliceblue"
                            text: qsTr("版权所有")
                        }
                    }
                    TextInput
                    {
                        height: 30
                        font.pixelSize: 13
                        color: "aliceblue"
                        verticalAlignment: TextInput.AlignVCenter
                        text: qsTr("上海倔老头智能科技有限公司")
                    }
                }
                Row
                {
                    spacing: 20
                    Item
                    {
                        width: 80
                        height: 30
                        Text
                        {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 13
                            color: "aliceblue"
                            text: qsTr("微信")
                        }
                    }
                    TextInput
                    {
                        height: 30
                        font.pixelSize: 13
                        color: "aliceblue"
                        readOnly: true
                        selectByMouse: true
                        verticalAlignment: TextInput.AlignVCenter
                        text: qsTr("z1273305587")
                    }
                }
                Row
                {
                    spacing: 20
                    Item
                    {
                        width: 80
                        height: 30
                        Text
                        {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 13
                            color: "aliceblue"
                            text: qsTr("电话")
                        }
                    }
                    TextInput
                    {
                        height: 30
                        font.pixelSize: 13
                        color: "aliceblue"
                        readOnly: true
                        selectByMouse: true
                        verticalAlignment: TextInput.AlignVCenter
                        text: qsTr("15536506659")
                    }
                }
                Row
                {
                    spacing: 20
                    Item
                    {
                        width: 80
                        height: 30
                        Text
                        {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 13
                            color: "aliceblue"
                            text: qsTr("B站账号")
                        }
                    }
                    TextInput
                    {
                        height: 30
                        font.pixelSize: 13
                        color: "aliceblue"
                        readOnly: true
                        selectByMouse: true
                        verticalAlignment: TextInput.AlignVCenter
                        text: qsTr("倔老头的会议室")
                    }
                }
                Row
                {
                    spacing: 20
                    Item
                    {
                        width: 80
                        height: 30
                        Text
                        {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 13
                            color: "aliceblue"
                            text: qsTr("B站UID")
                        }
                    }
                    TextInput
                    {
                        height: 30
                        font.pixelSize: 13
                        color: "aliceblue"
                        readOnly: true
                        selectByMouse: true
                        verticalAlignment: TextInput.AlignVCenter
                        text: qsTr("3546726275221982")
                    }
                }
                Row
                {
                    spacing: 20
                    Item
                    {
                        width: 80
                        height: 30
                        Text
                        {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 13
                            color: "aliceblue"
                            text: qsTr("教程")
                        }
                    }
                    Text
                    {
                        height: 30
                        font.pixelSize: 13
                        textFormat: Text.RichText
                        verticalAlignment: TextInput.AlignVCenter
                        text: "<a href='https://space.bilibili.com/3546726275221982?spm_id_from=333.337.0.0' style='color:#4682b4'>bilibili.com</a>"
                        onLinkActivated:function(link)
                        {
                            Qt.openUrlExternally(link);
                        }
                    }
                }
                Row
                {
                    spacing: 20
                    Item
                    {
                        width: 80
                        height: 30
                        Text
                        {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 13
                            color: "aliceblue"
                            text: qsTr("github")
                        }
                    }
                    Text
                    {
                        height: 30
                        font.pixelSize: 13
                        textFormat: Text.RichText
                        verticalAlignment: TextInput.AlignVCenter
                        text: "<a href='https://github.com/oldbabe/ob_os' style='color:#4682b4'>github.com</a>"
                        onLinkActivated:function(link)
                        {
                            Qt.openUrlExternally(link);
                        }
                    }
                }
            }
        }
    }
}
