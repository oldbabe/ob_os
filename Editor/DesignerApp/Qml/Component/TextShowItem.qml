import QtQuick 6.2
import QtQuick.Controls 6.2

//文本Item
BackGroundItem
{
    id: root

    //tag 标签文本
    property string tagText: "空"
    //后缀
    property string suffixText: ""
    //内容文本
    property string inputText: "0"
    //悬浮文本
    property string enteText: ""

    //
    property color textColor:"#D7D7D7"
    property color recColor: "#262626"
    property color borderColor: "#464646"


    function setValue(value)
    {
        data1.text = value;
    }

    Item
    {
        anchors.right: root.lineRect.left
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Label
        {
            font.pixelSize: 12
            color: textColor
            text: root.tagText
            anchors.centerIn: parent
        }
    }

    Text
    {
        id: data1
        text: inputText
        font.pixelSize: 12
        color: textColor
        anchors.left: root.lineRect.right
        anchors.leftMargin: 25
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: TextEdit.AlignVCenter
        horizontalAlignment: TextEdit.AlignHCenter

    }
}
