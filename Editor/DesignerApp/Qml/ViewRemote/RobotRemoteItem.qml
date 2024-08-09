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

Control
{
    id: control
    implicitWidth: 300
    implicitHeight: 30

    property real jogValue: 0
    property string dataText: ""
    property string dataTitleText: ""
    property string leftTitleText: ""
    property string rightTitleText: ""
    property color showColor: "#202020"

    signal jogMoved();
    signal jogStop();

    background: Rectangle
    {
        color: showColor
    }

    contentItem: Item
    {
        Item
        {
            id: centerItem
            width: 80
            height: parent.height
            anchors.centerIn: parent
            Text
            {
                id: dataTitleItem
                color: "darkorange"
                text: control.dataTitleText
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
            }
            Text
            {
                id: dataTextItem
                color: "aliceblue"
                text: control.dataText
                anchors.left: dataTitleItem.right
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Slider
        {
            id: rightSlider
            anchors.left: centerItem.right
            anchors.right: parent.right
            anchors.rightMargin: 1
            anchors.verticalCenter: parent.verticalCenter
            height: 24
            from: 0
            value: 0
            to: 100
            stepSize: 1
            background: Rectangle
            {
                radius: 12
                color: "#262626"
                border.color: "darkgrey"
                Text
                {
                    id: rightTextItem
                    color: "aliceblue"
                    text: control.rightTitleText
                    font.pixelSize: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle
                {
                    width: rightSlider.handle.x+rightSlider.handle.width
                    height: parent.height
                    color: "lightslategray"
                    radius: 12
                    Text
                    {
                        font.pixelSize: 12
                        text: rightSlider.value.toFixed(0)+"%"
                        color: "lightyellow"
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
            handle: Rectangle
            {
                x: rightSlider.leftPadding + rightSlider.visualPosition * (rightSlider.availableWidth - width)
                y: rightSlider.topPadding + rightSlider.availableHeight / 2 - height / 2
                implicitWidth: 24
                implicitHeight: 24
                radius: 12
                color: rightSlider.pressed ? "lightsteelblue" : "lightslategrey"
                border.color: "#bdbebf"
                Text
                {
                    text: qsTr(">")
                    color: "lightyellow"
                    anchors.centerIn: parent
                }
            }
            onPressedChanged:
            {
                control.jogValue = 0;
                if(!pressed)
                {
                    value = 0;
                    control.jogStop();
                }
            }
            onMoved:
            {
                control.jogValue = rightSlider.value/100;
                control.jogMoved();
            }
        }
        Slider
        {
            id: leftSlider
            anchors.left: parent.left
            anchors.leftMargin: 1
            anchors.right: centerItem.left
            anchors.verticalCenter: parent.verticalCenter
            height: 24
            from: 0
            value: 100
            to: 100
            stepSize: 1
            background: Rectangle
            {
                radius:12
                color: "#262626"
                border.color: "gray"
                Text
                {
                    id: leftTextItem
                    color: "aliceblue"
                    text: control.leftTitleText
                    font.pixelSize: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle
                {
                    x: leftSlider.handle.x
                    width: parent.width-leftSlider.handle.x
                    height: parent.height
                    color: "lightslategray"
                    radius: 12
                    Text
                    {
                        font.pixelSize: 12
                        text: (100-leftSlider.value.toFixed(0))+"%"
                        color: "lightyellow"
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
            handle: Rectangle
            {
                x: leftSlider.leftPadding + leftSlider.visualPosition * (leftSlider.availableWidth - width)
                y: leftSlider.topPadding + leftSlider.availableHeight / 2 - height / 2
                implicitWidth: 24
                implicitHeight: 24
                radius: 12
                color: leftSlider.pressed ? "lightsteelblue" : "lightslategrey"
                border.color: "#bdbebf"
                Text
                {
                    text: qsTr("<")
                    color: "lightyellow"
                    anchors.centerIn: parent
                }
            }
            onPressedChanged:
            {
                control.jogValue = 0;
                if(!pressed)
                {
                    value = 100;
                    control.jogStop();
                }
            }
            onMoved:
            {
                control.jogValue = -((100-leftSlider.value)/100);
                control.jogMoved();
            }
        }
    }
}

