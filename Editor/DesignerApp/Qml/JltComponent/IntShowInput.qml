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
import QtQuick.Layouts 6.2

Item
{
    id: root
    clip: true
    implicitHeight: 34
    implicitWidth: 100

    property string titleText: "标题"
    property alias valueItem: valueText

    signal valueChanged(int text);

    MouseArea
    {
        anchors.fill: parent
        propagateComposedEvents: true
        acceptedButtons: Qt.LeftButton
        onDoubleClicked:
        {
            titleEditor.readOnly = false;
            titleEditor.text = valueText.text;
            stackLayout.currentIndex = 1;
            titleEditor.selectAll();
            titleEditor.forceActiveFocus();
        }
    }
    StackLayout
    {
        id: stackLayout
        anchors.fill: parent
        currentIndex: 0
        Item
        {
            implicitHeight: parent.height
            implicitWidth: parent.width
            Text
            {
                id: nameText
                color: "aliceblue"
                text: root.titleText
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
            Text
            {
                id: valueText
                color: "aliceblue"
                text: qsTr("0")
                leftPadding: 5
                anchors.left: nameText.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
            }
        }
        TextField
        {
            id: titleEditor
            implicitHeight: parent.height
            implicitWidth: parent.width
            color: "aliceblue"
            validator: IntValidator{bottom: 0;}
            verticalAlignment: TextField.AlignVCenter
            background: Rectangle
            {
                color: "#202020"
            }
            onEditingFinished:
            {
                if(titleEditor.text.length === 0)
                {
                    titleEditor.text = nodeData.title;
                }
                else
                {
                    if(valueText.text !== titleEditor.text)
                    {
                        valueText.text = titleEditor.text;
                        root.valueChanged(titleEditor.text);
                    }
                }
                stackLayout.currentIndex = 0;
                titleEditor.focus = false;
            }
        }
    }
}
