import QtQuick 6.2
import QtQuick.Controls 6.2

Rectangle
{
    id:root

    color: "#303030"
    implicitWidth:120
    implicitHeight: textField.height


    property int titleWidth: 100

    property string titleText: "标题"
    property string valueText: ""

    property alias inputItem: textField
    signal textEditFinished(string text)

    function setValue(value)
    {
        textField.text = value;
    }

    Item
    {
        id: textItem
        width: titleWidth
        height: parent.height
        Label
        {
            id: label
            text: titleText
            color: "aliceblue"
            font.pixelSize: 12
            anchors.centerIn: parent
        }
    }

    TextField
    {
        id: textField
        font.pixelSize: 12
        text: valueText
        selectByMouse: true
        color: "aliceblue"
        anchors.verticalCenter: root.verticalCenter
        anchors.left: textItem.right
        anchors.leftMargin: 10
        anchors.right: root.right
        clip: true

        background: Rectangle
        {
            radius: 3
            color: "#262626"
            border.width: 1
            border.color: textField.focus?"#9F9F9F":(textField.hovered?"#9F9F9F":"#666666")
        }

        onEditingFinished:
        {
            textField.cursorVisible = false;
            textEditFinished(textField.text)
        }
    }
}

