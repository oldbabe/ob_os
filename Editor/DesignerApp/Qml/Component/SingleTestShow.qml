import QtQuick

Row
{
    id:root
    height: 30
    width: 200
    spacing: 10

    property string titleText : "Title"
    property alias textShowItem : textShow

    function setShowText(text)
    {
        textShow.text = text;
    }

    Item
    {
        id: titleItem
        width: mText.width+10
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
        width: parent.width-titleItem.width-parent.spacing
        height: parent.height
        radius: 5
        color: "#fafafa"
        border.width: 1
        border.color: "#888888"
        Text
        {
            id:textShow
            leftPadding: 5
            verticalAlignment: TextEdit.AlignVCenter
            anchors.fill: parent
        }
    }
}
