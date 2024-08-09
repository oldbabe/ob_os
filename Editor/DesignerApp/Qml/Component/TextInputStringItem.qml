import QtQuick 6.2
import QtQuick.Controls 6.2

//文本Item
BackGroundItem
{
    id: root

    //tag 标签文本
    property string tagText: "空"
    //后缀
    property string suffixText
    //内容文本
    property string inputText: ""
    //悬浮文本
    property string enteText: ""
    //前置文本
    property string titleText: ""
    //
    property int itemWidht : 80
    //
    property color textColor:"#D7D7D7"
    property color recColor: "#262626"
    property color borderColor: "#464646"

    signal textEditFinished(string text)

    function setValue(value)
    {
        inputText.text = value;
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
            color:textColor
            text: root.tagText
            anchors.centerIn: parent
        }
    }

    BaseTextItemString
    {
        id: data1
        implicitWidth: itemWidht
        titleText: root.titleText
        enterText: enteText
        lastText: suffixText

        valueText: root.inputText
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        onTextEditFinished:(textData) =>
        {
            root.textEditFinished(textData);
        }
        Text
        {
            id: text
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 5
            color:textColor
            text: suffixText
        }
    }
}

