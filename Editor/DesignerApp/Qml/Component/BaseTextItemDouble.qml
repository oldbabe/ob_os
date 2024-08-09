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
    property bool enteredAble: true
    property bool entered: false
    //滚轮是否开启
    property bool wheelAble: false
    //滚轮是否倍率
    property double whellRate: 1
    //标题文本
    property string titleText: ""
    //后缀文本
    property string lastText: ""
    //内容文本
    property string valueText: "0.0"
    //悬浮文本
    property string enterText:""
    //最大值
    property int maxNum: 7200
    //最小值
    property int minNum: 0

    signal textEditFinished(double text)

    function setValue(value)
    {
        inputText.text = value;
    }

    Text {
        id: leftText
        color:root.enabled ? "#D7D7D7" : "#666666"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 5
        font.pixelSize: 14
        text: root.titleText
    }
    Text
    {
        id: inputText
        anchors.left: leftText.right
        anchors.right:textdown.left
        color:root.enabled ? "#D7D7D7" : "#666666"
        text: valueText
        font.pixelSize: 14
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: TextEdit.AlignVCenter
        horizontalAlignment: TextEdit.AlignHCenter
    }
    Text {
        id: textdown
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: root.right
        anchors.rightMargin: 5
        font.pixelSize: 14
        color:root.enabled ? "#D7D7D7" : "#666666"
        text: root.lastText
    }

    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true
        onDoubleClicked:
        {
            const component = Qt.createComponent("BaseTextInputItemDouble.qml");
            if (component.status === Component.Ready)
            {
                var item = component.createObject(root,
                                       { width: root.width,
                                         height: root.height,
                                         displayName: inputText.text,
                                         lableName:root.titleText,
                                         downName:root.lastText,
                                         minCount:root.minNum,
                                         maxCount:root.maxNum,
                                         wheelAbled:root.wheelAble,
                                         whellRated:root.whellRate
                                       });
                item.renameSucceed.connect(root.textEditFinished);
            }
        }
        onEntered: root.entered = true;
        onExited: root.entered = false;

        ToolTip
        {
            id:conToolTip
            visible: entered && enteredAble
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

