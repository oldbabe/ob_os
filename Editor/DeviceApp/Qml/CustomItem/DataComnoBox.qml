import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root

    implicitHeight: 40
    implicitWidth: 200

    property string titleText: ""
    property alias dataComBox : typecomboBox

    Label
    {
        id:typeLabel
        width: 60
        text: titleText;
        color: "#F1F1F1";
        anchors.verticalCenter:  parent.verticalCenter
        anchors.left: parent.left
    }
    ComboBox
    {
        id:typecomboBox
        anchors.verticalCenter:  parent.verticalCenter
        anchors.left: typeLabel.right
        anchors.leftMargin: 10
        anchors.right: parent.right

        contentItem: Text
        {
            text: typecomboBox.displayText
            font: typecomboBox.font
            color: "#f1f1f1"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        background: Rectangle {
            color: "#202020"
            radius: 4
            border.width: 1
            border.color: "#565656"
        }
    }
}
