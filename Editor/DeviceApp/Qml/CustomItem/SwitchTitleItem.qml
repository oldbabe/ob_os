import QtQuick 6.2
import QtQuick.Controls 6.2

Item
{
    id: root
    implicitHeight: 40
    implicitWidth: 400

    property bool switchState: false
    property string titleText: ""

    function setSwitchState(state)
    {
        switchItem.checked = state;
    }

    signal toSwitchState();

    Label
    {
        id:label
        width: 60
        text: titleText;
        color: "#F1F1F1";
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
    }
    Switch
    {
        id: switchItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: label.right
        anchors.leftMargin: 10
        onReleased:toSwitchState();

        onPositionChanged:
        {
            if(position <= 0.5)
                switchState = false;
            else
                switchState = true;
        }
    }
}
