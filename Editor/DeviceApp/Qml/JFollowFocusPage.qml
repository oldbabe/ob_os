import QtQuick 6.2
import QtQuick.Controls 6.2

import JMoco 1.0
import "./CustomItem"

//相机实时图像
Item
{
    id:root
    signal quitPage();

    Component.onCompleted:
    {
        follwfocusComTypeComBox.updateText();
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: root.focus=true
    }

    //顶部
    Rectangle
    {
        id:topRectangle
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 60
        color: "#363636"
        //退出按钮
        ToolButton
        {
            id:quitButton
            width: 50
            height: 50
            showText: "×"
            showTextSize: 24
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10

            onButtonClicked:root.quitPage();
        }
        //标题
        Text
        {
            id: setTitleText
            font.pixelSize: 14
            color: "#f1f1f1"
            anchors.centerIn: parent
            text: qsTr("跟焦器")
        }
    }
    Rectangle
    {
        id:bottomItem
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topRectangle.bottom
        anchors.bottom: parent.bottom
        color: "#202020"

        DataComnoBox
        {
            id:follwfocusComTypeComBox
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 20

            titleText: "端口号";
            dataComBox.onPressedChanged:
            {
                if(dataComBox.pressed)
                    follwfocusComTypeComBox.updateText();
            }
            dataComBox.onActivated:
            {
                JFollowfocus.portName = dataComBox.currentText;
            }
            function updateText()
            {
                follwfocusComTypeComBox.dataComBox.model = JStudioController.ports();
                var index = follwfocusComTypeComBox.dataComBox.find(JFollowfocus.portName);
                if(index !== -1)
                    follwfocusComTypeComBox.dataComBox.currentIndex = index;
            }
        }
        Button
        {
            id:connectedButton
            anchors.left: follwfocusComTypeComBox.right
            anchors.leftMargin: 10
            anchors.verticalCenter: follwfocusComTypeComBox.verticalCenter
            width: 60
            height: follwfocusComTypeComBox.dataComBox.height
            text: JFollowfocus.connected?"断开":"连接"
            onClicked:
            {
                if(JFollowfocus.connected)
                    JFollowfocus.disconnectDevice();
                else
                    JFollowfocus.connectDevice();
            }
        }
        Button
        {
            anchors.left: connectedButton.right
            anchors.leftMargin: 10
            anchors.verticalCenter: connectedButton.verticalCenter
            width: 60
            height: connectedButton.height
            text: "校准"
            onClicked:JFollowfocus.calibrateDevice();
        }
        DataSlider
        {
            id:focusDataSlider
            titleText: "对焦"
            title.color: JFollowfocus.focusEnable ? "#F1F1F1" : "#666666"
            slider.from: 0
            slider.value: 3600
            slider.to: 7200
            anchors.top: follwfocusComTypeComBox.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            valueText: Number(JFollowfocus.focus)
            slider.onMoved:
            {
                JFollowfocus.focus = Number(slider.value)
            }
        }
        Button
        {
            width: 40
            height: focusDataSlider.height
            anchors.verticalCenter: focusDataSlider.verticalCenter
            anchors.left: focusDataSlider.right
            anchors.leftMargin: 10
            checkable: true
            checked: JFollowfocus.focusEnable
            onClicked: JFollowfocus.focusEnable = !JFollowfocus.focusEnable;
            text: JFollowfocus.focusEnable?"使能":"禁用"
        }

        DataSlider
        {
            id:zoomDataSlider
            titleText: "变焦"
            title.color: JFollowfocus.zoomEnable ? "#F1F1F1" : "#666666"
            slider.from: 0
            slider.value: 3600
            slider.to: 7200
            anchors.top: focusDataSlider.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            valueText: Number(JFollowfocus.zoom)
            slider.onMoved:
            {
                JFollowfocus.zoom = Number(slider.value)
            }
        }
        Button
        {
            width: 40
            height: zoomDataSlider.height
            anchors.verticalCenter: zoomDataSlider.verticalCenter
            anchors.left: zoomDataSlider.right
            anchors.leftMargin: 10
            checkable: true
            checked: JFollowfocus.zoomEnable
            onClicked: JFollowfocus.zoomEnable = !JFollowfocus.zoomEnable;
            text: JFollowfocus.zoomEnable?"使能":"禁用"
        }

        DataSlider
        {
            id:irisDataSlider
            titleText: "光圈"
            title.color: JFollowfocus.irisEnable ? "#F1F1F1" : "#666666"
            slider.from: 0
            slider.value: 3600
            slider.to: 7200
            anchors.top: zoomDataSlider.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            valueText: Number(JFollowfocus.iris)
            slider.onMoved:
            {
                JFollowfocus.iris = Number(slider.value)
            }
        }
        Button
        {
            width: 40
            height: irisDataSlider.height
            anchors.verticalCenter: irisDataSlider.verticalCenter
            anchors.left: irisDataSlider.right
            anchors.leftMargin: 10
            checkable: true
            checked: JFollowfocus.irisEnable
            onClicked: JFollowfocus.irisEnable = !JFollowfocus.irisEnable;
            text: JFollowfocus.irisEnable?"使能":"禁用"
        }
    }
}
