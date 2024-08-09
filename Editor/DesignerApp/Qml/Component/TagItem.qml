import QtQuick 6.2
import QtQuick.Controls 6.2
//树列表的顶级标签Item
BackGroundItem
{
    id: root

    implicitHeight: 30
    implicitWidth: 200

    //是否缩放属性
    property bool zoomFlag: false
    //tag 文本
    property string tagText: "tag"
    //双击事件
    onClickItem:
    {
        zoomFlag = !zoomFlag
        arrowImage.source= root.zoomFlag ? "qrc:/Image/icon_openArrow.png":"qrc:/Image/icon_arrow.png"
    }
    //箭头
    Item
    {
        id: arrowItem
        width: 16
        height: 16
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 5
        Image
        {
            id: arrowImage
            fillMode: Image.PreserveAspectFit
            source: root.zoomFlag ? "qrc:/Image/icon_openArrow.png":"qrc:/Image/icon_arrow.png"
            anchors.fill: parent
        }
        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: arrowImage.source = root.zoomFlag ? "qrc:/Image/icon_openArrow_hover.png": "qrc:/Image/icon_arrow_hover.png"
            onExited: arrowImage.source = root.zoomFlag ? "qrc:/Image/icon_openArrow.png":"qrc:/Image/icon_arrow.png"
            onPressed:
            {
                root.zoomFlag = !root.zoomFlag
                arrowImage.source= root.zoomFlag ? "qrc:/Image/icon_openArrow.png":"qrc:/Image/icon_arrow.png"
            }
        }
    }
    //tag 显示文本
    Label
    {
        id: showText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: arrowItem.right
        anchors.leftMargin: 5
        text: parent.tagText
        font.pixelSize: 12
        color: "#f2f2f2"
    }
}
