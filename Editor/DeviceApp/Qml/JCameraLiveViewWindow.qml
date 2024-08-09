import QtQuick 6.2
import JMoco 1.0
import QtMultimedia 6.2

import "./CustomItem"

Window
{
    id:root
    width: 1024
    height: 680
    title: "实时图像"

    Component.onCompleted:
    {
        JCamera.liveViewEnable = true;
        JCamera.videoSink = videoOutput.videoSink
    }

    Connections
    {
        target: root
        function onClosing(event)
        {
            JCamera.recEnable = false;
            JCamera.liveViewEnable = false;
            JCamera.videoSink = null;
            event.accepted = true;
        }
    }

    Rectangle
    {
        id: fileItem
        anchors.fill: parent
        color: "#202020"
        VideoOutput
        {
            id: videoOutput
            anchors.fill: parent
        }
        //旋转按钮
        ToolButton
        {
            id:rotationButton
            width: 50
            height: 50
            opacity: 0.7
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            showText: Number(JCamera.rotateAngle)+"°"
            onButtonClicked:
            {
                var angle = JCamera.rotateAngle+90;
                if(angle > 270)
                    angle  = 0;
                JCamera.rotateAngle = angle;
            }
        }

        //跟随按钮
        ToolButton
        {
            id:recButton
            width: 50
            height: 50
            opacity: 0.7
            anchors.verticalCenter: rotationButton.verticalCenter
            anchors.left: rotationButton.right
            anchors.leftMargin: 10
            showText: "跟随"
            checkable: true
            checked: JCamera.recEnable
            onButtonClicked:{
                JCamera.recEnable = !JCamera.recEnable;
            }
        }
    }
}
