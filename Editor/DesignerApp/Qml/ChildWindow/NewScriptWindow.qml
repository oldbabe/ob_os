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
    id: window
    color: "#363636"
    width: 400
    height: 160
    title: "新建脚本"
    modality:Qt.WindowModal

    Connections
    {
        target: window
        function onClosing()
        {
            window.destroy()
        }
    }

    Rectangle
    {
        id: root
        color: "#EEEEEE"
        anchors.fill: parent

        StrInputItem
        {
            id:scriptNameItem
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
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
            height: scriptNameItem.height
            titleWidth: 60
            titleText: "拍摄类型"
        }

        Item
        {
            id: buttonItem
            anchors.left: parent.left
            anchors.top: shutterItem.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20
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
                onButtonClicked: window.destroy();
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
                    //创建脚本
                    var sessionPath = JSession.dirName;
                    var scriptName = scriptNameItem.inputItem.text;
                    if(scriptName.length > 0)
                    {
                        var res = JSession.createScript(sessionPath,scriptName,shutterItem.currectindex)
                        if(res === 0)
                        {
                            window.close();
                            errorText.visible = false;
                        }
                        else if(res === 1)
                        {
                            errorText.text = qsTr("脚本已存在，请修改脚本名")
                            errorText.visible = true;
                        }
                        else if(res === 2)
                        {
                            errorText.text = qsTr("脚本写入失败")
                            errorText.visible = true;
                        }
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
