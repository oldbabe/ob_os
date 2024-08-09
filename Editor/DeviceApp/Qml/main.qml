import QtQuick 6.2
import QtQuick.Controls 6.2
import CppService 1.0
import JMoco 1.0

import "./CustomItem"

Window
{
    id:window
    width: 800
    height: 800
    visible: true

    Component.onCompleted:
    {
        JStudioController.controllerType = JStudioController.LocalControllerServer;
        JStudioController.init();
    }

    Connections
    {
        target: window
        function onClosing(event)
        {
            realTimeButton.closeWindow();
            JStudioController.release();
            setPageLoader.source = "";
            event.accepted = true;
        }
    }

    //背景
    Rectangle
    {
        id: background
        anchors.fill: parent
        color: "black"
        //本机IP
        Text
        {
            id: hostNameText
            font.pixelSize: 14
            color: "#f1f1f1"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            text: qsTr("本机IP:"+JStudioController.localHostName())
        }
        //脚本执行状态
        Text {
            color: "#f1f1f1"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            font.pixelSize: 32
            text: JCamera.lensName
        }
    }

    Column
    {
        spacing: 2
        anchors.fill: parent
        anchors.margins: 2
        DeviceTagItem
        {
            width: parent.width
            titleText.text: "基本设置"
            onButtonClick: setPageLoader.source = "qrc:/Qml/JConfigPage.qml";
        }
        DeviceTagItem
        {
            width: parent.width
            titleText.text: "采集卡"
            onButtonClick: setPageLoader.source = "qrc:/Qml/CameraView.qml";
        }
        DeviceTagItem
        {
            width: parent.width
            titleText.text: "机械臂&轨道"
            loadedText.text: JRobot.loaded?"(已加载)":"(未加载)"
            connectedText.text: JRobot.connected?"(已连接)":"(未连接)"
        }
        DeviceTagItem
        {
            width: parent.width
            titleText.text: "相机"
            loadedText.text: JCamera.loaded?"(已加载)":"(未加载)"
            connectedText.text: JCamera.connected?"(已连接)":"(未连接)"
            stateText.text: formatState()
            textItem5.text: formatTransferState()
            onButtonClick: setPageLoader.source = "qrc:/Qml/JCameraPage.qml";

            Button
            {
                id: realTimeButton
                width: 70
                text:"USB图像"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 5
                enabled: JCamera.loaded&&JCamera.connected
                visible: false

                signal closeWindow();

                onClicked:
                {
                    const component = Qt.createComponent("qrc:/Qml/JCameraLiveViewWindow.qml");
                    if (component.status === Component.Ready)
                    {
                        var object = component.createObject(null);
                        realTimeButton.closeWindow.connect(object.close);
                        object.show();
                    }
                }
            }

            function formatState()
            {
                if(JCamera.state === 0)
                    return "(线程未启动)";
                else if(JCamera.state === 1)
                    return "(查找中)";
                else if(JCamera.state === 2)
                    return "(连接中)";
                else if(JCamera.state === 3)
                    return "(就绪)";
                else if(JCamera.state === 4)
                    return "(关闭中)";
                else if(JCamera.state === 5)
                    return "(查找超时,请重插)";
                else
                    return "(error)";
            }

            function formatTransferState()
            {
                if(JCamera.remoteMode.value == "1")
                {
                    if(JCamera.transferState === 0)
                        return "(已完成)";
                    else if(JCamera.transferState === 1)
                        return "(开始下载)";
                    else
                        return "(失败"+JCamera.transferState+")";
                }
                else
                {
                    return "";
                }
            }
        }
        // DeviceTagItem
        // {
        //     width: parent.width
        //     titleText.text: "跟焦器"
        //     loadedText.text: JFollowfocus.loaded?"(已加载)":"(未加载)"
        //     connectedText.text: JFollowfocus.connected?"(已连接)":"(未连接)"
        //     onButtonClick: setPageLoader.source = "qrc:/Qml/JFollowFocusPage.qml";
        // }
        // DeviceTagItem
        // {
        //     width: parent.width
        //     titleText.text: "转盘"
        //     loadedText.text: JTurnplate.loaded?"(已加载)":"(未加载)"
        //     connectedText.text: JTurnplate.connected?"(已连接)":"(未连接)"
        // }
        DeviceTagItem
        {
            width: parent.width
            titleText.text: "XR-Freed"
            onButtonClick: setPageLoader.source = "qrc:/Qml/JFreedPage.qml";
        }
    }

    //页面加载器
    Loader
    {
        id: setPageLoader
        anchors.fill: parent
        Connections
        {
            target: setPageLoader.item
            function onQuitPage()
            {
                setPageLoader.source = "";
            }
        }
    }
}


