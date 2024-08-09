import QtQuick 6.2

Rectangle
{
    id: root
    color: "#363636"
    implicitHeight: 50
    implicitWidth: 300

    property alias titleText: text1
    property alias loadedText: text2
    property alias connectedText: text3
    property alias stateText: text4
    property alias textItem5: text5

    signal buttonClick()

    Row
    {
        anchors.centerIn: parent
        Text
        {
            id:text1
            color: "#f1f1f1"
        }
        Text
        {
            id:text2
            color: "#f1f1f1"
        }
        Text
        {
            id:text3
            color: "#f1f1f1"
        }
        Text
        {
            id:text4
            color: "#f1f1f1"
        }
        Text
        {
            id:text5
            color: "#f1f1f1"
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: root.buttonClick();
    }
}
