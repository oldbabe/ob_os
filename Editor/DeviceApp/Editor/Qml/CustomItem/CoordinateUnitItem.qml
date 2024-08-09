import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root

    implicitHeight: 40
    implicitWidth: 400

    property string titleText: ""

    signal unitChanged(int xIndex,int yIndex,int zIndex);

    function setUnits(xUnit,yUnit,zUnit)
    {
        if(xUnit === 1)
            xUnitComboBox.currentIndex = 0;
        else if(xUnit === 10)
            xUnitComboBox.currentIndex = 1;
        else if(xUnit === 100)
            xUnitComboBox.currentIndex = 2;

        if(yUnit === 1)
            yUnitComboBox.currentIndex = 0;
        else if(yUnit === 10)
            yUnitComboBox.currentIndex = 1;
        else if(yUnit === 100)
            yUnitComboBox.currentIndex = 2;

        if(zUnit === 1)
            zUnitComboBox.currentIndex = 0;
        else if(zUnit === 10)
            zUnitComboBox.currentIndex = 1;
        else if(xUnit === 100)
            zUnitComboBox.currentIndex = 2;
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
        id: xUnitItem
        anchors.verticalCenter: label.verticalCenter
        anchors.left: label.right
        anchors.leftMargin: 10
        spacing: 12
        topPadding: 5

        Label
        {
            text: "X";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
        ComboBox
        {
            id: xUnitComboBox
            width: 80
            height: 30
            model:["毫米","厘米","米"]
            contentItem: Text
            {
                leftPadding: 0

                text: xUnitComboBox.displayText
                font: xUnitComboBox.font
                color: xUnitComboBox.pressed ? "#f1f1f1" : "#ffffff"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "red"
            }

            onActivated: (value)=> {root.unitChanged(value,yUnitComboBox.currentIndex,zUnitComboBox.currentIndex);}
        }
    }
    Row
    {
        id: yUnitItem
        anchors.verticalCenter: xUnitItem.verticalCenter
        anchors.left: xUnitItem.right
        anchors.leftMargin: 10
        spacing: 12
        topPadding: 5

        Label
        {
            text: "Y";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
        ComboBox
        {
            id: yUnitComboBox
            width: 80
            height: 30
            model:["毫米","厘米","米"]
            contentItem: Text
            {
                leftPadding: 0

                text: yUnitComboBox.displayText
                font: yUnitComboBox.font
                color: yUnitComboBox.pressed ? "#f1f1f1" : "#ffffff"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "green"
            }
            onActivated: (value)=> {root.unitChanged(xUnitComboBox.currentIndex,value,zUnitComboBox.currentIndex);}
        }
    }

    Row
    {
        id: zUnitItem
        anchors.verticalCenter: yUnitItem.verticalCenter
        anchors.left: yUnitItem.right
        anchors.leftMargin: 10
        spacing: 12
        topPadding: 5

        Label
        {
            text: "Z";
            color: "#F1F1F1";
            height: 30
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
        }
        ComboBox
        {
            id: zUnitComboBox
            width: 80
            height: 30
            model:["毫米","厘米","米"]

            contentItem: Text
            {
                leftPadding: 0

                text: zUnitComboBox.displayText
                font: zUnitComboBox.font
                color: zUnitComboBox.pressed ? "#f1f1f1" : "#ffffff"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: "#202020"
                radius: 4
                border.width: 1
                border.color: "blue"
            }
            onActivated: (value)=> {root.unitChanged(xUnitComboBox.currentIndex,yUnitComboBox.currentIndex,value);}
        }
    }
}
