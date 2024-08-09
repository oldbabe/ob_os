import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root

    implicitHeight: 40
    implicitWidth: 300

    property string titleText: ""
    property string valueText: ""
    property alias slider : control
    property alias title : typeLabel

    Label
    {
        id:typeLabel
        width: 60
        text: titleText;
        color: "#F1F1F1";
        anchors.verticalCenter:  parent.verticalCenter
        anchors.left: parent.left
    }
    Slider
    {
        id:control
        anchors.verticalCenter:  parent.verticalCenter
        anchors.left: typeLabel.right
        anchors.leftMargin: 10
        anchors.right: parent.right

        background: Rectangle
        {
            x: control.leftPadding
            y: control.topPadding + control.availableHeight / 2 - height / 2
            width: control.availableWidth
            implicitHeight: 30
            radius: 2
            color: "#bdbebf"

            Rectangle
            {
                width: control.visualPosition * parent.width
                height: parent.height
                color: "#21be2b"
                radius: 2
            }
        }

        handle: Rectangle {
            x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
            y: control.topPadding + control.availableHeight / 2 - height / 2
            implicitWidth: 26
            implicitHeight: 26
            radius: 13
            color: control.pressed ? "#f0f0f0" : "#f6f6f6"
            border.color: "#bdbebf"

            Text {
                anchors.centerIn: parent
                text: valueText
            }
        }
    }
}
