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
import QtQuick
import QtQuick.Controls

import JMoco 1.0

Window
{
    id:window
    width: 640
    height: 480
    visible: true
    modality: Qt.WindowModal
    title: qsTr("镜头提交")

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
        anchors.fill: parent
        Column
        {
            id: column
            anchors.fill: parent
            Item
            {
                id: topItem
                width: parent.width
                height: 100
                Column
                {
                    leftPadding: 5
                    rightPadding: 5
                    anchors.fill: parent
                    Item
                    {
                        width: parent.width-parent.leftPadding-parent.rightPadding
                        height: parent.height/2
                        Row
                        {
                            anchors.fill: parent
                            Text
                            {
                                id: nasDirText
                                text: "NAS目录"
                                width: 80
                                height: parent.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                            Item
                            {
                                height: parent.height
                                width: parent.width-parent.spacing-nasDirText.width

                                Button
                                {
                                    id: selectDirButtom
                                    width: 35
                                    height: 35
                                    text: "..."
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.right: parent.right
                                    anchors.rightMargin: 5
                                    background: Rectangle
                                    {
                                        implicitWidth: 120
                                        implicitHeight: 40
                                        border.color: selectDirButtom.pressed ? "#666666" : "#000000"
                                        border.width: selectDirButtom.visualFocus ? 2 : 1
                                        color: "#fcfcfc"
                                        radius: 2
                                    }
                                    onClicked:
                                    {
                                        var dir = JSession.getExistingDirectory("选择NAS目录","B:/");
                                        if(dir.length > 0)
                                        {
                                            dirTextInput.text = dir;
                                        }
                                    }
                                }

                                Rectangle
                                {
                                    color: "#fcfcfc"
                                    anchors.margins: 5
                                    anchors.left: parent.left
                                    anchors.right: selectDirButtom.left
                                    anchors.top: parent.top
                                    anchors.bottom: parent.bottom
                                    border.width: 1
                                    border.color: "#363636"
                                    radius: 5

                                    TextInput
                                    {
                                        id: dirTextInput
                                        leftPadding: 3
                                        font.pixelSize: 16
                                        anchors.fill: parent
                                        selectByMouse: true
                                        verticalAlignment: TextInput.AlignVCenter
                                        text: ""
                                        readOnly: true
                                    }
                                }
                            }
                        }
                    }
                    Item
                    {
                        width: parent.width-parent.leftPadding-parent.rightPadding
                        height: parent.height/2
                        Row
                        {
                            anchors.fill: parent
                            Text
                            {
                                id: scripptText
                                text: "选择脚本"
                                width: 80
                                height: parent.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                            Item
                            {
                                height: parent.height
                                width: parent.width-parent.spacing-nasDirText.width

                                ComboBox
                                {
                                    id: scriptComboBox
                                    anchors.fill: parent
                                    anchors.margins: 5
                                    model: JSession.model
                                    textRole: "fileName"
                                    Component.onCompleted: currentIndex = find(JSession.currentFileName)
                                    delegate: ItemDelegate
                                    {
                                        width: scriptComboBox.width
                                        contentItem: Text {
                                            text: fileName
                                            font: scriptComboBox.font
                                            elide: Text.ElideRight
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        highlighted: scriptComboBox.highlightedIndex === index

                                        required property int index
                                        required property string fileName
                                    }
                                    background: Rectangle
                                    {
                                        implicitWidth: 120
                                        implicitHeight: 40
                                        border.color: scriptComboBox.pressed ? "#666666" : "#000000"
                                        border.width: scriptComboBox.visualFocus ? 2 : 1
                                        color: "#fcfcfc"
                                        radius: 2
                                    }
                                    indicator: Canvas {
                                        id: canvas
                                        x: scriptComboBox.width - width - scriptComboBox.rightPadding
                                        y: scriptComboBox.topPadding + (scriptComboBox.availableHeight - height) / 2
                                        width: 12
                                        height: 8
                                        contextType: "2d"

                                        Connections {
                                            target: scriptComboBox
                                            function onPressedChanged() { canvas.requestPaint(); }
                                        }

                                        onPaint: {
                                            context.reset();
                                            context.moveTo(0, 0);
                                            context.lineTo(width, 0);
                                            context.lineTo(width / 2, height);
                                            context.closePath();
                                            context.fillStyle = scriptComboBox.pressed ? "#666666" : "#000000"
                                            context.fill();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Item
            {
                id: contentItem
                width: parent.width
                height: column.height-column.spacing-topItem.height
                Row
                {
                    anchors.fill: parent
                    Item
                    {
                        id: leftContentItem
                        width: (parent.width-midContentItem.width)/2
                        height: parent.height
                        Column
                        {
                            anchors.fill: parent
                            spacing: 5
                            padding: 5
                            Row
                            {
                                Text
                                {
                                    id: codeText
                                    text: qsTr("请输入镜头代码")
                                }
                                Text
                                {
                                    color: "red"
                                    text: qsTr("[一行一个镜头代码]")
                                }
                            }
                            Rectangle
                            {
                                color: "#fcfcfc"
                                width: parent.width-parent.padding*2
                                height: parent.height-codeText.height-parent.spacing-parent.padding*2
                                border.width: 1
                                border.color: "#363636"
                                radius: 5
                                TextEdit
                                {
                                    id: contentTextEdit
                                    selectByMouse: true
                                    font.pixelSize: 16
                                    anchors.fill: parent
                                    anchors.margins: 3
                                }
                            }
                        }
                    }
                    Item
                    {
                        id: midContentItem
                        width: 80
                        height: parent.height
                        Button
                        {
                            id: uploadButtom
                            width: 70
                            height: 40
                            text: "提交>>"
                            anchors.centerIn: parent
                            background: Rectangle
                            {
                                implicitWidth: 120
                                implicitHeight: 40
                                border.color: uploadButtom.pressed ? "#666666" : "#000000"
                                border.width: uploadButtom.visualFocus ? 2 : 1
                                color: "#fcfcfc"
                                radius: 2
                            }
                            onClicked:
                            {
                                // enabled = false;
                                // resultTextEdit.text = JSession.commitScript(dirTextInput.text,scriptComboBox.currentText,contentTextEdit.text)
                                // enabled = true;
                                if(dirTextInput.text.length == 0)
                                {
                                    resultTextEdit.text = "请选择NAS目录!"
                                    return;
                                }
                                resultTextEdit.clear();
                                var str = contentTextEdit.text;
                                alert(str.trim());
                                if(str.length == 0)
                                {
                                    resultTextEdit.text = "请输入镜头代码!"
                                    return;
                                }

                                var fileNames = str.split("\n");
                                for(var i = 0; i < fileNames.length; i++)
                                {
                                    if(fileNames[i].length === 0)
                                    {
                                        resultTextEdit.append("失败:输入错误!");
                                        continue;
                                    }
                                    var scriptFileName = scriptComboBox.currentText;
                                    var commitFileName = dirTextInput.text+"/"+fileNames[i]+".json";
                                    if(scriptFileName.length === 0)
                                    {
                                        resultTextEdit.append(fileNames[i]+" 失败:请选择脚本!");
                                        continue;
                                    }
                                    else
                                    {
                                        console.log(scriptFileName,commitFileName)
                                        var result = JSession.copyFile(scriptFileName,commitFileName);
                                        if(result === 1)
                                        {
                                            resultTextEdit.append(fileNames[i]+" 失败:脚本文件未发现!");
                                        }
                                        else if(result === 2)
                                        {
                                            resultTextEdit.append(fileNames[i]+" 失败:旧文件移除失败!");
                                        }
                                        else if(result === 3)
                                        {
                                            resultTextEdit.append(fileNames[i]+" 失败:文件拷贝失败!");
                                        }
                                        else
                                        {
                                            resultTextEdit.append(fileNames[i]+" 成功!");
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Item
                    {
                        id: rightContentItem
                        width: (parent.width-midContentItem.width)/2
                        height: parent.height
                        Column
                        {
                            anchors.fill: parent
                            spacing: 5
                            padding: 5
                            Text
                            {
                                id: resultText
                                text: qsTr("NAS目录提交结果")
                            }
                            Rectangle
                            {
                                color: "#fcfcfc"
                                width: parent.width-parent.padding*2
                                height: parent.height-resultText.height-parent.spacing-parent.padding*2
                                border.width: 1
                                border.color: "#363636"
                                radius: 5

                                TextEdit
                                {
                                    id: resultTextEdit
                                    selectByMouse: true
                                    font.pixelSize: 16
                                    anchors.fill: parent
                                    anchors.margins: 3
                                    readOnly: true
                                    color: "red"
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
