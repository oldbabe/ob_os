import QtQuick 6.2
import QtQuick.Controls 6.2
// 一个数值Item
Rectangle
{
    id: root
    radius: 2
    color: "#262626"
    implicitHeight: 22
    implicitWidth: 100

    //悬浮是否显示文字
    property bool entered: false
    //标题文本
    property string titleText: ""
    //后缀文本
    property string lastText: ""
    //内容文本
    property string valueText: ""
    //悬浮文本
    property string enterText:""
    //最大值

    signal textEditFinished(string text)

    function setValue(value)
    {
        inputText.text = value;
    }

    Item
    {
        width: 20
        height: 22
        visible: titleText == ""?false:true
        Label
        {
            color:root.enabled ? "#D7D7D7" : "#666666"
            text: titleText
            font.pixelSize: 14
            anchors.centerIn: parent
        }
    }

    Text
    {
        id: inputText
        width: parent.width-20
        x:titleText == ""?5:25
//        y:0
        color:root.enabled ? "#D7D7D7" : "#666666"
        text: valueText
        font.pixelSize: 14
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: TextEdit.AlignVCenter
        horizontalAlignment: TextEdit.AlignHCenter
    }
    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true
        onDoubleClicked:
        {
            const component = Qt.createComponent("BaseTextInputItemString.qml");
            if (component.status === Component.Ready)
            {
                var item = component.createObject(root,
                                       { width: root.width,
                                         height: root.height,
                                         displayName: inputText.text,
                                         lableName:root.titleText,
                                         downName:root.lastText,
                                       });
                item.renameSucceed.connect(root.textEditFinished);
            }
        }
        onEntered: root.entered = true;
        onExited: root.entered = false;

        ToolTip
        {
            id:conToolTip
            visible: entered
            text: enterText
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

