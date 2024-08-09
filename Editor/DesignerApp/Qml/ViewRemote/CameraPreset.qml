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
import "../Component"

Item
{
    id:root

    Component.onCompleted:
    {
        //当给定相机的配置是空时,则初始化相机配置数据
        if(JCameraInstall.count(JCamera.cameraName) === 0)
        {
            JCameraInstall.init(JCamera.cameraName);
        }
        //读取数据
        for(var i = 0; i < JCameraInstall.count(JCamera.cameraName); i++)
        {
            var data = JCameraInstall.get(JCamera.cameraName,i);
            titleModel.append({"title":data.title});
            if(i == 0)
            {
                JCameraInstall.currentIndex = 0;
                propertyItem.setTitle(data.title);
                propertyItem.switchTitleIndex(0);
            }
        }
    }

    //相机名称
    Rectangle
    {
        // visible: JCamera.connected
        width: parent.width
        height: 30
        color: "#303030"
        border.color: "#000000"
        border.width: 2
        Text
        {
            color: "#EEEEEE"
            text: "相机名称"+":"+" "+JCamera.cameraName
            font.pixelSize: 16
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
        }
    }
    //内容
    SplitView
    {
        // visible: JCamera.connected
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        orientation: Qt.Horizontal
        //分离器
        handle: Rectangle
        {
            implicitWidth: 2
            color: SplitHandle.hovered ? "#EEEEEE" : "#000000"
        }
        //title数据
        ListModel
        {
            id:titleModel
        }
        //title视图列表组件
        ListView
        {
            id:titleView
            implicitHeight: parent.height
            implicitWidth: parent.width*0.2
            SplitView.maximumWidth: parent.width*0.5
            SplitView.minimumWidth: parent.width*0.2
            clip: true
            model:titleModel

            delegate:Control
            {
                id:deleItem
                property bool entered: false

                width: titleView.width
                height: 40

                background:Rectangle
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    color: JCameraInstall.currentIndex === index ? ((titleMouseArea.containsMouse||titleMouseArea.containsPress)?"#66DDEE":"#55CCEE"):(titleMouseArea.containsMouse||titleMouseArea.containsPress ?"#DDDDDD":"#CCCCCC")
                }

                contentItem:Item
                {
                    //title 文本显示组件
                    Text
                    {
                        text: title
                        anchors.centerIn: parent
                        elide: Text.ElideRight
                    }
                    MouseArea
                    {
                        id: titleMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked:
                        {
                            if(JCameraInstall.currentIndex != index)
                            {
                                JCameraInstall.currentIndex = index;
                                propertyItem.setTitle(title);
                                propertyItem.switchTitleIndex(JCameraInstall.currentIndex);
                            }
                        }
                    }
                }
            }
        }

        //属性视图
        Item
        {
            id: propertyItem
            implicitHeight: parent.height
            implicitWidth: parent.width*0.8
            //预设名称
            Item
            {
                id: useItem
                width:parent.width
                height: 30
                anchors.top: propertyItem.top
                anchors.left: parent.left
                Text
                {
                    id: useButtonText
                    width: 35
                    color: "#EEEEEE"
                    text: "名称"
                    font.pixelSize: 14
                    anchors.left:parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
                BaseTextItemString
                {
                    id: listname
                    anchors.left: useButtonText.right
                    anchors.leftMargin: 5
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    enterText:"双击修改"
                    onTextEditFinished:function(textData)
                    {
                        listname.valueText = textData;
                        titleModel.setProperty(JCameraInstall.currentIndex,"title",textData);
                        JCameraInstall.setTitle(JCamera.cameraName,JCameraInstall.currentIndex,textData);
                    }
                }
            }
            //属性数据
            ListModel
            {
                id:propertyModel
            }
            // 属性列表组件  - 设置title后端接口 JCameraInstall.setTitle(cameraName,index,title)
            ListView
            {
                id:propertyView
                anchors.top: useItem.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: buttonItem.top
                anchors.bottomMargin: 5
                clip: true
                model:propertyModel
                delegate:Control
                {
                    id:properItem
                    width: propertyView.width
                    height: 35
                    leftPadding:5
                    rightPadding:5
                    topPadding:3
                    bottomPadding:3
                    contentItem:Rectangle
                    {
                        id: titleItem
                        radius: 3
                        color: "#505050"
                        border.width: 2
                        border.color: "#303030"
                        Row
                        {
                            anchors.fill: parent
                            //title
                            Text
                            {
                                id:titleText
                                color: "#FFFFFF"
                                font.pixelSize:12
                                width: 120
                                height: parent.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                text: titleItem.getTitle()
                            }
                            //分割线
                            Rectangle
                            {
                                width: 2
                                height: parent.height
                                color: "#303030"
                            }
                            //displayText
                            Text
                            {
                                color: "#FFFFFF"
                                font.pixelSize:12
                                text: displayText
                                width: parent.width-titleText.width-2
                                height: parent.height
                                leftPadding:5
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        function getTitle()
                        {
                           if(key == 256)
                               return "光圈";
                           else if(key == 259)
                               return "快门速度";
                           else if(key == 260)
                               return "ISO";
                           else if(key == 261)
                               return "程序模式";
                           else if(key == 262)
                               return "静态影像文件格式";
                           else if(key == 263)
                               return "JPEG质量";
                           else if(key == 264)
                               return "白平衡";
                           else if(key == 265)
                               return "对焦模式";
                           else if(key == 270)
                               return "拍摄模式";
                           else if(key == 273)
                               return "长宽比";
                           else if(key == 275)
                               return "对焦区域";
                           else if(key == 295)
                               return "动态影像文件格式";
                           else if(key == 296)
                               return "动态影像设置";
                           else if(key == 297)
                               return "动态影像帧速率";
                           else
                               return "null";
                        }
                    }
                }
            }
            //按钮
            Row
            {
                id:buttonItem
                clip: true
                height: 30
                anchors.bottom: propertyItem.bottom
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.right: parent.right
                leftPadding: (buttonItem.width-120)/3
                spacing: (buttonItem.width-120)/3
                ToolButton
                {
                    width: 60
                    height: parent.height
                    showText:"刷新"
                    onButtonClicked:
                    {
                        if(propertyModel.count > 0)
                        {
                            var window = updateComponent.createObject(root);
                            window.updateProperty.connect(propertyItem.updateProperty);
                            window.show();
                        }
                        else
                        {
                            propertyItem.updateProperty(JCameraInstall.currentIndex);
                        }
                    }
                }
                ToolButton
                {
                    width: 60
                    height: parent.height
                    enable: propertyModel.count>0?true:false
                    showText:"应用"
                    onButtonClicked:
                    {
                        // conToolTip.visible = true;
                        // pathAnim.start();
                        enable = false;
                        JCameraInstall.apply(JCamera.cameraName,JCameraInstall.currentIndex);
                        enable = true;
                        conToolTip.visible = true;
                        pathAnim.start();
                    }
                }
                //成功标签
                Text
                {
                    id:conToolTip
                    visible: false
                    text:"应用成功"
                    color:"#DDDDDD"
                }
                PathAnimation
                {
                    id:pathAnim
                    target: conToolTip
                    path: Path{
                        startX: buttonItem.width/2-24 ; startY: 50
                        PathLine { x: buttonItem.width/2-24 ; y: -50 }
                    }
                    duration: 2000
                    onFinished: conToolTip.visible = false
                }
            }

            //提示文本
            Text
            {
                visible: propertyModel.count===0?true:false
                color: "#FFFFFF"
                text: qsTr("请点击刷新按钮！")
                anchors.centerIn: parent
            }

            function setTitle(text)
            {
                listname.valueText = text;
            }

            //切换title index数据
            function switchTitleIndex(index)
            {
                propertyModel.clear();
                var props = JCameraInstall.getProperty(JCamera.cameraName,index);
                for(var i = 0; i < props.length;i++)
                {
                    var prop = props[i]
                    if(prop.writable === 1)
                        propertyModel.append({"key":prop.key, "displayText": prop.value});
                }
            }
            //更新 index属性数据
            function updateProperty(index)
            {
                JCameraInstall.setProperty(JCamera.cameraName,0,JCamera.programMode.key,JCamera.programMode.writable,JCamera.programMode.value);
                JCameraInstall.setProperty(JCamera.cameraName,1,JCamera.aspectRatio.key,JCamera.aspectRatio.writable,JCamera.aspectRatio.value);
                JCameraInstall.setProperty(JCamera.cameraName,2,JCamera.fileType.key,JCamera.fileType.writable,JCamera.fileType.value);
                JCameraInstall.setProperty(JCamera.cameraName,3,JCamera.jpegQuality.key,JCamera.jpegQuality.writable,JCamera.jpegQuality.value);
                JCameraInstall.setProperty(JCamera.cameraName,4,JCamera.driveMode.key,JCamera.driveMode.writable,JCamera.driveMode.value);         JCameraInstall.setProperty(JCamera.cameraName,11,JCamera.focusMode.key,JCamera.focusMode.writable,JCamera.focusMode.value);
                JCameraInstall.setProperty(JCamera.cameraName,5,JCamera.focusMode.key,JCamera.focusMode.writable,JCamera.focusMode.value);
                JCameraInstall.setProperty(JCamera.cameraName,6,JCamera.focusArea.key,JCamera.focusArea.writable,JCamera.focusArea.value);
                JCameraInstall.setProperty(JCamera.cameraName,7,JCamera.whiteBalance.key,JCamera.whiteBalance.writable,JCamera.whiteBalance.value);
                JCameraInstall.setProperty(JCamera.cameraName,8,JCamera.fNumber.key,JCamera.fNumber.writable,JCamera.fNumber.value);
                JCameraInstall.setProperty(JCamera.cameraName,9,JCamera.shutterSpeed.key,JCamera.shutterSpeed.writable,JCamera.shutterSpeed.value);
                JCameraInstall.setProperty(JCamera.cameraName,10,JCamera.isoSensitivity.key,JCamera.isoSensitivity.writable,JCamera.isoSensitivity.value);
                JCameraInstall.setProperty(JCamera.cameraName,11,JCamera.movieFileFormat.key,JCamera.movieFileFormat.writable,JCamera.movieFileFormat.value);
                JCameraInstall.setProperty(JCamera.cameraName,12,JCamera.movieRecordingFrameRate.key,JCamera.movieRecordingFrameRate.writable,JCamera.movieRecordingFrameRate.value);
                JCameraInstall.setProperty(JCamera.cameraName,13,JCamera.movieRecording.key,JCamera.movieRecording.writable,JCamera.movieRecording.value);

                propertyModel.clear();
                var prop = {"key":"", "displayText": "",}
                if(JCamera.programMode.writable === 1)
                {
                    prop.key = JCamera.programMode.key;
                    prop.displayText = JCamera.programMode.value;
                    propertyModel.append(prop);
                }
                if(JCamera.aspectRatio.writable === 1)
                {
                    prop.key = JCamera.aspectRatio.key;
                    prop.displayText = JCamera.aspectRatio.value;
                    propertyModel.append(prop);
                }
                if(JCamera.fileType.writable === 1)
                {
                    prop.key = JCamera.fileType.key;
                    prop.displayText = JCamera.fileType.value;
                    propertyModel.append(prop);
                }
                if(JCamera.jpegQuality.writable === 1)
                {
                    prop.key = JCamera.jpegQuality.key;
                    prop.displayText = JCamera.jpegQuality.value;
                    propertyModel.append(prop);
                }
                if(JCamera.driveMode.writable === 1)
                {
                    prop.key = JCamera.driveMode.key;
                    prop.displayText = JCamera.driveMode.value;
                    propertyModel.append(prop);
                }
                if(JCamera.focusMode.writable === 1)
                {
                    prop.key = JCamera.focusMode.key;
                    prop.displayText = JCamera.focusMode.value;
                    propertyModel.append(prop);
                }
                if(JCamera.focusArea.writable === 1)
                {
                    prop.key = JCamera.focusArea.key;
                    prop.displayText = JCamera.focusArea.value;
                    propertyModel.append(prop);
                }
                if(JCamera.whiteBalance.writable === 1)
                {
                    prop.key = JCamera.whiteBalance.key;
                    prop.displayText = JCamera.whiteBalance.value;
                    propertyModel.append(prop);
                }
                if(JCamera.fNumber.writable === 1)
                {
                    prop.key = JCamera.fNumber.key;
                    prop.displayText = JCamera.fNumber.value;
                    propertyModel.append(prop);
                }
                if(JCamera.shutterSpeed.writable === 1)
                {
                    prop.key = JCamera.shutterSpeed.key;
                    prop.displayText = JCamera.shutterSpeed.value;
                    propertyModel.append(prop);
                }
                if(JCamera.isoSensitivity.writable === 1)
                {
                    prop.key = JCamera.isoSensitivity.key;
                    prop.displayText = JCamera.isoSensitivity.value;
                    propertyModel.append(prop);
                }
                if(JCamera.movieFileFormat.writable === 1)
                {
                    prop.key = JCamera.movieFileFormat.key;
                    prop.displayText = JCamera.movieFileFormat.value;
                    propertyModel.append(prop);
                }
                if(JCamera.movieRecordingFrameRate.writable === 1)
                {
                    prop.key = JCamera.movieRecordingFrameRate.key;
                    prop.displayText = JCamera.movieRecordingFrameRate.value;
                    propertyModel.append(prop);
                }
                if(JCamera.movieRecording.writable === 1)
                {
                    prop.key = JCamera.movieRecording.key;
                    prop.displayText = JCamera.movieRecording.value;
                    propertyModel.append(prop);
                }
            }
        }
    }
    //蒙版
    // Item
    // {
    //     id: unConitem
    //     visible: !JCamera.connected
    //     anchors.fill: parent

    //     Text
    //     {
    //         id: hintText
    //         color: "#F2F2F2"
    //         font.pixelSize: 18
    //         text: qsTr("请连接相机")
    //         anchors.centerIn: parent
    //     }
    //     Image
    //     {
    //         id:btn_icon
    //         anchors.right: hintText.left
    //         anchors.rightMargin: 5
    //         anchors.verticalCenter: hintText.verticalCenter

    //         width: 24
    //         height: 24
    //         fillMode: Image.PreserveAspectFit
    //         source: "qrc:/Image/icon_studio_link.png"
    //     }
    // }

    //确认刷新的窗口
    Component
    {
        id: updateComponent
        Window
        {
            id: updateWindow
            width: 300
            height: 80
            maximumHeight: 80
            maximumWidth: 240
            minimumHeight: 80
            minimumWidth: 240
            title: "相机预设"
            modality: Qt.ApplicationModal

            signal updateProperty(int index);

            Item
            {
                anchors.fill: parent
                Row
                {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    Text {
                        text: "确认刷新预设？"
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
                        height: 26
                        text: "确认"
                        onClicked:
                        {
                            updateWindow.updateProperty(JCameraInstall.currentIndex);
                            updateWindow.close();
                            updateWindow.destroy();
                        }
                    }
                    Button
                    {
                        width: 60
                        height: 26
                        text: "取消"
                        onClicked:
                        {
                            updateWindow.close();
                            updateWindow.destroy();
                        }
                    }
                }
            }
        }
    }
}
