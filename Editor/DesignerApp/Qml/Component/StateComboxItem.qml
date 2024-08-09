import QtQuick 6.2
import QtQuick.Controls 6.2


Item
{
    id:root
    implicitWidth: 150
    implicitHeight: 40

    //
    property var comboxArray: [""]
    property string titleText: "标题"
    property string valueText: control.currentText
    property int comboxIndex: control.currentIndex
    property int titleWidth: 100
    property alias comboBoxItem : control
    signal indeActivated(int index);

    function setCurrentIndex(index)
    {
        control.currentIndex = index;
    }

    Item
    {
        id: titleItem
        width:titleWidth
        height: parent.height
        anchors.left: root.left
        Label
        {
            id: label
            text: titleText
            color: "#000000"
            font.pixelSize: 12
            anchors.left: titleItem.left
        }
    }

    ComboBox
    {
        id: control
        model: comboxArray
        anchors.left: titleItem.right
        anchors.leftMargin: 10
        anchors.right: root.right
        anchors.top: root.top
        anchors.bottom: root.bottom

        onActivated:index=>
        {
            root.indeActivated(index);
        }

        //委托项
        delegate: ItemDelegate
        {
            id: itemDelegate
            width: control.width-2
            contentItem: Text
            {
                text: control.textRole
                    ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole])
                    : modelData
                color: itemDelegate.hovered?"#000000":"#101010"
                font: control.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle
            {
                color: itemDelegate.hovered?"#AAAAAA":"#BBBBBB"
            }
        }
        //右边箭头
        indicator: Canvas
        {
            id: canvas
            x: control.width - width - control.rightPadding
            y: control.topPadding + (control.availableHeight - height) / 2
            width: 12
            height: 8
            contextType: "2d"

            Connections
            {
                target: control
                function onPressedChanged() { canvas.requestPaint(); }
            }
            //点击颜色
            onPaint:
            {
                context.reset();
                context.moveTo(0, 0);
                context.lineTo(width, 0);
                context.lineTo(width / 2, height);
                context.closePath();
                context.fillStyle = control.pressed ? "#969696" : "#696969"
                context.fill();
            }
        }
        //内容
        contentItem: Text
        {
            leftPadding: 0
            rightPadding: control.indicator.width + control.spacing

            text: control.displayText
            font: control.font
            color: control.pressed ? "#000000" : "#101010"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        //背景
        background: Rectangle
        {
            color: "#EEEEEE"
            width: control.width
            height: control.height
            border.color: control.hovered ? "#666666":"#9F9F9F"
            border.width: control.visualFocus ? 2 : 1
            radius: 3
        }

    }
}
