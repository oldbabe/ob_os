import QtQuick 6.2

//列表标签基础Item
//Rectangle
Item
{
    id: root
    implicitWidth: 300
    implicitHeight: 30
    //别名
    property alias lineRect: line

    property color norColor: "#363636"
    property color hovColor: "#404040"

    //双击信号
    signal clickItem();
    signal doubleClickItem();

    Rectangle
    {
        id:backgroundRect
        anchors.fill: parent
        color: mouseArea.containsMouse ? hovColor:norColor
    }

    //根对象 鼠标事件
    MouseArea
    {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: root.clickItem();
        onDoubleClicked: root.doubleClickItem()
    }
    //分割线
    Rectangle
    {
        id: line
        width: 1
        height: parent.height
        color: "#303030"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 80
    }
}
