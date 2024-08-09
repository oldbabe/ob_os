import QtQuick 6.2
import QtQuick.Controls 6.2
import "../Component"

// 六个值显示Item
BackGroundItem
{
    id: root

    implicitWidth: 200
    implicitHeight: 100

    property alias bindButton: updateBt
    //标题文本
    property string tagText: "tag"
    //标题列表
    property var titleList:["X","Y","Z","A","B","C","E1"]
    //参数列表
    property var valueList:["0","0","0","0","0","0","0"]
    //
    signal butttonClick();

    property alias posX: data1
    property alias posY: data2
    property alias posZ: data3
    property alias posA: data4
    property alias posB: data5
    property alias posC: data6
    property alias posE1: data7

    function setX(value)
    {
        data1.setText(value);
    }
    function setY(value)
    {
        data2.setText(value);
    }
    function setZ(value)
    {
        data3.setText(value);
    }
    function setA(value)
    {
        data4.setText(value);
    }
    function setB(value)
    {
        data5.setText(value);
    }
    function setC(value)
    {
        data6.setText(value);
    }
    function setE1(value)
    {
        data7.setText(value);
    }

    //标题Item
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
    //数值Item
    Grid
    {
        id: grids
        columns: 2
        spacing: 2
        columnSpacing: 5
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        BaseValueItem
        {
            id: data1
            implicitWidth:90
            titleText: titleList[0]
            valueText: valueList[0]
        }
        BaseValueItem
        {
            id: data2
            implicitWidth:90
            titleText: titleList[1]
            valueText: valueList[1]
        }
        BaseValueItem
        {
            id: data3
            implicitWidth:90
            titleText: titleList[2]
            valueText: valueList[2]
        }
        BaseValueItem
        {
            id: data4
            implicitWidth:90
            titleText: titleList[3]
            valueText: valueList[3]
        }
        BaseValueItem
        {
            id: data5
            implicitWidth:90
            titleText: titleList[4]
            valueText: valueList[4]
        }
        BaseValueItem
        {
            id: data6
            implicitWidth:90
            titleText: titleList[5]
            valueText: valueList[5]
        }
        BaseValueItem
        {
            id: data7
            implicitWidth:90
            titleText: titleList[6]
            valueText: valueList[6]
        }
        //刷新按钮
        ToolButton
        {
            id: updateBt

            width: 20
            height: 20
            icon: "qrc:/Image/icon_data_refresh.png"
            onButtonClicked: root.butttonClick();
        }
    }
}
