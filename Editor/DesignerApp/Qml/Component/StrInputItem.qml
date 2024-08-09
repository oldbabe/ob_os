import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id:root

    implicitWidth:120
    implicitHeight: textField.height


    property int titleWidth: 100

    property string titleText: "标题"
    property string valueText: ""
    //    property int maxCount: 60
    //    property int minCount: 1
    property alias inputItem: textField

    signal textEditFinished(string text)

    function setValue(value)
    {
        textField.text = value;
    }
    Item
    {
        id: textItem
        width: titleWidth
        height: parent.height
        Label
        {
            id: label
            text: titleText
            color: "#000000"
            font.pixelSize: 12

            anchors.verticalCenter: textItem.verticalCenter
            anchors.left: textItem.left
        }
    }

    TextField
    {
        id: textField
        color: "#000000"
        font.pixelSize: 12
        text: valueText
        selectByMouse: true

        anchors.verticalCenter: root.verticalCenter
        anchors.left: textItem.right
        anchors.leftMargin: 10
        anchors.right: root.right

        onEditingFinished:
        {
            textField.cursorVisible = false;
            textEditFinished(textField.text);
        }

        background: Rectangle
        {
            width: parent.width
            height: parent.height
            radius: 3
            color: "#FFFFFF"
            border.width: 1
            border.color: textField.focus?"#9F9F9F":(textField.hovered?"#9F9F9F":"#666666")
        }
    }
}




//    signal textEditFinished(string text)



//    Item
//    {
//        anchors.right: root.lineRect.left
//        anchors.left: parent.left
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        Label
//        {
//            font.pixelSize: 10
//            color:"#D7D7D7"
//            text: root.tagText
//            anchors.centerIn: parent
//        }
//    }

//    Rectangle
//    {
//        id: inputRect
//        radius: 2
//        height: 22
//        width: 100
//        color: "#262626"
//        border.color: "#464646"

//        anchors.left: root.lineRect.right
//        anchors.leftMargin: 5
//        anchors.verticalCenter: parent.verticalCenter

//        TextInput
//        {
//            id: inputText
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.leftMargin: 5
//            anchors.right:text.left
//            selectByMouse: true
//            color:"#D7D7D7"
//            validator: IntValidator{bottom: 0;}
//            text: minCount
//            clip: true

//            onEditingFinished:
//            {
//                if(inputText.text === "")
//                {
//                    inputText.text = "0"
//                }

//                if(Number(inputText.text) >= root.maxCount)
//                {
//                    inputText.text = root.maxCount
//                }
//                else if(Number(inputText.text) <= root.minCount)
//                {
//                    inputText.text = root.minCount
//                }
//                else
//                {
//                    inputText.text = Number(inputText.text)
//                }

//                inputText.cursorVisible = false;
//                textEditFinished(inputText.text)
//            }
//        }
//        Text
//        {
//            id: text
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.right: parent.right
//            anchors.rightMargin: 5
//            color:"#D7D7D7"
//            text: suffixText
//        }
//    }
//}
