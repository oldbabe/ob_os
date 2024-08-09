import QtQuick 6.2
import QtQuick.Controls 6.2


Item
{
    id:root
    implicitWidth: 150
    implicitHeight: 40

    property string titleText: "标题"
    property int titleWidth: 100
    property int currectindex: 1

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
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    ButtonGroup
    {
        id:buttonGroup
        buttons: rowBT.children
        onClicked: function(button)
        {
            currectindex = button.index
        }
    }

    Row
    {
        id: rowBT
        spacing: 20
        anchors.left: titleItem.right
        anchors.leftMargin: 5
        anchors.right: root.right
        anchors.top: root.top
        anchors.bottom: root.bottom

        RadioButton
        {
            id: imgRadioButton
            property int index: 1
            checked: true
            text: qsTr("平面")

            indicator: Rectangle {
                implicitWidth: 20
                implicitHeight: 20
                x: imgRadioButton.leftPadding
                radius: 10
                border.color: imgRadioButton.down ? "#000000" : "#363636"

                Rectangle {
                    width: 12
                    height: 12
                    x: 4
                    y: 4
                    radius: 6
                    color:  imgRadioButton.down ? "#00ff00" : "#00aa00"
                    visible: imgRadioButton.checked
                }
            }

            contentItem: Text {
                text: imgRadioButton.text
                font: imgRadioButton.font
                opacity: enabled ? 1.0 : 0.3
                color: imgRadioButton.down ? "#363636" : "#000000"
                verticalAlignment: Text.AlignVCenter
                leftPadding: imgRadioButton.indicator.width + imgRadioButton.spacing
                bottomPadding: 10
            }
        }

        RadioButton
        {
            id: videoRadioButton
            property int index: 2
            text: qsTr("视频")

            indicator: Rectangle {
                implicitWidth: 20
                implicitHeight: 20
                x: videoRadioButton.leftPadding
                radius: 10
                border.color: videoRadioButton.down ? "#000000" : "#363636"

                Rectangle {
                    width: 12
                    height: 12
                    x: 4
                    y: 4
                    radius: 6
                    color: videoRadioButton.down ? "#00ff00" : "#00aa00"
                    visible: videoRadioButton.checked
                }
            }
            contentItem: Text {
                text: videoRadioButton.text
                font: videoRadioButton.font
                opacity: enabled ? 1.0 : 0.3
                color: videoRadioButton.down ? "#363636" : "#000000"
                verticalAlignment: Text.AlignTop
                leftPadding: videoRadioButton.indicator.width + videoRadioButton.spacing
                bottomPadding: 10
            }
        }
    }

}

