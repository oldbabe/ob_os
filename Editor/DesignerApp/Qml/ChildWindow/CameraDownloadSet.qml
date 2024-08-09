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

Window
{
    id: window
    width: 400
    height: 400
    flags: Qt.Dialog
    modality: Qt.WindowModal
    title: qsTr("相机下载目录设置")

    Component.onCompleted:
    {
        var list = [];
        var item = {
            "directory" : ""
        };

        list = JCameraInstall.getDownLoadList();
        if(JSession.opened && JSession.dirName.length > 0)
        {
            if(list.indexOf(JSession.dirName) === -1)
            {
                item.directory = JSession.dirName;
                listModel.append(item);
            }
        }
        for(var i = 0; i < list.length; i++)
        {
            item.directory = list[i];
            listModel.append(item);
        }
    }
    Connections
    {
        target: window
        function onClosing(event)
        {
            var list = [];
            for(var i = 0;i < listModel.count; i++)
            {
                var item = listModel.get(i);
                list.push(item.directory);
            }
            JCameraInstall.setDownLoadList(list);
            event.accepted = true;
        }
    }

    Control
    {
        id: control
        padding: 10
        anchors.fill: parent
        ListModel
        {
            id:listModel
        }
        background: Rectangle
        {
            color: "#303030"
        }
        contentItem: ListView
        {
            id: listView
            spacing: 1
            model: listModel
            delegate: Rectangle
            {
                height: 40
                color: mouseArea.containsMouse?"steelblue":"#363636"
                width: ListView.view.height
                radius: 5
                border.width: 1
                border.color: "#444444"
                Text
                {
                    text: directory === JSession.dirName ? ("会话目录:"+directory) : directory
                    color: directory === JSession.dirName ? "red" : "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                MouseArea
                {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                }
                Button
                {
                    id: defaultButton
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: "设为默认"
                    enabled: JCamera.downloadDir===directory?false:true
                    onClicked: JCamera.setDownloadDirectory(directory);
                }
                Button
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: defaultButton.left
                    anchors.rightMargin: 5
                    text: "删除"
                    enabled: JCamera.downloadDir===directory?false:true
                    onClicked:listModel.remove(index);
                }
            }
            Button
            {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                text: "新增地址"
                onClicked:
                {
                    var path = JSession.getExistingDirectory("选择图像下载地址");
                    if(path.length === 0)
                        return;
                    var addFlag = true;
                    for(var i = 0;i < listModel.count; i++)
                    {
                        var item = listModel.get(i);
                        if(item.directory === path)
                        {
                            addFlag = false;
                            break;
                        }
                    }
                    if(addFlag)
                    {
                        var itemData = {
                            "directory" : path
                        };
                        listModel.append(itemData);
                    }
                }
            }
        }
    }
}
