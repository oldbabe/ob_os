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

import "./DevelopItems"
import "../Component"

import JMoco 1.0

Rectangle
{

    id:root
    color: "#202020"

    Component.onDestruction:
    {
        JRobot.installSave();
    }

    SplitView
    {
        anchors.fill: parent
        orientation: Qt.Horizontal

        handle: Rectangle
        {
            implicitWidth: 1
            color: SplitHandle.hovered ? "#EEEEEE" : "#000000"
        }
        Rectangle
        {
            color: "#202020"
            implicitWidth:parent.width*0.2
            SplitView.maximumWidth: parent.width*0.5
            SplitView.minimumWidth: parent.width*0.2

            Item
            {
                id: listviewItem
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right

                ListView
                {
                    id:listview
                    anchors.fill: parent
                    model: JRobot.installCount()
                    clip:true
                    spacing: 1
                    delegate:Control
                    {
                        id:control
                        hoverEnabled: true
                        width: listviewItem.width
                        height: 28

                        background:Rectangle
                        {
                            color: JRobot.installIndex===index?"steelblue":"#585858"
                            Text
                            {
                                anchors.centerIn: parent
                                text: JRobot.installGet(index).title
                                elide: Text.ElideRight
                                color: "aliceblue"
                            }
                        }
                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked:
                            {
                                root.focus = true;
                                JRobot.installIndex = index;
                                JRobot.installApply(JRobot.installIndex);
                            }
                        }
                    }
                }
            }
        }
        Item
        {
            implicitWidth: parent.width*0.8
            implicitHeight: parent.height
            SplitView.maximumWidth: parent.width*0.8
            SplitView.minimumWidth: parent.width*0.5
            MouseArea
            {
                anchors.fill: parent
                onPressed: parent.focus=true;
            }

            Column
            {
                topPadding: 5
                width: parent.width
                height: parent.height
                Column
                {
                    id: topItem
                    height: 90
                    Row
                    {
                        spacing: 5
                        height: 30

                        Text
                        {
                            width: 50
                            height: titleInputItem.height
                            color: "aliceblue"
                            text: "标题:"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        BaseTextItemString
                        {
                            id: titleInputItem
                            width: 180
                            enterText:"双击修改"
                            valueText: JRobot.installGet(JRobot.installIndex).title
                            onTextEditFinished:function(textData)
                            {
                                JRobot.installGet(JRobot.installIndex).title = textData;
                            }
                        }
                    }
                    Row
                    {
                        spacing: 5
                        height: 30
                        Text
                        {
                            text: "型号:"
                            color: "aliceblue"
                            width: 50
                            height: titleInputItem.height
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        Text
                        {
                            text: JRobot.installGet(JRobot.installIndex).model
                            color: "aliceblue"
                            height: titleInputItem.height
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    //复位按键
                    Row
                    {
                        spacing: 20
                        leftPadding: 10
                        ToolButton
                        {
                            width: 100
                            height: 26
                            showText: "复位"
                            Component.onCompleted:
                            {
                                enable = Qt.binding(function(){
                                    var install = JRobot.installGet(JRobot.installIndex);
                                    if(install.reset.a1==="0"&&install.reset.a2==="0"&&install.reset.a3==="0"&&
                                            install.reset.a4==="0"&&install.reset.a5==="0"&&install.reset.a6==="0")
                                    {
                                        return false;
                                    }
                                    return true;
                                });
                            }

                            onButtonEntered: windowRoot.rest3dValue = true;
                            onButtonExited: windowRoot.rest3dValue = false;
                            onButtonPressed:JRobot.installReset(JRobot.installIndex);
                            onButtonRelease:JRobot.runStop();
                        }
                        ToolButton
                        {
                            width: 100
                            height: 26
                            showText: "导入当前数据"
                            onButtonClicked: JRobot.installUpdate(JRobot.installIndex);
                        }
                    }
                }

                Flickable
                {
                    clip: true
                    boundsMovement :Flickable.StopAtBounds

                    height: parent.height-topItem.height-parent.spacing
                    width: parent.width

                    contentHeight: column.height
                    ScrollBar.vertical: ScrollBar
                    {
                        policy:ScrollBar.AlwaysOff
                    }
                    Column
                    {
                        id: column
                        width: parent.width-4
                        spacing: 1
                        leftPadding: 2
                        topPadding: 2
                        RobotWorldItem
                        {
                            id:robotWord
                            width: parent.width
                        }
                        RobotToolItem
                        {
                            id:robotTool
                            width: parent.width
                        }
                        RobotLoadeItem
                        {
                            id:robotLoad
                            width: parent.width
                        }
                    }
                }
            }
        }
    }
}
