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
import "./JltComponent"

MenuBar
{
    id: menuBar

    JltMenu
    {
        title: qsTr("文件")
        JltMenuItem{action: createSessionAction}
        JltMenuItem{action: createScriptAction}
        JltMenuItem{action: importScriptAction}
        JltMenuItem{action: openSessionAction}
        JltMenuItem{action: openSessionDdirAction}
        JltMenuItem{action: closeSessionAction}
        JltMenuItem{action: saveAction}
        JltMenuItem{action: saveAllAction}
    }
    JltMenu
    {
        id: cameraMenu
        title: qsTr("视频输入");
        JltMenu
        {
            id: inputVideoMenu
            title: qsTr("输入源")
            Component
            {
                id: inputSourceComponent
                JltMenuItem
                {
                    showArrow: false
                    property int index: -1
                    checked: index === JCameraDevice.currentIndex
                    onTriggered:
                    {
                        if(index === JCameraDevice.currentIndex)
                            return;

                        if(index !== -1)
                        {
                            JCameraDevice.play(index);
                        }
                        else
                        {
                            JCameraDevice.stop();
                        }
                    }
                }
            }

            onAboutToHide:inputVideoMenu.clearItem();
            onAboutToShow:
            {
                inputVideoMenu.clearItem();
                var cameraNames = [];
                cameraNames = JCameraDevice.cameraList();
                for(var i = 0; i < cameraNames.length; i++)
                {
                    var item = inputSourceComponent.createObject(null,{text:cameraNames[i],index:i-1});
                    if(item !== null)
                    {
                        inputVideoMenu.addItem(item);
                    }
                }
            }
            function clearItem()
            {
                for(var i = 0; i < inputVideoMenu.count; i++)
                {
                    var item = inputVideoMenu.takeItem(i);
                    if(item !== null)
                        item = null;
                    var active = inputVideoMenu.takeAction(i);
                    if(active !== null)
                        active = null;
                }
            }

            // delegate: JltMenuItem{}
        }

        JltMenu
        {
            title: qsTr("旋转")
            Action{text:"0°";checked:JCameraDevice.rotateFlag===JCameraDevice.RotateFlag_0;onTriggered:JCameraDevice.rotateFlag=JCameraDevice.RotateFlag_0;}
            Action{text:"90°";checked:JCameraDevice.rotateFlag===JCameraDevice.RotateFlag_90;onTriggered:JCameraDevice.rotateFlag=JCameraDevice.RotateFlag_90;}
            Action{text:"180°";checked:JCameraDevice.rotateFlag===JCameraDevice.RotateFlag_180;onTriggered:JCameraDevice.rotateFlag=JCameraDevice.RotateFlag_180;}
            Action{text:"270°";checked:JCameraDevice.rotateFlag===JCameraDevice.RotateFlag_270;onTriggered:JCameraDevice.rotateFlag=JCameraDevice.RotateFlag_270;}
            delegate: JltMenuItem{}
        }
        JltMenu
        {
            title: qsTr("网格")
            Action{text:"关闭";checked:JCameraDevice.gridFlag===JCameraDevice.GridFlags_Close;onTriggered:JCameraDevice.gridFlag=JCameraDevice.GridFlags_Close;}
            Action{text:"三等分";checked:JCameraDevice.gridFlag===JCameraDevice.GridFlags_Trisector;onTriggered:JCameraDevice.gridFlag=JCameraDevice.GridFlags_Trisector;}
            Action{text:"方形";checked:JCameraDevice.gridFlag===JCameraDevice.GridFlags_Square;onTriggered:JCameraDevice.gridFlag=JCameraDevice.GridFlags_Square;}
            Action{text:"方形+三等分";checked:JCameraDevice.gridFlag===JCameraDevice.GridFlags_Diagonal;onTriggered:JCameraDevice.gridFlag=JCameraDevice.GridFlags_Diagonal;}
            delegate: JltMenuItem{}
        }
        JltMenu
        {
            title: qsTr("镜像")
            Action{text:"水平镜像";checked:JCameraDevice.horizontalMirrored;onTriggered:JCameraDevice.horizontalMirrored = !JCameraDevice.horizontalMirrored;}
            Action{text:"垂直镜像";checked:JCameraDevice.verticalMirrored;onTriggered:JCameraDevice.verticalMirrored = !JCameraDevice.verticalMirrored;}
            delegate: JltMenuItem{}
        }
        JltMenu
        {
            title: qsTr("控制")
            Action{text:"无";checked:JCameraDevice.controlFlag===JCameraDevice.ControlFlags_NULL;onTriggered:JCameraDevice.controlFlag=JCameraDevice.ControlFlags_NULL;}
            Action{text:"仅对焦";checked:JCameraDevice.controlFlag===JCameraDevice.ControlFlags_Focus;onTriggered:JCameraDevice.controlFlag=JCameraDevice.ControlFlags_Focus;}
            Action{text:"对焦拍摄";checked:JCameraDevice.controlFlag===JCameraDevice.ControlFlags_FocusShoot;onTriggered:JCameraDevice.controlFlag=JCameraDevice.ControlFlags_FocusShoot;}
            delegate: JltMenuItem{}
        }
        delegate: JltMenuItem{}
    }

    JltMenu
    {
        title: qsTr("帮助")
        delegate: JltMenuItem{}
        Action
        {
            text:"关于我们";
            onTriggered:
            {
                var component = Qt.createComponent("qrc:/Qml/ChildWindow/AboutUsWindow.qml");
                if (component.status === Component.Ready)
                {
                    var window = component.createObject(windowRoot);
                    window.show();
                }
            }
        }
    }
    delegate: MenuBarItem
    {
        id: menuBarItem
        hoverEnabled: true

        //表示菜单的打开状态
        property bool isOpened: false

        Connections
        {
            target: menuBarItem.menu
            function onOpened()
            {
                menuBarItem.isOpened = true;
            }
            function onClosed()
            {
                menuBarItem.isOpened = false;
            }
        }

        contentItem: Text
        {
            text: menuBarItem.text
            font: menuBarItem.font
            opacity: enabled ? 1.0 : 0.3
            color: "aliceblue"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle
        {
            opacity: enabled ? 1 : 0.3
            color: (menuBarItem.hovered||menuBarItem.isOpened) ? Qt.darker(windowRoot.backgroundColor,0.5) : "transparent"
        }

    }

    background: Rectangle
    {
        color: windowRoot.backgroundColor
    }

    Action
    {
        id: createSessionAction
        text: qsTr("新建会话")
        shortcut: "Ctrl+Shift+N";
        icon.source: ""
        onTriggered:
        {
            //组件创建
            var component = Qt.createComponent("qrc:/Qml/ChildWindow/NewSessionWindow.qml");
            //提取对象
            if(component.status === Component.Ready)
            {
                var objWindow = component.createObject(windowRoot);
                objWindow.show();
            }
        }
    }
    Action
    {
        id: createScriptAction
        text: qsTr("新建脚本")
        shortcut: "Ctrl+N";
        icon.source: "qrc:/Image/icon_new_script.png"
        onTriggered:
        {
            var component = Qt.createComponent("qrc:/Qml/ChildWindow/NewScriptWindow.qml");
            if(component.status === Component.Ready)
            {
                var objWindow = component.createObject(windowRoot);
                objWindow.show();
            }
        }
    }
    Action
    {
        id: importScriptAction
        text: qsTr("导入脚本")
        shortcut: "";
        enabled: JSession.opened
        icon.source: "qrc:/Image/icon_new_script.png"
        onTriggered:
        {
            var path = JSession.getExistingFile("选择脚本",JSession.dirName,"脚本(*.json)");
            if(path.length > 0)
            {
                if(!JSession.importScript(path))
                {
                    console.log("importScriptAction failed!");
                }
            }
        }
    }
    Action
    {
        id: openSessionAction
        text: qsTr("打开会话")
        shortcut: "Ctrl+O";
        icon.source: "qrc:/Image/icon_open_script.png"
        onTriggered:
        {
            var saveFlag = false;
            for(var i = 0; i < JSession.model.count(); i++)
            {
                if(JSession.model.getScript(i).changed)
                {
                    saveFlag = true;
                    break;
                }
            }
            if(saveFlag)
            {
                var component = Qt.createComponent("qrc:/Qml/ChildWindow/CloseMainWindow.qml");
                if(component.status === Component.Ready)
                {
                    var objWindow = component.createObject(windowRoot);
                    objWindow.quitWindow.connect(windowRoot.switchSession);
                }
            }
            else
            {
                windowRoot.switchSession();
            }
        }
    }
    Action
    {
        id: openSessionDdirAction
        text: qsTr("打开会话目录")
        shortcut: "";
        icon.source: ""
        enabled: JSession.opened
        onTriggered: JSession.openExistingDirectory(JSession.dirName);
    }
    Action
    {
        id: closeSessionAction
        text: qsTr("关闭会话")
        shortcut: "";
        icon.source: ""
        onTriggered:
        {
            var saveFlag = false;
            for(var i = 0; i < JSession.model.count(); i++)
            {
                if(JSession.model.getScript(i).changed)
                {
                    saveFlag = true;
                    break;
                }
            }
            if(saveFlag)
            {
                var component = Qt.createComponent("qrc:/Qml/ChildWindow/CloseMainWindow.qml");
                if(component.status === Component.Ready)
                {
                    var objWindow = component.createObject(windowRoot);
                    objWindow.quitWindow.connect(JSession.closeSession);
                }
            }
            else
            {
                JSession.closeSession();
            }
        }
    }
    Action
    {
        id: saveAction
        shortcut: "Ctrl+S";
        icon.source: "qrc:/Image/icon_save.png"
        icon.color: "aliceblue"
        text: qsTr("保存")
        Component.onCompleted:
        {
            enabled = Qt.binding(function(){
                if(!JSession.opened)
                    return false;
                if(JSession.currentScript === null)
                    return false;
                return JSession.currentScript.changed;
            });
        }
        onTriggered: JSession.currentScript.save();
    }
    Action
    {
        id: saveAllAction
        shortcut: "Ctrl+Shift+S";
        icon.source: ""
        text: qsTr("保存所有")
        Component.onCompleted:
        {
            enabled = Qt.binding(function(){
                if(!JSession.opened)
                    return false;
                if(JSession.currentScript === null)
                {
                    for(var i = 0; i < JSession.model.count(); i++)
                    {
                        if(JSession.model.getScript(i).changed)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                if(!JSession.currentScript.changed)
                {
                    for(var j = 0; j < JSession.model.count(); j++)
                    {
                        if(JSession.model.getScript(j).changed)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                return JSession.currentScript.changed;
            });
        }
        onTriggered:
        {
            for(var i = 0; i < JSession.model.count(); i++)
            {
                if(JSession.model.getScript(i).changed)
                {
                    var result = JSession.model.getScript(i).save();
                    if(result !== 0)
                    {
                        console.log("saveAllAction failed:",i,result);
                    }
                }
            }
        }
    }
    // Action
    // {
    //     id: erpCommitAction
    //     shortcut: "";
    //     icon.source: "qrc:/Image/icon_Cloud.png"
    //     text: qsTr("导出到NAS")
    //     onTriggered:
    //     {
    //         var component = Qt.createComponent("qrc:/Qml/ChildWindow/NasCommitWindow.qml");
    //         if(component.status === Component.Ready)
    //         {
    //             var objWindow = component.createObject(windowRoot);
    //             objWindow.show();
    //         }
    //     }
    // }
}

