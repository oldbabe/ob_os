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
import JltView 1.0
import JMoco 1.0
import "../../JltComponent"

JltScriptNode
{
    id: control
    implicitWidth: 220
    implicitHeight: 36
    transformOrigin: Item.TopLeft
    inputConnector: inConnector
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

        if(nodeData.robot.type === 1)
            nodeTypeImage.source = "qrc:/Image/icon_ptpNode.png";
        else if(nodeData.robot.type === 2)
            nodeTypeImage.source = "qrc:/Image/icon_lineNode.png";
        else if(nodeData.robot.type === 3)
            nodeTypeImage.source = "qrc:/Image/icon_aroNode.png";

        borderItem.border.color = Qt.binding(function(){
            if(control.nodeData === null)
                return "darkgrey";

            if(scriptScene.currentNode===control)
                return "peru";
            else if(inConnector.dragActive||outConnector.dragActive||mouseArea.containsMouse)
                return "cornflowerblue";
            else
                return "darkgrey";
        });
        titleEditor.text = control.nodeData.title;
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
            if(inConnector.dragActive)
                inConnector.stopDrag();
            if(outConnector.dragActive)
                outConnector.stopDrag();
        }
    }

    function disconnectInputConnector()
    {
        if(control.inputConnector.bindConnector !== null)
        {
            control.inputConnector.bindConnector.bindConnector = null;
            control.inputConnector.bindConnector = null;
            scriptShape.update();
        }
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

            MouseArea
            {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                propagateComposedEvents: true
                acceptedButtons: Qt.LeftButton|Qt.RightButton
                drag.target: control
                onPressAndHold: function(event)
                {
                    titleEditor.readOnly = false;
                    titleEditor.focus = true;
                    stackLayout.currentIndex = 1;
                    titleEditor.selectAll();
                    titleEditor.forceActiveFocus();
                }
                onPressed: function(mouse)
                {
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
                        var lenWidth = 30;
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


    Item
    {
        anchors.fill: parent
        //输入口
        Rectangle
        {
            id: inputItem
            width: 12
            height: 12
            radius: 6
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            color: (inConnector.bindConnector!==null||inMouseArea.containsMouse||inConnector.dropActive)?"dodgerblue":borderItem.border.color
            JltScriptConnector
            {
                id: inConnector
                anchors.fill: parent
                connectorType: JltScriptConnector.ConnectorType_Input
                disableConnector: outConnector
                onDragActiveChanged:
                {
                    if(dragActive)
                    {
                        control.scriptShape.setActiveConnector(inConnector);
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
                    if(inConnector.bindConnector == null)
                    {
                        nodeData.last = null;
                    }
                    else
                    {
                        var lastNode = inConnector.bindConnector.getBindNode();
                        if(lastNode !== null)
                        {
                            nodeData.last = lastNode.nodeData;
                        }
                    }
                    JSession.currentScript.changed = true;
                }
            }
            MouseArea
            {
                id: inMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onPressed:
                {
                    inConnector.startDrag();
                }
            }
        }
        //节点类型图标
        Item
        {
            id: imageeItem
            width: parent.height
            anchors.left: inputItem.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Image
            {
                id: nodeTypeImage
                anchors.fill: parent
                anchors.margins: 10
                fillMode: Image.PreserveAspectFit
            }
        }
        //节点标题
        StackLayout
        {
            id: stackLayout
            anchors.left: imageeItem.right
            anchors.right: previewButton.left
            anchors.verticalCenter: parent.verticalCenter
            currentIndex: 0
            Text
            {
                color: "aliceblue"
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                text: nodeData !== null ? nodeData.title : ""
            }
            TextField
            {
                id: titleEditor
                color: "aliceblue"
                background: Rectangle
                {
                    color: borderItem.color
                }
                onEditingFinished:
                {
                    if(titleEditor.text.length === 0)
                    {
                        titleEditor.text = nodeData.title;
                    }
                    else
                    {
                        nodeData.title = titleEditor.text;
                    }
                    stackLayout.currentIndex = 0;
                }
            }
        }
        //节点预览图
        Button
        {
            id: previewButton
            focus: true;down:false;flat: true
            hoverEnabled: true
            width: 28;height: 28
            property var menuWindow: null
            icon.source: menuWindow === null ? "qrc:/Image/icon_hide.png" : "qrc:/Image/icon_show.png"
            icon.color: hovered?"white":"darkgrey"
            icon.width: 20
            icon.height: 20
            background: Item{}
            anchors.right: outputItem.left
            anchors.verticalCenter: parent.verticalCenter

            onPressed:
            {
                var pos = previewButton.mapToGlobal(previewButton.width/2,previewButton.height/2);
                var component = Qt.createComponent("qrc:/Qml/ViewEditor/Node/NodePreviewWindow.qml");
                if (component.status === Component.Ready) {
                    var window = component.createObject(null,{x:pos.x,y:pos.y,nodeData:control.nodeData});
                    window.show();
                    previewButton.menuWindow = window;
                }
            }
            onReleased: previewButton.quitPreview();
            onCanceled: previewButton.quitPreview();
            function quitPreview()
            {
                if(previewButton.menuWindow !== null)
                {
                    previewButton.menuWindow.destroy();
                    previewButton.menuWindow = null;
                }
            }
        }
        //输出口
        Rectangle
        {
            id: outputItem
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
                disableConnector: inConnector
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
