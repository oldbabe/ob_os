import QtQuick 6.2
import QtQuick.Controls 6.2
import QtMultimedia 6.2
import JMoco 1.0

import "./CustomItem"

//相机实时图像
Item
{
    id:root

    signal quitPage();

    //初始化
    Component.onCompleted:
    {
        cameraComboBox.model = JCameraDevice.cameraList();
        JCameraDevice.videoSink = videoOutput.videoSink;
        if(cameraComboBox.count > 0)
        {
            JCameraDevice.play(0);
        }
    }

    Component.onDestruction:
    {
        JCameraDevice.videoSink = null;
        JCameraDevice.stop();
    }

    Rectangle
    {
        color: "#101010"
        anchors.fill: parent
        MouseArea
        {
            anchors.fill: parent
            onClicked: root.focus=true
        }
    }

    Column
    {
        anchors.fill: parent
        Item {
            id: topItem
            width: root.width
            height: 50
            //退出按钮
            ToolButton
            {
                id:quitButton
                showText: "×"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                onButtonClicked:root.quitPage();
            }
            ComboBox
            {
                id: cameraComboBox
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: quitButton.right
                anchors.leftMargin: 10
                height: quitButton.height
                background: Rectangle {
                    width: cameraComboBox.width
                    height: cameraComboBox.height
                    color: "#363636"
                }
                contentItem: Label {
                    text: cameraComboBox.displayText
                    font: cameraComboBox.font
                    color: "#f1f1f1"
                    verticalAlignment: Text.AlignVCenter
                }

                onPressedChanged:
                {
                    if(!pressed)
                        return;

                    cameraComboBox.model = JCameraDevice.cameraList();
                }

                onActivated: (index)=>{ JCameraDevice.play(index); }
            }
            Row
            {
                spacing: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: cameraComboBox.right
                anchors.leftMargin: 10
                ToolButton
                {
                    opacity: 0.7
                    showText: Number(JCameraDevice.rotateFlag)*90+"°"
                    onButtonClicked:
                    {
                        if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_0)
                            JCameraDevice.rotateFlag = JCameraDevice.RotateFlag_90;
                        else if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_90)
                            JCameraDevice.rotateFlag = JCameraDevice.RotateFlag_180;
                        else if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_180)
                            JCameraDevice.rotateFlag = JCameraDevice.RotateFlag_270;
                        else if(JCameraDevice.rotateFlag === JCameraDevice.RotateFlag_270)
                            JCameraDevice.rotateFlag = JCameraDevice.RotateFlag_0;
                    }
                }
                ToolButton
                {
                    width: 70
                    opacity: 0.7
                    checkable: true
                    checked: JCameraDevice.horizontalMirrored
                    showText: "水平镜像"
                    onButtonClicked:JCameraDevice.horizontalMirrored = !JCameraDevice.horizontalMirrored;
                }
                ToolButton
                {
                    width: 70
                    opacity: 0.7
                    checkable: true
                    checked: JCameraDevice.verticalMirrored
                    showText: "垂直镜像"
                    onButtonClicked:JCameraDevice.verticalMirrored = !JCameraDevice.verticalMirrored;
                }
                ToolButton
                {
                    width: 70
                    opacity: 0.7

                    Component.onCompleted:
                    {
                        showText = Qt.binding(function(){
                            if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Close)
                                return "网格关闭";
                            else if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Trisector)
                                return "三等分";
                            else if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Square)
                                return "方形";
                            else if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Diagonal)
                                return "方向+对角";
                            else
                                return "其它"
                        });
                    }

                    onButtonClicked:
                    {
                        if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Close)
                            JCameraDevice.gridFlag = JCameraDevice.GridFlags_Trisector;
                        else if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Trisector)
                            JCameraDevice.gridFlag = JCameraDevice.GridFlags_Square;
                        else if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Square)
                            JCameraDevice.gridFlag = JCameraDevice.GridFlags_Diagonal;
                        else if(JCameraDevice.gridFlag === JCameraDevice.GridFlags_Diagonal)
                            JCameraDevice.gridFlag = JCameraDevice.GridFlags_Close;
                    }
                }
            }
        }
        Item
        {
            id: bottomItem
            width: root.width
            height: root.height-50
            VideoOutput
            {
                id: videoOutput
                anchors.fill: parent
            }
        }
    }
}
