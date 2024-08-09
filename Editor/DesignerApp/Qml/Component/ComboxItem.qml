import QtQuick 6.2
import QtQuick.Controls 6.2

BackGroundItem
{
    id: root

    implicitWidth: 200
    implicitHeight: 30

    //索引
    property int currentIndex: control.currentIndex

    //tag 标签文本
    property string tagText: "空"
    //model array
    property var comboxArray: ["First"]
    property int cobWith:100
    property int cobHeight:22
    //ComboBox 引用
    property alias comboxAlias: control

    signal indexActivated(int index);

    function setValue(value)
    {
        control.currentIndex = value;
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
            color:"#D7D7D7"
            text: root.tagText
            anchors.centerIn: parent
        }
    }

    ComboBox
    {
        id: control
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 12
        model: comboxArray
        onActivated:(index)=>
        {
            root.indexActivated(index);
        }

        //委托项
        delegate: ItemDelegate {
            id: itemDelegate
            width: control.width-2
            contentItem: Text {
                text: control.textRole
                    ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole])
                    : modelData
                color: itemDelegate.hovered?"#D7D7D7":"#F2F2F2"
                font: control.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle
            {
                color: itemDelegate.hovered?"#169BD5":"#363636"
            }
        }
        //右边箭头
        indicator: Canvas {
            id: canvas
            x: control.width - width - control.rightPadding
            y: control.topPadding + (control.availableHeight - height) / 2
            width: 12
            height: 8
            contextType: "2d"

            Connections {
                target: control
                function onPressedChanged() { canvas.requestPaint(); }
            }
            //点击颜色
            onPaint: {
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
        contentItem: Text {
            leftPadding: 0
            rightPadding: control.indicator.width + control.spacing

            text: control.displayText
            font: control.font
            color: control.pressed ? "#F2F2F2" : "#FFFFFF"
            verticalAlignment: TextEdit.AlignVCenter
            horizontalAlignment: TextEdit.AlignHCenter
            elide: Text.ElideRight
        }
        //背景
        background: Rectangle {
            color: "#262626"
            implicitWidth: root.cobWith
            implicitHeight: root.cobHeight
            border.color: control.pressed ? "#696969" : "#494949"
            border.width: control.visualFocus ? 2 : 1
            radius: 2
        }

        popup: Popup {
            y: control.height - 1
            width: control.width
            implicitHeight: contentItem.implicitHeight + 2
            padding: 1
            contentItem: ListView {

                clip: true
                implicitHeight: contentHeight
                model: control.popup.visible ? control.delegateModel : null
                currentIndex: control.highlightedIndex
                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle {
                border.color: "#303030"
                radius: 2
            }
        }
    }

}
