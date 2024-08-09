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
import "../JltComponent"

//场景的原点的拖拽、缩放和场景右键菜单信号
JltScriptScene
{
    id: jltScriptScene
    clip: true

    property JltScriptNode currentNode: null
    property var nodes: []

    function clearAll()
    {
        for(var i = 0; i < nodes.length; i++)
            nodes[i].destroy();
        nodes = [];
    }

    //递归创建连接的节点数据
    function createNode(data)
    {
        var fileName = "";
        if(data.type === JNode.NodeType_Move)
            fileName = "qrc:/Qml/ViewEditor/Node/ScriptNodeMove.qml";
        else if(data.type === JNode.NodeType_Erp)
            fileName = "qrc:/Qml/ViewEditor/Node/ScriptNodeErp.qml";
        else if(data.type === JNode.NodeType_StopMotionAnimation)
            fileName = "qrc:/Qml/ViewEditor/Node/ScriptNodeSma.qml";
        else
            return;

        var component = Qt.createComponent(fileName);
        if(component.status === Component.Ready)
        {
            var node = component.createObject(jltScriptDrop,{scriptScene:jltScriptScene,
                                                  scriptShape:jltScriptShape,
                                                  scriptDrop:jltScriptDrop,
                                                  sceneX:data.x,sceneY:data.y,nodeData:data});
            jltScriptScene.nodes.push(node);
            if(data.next)
            {
                var nextNode = createNode(data.next);
                if(nextNode)
                {
                    node.outputConnector.bindConnector = nextNode.inputConnector;
                    nextNode.inputConnector.bindConnector = node.outputConnector;
                }
            }
            return node;
        }
    }

    function pushPage(url)
    {
        var page = jltScriptScene.StackView.view.push(url,{},StackView.Immediate);
        if(page === null)
        {
            console.log("pushPage: failed!",url)
        }
    }

    function openNodeMenu(item,x,y)
    {
        var pos = jltScriptScene.mapFromItem(item,x,y);
        nodeMenu.x=pos.x;
        nodeMenu.y=pos.y;
        nodeMenu.open();
    }
    //脚本页面-切换脚本通过重载页面实现
    Connections
    {
        target: JSession
        //脚本切换
        function onCurrentScriptChanged()
        {
            //清空旧数据
            clearAll();
            jltScriptScene.StackView.view.pop(StackView.Immediate)

            //空脚本
            if(JSession.currentScript == null)
                return;

            //加载脚本
            if(JSession.currentScript.fileState === JScript.FileState_NULL)
            {
                var result = JSession.currentScript.loadFile();
                if(result !== 0)
                {
                    console.log("loadFile error: ",result);
                    return;
                }
            }

            //创建节点
            var nodes = [];
            nodes = JSession.currentScript.getNodes();
            for(var i = 0; i < nodes.length; i++)
            {
                createNode(nodes[i]);
            }

            //场景还原
            jltScriptScene.gridWidth = JSession.currentScript.glScene.gridWidth;
            jltScriptScene.originX = JSession.currentScript.glScene.x;
            jltScriptScene.originY = JSession.currentScript.glScene.y;
        }
    }
    onOriginChanged: function(point)
    {
        if(JSession.currentScript !== null)
        {
            JSession.currentScript.glScene.x = point.x;
            JSession.currentScript.glScene.y = point.y;
            JSession.currentScript.changed = true;
        }
    }
    onWheelChanged:function(value)
    {
        if(JSession.currentScript !== null)
        {
            JSession.currentScript.glScene.gridWidth = value;
            JSession.currentScript.changed = true;
        }
    }

    //右键菜单事件
    onMenuOpened: function(x,y)
    {
        sceneMenu.x = x;
        sceneMenu.y = y;
        sceneMenu.toConnect = false;
        sceneMenu.open();
    }

    MouseArea
    {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        cursorShape: jltScriptScene.dragActive?Qt.ClosedHandCursor:Qt.ArrowCursor
        onPressed: function(event)
        {
            parent.forceActiveFocus();
            if(event.buttons === Qt.RightButton)
            {
                jltScriptScene.mousePress(Qt.point(event.x,event.y));
            }
        }
        onReleased: function(event)
        {
            if(event.button === Qt.RightButton)
            {
                jltScriptScene.mouseRelease(Qt.point(event.x,event.y));
            }
        }
        onPositionChanged: function(event)
        {
            if(event.buttons === Qt.RightButton)
            {
                jltScriptScene.mouseMove(Qt.point(event.x,event.y));
            }
        }
        onWheel: function(event)
        {
            jltScriptScene.wheelMove(Qt.point(event.x,event.y),event.angleDelta);
        }
    }

    //连接线管理器组件
    JltScriptShape
    {
        id: jltScriptShape
        anchors.fill: parent
        scriptScene: jltScriptScene
        //场景视图
        ScriptSceneView
        {
            anchors.fill: parent
            scene: jltScriptScene
        }
        //拖放功能组件
        JltScriptDrop
        {
            id: jltScriptDrop
            anchors.fill: parent
            //拖放菜单事件
            onMenuOpened: function(x,y)
            {
                sceneMenu.x = x;
                sceneMenu.y = y;
                sceneMenu.toConnect = true;
                sceneMenu.open();
            }
            //拖拽移动事件
            onDragMove: function(point)
            {
                //更新拖拽点
                jltScriptShape.updateActiveConnectorEndF(point);
                //拖动到边缘时自动运动
                var lenWidth = 30;
                var moveMouseX = point.x;
                if(moveMouseX>(jltScriptScene.width-lenWidth))
                {
                    jltScriptScene.originX-=((moveMouseX-(jltScriptScene.width-lenWidth))/20);
                }
                else if(moveMouseX < lenWidth)
                {
                    jltScriptScene.originX-=(moveMouseX-lenWidth)/20;
                }
                var moveMouseY = point.y;
                if(moveMouseY>(jltScriptScene.height-lenWidth))
                {
                    jltScriptScene.originY-=((moveMouseY-(jltScriptScene.height-lenWidth))/20);
                }
                else if(moveMouseY < lenWidth)
                {
                    jltScriptScene.originY-=(moveMouseY-lenWidth)/20;
                }
            }
        }
    }
    //场景菜单
    ScriptSceneMenu
    {
        id: sceneMenu
        scene: jltScriptScene
        onAboutToHide:
        {
            jltScriptDrop.menuClosed();
        }
    }
    //节点菜单
    ScriptNodeMenu
    {
        id: nodeMenu
        scene: jltScriptScene
    }

    ///////////////////
    function removeErpNode(nodeType)
    {
        for(var i = 0; i < nodes.length; i++)
        {
            if(nodes[i].nodeData.type === JNode.NodeType_Erp)
            {
                jltScriptScene.removeNode(nodes[i]);
                break;
            }
        }
    }

    function menuCreateNode(nodeType,robotType = 1)
    {
        if(JSession.currentScript === null)
        {
            console.log("JSession.currentScript === null");
            return;
        }
        //移除旧的ERP标定点
        if(nodeType === JNode.NodeType_Erp)
        {
            jltScriptScene.removeErpNode(nodeType);
        }

        //创建节点数据
        var setX = (sceneMenu.x-jltScriptScene.originX)/jltScriptScene.gridWidth;
        var setY = (sceneMenu.y-jltScriptScene.originY)/jltScriptScene.gridWidth;
        var nodeData = JSession.currentScript.createNode(setX,setY,robotType,nodeType);
        if(nodeData === null)
        {
            console.log(">JSession.currentScript.createNode failed!");
            return;
        }

        var node = jltScriptScene.createNode(nodeData);
        if(sceneMenu.toConnect)
        {
            //读取场景中拖拽的连接器
            var drapConnector = jltScriptDrop.getDrapConnector();
            if(drapConnector === null)
            {
                console.log("drapConnector === NULL");
                return;
            }
            //读取场景中拖拽连接器绑定的节点
            var dragNode = drapConnector.getBindNode();
            if(dragNode === null)
            {
                console.log("dragNode === NULL");
                return;
            }
            //当拖拽连接器是输入类型时
            if(drapConnector.connectorType === JltScriptConnector.ConnectorType_Input)
            {
                if(drapConnector.bindConnector !== null)
                {
                    drapConnector.bindConnector.bindConnector = null;
                    dragNode.nodeData.last.next = null;
                }
                //数据绑定
                dragNode.nodeData.last = node.nodeData;
                node.nodeData.next = dragNode.nodeData;
                //视图绑定
                drapConnector.bindConnector = node.outputConnector;
                node.outputConnector.bindConnector = drapConnector;
            }
            else if(drapConnector.connectorType === JltScriptConnector.ConnectorType_Output)
            {
                if(drapConnector.bindConnector !== null)
                {
                    drapConnector.bindConnector.bindConnector = null;
                    dragNode.nodeData.next.last = null;
                }
                //数据绑定
                dragNode.nodeData.next = node.nodeData;
                node.nodeData.last = dragNode.nodeData;
                //视图绑定
                drapConnector.bindConnector = node.inputConnector;
                node.inputConnector.bindConnector = drapConnector;
            }
            JSession.currentScript.currentNode = node.nodeData;
            jltScriptScene.currentNode = node;
            jltScriptShape.update();
        }
        JSession.currentScript.changed=true;
    }

    function removeNode(node)
    {
        if(node === null)
        {
            console.log("removeNode failed: node === null")
            return;
        }
        if(node.nodeData === null)
        {
            console.log("removeNode failed: node.nodeData === null")
            return;
        }
        for(var i = 0; i < nodes.length; i++)
        {
            if(nodes[i].nodeData === node.nodeData)
            {
                var datas = nodes.splice(i,1);
                if(datas.length===1)
                {
                    //断开连接
                    if(datas[0].outputConnector !== null)
                    {
                        if(datas[0].outputConnector.bindConnector !== null)
                        {
                            datas[0].outputConnector.bindConnector.bindConnector = null;
                        }
                        datas[0].outputConnector.bindConnector = null;
                    }
                    if(datas[0].inputConnector !== null)
                    {
                        if(datas[0].inputConnector.bindConnector !== null)
                        {
                            datas[0].inputConnector.bindConnector.bindConnector = null;
                        }
                        datas[0].inputConnector.bindConnector = null;
                    }
                    //移除图像和数据
                    JSession.currentScript.removeNode(datas[0].nodeData);
                    JSession.currentScript.changed = true;
                    datas[0].destroy();
                }
                return;
            }
        }
    }
}
