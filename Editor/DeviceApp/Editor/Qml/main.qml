import QtQuick 6.2
import CppService 1.0

import "./CustomItem"

Window
{
    id:window
    width: 800
    height: 800
    visible: true
//    color: "black"

    Connections
    {
        target: window
        function onClosing(close)
        {
            setPageLoader.source = "";
        }
    }

    Component.onCompleted:
    {
        var textd =  EditorQml.getRobotConnected()?"(已连接)":"(未连接)";
        listModel.set(2,{"name":"机械臂&轨道"+textd})
        textd = EditorQml.getCameraConnected()?"(已连接)":"(未连接)";
        listModel.set(3,{"name":"相机"+textd})
        textd =  EditorQml.getFollowfocusConnected()?"(已连接)":"(未连接)";
        listModel.set(4,{"name":"跟焦器"+textd})
        textd =  EditorQml.getTurnplateConnected()?"(已连接)":"(未连接)";
        listModel.set(5,{"name":"转盘"+textd})
    }

    Connections
    {
        target: EditorQml
        function onDeviceStateChanged(deviceId,state)
        {
            var textd = state?"(已连接)":"(未连接)";
            if(deviceId === 1)
                listModel.set(2,{"name":"机械臂&轨道"+textd});
            else if(deviceId === 2)
                listModel.set(3,{"name":"相机"+textd});
            else if(deviceId === 3)
                listModel.set(4,{"name":"跟焦器"+textd});
            else if(deviceId === 4)
                listModel.set(5,{"name":"转盘"+textd});
        }
    }

    Rectangle{
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
            text: qsTr("本机IP:"+EditorQml.getLocalHostName())
        }
    }

    //标题
    Text
    {
        id: setTitleText
        font.pixelSize: 14
        color: "#f1f1f1"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        text: qsTr("偏好设置")
    }

    ListModel
    {
        id: listModel
        ListElement {name: "基本设置"}
        ListElement {name: "实时图像"}
        ListElement {name: "机械臂&轨道"}
        ListElement {name: "相机"}
        ListElement {name: "跟焦器"}
        ListElement {name: "转盘"}
        ListElement {name: "LiveLinkFreed"}
    }

    ListView
    {
        id: listView

        anchors.top: setTitleText.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        model:listModel
        delegate: Item
        {
            id: listItem
            width: listView.width
            height: 50
            Rectangle
            {
                color: "#363636"
                width: parent.width-4
                height: parent.height-4
                anchors.centerIn: parent

                Text
                {
                    anchors.centerIn: parent
                    color: "#f1f1f1"
                    text: name
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        if(index === 0)
                            setPageLoader.source = "qrc:/Qml/EditorBaseSetupPage.qml";
                        else if(index === 1)
                            setPageLoader.source = "qrc:/Qml/CameraVieo.qml";
                        else if(index === 6)
                            setPageLoader.source = "qrc:/Qml/LivelinkFreed.qml";
                    }
                }
            }
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



