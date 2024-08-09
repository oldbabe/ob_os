import QtQuick 6.2
import QtQuick.Controls 6.2

//单个数值的Item (可修改)
BackGroundItem
{
    id: root

    implicitWidth: 200
    implicitHeight: 30
    property bool valueAble: true
    property int maxValue: 100
    property int minValue: 1
    //tag 标签文本
    property string tagText: "tag"
    //标题文本
    property string titleText: "G"
    //内容文本
    property string valueText: "0"
    property string enteText: "输入值1-100"

    property alias slideritem :slider
    property int newValue: 0

    onNewValueChanged:
    {
        setValue(newValue)
    }

    //滑块移动
    signal handleMove(int value)

    function setValue(value)
    {
        root.valueText = value;
        slider.setValue(value);
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
        id: data1
        implicitWidth: 60
        titleText: root.titleText
        enterText: enteText
        maxNum: maxValue
        minNum: minValue
        valueText: root.valueText
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        onTextEditFinished:(textData) =>
        {
            slider.setValue(textData);
            handleMove(textData);
        }
    }

    SliderPressItem
    {
        id: slider
        fromValue:minValue
        toValue:maxValue 
        anchors.left: data1.right
        anchors.leftMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        onMovedValue:
        {
            handleMove(removeValue);
        }
    }
}
