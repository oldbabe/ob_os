import QtQuick 6.2
import QtQuick.Controls 6.2

//文本Item
BackGroundItem
{
    id: root

    property alias dataItem: data1
    //tag 标签文本
    property string tagText: "空"
    //后缀
    property string suffixText:""
    //内容文本
    property string inputText: ""
    //悬浮文本
    property string enteText: ""
    //前置文本
    property string titleText: ""
    //
    property int dataWidth: 80
    property int maxCount: 60
    property int minCount: 1
    property color textColor:"#D7D7D7"
    property color recColor: "#262626"
    property color borderColor: "#464646"

    signal textInput(int text)
    function setValue(value)
    {
        inputText = value;
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

    BaseTextItem
    {
        id: data1
        implicitWidth: dataWidth
        titleText: root.titleText
        enterText: enteText
        lastText: suffixText
        maxNum: maxCount
        minNum: minCount
        valueText: root.inputText
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        onTextEditFinished:(textData) =>
        {
            root.textInput(textData);
        }
    }

}
