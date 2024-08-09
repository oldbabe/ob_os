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

Item
{
    id:root

    property string tagText: "空"
    property string suffixText:"-"
    property int cobWith:100
    property int cobHeight:22
    property int key:-1
    property bool wirtable:false
    property int currentIndex: control.currentIndex
    property string currentText: control.currentText
    property var comboxArray: ["First"]
    signal indexActivated(int index);
    property alias mComboBox:control
//    function setCurrentIndex(index)
//    {
//        control.currentIndex = index;
//    }
//    function setComboxArray(array)
//    {
//       root.comboxArray = array;
//    }
//    function setSuffixText(test)
//    {
//        root.suffixText = test;
//    }

    Text
    {
        id: textCRD1
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 5
        width: 100
        height: 25
        color: "#FFFFFF"
        font.pixelSize:12
        text: root.tagText
    }
    ComboBox
    {
        id: control
        anchors.left: textCRD1.right
        anchors.leftMargin: 3
        anchors.right: parent.right
        anchors.rightMargin: 10
        visible: wirtable
        model: comboxArray
        flat:true
        onActivated:(index)=>
        {
//            root.indexActivated(index);
        }

        //委托项
        delegate: ItemDelegate {
            id: itemDelegate
            width: control.width-2
            onClicked:root.indexActivated(control.highlightedIndex)
            contentItem: Text {
                text: control.textRole
                    ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole])
                    : modelData
                color: itemDelegate.hovered?"#D7D7D7":"#F2F2F2"
                font: control.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
//                覆盖鼠标
//                MouseArea{
//                    anchors.fill: parent
//                    onClicked:
//                    {
//                        console.log("click",control.highlightedIndex)
//                        //发送指令
//                        root.indexActivated(control.highlightedIndex)
//                        //关闭菜单
//                        control.popup.close();
//                    }
//                }
            }
            background: Rectangle
            {
                color: itemDelegate.hovered?"#169BD5":"#363636"
            }
        }
        //右边箭头
        indicator: Canvas {
            id: canvas
            x: control.width - width - control.rightPadding
            y: control.topPadding + (control.availableHeight - height) / 2
            width: 12
            height: 8
            contextType: "2d"

            Connections {
                target: control
                function onPressedChanged() { canvas.requestPaint(); }
            }
            //点击颜色
            onPaint: {
                context.reset();
                context.moveTo(0, 0);
                context.lineTo(width, 0);
                context.lineTo(width / 2, height);
                context.closePath();
                context.fillStyle = control.pressed ? "#969696" : "#696969"
                context.fill();
            }
        }
        //内容
        contentItem: Text {
            leftPadding: 0
            rightPadding: control.indicator.width + control.spacing

            text: control.displayText
            font: control.font
            color: control.pressed ? "#F2F2F2" : "#FFFFFF"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        //背景
        background: Rectangle {
            color: "#262626"
            implicitWidth: root.cobWith
            implicitHeight: root.cobHeight
            border.color: control.pressed ? "#696969" : "#494949"
            border.width: control.visualFocus ? 2 : 1
            radius: 2
        }


        popup: Popup {
            y: control.height - 1
            width: control.width
            implicitHeight: contentItem.implicitHeight + 2
            padding: 1
            contentItem: ListView {

                clip: true
                implicitHeight: contentHeight
                model: control.popup.visible ? control.delegateModel : null
//                currentIndex: control.highlightedIndex

                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle {
                border.color: "#303030"
                radius: 2
            }
        }
    }
    Rectangle
    {
        width: parent.width-textCRD1.width-10
        height: 25
        visible:  !wirtable
        anchors.left: textCRD1.right
        anchors.leftMargin: 3
        anchors.right: parent.right
        anchors.rightMargin: 10
        color: "#151515"
        border.color:"#505050"
        border.width:1
        radius: 2
        Text
        {
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            color: "#808080"
            text: root.suffixText

        }
    }

}
