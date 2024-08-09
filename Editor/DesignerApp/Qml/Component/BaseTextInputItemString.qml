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
    property  int textSize:14
    property  color textColor:"#000000"
    signal renameSucceed(string newName);

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
        font.pixelSize: textSize
        text: root.lableName
        color: textColor
    }
    TextInput
    {
        id: textEdit
        color: textColor
        anchors.left: textnamea.right
        anchors.leftMargin: 5
        anchors.right: textdown.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        focus: true
        selectByMouse: true
        font.pixelSize: textSize
        verticalAlignment: TextEdit.AlignVCenter
        horizontalAlignment: TextEdit.AlignHCenter

        text: root.displayName

        onEditingFinished:
        {
            root.renameSucceed(textEdit.text);
            root.destroy();
        }
    }
    Text {
        id: textdown
        color: textColor
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
        font.pixelSize: textSize
        text: root.downName
    }
}

