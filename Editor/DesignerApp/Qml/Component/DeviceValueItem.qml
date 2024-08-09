import QtQuick 6.2
import QtQuick.Controls 6.2
import "../Component"

//单个数值的Item (可修改)
BackGroundItem
{
    id: root

    property alias bindButton: updateBt
    //标签文本
    property alias textItem: dataItem
    //标签文本
    property string tagText: "tag"
    //标题文本
    property string titleText: "G"
    //内容文本
    property string inputText: "0"
    //悬浮文本
    property string enteText: "输入值-360到360"
    //
    property int maxCount: 360
    property int minCount: -360
    signal butttonClick();
    signal textInput(int text)


    //设置值
    function setValue(value)
    {
        dataItem.valueText=value;
    }

    //tag 标签
    Item
    {
        anchors.right: root.lineRect.left
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Label
        {
            font.pixelSize: 12
            color:"#D7D7D7"
            text: root.tagText
            anchors.centerIn: parent
        }
    }

    BaseTextItem
    {
        id: dataItem
        implicitWidth: 60
        titleText: root.titleText
        enterText: enteText
        maxNum: maxCount
        minNum: minCount
        valueText: valueText
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        onTextEditFinished:(textData) =>
        {
            root.textInput(textData);
        }
    }
    //刷新按钮
    ToolButton
    {
        id: updateBt

        width: 20
        height: 20
        icon: "qrc:/Image/icon_data_refresh.png"

        anchors.left: dataItem.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onButtonClicked: root.butttonClick();
    }
}
