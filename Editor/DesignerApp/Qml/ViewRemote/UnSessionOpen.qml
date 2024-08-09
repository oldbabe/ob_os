import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import "../Component"

Window
{
    id: root

    width:260
    height: 90
    visible: true
    title: qsTr("会话未打开")
    modality: Qt.WindowModal
    onClosing:(close)=>{root.destroy()}

    Rectangle
    {
        width: parent.width
        height: parent.height
        color: "#EEEEEE"
        Text
        {
            id: badText
            text: qsTr("请先打开会话或创建会话!!!")
            font.pointSize: 12
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
        }
        ToolButton
        {
            implicitHeight: 30
            implicitWidth: 60
            norColor: "#CCCCCC"
            anchors.top: badText.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            backAdius:8
            showText:"关闭"
            hoverColor:"#EE5050"
            showTextColor:"#202020"
            showTextSize:16
            onButtonClicked:root.destroy();
        }
    }
}

