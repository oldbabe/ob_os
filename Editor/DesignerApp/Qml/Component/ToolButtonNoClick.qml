import QtQuick 6.2
import QtQuick.Controls 6.2

Control
{
    id: control
    padding:4
    implicitHeight: 30
    implicitWidth: 30

    //按钮图标
    property string icon: ""
    //-正常配色
    property color norColor: "#202020"
    //-鼠标悬浮正常配色
    property color hoverColor: "#464646"
    //-鼠标点击正常配色
    property color pressColor: "#565656"
    //显示文本
    property string showText: ""
    // 悬浮显示文字
    property string enterText: ""
    //显示文本颜色
    property color showTextColor: "#F2F2F2"
    //显示文本颜色
    property color showCheckColor: "#F2F2F2"
    //显示文本大小
    property int showTextSize: 12
    //按钮是否可以被选中
    property bool checkable: false
    //选中是否选中
    property bool checked: false
    //左键点击
    property bool leftchecked: false
    //-悬浮是否显示文字
    property bool entered: false
    //
    property int backAdius: 3
    //图标透明度
    property real opacityIMG: 1.0
    //-选中配色
    property color norCheckColor: "#666666"
    //-鼠标悬浮选中配色
    property color hoverCheckColor: "#696969"
    //-鼠标点击选中配色
    property color pressCheckColor: "#999999"
    //边框颜色
    property color borderColor: "#464646"

    //信号
    signal buttonEntered();
    signal buttonClicked();
    signal buttonPressed();
    signal buttonRelease();
    signal buttonCanceled();
    signal buttonExited();
    signal buttonLeftClicked();
    signal buttonRightClicked();

    background: Rectangle
    {
        id: backRect
        width:control.width
        height:control.height
        color: {(control.checkable && control.checked)?
                   (ctrlArea.containsPress ? control.pressCheckColor : (ctrlArea.containsMouse ? control.hoverCheckColor : control.norCheckColor)) :
                   ctrlArea.containsPress ? control.pressColor:(ctrlArea.containsMouse ? control.hoverColor : control.norColor)}
        border.color: borderColor
        border.width: 1
        radius:backAdius
    }

    contentItem: Item
    {
        width:control.width
        height:control.height

        Image
        {
            id:btn_icon
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: control.icon.length > 0 ? control.icon : ""
            opacity:opacityIMG
        }

        Text
        {
            anchors.centerIn: parent
            text: control.showText
            font.pixelSize: control.showTextSize
            color: (control.checkable && control.checked)?control.showCheckColor:control.showTextColor
        }
    }
    MouseArea
    {
        id:ctrlArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked:(mouse)=>
        {
            if(mouse.button === Qt.RightButton)
            {
                buttonRightClicked();
            }
            if(mouse.button === Qt.LeftButton)
            {
                buttonLeftClicked();
                leftchecked = !leftchecked;
            }
//            if(checkable)
//            {
//                checked = !checked;
//            }
            buttonClicked();
        }
        onEntered:buttonEntered();
        onExited:buttonExited();
        onPressed:buttonPressed();
        onReleased:buttonRelease();
        onCanceled:buttonCanceled();


        ToolTip
        {
            id:conToolTip
            visible: entered
            text:enterText
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
