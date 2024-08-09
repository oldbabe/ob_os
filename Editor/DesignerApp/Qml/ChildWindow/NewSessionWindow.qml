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
import QtQuick.Window
import JMoco 1.0
import "../../JS/ScriptBuffer.js" as MyScript

import "../Component"


Window
{
    id: sessionWindow
    width: 450
    height: 240
    title: "新建会话"
    modality:Qt.WindowModal


    Component.onCompleted:
    {
        if(JSession.dirName.length > 0 && JSession.baseName.length > 0)
            dirItem.valueText = JSession.dirName.replace("/" + JSession.baseName,"");
    }

    Connections
    {
        target: sessionWindow
        function onClosing()
        {
            sessionWindow.destroy()
        }
    }

    Rectangle
    {
        id: root
        color: "#EEEEEE"
        anchors.fill: parent
        StrInputItem
        {
            id:dirItem
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: lookDir.left
            anchors.rightMargin: 5

            titleWidth: 60
            titleText: "会话目录"
            inputItem.placeholderText: "请输入会话创建目录."
        }

        ToolButton
        {
            id: lookDir
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: dirItem.verticalCenter

            height: 30
            showText: "..."
            onButtonClicked:
            {
                var dir = JSession.getExistingDirectory("选择目录");
                if(dir.length > 0)
                {
                    dirItem.inputItem.focus = true
                    dirItem.valueText = dir;
                }
            }
        }

        StrInputItem
        {
            id:nameItem
            titleText: "会话名称"
            anchors.left: parent.left
            anchors.top: dirItem.bottom
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.topMargin: 20
            inputItem.placeholderText: "请输入会话名称."
            titleWidth: 60
    //        inputItem.validator: RegularExpressionValidator { regularExpression: /^[A-Za-z0-9]{5,20}$/ }
    //        inputItem.placeholderText: "请输入数字(0-9)或字符(a-zA-Z),长度5~20."
        }

        StrInputItem
        {
            id:scriptNameItem
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: nameItem.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            titleText: "脚本名称"
            titleWidth: 60
            inputItem.placeholderText: "请输入会话脚本名称."
        }

        StateButtonItem
        {
            id:shutterItem
            anchors.left: parent.left
            anchors.top: scriptNameItem.bottom
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.topMargin: 20
            titleText: "拍摄类型"
            titleWidth: 60
            height: nameItem.height
        }

        Item
        {
            id: buttonItem
            anchors.left: parent.left
            anchors.top: shutterItem.bottom
            anchors.right: parent.right
            anchors.topMargin: 20
            height: 30
            ToolButton
            {
                id: creatBt
                width: 60
                height: 30
                showText: "取消"
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                onButtonClicked: sessionWindow.destroy();
            }

            ToolButton
            {
                id: cancelBt
                width: 60
                height: 30
                showText: "创建"
                anchors.right: creatBt.left
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                onButtonClicked:
                {
                    if(JSession.opened)
                        JSession.closeSession();

                    var path = dirItem.inputItem.text;
                    var name = nameItem.inputItem.text;
                    var res = JSession.createSession(path,name);
                    if(res === 0)
                    {
                        var sessionPath = path+"/"+name;
                        var scriptName = scriptNameItem.inputItem.text;
                        if(scriptName==="")
                        {
                            scriptName = name;
                        }
                        if(JSession.createScript(sessionPath,scriptName,shutterItem.currectindex) === 0)
                        {
                            JSession.openSession(sessionPath);
                            sessionWindow.close();
                        }
                    }
                    else if(res === 1)
                    {
                        errorText.text = qsTr("会话已存在 或 会话目录错误.")
                        errorText.visible = true;
                    }
                    else if(res === 2)
                    {
                        errorText.text = qsTr("下载目录创建失败")
                        errorText.visible = true;
                    }
                }
            }
        }

        Text
        {
            id: errorText
            visible: false
            anchors.top: buttonItem.bottom
            anchors.topMargin: 2
            anchors.horizontalCenter: parent.horizontalCenter
            color: "red"
            font.pixelSize: 16
            text: qsTr("text")
            onVisibleChanged:
            {
                if(visible)
                {
                    errorShowTime.start()
                }
            }

            Timer
            {
                id:errorShowTime
                interval: 2000
                onTriggered: errorText.visible = false
            }
        }
    }
}
