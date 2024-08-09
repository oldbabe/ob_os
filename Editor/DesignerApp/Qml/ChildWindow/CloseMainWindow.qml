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
    height: 200
    visible: true
    title: qsTr("保存修改 - 设计端")
    modality: Qt.WindowModal
    flags: Qt.Dialog

    //关闭主窗口
    signal quitWindow();

    Component.onCompleted:
    {
        for(var i = 0; i < JSession.model.count(); i++)
        {
            if(JSession.model.getScript(i).changed)
            {
                var nodeData = {
                    "scriptName": JSession.model.getScript(i).fileName,
                    "scriptType": JSession.model.getScript(i).scriptType
                };
                listModel.append(nodeData)
            }
        }
        listView.currentIndex = 0;
    }

    ListModel
    {
        id: listModel
    }

    Control
    {
        id: control
        anchors.fill: parent
        background: Rectangle
        {
            color: "#303030"
        }
        contentItem: Column
        {
            id: column
            padding: 10
            spacing: 3
            Text
            {
                id: titleItem
                color: "ivory"
                text: qsTr("以下脚本有未保存的修改:")
                verticalAlignment: Text.AlignVCenter
                width: parent.width-column.padding*2
            }
            Control
            {
                id: dataItem
                height: 130
                width: parent.width-column.padding*2

                background: Canvas
                {
                    onPaint:
                    {
                        var ctx = getContext("2d");
                        ctx.clearRect(0, 0, width, height);
                        ctx.strokeStyle = Qt.rgba(1, 1, 1, 1);
                        ctx.lineWidth = 0.1;

                        ctx.beginPath();
                        ctx.moveTo(0,0);
                        ctx.lineTo(width,0);
                        ctx.lineTo(width,height);
                        ctx.lineTo(0,height);
                        ctx.lineTo(0,0);
                        ctx.stroke();
                    }
                }

                contentItem: ListView
                {
                    id: listView
                    model: listModel
                    clip: true
                    currentIndex: 0
                    boundsBehavior: Flickable.StopAtBounds
                    delegate: Control
                    {
                        id: delegate
                        width: ListView.view.width
                        height: 25

                        Component.onCompleted:
                        {
                            var index = scriptName.lastIndexOf("/");
                            var len = JSession.currentScript.fileName.length;
                            baseNameText.text = scriptName.slice(index+1,len);
                            pathNameText.text = scriptName.slice(0,index);
                            if(scriptType === 2)
                                typeImage.icon.source = "qrc:/Image/icon_Videos.png";
                            else if(scriptType === 1)
                                typeImage.icon.source = "qrc:/Image/icon_pictures.png";
                        }

                        background: Rectangle
                        {
                            color:  (delegate.ListView.view.currentIndex===index)?"royalblue":"transparent"
                        }

                        contentItem: Row
                        {
                            spacing: 5
                            leftPadding: 3

                            Button
                            {
                                id: typeImage
                                width: parent.height
                                height: parent.height
                                icon.width: 15
                                icon.height: 15
                                icon.color: "aliceblue"
                                down:false
                                flat:true
                                background: Item{}
                            }
                            Text
                            {
                                id: baseNameText
                                color: "white"
                                height: parent.height
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text
                            {
                                id: pathNameText
                                color: "white"
                                height: parent.height
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked:
                            {
                                delegate.ListView.view.currentIndex=index;
                            }
                        }
                    }
                }
            }

            Row
            {
                id: buttonItem
                width: parent.width-column.leftPadding-column.rightPadding
                height: parent.height-titleItem.height-dataItem.height-column.padding*2
                layoutDirection: Qt.RightToLeft
                spacing: 5
                Button
                {
                    text: "取消"
                    height: parent.height-10
                    width: 60
                    onClicked:
                    {
                        window.destroy();
                    }
                }
                Button
                {
                    text: "不保存"
                    height: parent.height-10
                    width: 60
                    onClicked:
                    {
                        window.destroy();
                        window.quitWindow();
                    }
                }
                Button
                {
                    text: "全部保存"
                    height: parent.height-10
                    width: 80
                    onClicked:
                    {
                        for(var i = 0; i < JSession.model.count(); i++)
                        {
                            if(JSession.model.getScript(i).changed)
                            {
                                var result = JSession.model.getScript(i).save();
                                if(result !== 0)
                                {
                                    console.log("JSession.model.getScript(i).save() failed:",result);
                                }
                            }
                        }
                        window.destroy();
                        window.quitWindow();
                    }
                }
            }
        }
    }
}
