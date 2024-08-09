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
import QtQuick 2.15
import QtQuick.Controls 6.2

Rectangle
{
    id: root
    focus: true
    implicitWidth: 60
    implicitHeight: 30
    radius: 3
    opacity: 0.85
    color: root.checked?"dodgerblue":"#202020"
    border.color: "#444444"
    property int iconWidth: width
    property int iconHeight: height
    property bool checked: false
    property string showText: ""
    property string checkedText: ""
    property string iconSource: ""
    property string normalColor: "gainsboro"
    property string horverColor: "white"
    property string normalTextColor: "gainsboro"
    property string horverTextColor: "white"
    signal buttonClicked();
    Row
    {
        anchors.fill: parent
        Button
        {
            id: button
            enabled: false
            down:false;flat: true
            width: parent.height;height: parent.height
            icon.source: iconSource
            icon.color: mouseArea.containsMouse?horverColor:normalColor
            icon.width: iconWidth
            icon.height: iconHeight
            background: Item{}
        }
        Text
        {
            height: parent.height
            width: parent.width-button.width
            color: mouseArea.containsMouse?horverTextColor:normalTextColor
            text: root.checked?root.checkedText:root.showText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }
    MouseArea
    {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked:
        {
            root.focus = true;
            root.buttonClicked();
        }
    }
}
