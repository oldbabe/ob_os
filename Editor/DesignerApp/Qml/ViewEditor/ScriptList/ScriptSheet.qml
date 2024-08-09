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
import QtQuick.Window 6.2
import JMoco 1.0

Control
{
    id: control
    implicitHeight: 30
    implicitWidth: 180//fileNameText.contentWidth + 80

    property string showText: changed?"*":""
    property string suffix: changed?"*":""
    property string path: ""
    property string name: ""
    property bool checked: JSession.currentScript !== null ? (JSession.currentScript.fileName === fileName ? true : false) : false

    Component.onCompleted:
    {
        var index = fileName.lastIndexOf("/");
        control.path = fileName.substring(0,index);
        control.name = fileName.substring(index+1,fileName.length);
        showText = control.name.slice(0,control.name.length-5)
    }

    onCheckedChanged:
    {
        delCanvas.requestPaint();
    }

    background: Rectangle
    {
        color: control.checked ? "#464646": "#363636"
        //顶部条形选中框
        Rectangle
        {
            height: 2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            color: control.checked ? "#0078D4": "#363636"
        }

        //脚本类型图标
        Button
        {
            id: iconButton
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin:  2
            anchors.bottom: parent.bottom
            width: parent.height
            icon.width: 20
            icon.height: 20
            icon.color: "aliceblue"
            down:false
            flat:true
            background: Item{}
            Component.onCompleted:
            {
                icon.source = Qt.binding(function(){
                    if(scriptType === 2)
                        return "qrc:/Image/icon_Videos.png";
                    else if(scriptType === 1)
                        return "qrc:/Image/icon_pictures.png";
                    else
                        return "";
                })
            }
        }
        //脚本名
        TextInput
        {
            id: fileNameText
            readOnly: true
            selectByMouse: true
            text: showText+suffix
            color: control.checked ? "white" : "#a1a1a1"
            font.italic: control.checked ? true : false
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: iconButton.right
            anchors.leftMargin: 3

            property bool hovered: false
            // ToolTip.visible: mouseArea.containsMouse && hovered
            // ToolTip.text: fileName

            function rename()
            {
                fileNameText.readOnly = false;
                fileNameText.selectAll();
                fileNameText.forceActiveFocus();
            }

            onEditingFinished:
            {
                if(fileNameText.readOnly === false)
                {
                    fileNameText.readOnly = true;
                    fileNameText.focus = false;
                    if(fileNameText.length > 0)
                    {
                        var oldName = fileName;
                        var newName = control.path+"/"+text+".json";
                        if(JSession.renameScript(oldName,newName))
                            JSession.currentScript.fileName = newName;

                        var index = fileName.lastIndexOf("/");
                        control.path = fileName.substring(0,index);
                        control.name = fileName.substring(index+1,fileName.length);
                        showText = control.name.slice(0,control.name.length-5);
                    }
                    else
                    {
                        showText = control.name.slice(0,fileName.length-5);
                    }
                }
            }
        }

        //删除图标绘制
        Canvas
        {
            id: delCanvas
            width: 20
            height: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 3
            property bool hovered: false
            ToolTip.visible: mouseArea.containsMouse && hovered
            ToolTip.text: "删除该脚本"
            onHoveredChanged: requestPaint();
            onPaint:
            {
                var ctx = getContext("2d");
                //鼠标捕获时更新背景颜色
                if(delCanvas.hovered && mouseArea.containsMouse)
                    ctx.fillStyle = "#565656";
                else
                    ctx.fillStyle = control.background.color;

                ctx.fillRect(0, 0, width, height);
                //选中时或捕获鼠标时显示叉号
                if(control.checked || mouseArea.containsMouse)
                {
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = fileNameText.color;
                    ctx.beginPath();
                    ctx.moveTo(5,5);
                    ctx.lineTo(width-5,height-5);
                    ctx.moveTo(width-5,5);
                    ctx.lineTo(5,height-5);
                    ctx.stroke();
                }
            }
        }

        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            // propagateComposedEvents: true
            cursorShape: containsMouse?Qt.CrossCursor:Qt.ArrowCursor
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onContainsMouseChanged: delCanvas.requestPaint();
            onPositionChanged:(mouse)=>
            {
                if(mouse.x >= delCanvas.x && mouse.x <= (delCanvas.x+delCanvas.width) &&
                   mouse.y >= delCanvas.y && mouse.y <= (delCanvas.y+delCanvas.height))
                {
                    delCanvas.hovered = true;
                }
                else
                {
                    delCanvas.hovered = false;
                }
                if(mouse.x >= 0 && mouse.x < delCanvas.x)
                {
                    fileNameText.hovered = true;
                }
                else
                {
                    fileNameText.hovered = false;
                }
            }
            onClicked:function(mouse)
            {
                var script = JSession.model.getScript(index);
                if(!script.editEnable)
                    return;
                fileNameText.forceActiveFocus();
                if(mouse.button === Qt.RightButton)
                {
                    var menu = menuComponent.createObject(control,{x:mouse.x,y:mouse.y});
                    menu.rename.connect(fileNameText.rename);
                    menu.open();
                }
                else if(mouse.button === Qt.LeftButton)
                {
                    if(delCanvas.hovered)
                    {
                        var window = delWindowComponent.createObject(control);
                        window.show();
                    }
                    else
                    {
                        //未选中时按下鼠标则切换后台脚本
                        if(!control.checked)
                        {
                            if(JSession.currentScript!==null)
                            {
                                if(!JSession.currentScript.editEnable)
                                    return;
                            }
                            JSession.currentScript = JSession.model.getScript(index);
                        }
                        //让sheet进入可视范围
                        control.ListView.view.positionViewAtIndex(index,ListView.Contain);
                    }
                }
            }
        }
    }

    contentItem: Item
    {
        id: mContentItem
        Loader
        {
            id: runLoader
            anchors.fill: parent
            active: !control.checked && (JStudioClient.studioCtrlState===800||JStudioClient.studioCtrlState===784||JStudioClient.studioCtrlState===513)
            sourceComponent: runComponent
        }
        Component
        {
            id: runComponent
            Rectangle
            {
                color: "#505050"
                Image
                {
                    height: parent.height*2/3
                    width: height
                    anchors.centerIn: parent
                    asynchronous: true
                    opacity: 0.6
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/Image/icon_clock_ok.png"
                }
                MouseArea
                {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                }
            }
        }
    }

    //菜单
    Component
    {
        id: menuComponent
        Menu
        {
            id: menuItem
            signal rename();
            MenuItem
            {
                text: "删除"
                onTriggered:
                {
                    JSession.removeScript(fileName);
                }
            }
            MenuItem
            {
                text: "重命名"
                onTriggered:
                {
                    menuItem.rename();
                }
            }
            MenuItem
            {
                text: "创建副本"
                onTriggered:
                {
                    var result = JSession.createCopyScript(JSession.model.getScript(index));
                    if(result !== 0)
                        console.log("createCopyScript result:",result);
                }
            }
            onAboutToHide: menuItem.destroy();
        }
    }
    //删除确认窗口
    Component
    {
        id: delWindowComponent
        Window
        {
            id: delWindow
            width: 240
            height: 80
            maximumHeight: 80
            maximumWidth: 240
            minimumHeight: 80
            minimumWidth: 240
            title: "删除脚本"
            modality: Qt.ApplicationModal

            Item
            {
                anchors.fill: parent
                Row
                {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    Text {
                        text: "["+ fileNameText.text + "]"
                        color: "red"
                    }
                    Text {
                        text: " 确认删除？"
                    }
                }

                Row
                {
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.bottom:  parent.bottom
                    anchors.bottomMargin: 10
                    spacing: 10
                    Button
                    {
                        width: 60
                        height: 30
                        text: "删除"
                        onClicked:
                        {
                            JSession.removeScript(fileName);
                            delWindow.close();
                            delWindow.destroy();
                        }
                    }
                    Button
                    {
                        width: 60
                        height: 30
                        text: "取消"
                        onClicked:
                        {
                            delWindow.close();
                            delWindow.destroy();
                        }
                    }
                }
            }
        }
    }
}
