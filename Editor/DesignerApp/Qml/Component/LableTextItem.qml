import QtQuick 6.2
import QtQuick.Controls 6.2
//两个lable
Item
{
    id: root

    width: 80
    height:25
    //标题文本
    property string titleText: "数值"
    //内容文本
    property string valueText: "0"

    property color titleColor:"#E0A030"
    property color valueColor:"#00C0D0"

    property int titleSize:20
    property int valueSize:20
    Label
    {
        id:lab1
        color: titleColor
        text: titleText
        font.pixelSize: titleSize
        anchors.left: parent.left
        anchors.verticalCenter : parent.verticalCenter
    }

    Label
    {
        id:lab2
        color: valueColor
        text: valueText
        font.pixelSize: valueSize
        anchors.left:lab1.right
        anchors.verticalCenter : parent.verticalCenter

    }
}
