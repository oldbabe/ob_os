import QtQuick 6.2
import QtQuick.Controls 6.2
// 一个数值Item
Rectangle
{
    id: root
    radius: 2
    color: "#262626"
    implicitHeight: 22
    implicitWidth: 60

    //标题文本
    property string titleText: "数值"
    //内容文本
    property string valueText: "0"

    function setText(text)
    {
        label.text = text;
    }

    Item
    {
        width: 20
        height: 22
        visible: titleText == ""?false:true
        Label
        {
            color:"#D7D7D7"
            text: titleText
            font.pixelSize: 12
            anchors.centerIn: parent
        }
    }

    Label
    {
        id: label
        x:titleText == ""?5:20
        y:0
        color:"#D7D7D7"
        text: valueText
        font.pixelSize: 12
        anchors.verticalCenter: parent.verticalCenter
    }
}
