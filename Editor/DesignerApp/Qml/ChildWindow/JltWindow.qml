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
    id: root

    width: 640
    height: 480
    visible: true
    minimumHeight: 300
    minimumWidth: 300
    flags: Qt.Window | Qt.FramelessWindowHint   //去掉原窗口标题栏
    color: "transparent"                        //窗口颜色设为透明

    property Item customItem: null
    property Item toolItem: null
    property color backgroundColor: "#212121"

    Component.onCompleted:
    {
        if(customItem !== null)
        {
            customItem.parent = backgroundObject
            customItem.x = Qt.binding(function(){return topObject.x+4;})
            customItem.y = Qt.binding(function(){return topObject.height;})
            customItem.height = Qt.binding(function(){return (root.height-topObject.height)-4;})
            customItem.width = Qt.binding(function(){return root.width-8;})
        }
        if(toolItem !== null)
        {
            toolItem.parent = topObject
            toolItem.x = Qt.binding(function(){return topObject.x;})
            toolItem.y = Qt.binding(function(){return topObject.y;})
            toolItem.height = Qt.binding(function(){return topObject.height;})
            toolItem.width = Qt.binding(function(){return topObject.width-rowObject.width;})
        }
    }

    Rectangle
    {
        id: backgroundObject
        anchors.fill: parent
        color: root.backgroundColor
        //窗体拖拽：窗口最大化时拖拽会使窗口自动恢复成默认大小
        Item
        {
            id: topObject
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40

            MouseArea
            {
                anchors.fill: parent
                drag.target: parent
                //拖拽窗体
                drag.onActiveChanged:
                {
                    if (drag.active)
                    {
                        root.startSystemMove()
                    }
                }
                //双击最大化，再次双击恢复默认大小
                onDoubleClicked:
                {
                    root.visibility = root.visibility == 4 ? 2 : 4
                }
            }

            Row
            {
                id: rowObject
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                Rectangle
                {
                    width: parent.height
                    height: parent.height
                    color:Qt.darker(root.backgroundColor,minMouseArea.containsMouse?0.5:1)
                    Canvas
                    {
                        anchors.fill: parent
                        onPaint:
                        {
                            var ctx = getContext("2d");
                            ctx.clearRect(0, 0, width, height);
                            ctx.lineWidth = 1;
                            ctx.strokeStyle = "aliceblue";
                            ctx.beginPath();
                            ctx.moveTo(width/3, height/2);
                            ctx.lineTo(width/3*2, height/2);
                            ctx.stroke();
                        }
                    }
                    MouseArea
                    {
                        id: minMouseArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: root.visibility = 3  //QWindow::Minimized
                    }
                }
                Rectangle
                {
                    id: midRectangle
                    width: parent.height
                    height: parent.height
                    color:Qt.darker(root.backgroundColor,maxMouseArea.containsMouse?0.5:1)
                    Canvas
                    {
                        id: midCanvas
                        anchors.fill: parent
                        Connections
                        {
                            target: root
                            function onVisibilityChanged()
                            {
                                midCanvas.requestPaint();
                            }
                        }
                        onPaint:
                        {
                            var ctx = getContext("2d");
                            ctx.clearRect(0, 0, width, height);
                            ctx.lineWidth = 1;
                            ctx.fillStyle = root.backgroundColor;
                            ctx.strokeStyle = "aliceblue";
                            ctx.beginPath();
                            if(root.visibility !== 4)
                            {
                                ctx.roundedRect((width-width/4)/2,(height-height/4)/2,width/4,height/4,0,0);
                                ctx.stroke();
                            }
                            else
                            {
                                ctx.roundedRect((width-width/4)/2+2,(height-height/4)/2,width/4-2,height/4-2,0,0);
                                ctx.stroke();
                                ctx.clearRect((width-width/4)/2,(height-height/4)/2+2,width/4-2,height/4-2);
                                ctx.beginPath();
                                ctx.roundedRect((width-width/4)/2,(height-height/4)/2+2,width/4-2,height/4-2,0,0);
                                ctx.stroke();
                            }
                        }
                    }
                    MouseArea
                    {
                        id: maxMouseArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: root.visibility = root.visibility == 4 ? 2 : 4   //最大化：QWindow::Maximized = 4 原尺寸：QWindow::Windowed = 2
                    }
                }
                Rectangle
                {
                    width: parent.height
                    height: parent.height
                    color: closeMouseArea.containsMouse?"red":root.backgroundColor
                    Canvas
                    {
                        anchors.fill: parent
                        onPaint:
                        {
                            var ctx = getContext("2d");
                            ctx.clearRect(0, 0, width, height);
                            ctx.lineWidth = 1;
                            ctx.strokeStyle = "aliceblue";
                            ctx.beginPath();
                            ctx.moveTo(width/3, height/3);
                            ctx.lineTo(width/3*2, height/3*2);
                            ctx.moveTo(width/3*2, height/3);
                            ctx.lineTo(width/3, height/3*2);
                            ctx.stroke();
                        }
                    }
                    MouseArea
                    {
                        id: closeMouseArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: root.close()
                    }
                }
            }
        }

        //调整窗口大小：↑ ↓ ← → ↖ ↗ ↙ ↘
        Item
        {
            id: dragObject
            anchors.fill: parent
            enabled: root.visibility !== 4  //窗口最大化时禁用
            z: 0x1000

            property int dragWidth: 4

            Item    //上边缘调整窗口大小
            {
                width: parent.width; height: parent.dragWidth

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeVerCursor   //改变鼠标样式，让用户知道现在正处于调整窗口大小状态，带ver的是上下箭头，带hor的是左右箭头
                    onPressed: root.startSystemResize(Qt.TopEdge)
                }
            }

            Item    //下边缘调整窗口大小
            {
                width: parent.width; height: parent.dragWidth; anchors.bottom: parent.bottom

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeVerCursor
                    onPressed: root.startSystemResize(Qt.BottomEdge)
                }
            }

            Item    //左边缘调整窗口大小
            {
                width: parent.dragWidth; height: parent.height

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeHorCursor
                    onPressed: root.startSystemResize(Qt.LeftEdge)
                }
            }

            Item    //右边缘调整窗口大小
            {
                width: parent.dragWidth; height: parent.height; anchors.right: parent.right

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeHorCursor
                    onPressed: root.startSystemResize(Qt.RightEdge)
                }
            }

            Item    //左上角调整窗口大小
            {
                width: parent.dragWidth+2; height: parent.dragWidth+2

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeFDiagCursor
                    onPressed: root.startSystemResize(Qt.LeftEdge | Qt.TopEdge)
                }
            }

            Item    //右上角调整窗口大小
            {
                width: parent.dragWidth+2; height: parent.dragWidth+2; anchors.right: parent.right

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeBDiagCursor
                    onPressed: root.startSystemResize(Qt.RightEdge | Qt.TopEdge)
                }
            }

            Item    //左下角调整窗口大小
            {
                width: parent.dragWidth+2; height: parent.dragWidth+2; anchors.bottom: parent.bottom

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeBDiagCursor
                    onPressed: root.startSystemResize(Qt.LeftEdge | Qt.BottomEdge)
                }
            }

            Item    //右下角调整窗口大小
            {
                width: parent.dragWidth+2; height: parent.dragWidth+2; anchors.bottom: parent.bottom; anchors.right: parent.right

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SizeFDiagCursor
                    onPressed: root.startSystemResize(Qt.RightEdge | Qt.BottomEdge)
                }
            }
        }
    }
}

