import QtQuick
import QtQuick.Controls

Row
{
    id:root
    height: 30
    width: 200
    spacing: 10

    property bool btFlag: false
    property string titleText : "Title"
    property alias textEditItem : textEdit
    property alias leftButton : subButton
    property alias rightButton : addButton

    function setShowText(text)
    {
        if(!textEdit.cursorVisible)
            textEdit.text = text;
    }

    Item
    {
        id: titleItem
        width: (mText.width+10)>40?(mText.width+10):40
        height: parent.height
        Text
        {
            id: mText
            anchors.centerIn: parent
            text: root.titleText
        }
    }
    Rectangle
    {
        id: rect1
        width: parent.width-titleItem.width-parent.spacing
        height: parent.height
        radius: 5
        color: "#fafafa"
        border.width: 1
        border.color: "#888888"
        TextInput
        {
            id:textEdit
            selectByMouse: true
            leftPadding: 5
            verticalAlignment: TextEdit.AlignVCenter
            anchors.fill: parent
            onCursorVisibleChanged:
            {
               if(cursorVisible)
                   selectAll();
            }

        }
        Row
        {
            anchors.verticalCenter: rect1.verticalCenter
            anchors.right: rect1.right
            anchors.rightMargin: 5
            spacing: 5
            visible: root.btFlag
            Button
            {
                id:subButton
                width: 28
                height: 28
                text: "-"
            }
            Button
            {
                id:addButton
                width: 28
                height: 28
                text: "+"
            }
        }
    }
}
