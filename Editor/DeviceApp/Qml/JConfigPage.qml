import QtQuick 6.2
import QtQuick.Controls 6.2
import CppService 1.0
import JMoco 1.0
import "./CustomItem"

Rectangle
{
    id:root
    color: "black"

    implicitHeight: 200
    implicitWidth: 200

    //退出页面
    signal quitPage();

    Component.onCompleted:
    {
        studioTypeComBox.dataComBox.currentIndex = JConfig.type
        robotIpDataTextField.dataTextField.text = JConfig.robotAddr
        railIpDataTextField.dataTextField.text = JConfig.railAddr
        railDriveDataTextField.dataTextField.text = JConfig.railDeviceAddr
        turnpateComTypeComBox.dataComBox.currentIndex = turnpateComTypeComBox.dataComBox.indexOfValue(JConfig.turnplatePortName)
    }

    //鼠标接收
    MouseArea{anchors.fill: parent}
    //退出按钮
    ToolButton
    {
        id: quitButton
        showText: "×"
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left:  parent.left
        anchors.leftMargin: 15
        onButtonClicked:  root.quitPage();
    }
    //标题
    Text
    {
        id: setTitleText
        font.pixelSize: 14
        color: "#f1f1f1"
        anchors.verticalCenter: quitButton.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("基本设置")
    }
    DataComnoBox
    {
        id:studioTypeComBox
        anchors.top: setTitleText.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "影棚类型";
        dataComBox.model: ["静物影棚","人像影棚"]
        dataComBox.onActivated:JConfig.type = dataComBox.currentIndex;
    }
    DataTextField
    {
        id:robotIpDataTextField
        anchors.top: studioTypeComBox.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "机械臂IP";
        dataTextField.selectByMouse: true
        dataTextField.validator: RegularExpressionValidator { regularExpression: /((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}/ }
        dataTextField.onEditingFinished:
        {
            dataTextField.focus = false;
            JConfig.robotAddr = dataTextField.text
        }
    }
    DataTextField
    {
        id:railIpDataTextField
        anchors.top: robotIpDataTextField.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "轨道IP(PLC)";
        dataTextField.selectByMouse: true
        dataTextField.validator: RegularExpressionValidator { regularExpression: /((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}/ }
        dataTextField.onEditingFinished:
        {
            dataTextField.focus = false;
            JConfig.railAddr = dataTextField.text
        }
    }
    DataTextField
    {
        id:railDriveDataTextField
        anchors.top: railIpDataTextField.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "轨道IP(驱动)";
        dataTextField.selectByMouse: true
        dataTextField.validator: RegularExpressionValidator { regularExpression: /((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}/ }
        dataTextField.onEditingFinished:
        {
            dataTextField.focus = false;
            JConfig.railDeviceAddr = dataTextField.text
        }
    }
    DataComnoBox
    {
        id:comTypeComBox
        anchors.top: railDriveDataTextField.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "查看端口号";
        dataComBox.onPressedChanged:
        {
            if(dataComBox.pressed)
            {
                comTypeComBox.dataComBox.model = JStudioController.ports();
            }
        }
    }
    DataComnoBox
    {
        id:turnpateComTypeComBox
        anchors.top: comTypeComBox.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "转盘端口号";
        dataComBox.model: ["","COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9","COM10","COM11","COM12","COM13","COM14","COM15","COM16"]
        dataComBox.onActivated: JConfig.turnplatePortName = dataComBox.currentText;
    }
}
