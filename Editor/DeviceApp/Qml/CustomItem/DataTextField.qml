import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root

    implicitHeight: 40
    implicitWidth: 200

    property string titleText: ""
    property alias dataTextField : textField
    property alias titleLabel : label
    property int labelWidth: 60

    Label
    {
        id:label
        width: labelWidth
        text: titleText;
        color: "#F1F1F1";
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
    }
    TextField
    {
        id:textField
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: label.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        height: 30

        color: "#f1f1f1"
        verticalAlignment: TextInput.AlignVCenter

        background: Rectangle {
            color: "#202020"
            radius: 4
            border.width: 1
            border.color: "#565656"
        }
    }
}
