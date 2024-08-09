import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root

    implicitHeight: 40
    implicitWidth: 400

    property alias xTextField : xField
    property alias yTextField : yField
    property alias zTextField : zField
    property string titleText: ""
    property string suffix: ""

    signal valueChanged(string value1,string value2,string value3);


    function setValues(value1,value2,value3)
    {
        xField.text = value1;
        yField.text = value2;
        zField.text = value3;
    }
    function setVlaue(num,value)
    {
        //x
        if(num === 0)
            xField.text = value;
        //y
        else if(num === 1)
            yField.text = value;
        //z
        else if(num === 2)
            zField.text = value;
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
    TextField
    {
        id:xField
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: label.right
        anchors.leftMargin: 10
        width: 100
        height: 30

        color: "#f1f1f1"
        selectByMouse: true
        rightPadding:xSuffixText.width+2
        validator: DoubleValidator{}
        verticalAlignment: TextInput.AlignVCenter

        property string oldName: ""

        background: Rectangle {
            color: "#202020"
            radius: 4
            border.width: 1
            border.color: "red"
            Text {
                id:xSuffixText
                text: root.suffix
                color: "#f1f1f1"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 3
            }
        }
        onPressed: {oldName = text;}
        onEditingFinished:
        {
            if(focus === false && oldName !== text)
            {
                root.valueChanged(xField.text,yField.text,zField.text);
                text=Number(text);
            }
        }
        onAccepted:
        {
            if(oldName !== text)
            {
                root.valueChanged(xField.text,yField.text,zField.text);
                text=Number(text);
                oldName = text;
                focus=false;
            }
        }
    }
    TextField
    {
        id:yField
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: xField.right
        anchors.leftMargin: 10
        width: 100
        height: 30

        color: "#f1f1f1"
        selectByMouse: true
        rightPadding:ySuffixText.width+2
        validator: DoubleValidator{}
        verticalAlignment: TextInput.AlignVCenter

        property string oldName: ""

        background: Rectangle {
            color: "#202020"
            radius: 4
            border.width: 1
            border.color: "green"
            Text {
                id:ySuffixText
                text: root.suffix
                color: "#f1f1f1"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 3
            }
        }
        onPressed: {oldName = text;}
        onEditingFinished:
        {
            if(focus === false && oldName !== text)
            {
                root.valueChanged(xField.text,yField.text,zField.text);
                text=Number(text);
            }
        }
        onAccepted:
        {
            if(oldName !== text)
            {
                root.valueChanged(xField.text,yField.text,zField.text);
                text=Number(text);
                oldName = text;
                focus=false;
            }
        }
    }
    TextField
    {
        id:zField
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: yField.right
        anchors.leftMargin: 10
        width: 100
        height: 30

        color: "#f1f1f1"
        selectByMouse: true
        rightPadding:zSuffixText.width+2
        validator: DoubleValidator{}
        verticalAlignment: TextInput.AlignVCenter

        property string oldName: ""

        background: Rectangle {
            color: "#202020"
            radius: 4
            border.width: 1
            border.color: "blue"
            Text {
                id:zSuffixText
                text: root.suffix
                color: "#f1f1f1"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 3
            }
        }
        onPressed: {oldName = text;}
        onEditingFinished:
        {
            if(focus === false && oldName !== text)
            {
                root.valueChanged(xField.text,yField.text,zField.text);
                text=Number(text);
            }
        }
        onAccepted:
        {
            if(oldName !== text)
            {
                root.valueChanged(xField.text,yField.text,zField.text);
                text=Number(text);
                oldName = text;
                focus=false;
            }
        }
    }
}
