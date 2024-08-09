import QtQuick 6.2
import QtQuick.Controls 6.2

Control
{
    id: control
    padding:4
    implicitHeight: 30
    implicitWidth: 30

    //圆角
    property int radius: 2
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
    //显示文本颜色
    property color showTextColor: "#F2F2F2"
    //显示文本大写
    property int showTextSize: 12
    //按钮是否可以被选中
    property bool checkable: false
    //选中是否选中
    property bool checked: false
    //-选中配色
    property color norCheckColor: "#148CBE"
    //-鼠标悬浮选中配色
    property color hoverCheckColor: "#169BD5"
    //-鼠标点击选中配色
    property color pressCheckColor: "#148CBE"
    //-边框宽度
    property int borderWidth: 1
    //-边框宽度
    property color borderColor: "#464646"
    //-icon 旋转
    property bool animationEnable: false

    //信号
    signal buttonEntered();
    signal buttonClicked();
    signal buttonPressed();
    signal buttonRelease();
    signal buttonCanceled();
    signal buttonPressAndHold();

    //选中状态改变
    onCheckedChanged:
    {
        if(checkable && checked)
        {
            backRect.color = ctrlArea.containsPress ? pressCheckColor : (ctrlArea.containsMouse ? hoverCheckColor : norCheckColor);
        }
        else if(checkable && !checked)
        {
            backRect.color = ctrlArea.containsPress ? pressColor:(ctrlArea.containsMouse ? hoverColor : norColor);
        }
    }

    background: Rectangle
    {
        id: backRect
        width:control.width
        height:control.height
        radius:control.radius
        color: ctrlArea.containsPress?control.pressColor:(ctrlArea.containsMouse?control.hoverColor:control.norColor)
        border.color: borderColor
        border.width: borderWidth
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
            NumberAnimation
            {
                running: animationEnable
                loops: Animation.Infinite
                target: btn_icon
                from: 0
                to: 360
                property: "rotation"
                duration: 2000
                onStopped:
                {
                    btn_icon.rotation = 0;
                }
            }
        }

        Text
        {
            anchors.centerIn: parent
            text: control.showText
            font.pixelSize: control.showTextSize
            color: control.showTextColor
        }
    }
    MouseArea
    {
        id:ctrlArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked:buttonClicked();
        onEntered:buttonEntered();
        onPressed:buttonPressed();
        onReleased:buttonRelease();
        onCanceled:buttonCanceled();
        onPressAndHold: buttonPressAndHold();
    }
}
