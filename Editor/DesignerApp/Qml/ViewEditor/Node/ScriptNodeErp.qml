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
import JltView 1.0
import JMoco 1.0

JltScriptNode
{
    id: control
    implicitWidth: 130
    implicitHeight: 36
    transformOrigin: Item.TopLeft
    inputConnector: null
    outputConnector: outConnector
    z:mouseArea.containsMouse?1:0

    property JNode nodeData: null
    property JltScriptScene scriptScene: null
    property JltScriptShape scriptShape: null
    property JltScriptDrop scriptDrop: null
    property real sceneX: 0
    property real sceneY: 0

    signal openNodeMenu(var item,real x,real y);

    Component.onCompleted:
    {
        scale = Qt.binding(function(){return scriptScene.axisScale;});
        x = Qt.binding(function(){return scriptScene.originX+sceneX*scriptScene.gridWidth;});
        y = Qt.binding(function(){return scriptScene.originY+sceneY*scriptScene.gridWidth;});
        scriptShape.appendNode(control);
        if(nodeData.checked)
        {
            scriptScene.currentNode = control;
        }
    }

    //拖拽后呼出的菜单关闭处理
    Connections
    {
        target: scriptDrop
        function onMenuClosed()
        {
            if(outConnector.dragActive)
                outConnector.stopDrag();
        }
    }

    function disconnectInputConnector()
    {

    }

    function disconnectOutputConnector()
    {
        if(control.outputConnector.bindConnector !== null)
        {
            control.outputConnector.bindConnector.bindConnector = null;
            control.outputConnector.bindConnector = null;
            scriptShape.update();
        }
    }

    Item
    {
        id: background
        anchors.fill: parent
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        //边框
        Rectangle
        {
            id: borderItem
            anchors.fill: parent
            antialiasing: true
            opacity: 0.9
            radius: 5
            color: "#262626"
            border.width: 1
            border.color: (outConnector.dragActive)?"cornflowerblue":((mouseArea.containsMouse||scriptScene.currentNode===control)?"peru":"darkgrey")

            Item
            {
                anchors.fill: parent

                Item
                {
                    id: imageeItem
                    width: parent.height
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    Image
                    {
                        id: nodeTypeImage
                        anchors.fill: parent
                        anchors.margins: 10
                        fillMode: Image.PreserveAspectFit
                        source:  "qrc:/Image/icon_startNode.png"
                    }
                }

                Text
                {
                    id: titleItem
                    anchors.left: imageeItem.right
                    anchors.verticalCenter: parent.verticalCenter
                    color: "aliceblue"
                    font.pixelSize: 14
                    text: qsTr("ERP标定")
                }

                MouseArea
                {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton|Qt.RightButton
                    drag.target: control
                    onPressed: function(mouse)
                    {
                        parent.forceActiveFocus();
                        scriptScene.currentNode = control;
                        if(JSession.currentScript.currentNode !== control.nodeData)
                        {
                            JSession.currentScript.currentNode = control.nodeData;
                            JSession.currentScript.changed = true;
                        }
                        //仅在鼠标左键按下时拖拽
                        if(mouse.button === Qt.LeftButton)
                        {
                            drag.target = control;
                        }
                        else
                        {
                            drag.target = null;
                            //右键菜单
                            if(mouse.button === Qt.RightButton)
                            {
                                scriptScene.openNodeMenu(control,mouse.x,mouse.y);
                            }
                        }
                    }

                    onPositionChanged: function(mouse)
                    {
                        if(drag.active)
                        {
                            //更新场景位置
                            control.sceneX = (control.x-control.scriptScene.originX)/control.scriptScene.gridWidth;
                            control.sceneY = (control.y-control.scriptScene.originY)/control.scriptScene.gridWidth;
                            nodeData.x = control.sceneX;
                            nodeData.y = control.sceneY;
                            //拖动到边缘时自动运动
                            var lenWidth = 50;
                            var moveMouseX = mouse.x+control.x;
                            if(moveMouseX>(control.scriptScene.width-lenWidth))
                            {
                                control.scriptScene.originX-=((moveMouseX-(control.scriptScene.width-lenWidth))/20);
                            }
                            else if(moveMouseX < lenWidth)
                            {
                                control.scriptScene.originX-=(moveMouseX-lenWidth)/20;
                            }
                            var moveMouseY = mouse.y+control.y;
                            if(moveMouseY>(control.scriptScene.height-lenWidth))
                            {
                                control.scriptScene.originY-=((moveMouseY-(control.scriptScene.height-lenWidth))/20);
                            }
                            else if(moveMouseY < lenWidth)
                            {
                                control.scriptScene.originY-=(moveMouseY-lenWidth)/20;
                            }
                            JSession.currentScript.changed = true;
                        }
                    }
                }
            }
        }
    }


    Item
    {
        anchors.fill: parent
        Rectangle
        {
            radius: 6
            width: 12
            height: 12
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            color: (outConnector.bindConnector!==null||outMouseArea.containsMouse||outConnector.dropActive)?"dodgerblue":borderItem.border.color
            JltScriptConnector
            {
                id: outConnector
                anchors.fill: parent
                connectorType: JltScriptConnector.ConnectorType_Output
                disableConnector: null
                dragPenStyle: 2//虚线
                onDragActiveChanged:
                {
                    if(dragActive)
                    {
                        control.scriptShape.setActiveConnector(outConnector);
                    }
                    else
                    {
                        control.scriptShape.clearActiveConnector();
                    }
                }
                //拖拽移动事件
                onDragMove: function(point)
                {
                    control.scriptShape.updateActiveConnectorEndF(control.scriptShape.mapFromGlobal(point));
                }
                //连接改变事件
                onBindUpdate:
                {
                    if(outConnector.bindConnector == null)
                    {
                        nodeData.next = null;
                    }
                    else
                    {
                        var nextNode = outConnector.bindConnector.getBindNode();
                        if(nextNode !== null)
                        {
                            nodeData.next = nextNode.nodeData;
                        }
                    }
                    JSession.currentScript.changed = true;
                }
            }
            MouseArea
            {
                id: outMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onPressed:
                {
                    outConnector.startDrag();
                }
            }
        }
    }
}
