import QtQuick 6.2
import JMoco 1.0

Rectangle
{
    id: root
    radius:5
    color: "#c0c0c0"

    property string displayName: ""
    property string lableName: ""
    property string downName: ""
    property int maxCount : 7200
    property int minCount : 0
    property bool wheelAbled: false
    property double whellRated: 1
    signal renameSucceed(double newName);

    Component.onCompleted:
    {
        textEdit.selectAll();
//        textEdit.focus = true;
        textEdit.forceActiveFocus(Qt.MouseFocusReason);
    }

    Text {
        id: textnamea
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 5
        font.pixelSize: 14
        text: root.lableName
    }
    TextInput
    {
        id: textEdit
        anchors.left: textnamea.right
        anchors.right: textdown.left
        anchors.verticalCenter: parent.verticalCenter
        text: root.displayName
        font.pixelSize: 14
        focus: true
        selectByMouse: true
        validator:DoubleValidator{}
        verticalAlignment: TextEdit.AlignVCenter
        horizontalAlignment: TextEdit.AlignHCenter

        onEditingFinished:
        {
            if(inputText.text === "")
            {
                inputText.text = "0"
            }
            if(Number(textEdit.text) >= root.maxCount)
            {
                textEdit.text = root.maxCount
            }
            else if(Number(textEdit.text) <= root.minCount)
            {
                textEdit.text = root.minCount
            }
            else
            {
                textEdit.text = Number(textEdit.text)
            }
            root.renameSucceed(textEdit.text);
            root.destroy();
        }
    }
    Text {
        id: textdown
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
        font.pixelSize: 14
        text: root.downName
    }
    MouseArea
    {
        anchors.fill: parent
        visible: wheelAbled
        onWheel: (wheel)=>
        {
            textEdit.text = Number(textEdit.text) + Number(wheel.angleDelta.y*whellRated/120)
        }
    }
}
