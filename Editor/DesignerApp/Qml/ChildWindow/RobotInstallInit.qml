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
    height: 110
    flags: Qt.Dialog
    modality: Qt.WindowModal
    title: qsTr("机械臂安装方式初始化")

    property string displayText: "当前安装方式与机械臂的数据不同,请重新设置!"

    Connections
    {
        target: window
        function onClosing(event)
        {
            event.accepted = true;
            window.destroy();
            JRobot.installSave();
        }
    }

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
            id:column
            Item
            {
                height: 60
                width: parent.width-column.padding*2
                Text
                {
                    anchors.centerIn: parent
                    text: window.displayText
                    color: "aliceblue"
                }
            }

            Item
            {
                height: 30
                width: parent.width-column.padding*2
                Button
                {
                    id: rightButton
                    text: "以机械臂为准"
                    height: 24
                    width: 100
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    onClicked:
                    {
                        JRobot.installUpdate(JRobot.installIndex);
                        window.close();
                    }
                }
                Button
                {
                    id: leftButton
                    text: "以安装方式为准"
                    height: 24
                    width: 100
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: rightButton.left
                    anchors.rightMargin: 10
                    onClicked:
                    {
                        JRobot.installApply(JRobot.installIndex);
                        window.close();
                    }
                }
            }
        }
    }
}
