import QtQuick 6.2
import QtQuick.Controls 6.2
import "../Component"

//单个数值 的Item(不可修改)
BackGroundItem
{
    id: root

    norColor: "#404040"
    hovColor: "#444444"

    //快速度百分比 1~70%
    property real kPer: 0.3
    //慢速度百分比 1~70%
    property real mPer: 0.15

    //tag 标签文本
    property string tagText: "标签"
    //内容文本列表
    property string valueText :"0"
    //单位
    property string unitValue : "°"

    property bool remotePower: true
    //回正按键
    property bool returnPower: false

    //信号 -1表示leftbt 1表示rightbt
    signal buttonLeft1Pressed();
    signal buttonLeft2Pressed();
    signal buttonRight1Pressed();
    signal buttonRight2Pressed();
    signal buttonReturnPressed(); //回正按键
    signal buttonRelease();

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

    ToolButton
    {
        id: rightBt1

        width: 25
        height: 25
        showText: "<<"
        pressColor: "#02A7F0"
        visible: root.remotePower

        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onButtonPressed: root.buttonLeft2Pressed();
        onButtonRelease: root.buttonRelease();
        onButtonCanceled: root.buttonRelease();

    }
    ToolButton
    {
        id: rightBt2

        width: 25
        height: 25
        showText: "<"
        pressColor: "#02A7F0"
        visible: root.remotePower

        anchors.left: rightBt1.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onButtonPressed: root.buttonLeft1Pressed();
        onButtonRelease: root.buttonRelease();
        onButtonCanceled: root.buttonRelease();
    }

    BaseValueItem
    {
        id: data
        width: 80
        anchors.left: rightBt2.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        valueText: root.valueText
        titleText: ""

        Label
        {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 5
            color:"#D7D7D7"
            text: root.unitValue
            font.pixelSize: 9
        }
    }

    ToolButton
    {
        id: leftBt1

        width: 25
        height: 25
        showText: ">"
        pressColor: "#02A7F0"
        visible: root.remotePower

        anchors.left: data.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onButtonPressed: root.buttonRight1Pressed();
        onButtonRelease: root.buttonRelease();
        onButtonCanceled: root.buttonRelease();

    }
    ToolButton
    {
        id: leftBt2

        width: 25
        height: 25
        showText: ">>"
        pressColor: "#02A7F0"
        visible: root.remotePower

        anchors.left: leftBt1.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onButtonPressed: root.buttonRight2Pressed();
        onButtonRelease: root.buttonRelease();
        onButtonCanceled: root.buttonRelease();

    }

    ToolButton
    {
        id: returnBT

        width: 25
        height: 25
        icon: "qrc:/Image/icon_leve.png"
        pressColor: "#02A7F0"
        visible: root.remotePower && root.returnPower

        anchors.left: leftBt2.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        onButtonPressed: root.buttonReturnPressed();
        onButtonRelease: root.buttonRelease();
        onButtonCanceled: root.buttonRelease();

    }
}
