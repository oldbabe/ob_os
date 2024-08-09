import QtQuick 6.2
import QtQuick.Controls 6.2

Switch {
    id: root
    display:AbstractButton.IconOnly
    indicator: Rectangle {
        width: 40
        height:20
        radius: height / 2
        color: root.checked ? "#0ACF97" : "#EF5A67"
        border.width: 2
        border.color: root.checked ? "#0ACA67" : "#DA1A27"

        Rectangle {
            x: root.checked ? parent.width - width - 2 : 2
            width: parent.height - 2
            height: width
            radius: width / 2
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            border.color: "#D5D5D5"

            Behavior on x {
                NumberAnimation { duration: 200 }
            }
        }
    }
    background: MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered:conToolTip.visible = true;
        onExited:conToolTip.visible = false;
        propagateComposedEvents: true
        ToolTip
        {
            id:conToolTip
            visible: false
            text:"是否使用下载地址"
            delay: 300

            contentItem: Text{
                text:conToolTip.text
                font:conToolTip.font
                color:"#202020"
            }
            background: Rectangle{border.color: "#EEEEEE"}
        }
    }
}
