import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root

    implicitHeight: 40
    implicitWidth: 400

    property string titleText: ""

    signal minValueEditingFinished(string value);
    signal maxValueEditingFinished(string value);

    function setMinValue(value)
    {
        minTextField.text = value
    }
    function setMaxValue(value)
    {
        maxTextField.text = value
    }

    function setFocus(num,flag)
    {
        //min
        if(num === 0)
            minTextField.focus = flag;
        //max
        else if(num === 1)
            maxTextField.focus = flag;
    }

    Label
    {
        id:label
        width: 60
        text: titleText;
        color: "#F1F1F1";
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
    }

    Row
    {
        id: minItem
        anchors.verticalCenter: label.verticalCenter
        anchors.left: label.right
        anchors.leftMargin: 10
        spacing: 5
        topPadding: 5

        Label
        {
            text: "最小值";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
        }
        TextField
        {
            id: minTextField
            width: 100
            height: 30

            color: "#f1f1f1"
            selectByMouse: true
            validator: IntValidator{bottom: 0}
            verticalAlignment: TextInput.AlignVCenter

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "red"
            }
            onEditingFinished: root.minValueEditingFinished(text);
        }
    }


    Row
    {
        id: maxItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: minItem.right
        anchors.leftMargin: 10
        spacing: 5
        topPadding: 5

        Label
        {
            text: "最大值";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
        }
        TextField
        {
            id: maxTextField
            width: 100
            height: 30

            color: "#f1f1f1"
            selectByMouse: true
            validator: IntValidator{bottom: 0}
            verticalAlignment: TextInput.AlignVCenter

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "green"
            }
            onEditingFinished: root.maxValueEditingFinished(text);
        }
    }
}
