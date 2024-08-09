import QtQuick 6.2

Rectangle
{
    id:root
    color: "#262626"
    implicitHeight: 40
    implicitWidth: 200

    property string title: "标题"
    property int key: -1
    property int writable: -1
    property string value: ""
    property var values: []

    signal mousePressed();

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 14
        color: (writable===1) ? "#f1f1f1" : "#919191"
        text: title
    }

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        font.pixelSize: 14
        color: (writable===1) ? "#f1f1f1" : "#919191"
        text: value
    }

    MouseArea
    {
        anchors.fill: parent
        onPressed:
        {
            root.mousePressed();
        }
    }


}
