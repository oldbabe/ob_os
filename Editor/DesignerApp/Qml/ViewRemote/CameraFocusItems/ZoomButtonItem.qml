import QtQuick 6.2
import QtQuick.Controls 6.2

import "../../Component"

import JMoco 1.0

//单个数值的Item (可修改)
BackGroundItem
{
    id: root

    implicitWidth: 200
    implicitHeight: 40
    norColor: "#202020"
    hovColor: "#272727"
    //tag 标签文本
    property string tagText: "Zoom"

    //tag 标签
    Item
    {
        anchors.right: root.lineRect.left
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Label
        {
            font.pixelSize: 14
            color:"#D7D7D7"
            text: root.tagText
            anchors.centerIn: parent
        }
    }

    Item
    {
        anchors.left: root.lineRect.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Row
        {
            topPadding: 5
            leftPadding: (parent.width-6*30)/7
            spacing:(parent.width-6*30)/7
            ToolButton
            {
                id:left3
                width: 30
                height: 30
                enable:JCamera.zoomOperationStatus.value  === "1" && JCamera.lensName.includes("PZ");
                icon: "qrc:/Image/icon_play_left3.png"
                opacityIMG: enable? 0.9 : 0.4
                onButtonPressed: JCamera.zoomOperation(-8)
                onButtonRelease: JCamera.zoomOperation(0)
            }
            ToolButton
            {
                id:left2
                width: 30
                height: 30
                icon: "qrc:/Image/icon_play_left2.png"
                enable:JCamera.zoomOperationStatus.value  === "1" && JCamera.lensName.includes("PZ");
                opacityIMG: enable? 0.9 : 0.4
                onButtonPressed: JCamera.zoomOperation(-4)
                onButtonRelease: JCamera.zoomOperation(0)
            }
            ToolButton
            {
                id:left1
                width: 30
                height: 30
                icon: "qrc:/Image/icon_play_left1.png"
                enable:JCamera.zoomOperationStatus.value  === "1" && JCamera.lensName.includes("PZ");
                opacityIMG: enable? 0.9 : 0.4
                onButtonPressed: JCamera.zoomOperation(-2)
                onButtonRelease: JCamera.zoomOperation(0)
            }
            ToolButton
            {
                id:right1
                width: 30
                height: 30
                icon: "qrc:/Image/icon_play_right1.png"
                enable:JCamera.zoomOperationStatus.value  === "1" && JCamera.lensName.includes("PZ");
                opacityIMG: enable? 0.9 : 0.4
                onButtonPressed: JCamera.zoomOperation(2)
                onButtonRelease: JCamera.zoomOperation(0)
            }
            ToolButton
            {
                id:right2
                width: 30
                height: 30
                icon: "qrc:/Image/icon_play_right2.png"
                enable:JCamera.zoomOperationStatus.value  === "1" && JCamera.lensName.includes("PZ");
                opacityIMG: enable? 0.9 : 0.4
                onButtonPressed: JCamera.zoomOperation(4)
                onButtonRelease: JCamera.zoomOperation(0)
            }
            ToolButton
            {
                id:right3
                width: 30
                height: 30
                enterText: ""
                icon: "qrc:/Image/icon_play_right3.png"
                enable:JCamera.zoomOperationStatus.value  === "1" && JCamera.lensName.includes("PZ");
                opacityIMG: enable? 0.9 : 0.4
                onButtonPressed: JCamera.zoomOperation(8)
                onButtonRelease: JCamera.zoomOperation(0)
            }
        }
    }
}
