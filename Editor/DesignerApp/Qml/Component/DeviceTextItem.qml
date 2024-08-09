import QtQuick 6.2
import QtQuick.Controls 6.2
import "../Component"

//单个数值的Item (可修改)
BackGroundItem
{
    id: root
    height: 70

    //标签文本
    property string tagText: "tag"
    //标题文本
    property string titleText: "G"
    //内容文本
    property string showText:""
    //悬浮文本
    property string entetext:"输入范围0-7200"
    //模式
    property int valueModel: 0
    //刷新按钮
    signal butttonClick();
    //模式修改
    signal modelClick(int model);
    signal editFinished(int textdata);

    state: "photo"
    states: [
        State {
            name: "video"
            PropertyChanges {
                target: root; height:70
            }
            PropertyChanges {
                target: upItem; anchors.bottom: parent.verticalCenter ;anchors.topMargin: 15
            }
            PropertyChanges {
                target: model4; visible:true
            }
            PropertyChanges {
                target: model5; visible:true
            }
            PropertyChanges {
                target: downItem; visible:true
            }
        },
        State {
            name: "photo"
            PropertyChanges {
                target: root; height:30
            }
            PropertyChanges {
                target: upItem; anchors.bottom: parent.bottom;anchors.topMargin: 2
            }
            PropertyChanges {
                target: model4; visible:false
            }
            PropertyChanges {
                target: model5; visible:false
            }
            PropertyChanges {
                target: downItem; visible:false
            }
        }
    ]
    //设置值
   function setValue(value)
   {
       dataItem.valueText = value;
   }

    //tag 标签
    Item
    {
        anchors.right: root.lineRect.left
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.verticalCenter: parent.verticalCenter
        Label
        {
            font.pixelSize: 12
            color:"#D7D7D7"
            text: root.tagText
            anchors.centerIn: parent
        }
    }
    //上item
    Item
    {
        id:upItem
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.bottom: parent.verticalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 15

        BaseTextItem
        {
            id: dataItem
            implicitWidth: 60
            titleText: root.titleText
            enterText: entetext
            valueText: showText
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            onTextEditFinished:(textData) =>
            {
                root.editFinished(textData);
            }
        }

        //刷新按钮
        ToolButton
        {
            id: updateBt
            width: 20
            height: 20
            icon: "qrc:/Image/icon_data_refresh.png"
            anchors.left: dataItem.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            onButtonClicked: root.butttonClick();
        }
        ToolButtonNoClick
        {
            id: model4
            width: 60
            height: 20
            entered: false
            enterText: "手动时间记录"
            showText: "时间记录"
            norCheckColor: "#CCCC44"
            hoverCheckColor: "#DDDD55"
            showCheckColor: "#202020"
            checkable: true
            checked: (checkable && root.valueModel === 4)? true : false
            anchors.left: updateBt.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            onButtonEntered: model4.entered = true;
            onButtonExited: model4.entered = false;
            onButtonClicked: root.modelClick(4);
        }
        ToolButtonNoClick
        {
            id: model5
            width: 60
            height: 20
            entered: false
            enterText: "自动时间回看"
            showText: "时间回看"
            norCheckColor: "#22BB66"
            hoverCheckColor: "#33DC77"
            showCheckColor: "#202020"
            checkable: true
            checked: (checkable && root.valueModel === 5)? true : false
            anchors.left: model4.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            onButtonEntered: model5.entered = true;
            onButtonExited: model5.entered = false;
            onButtonClicked: root.modelClick(5);
        }
    }

    //下item
    Item
    {
        id:downItem
        anchors.left: root.lineRect.right
        anchors.leftMargin: 5
        anchors.top: parent.verticalCenter
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Row
        {
            spacing: 5
            anchors.centerIn: parent
            width: parent.width
            height: parent.height

            ToolButtonNoClick
            {
                id: model0
                width: 40
                height: 20
                entered: false
                enterText: "固定值模式"
                showText: "固定"
                norCheckColor: "#6666EE"
                hoverCheckColor: "#8888EE"
                showCheckColor: "#202020"
                checkable: true
                checked: (checkable && root.valueModel === 0)? true : false
                anchors.verticalCenter: parent.verticalCenter
                onButtonEntered: model0.entered = true;
                onButtonExited: model0.entered = false;
                onButtonClicked: root.modelClick(0);
            }
            ToolButtonNoClick
            {
                id: model1
                width: 40
                height: 20
                entered: false
                enterText: "手动遥控模式"
                showText: "手动"
                norCheckColor: "#DDAA55"
                hoverCheckColor: "#EEBB66"
                showCheckColor: "#202020"
                checkable: true
                checked: (checkable && root.valueModel === 1)? true : false
                anchors.verticalCenter: parent.verticalCenter
                onButtonEntered: model1.entered = true;
                onButtonExited: model1.entered = false;
                onButtonClicked: root.modelClick(1);
            }

            ToolButtonNoClick
            {
                id: model2
                width: 60
                height: 20
                entered: false
                enterText: "手动路径记录"
                showText: "路径记录"
                norCheckColor: "#CCCC44"
                hoverCheckColor: "#DDDD55"
                showCheckColor: "#202020"
                checkable: true
                checked: (checkable && root.valueModel === 2)? true : false
                anchors.verticalCenter: parent.verticalCenter
                onButtonEntered: model2.entered = true;
                onButtonExited: model2.entered = false;
                onButtonClicked: root.modelClick(2);
            }
            ToolButtonNoClick
            {
                id: model3
                width: 60
                height: 20
                entered: false
                enterText: "自动路径回看"
                showText: "路径回看"
                norCheckColor: "#22BB66"
                hoverCheckColor: "#33DC77"
                showCheckColor: "#202020"
                checkable: true
                checked: (checkable && root.valueModel === 3)? true : false
                anchors.verticalCenter: parent.verticalCenter
                onButtonEntered: model3.entered = true;
                onButtonExited: model3.entered = false;
                onButtonClicked: root.modelClick(3);
            }

        }
    }
}
