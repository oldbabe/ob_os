import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root

    implicitHeight: 40
    implicitWidth: 400

    property string titleText: ""

    signal valueChanged(int xIndex,int yIndex,int zIndex);

    function setTransForm(x,y,z)
    {
        xComboBox.currentIndex = x;
        yComboBox.currentIndex = y;
        zComboBox.currentIndex = z;
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
        id: xItem
        anchors.verticalCenter: label.verticalCenter
        anchors.left: label.right
        anchors.leftMargin: 10
        topPadding: 5

        Label
        {
            text: "X=>";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
        ComboBox
        {
            id: xComboBox
            width: 75
            height: 30
            model:["X","Y","Z","-X","-Y","-Z"]
            contentItem: Text
            {
                leftPadding: 0

                text: xComboBox.displayText
                font: xComboBox.font
                color: xComboBox.pressed ? "#f1f1f1" : "#ffffff"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "red"
            }
            onActivated: (value)=> {root.valueChanged(value,yComboBox.currentIndex,zComboBox.currentIndex);}
        }
    }
    Row
    {
        id: yItem
        anchors.verticalCenter: xItem.verticalCenter
        anchors.left: xItem.right
        anchors.leftMargin: 10
        topPadding: 5

        Label
        {
            text: "Y=>";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
        ComboBox
        {
            id: yComboBox
            width: 75
            height: 30
            model:["X","Y","Z","-X","-Y","-Z"]
            contentItem: Text
            {
                leftPadding: 0

                text: yComboBox.displayText
                font: yComboBox.font
                color: yComboBox.pressed ? "#f1f1f1" : "#ffffff"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "green"
            }
            onActivated: (value)=> {root.valueChanged(xComboBox.currentIndex,value,zComboBox.currentIndex);}
        }
    }

    Row
    {
        id: zItem
        anchors.verticalCenter: yItem.verticalCenter
        anchors.left: yItem.right
        anchors.leftMargin: 10
        topPadding: 5

        Label
        {
            text: "Z=>";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
        ComboBox
        {
            id: zComboBox
            width: 75
            height: 30
            model:["X","Y","Z","-X","-Y","-Z"]

            contentItem: Text
            {
                leftPadding: 0

                text: zComboBox.displayText
                font: zComboBox.font
                color: zComboBox.pressed ? "#f1f1f1" : "#ffffff"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "blue"
            }
            onActivated: (value)=> {root.valueChanged(xComboBox.currentIndex,yComboBox.currentIndex,value);}
        }
    }
}
