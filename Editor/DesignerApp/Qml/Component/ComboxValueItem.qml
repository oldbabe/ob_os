import QtQuick 6.2
import QtQuick.Controls 6.2

//单个数值 的Item(不可修改)
BackGroundItem
{
    id: root

    norColor: "#404040"
    hovColor: "#444444"


    //tag 标签文本
    property string tagText: "标签"
    //显示文本
    property string showText: ""


    //显示文本
    property alias comboxItem : comboBox

    Item
    {
        anchors.right: root.lineRect.left
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Label
        {
            font.pixelSize: 10
            color:"#D7D7D7"
            text: root.tagText
            anchors.centerIn: parent
        }
    }

    Text
    {
        id:comboText

        anchors.left: root.lineRect.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

    }

    ComboBox
    {
        id:comboBox

        anchors.left: root.lineRect.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        currentIndex: 0
        model:["1","2","3","4"]
        contentItem: Text
        {
            text: comboBox.displayText
            font: comboBox.font
            color: "#f1f1f1"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        background: Rectangle
        {
            color: "#202020"
            radius: 4
            border.width: 1
            border.color: "#565656"
        }
    }
}
