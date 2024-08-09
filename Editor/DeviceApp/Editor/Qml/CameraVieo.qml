import QtQuick 6.2
import QtQuick.Controls 6.2
import QtMultimedia 6.2
import CppService 1.0

import "./CustomItem"

//相机实时图像
Rectangle
{
    id:root
    color: "#202020"

    property int jxValue: 1
    property bool autoFollowFlag: frameLoader.status == Loader.Ready

    signal quitPage();

    //初始化
    Component.onCompleted:
    {
        updateCamera();
    }

    //更新相机数据
    function updateCamera()
    {
        if(mediaDevices.videoInputs.length === 1)
        {
            camera.cameraDevice= mediaDevices.defaultVideoInput
            camera.start();
        }
        else if(mediaDevices.videoInputs.length === 2)
        {
            camera.cameraDevice= mediaDevices.videoInputs[0];
            camera.start();
        }
        else
        {
            camera.stop();
        }
    }

    //退出按钮
    ToolButton
    {
        id:quitButton
        showText: "×"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        onButtonClicked:root.quitPage();
    }


    Item
    {
        id: fileItem

        state: EditorQml.cameraRotate
        states: [
            State {
                name: "0"
                PropertyChanges {
                    target: fileItem
                    width: parent.width-10
                    height: parent.height-10
                    x:(parent.width-width)/2
                    y:(parent.height-height)/2
                    rotation:0
                }
            },
            State {
                name: "90"
                PropertyChanges {
                    target: fileItem
                    width: parent.height-10
                    height: parent.width-10
                    x:(parent.width-width)/2
                    y:(parent.height-height)/2
                    rotation:90
                }
            },
            State {
                name: "180"
                PropertyChanges {
                    target: fileItem
                    width: parent.width-10
                    height: parent.height-10
                    x:(parent.width-width)/2
                    y:(parent.height-height)/2
                    rotation:180
                }
            },
            State {
                name: "270"
                PropertyChanges {
                    target: fileItem
                    width: parent.height-10
                    height: parent.width-10
                    x:(parent.width-width)/2
                    y:(parent.height-height)/2
                    rotation:270
                }
            }
        ]

        transform:[
            Rotation
            {
                id: rotation
                origin.x: fileItem.width / 2
                origin.y: fileItem.height / 2
                axis.x: root.jxValue
                axis.y: 0
                axis.z: 0
                angle: 180
            }
        ]

        MediaDevices
        {
            id: mediaDevices
            onDefaultVideoInputChanged:
            {
                updateCamera();
            }
        }

        CaptureSession
        {
            camera: Camera
            {
                id:camera
            }
            imageCapture: ImageCapture
            {
                id: imageCapture
            }
            videoOutput: videoOutput
        }

        VideoOutput
        {
            id: videoOutput
            anchors.fill: parent
        }
    }

    Loader
    {
        id:frameLoader
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
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
        showText: fileItem.state+"°"
        onButtonClicked:
        {
            var angle = Number(EditorQml.cameraRotate);
            var newAngle = angle + 90;
            if(newAngle > 270)
                newAngle  = 0;
            EditorQml.cameraRotate = newAngle.toString();
        }
    }
    //镜像按钮
    ToolButton
    {
        id:jxButton
        width: 50
        height: 50
        opacity: 0.7
        checkable: true
        checked: root.jxValue
        anchors.verticalCenter: rotationButton.verticalCenter
        anchors.left: rotationButton.right
        anchors.leftMargin: 10
        showText: "镜像"
        onButtonClicked:
        {
            if(root.jxValue == 1)
                root.jxValue = 0;
            else
                root.jxValue = 1;
        }
    }
    //播放按钮
//    ToolButton
//    {
//        id:playButton
//        width: 50
//        height: 50
//        opacity: 0.5
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.bottom:  parent.bottom
//        anchors.bottomMargin:  10
//        showText: camera.active?"暂停":"播放"
//        onButtonClicked:
//        {
//            if(camera.active)
//            {
//                camera.stop();
//            }
//            else if(!camera.active && mediaDevices.videoInputs.length > 0)
//            {
//                camera.start();
//            }
//        }
//    }

    //输入源按钮
//    ToolButton
//    {
//        id:camerasButton
//        width: 50
//        height: 50
//        opacity: 0.5
//        anchors.verticalCenter: playButton.verticalCenter
//        anchors.right: parent.right
//        anchors.rightMargin: 10
//        showText: "输入源"
//        Menu
//        {
//            id:cameraMenu
//            y:-height

//            //切换视频输入要
//            function clearItem()
//            {
//                for(var i = 0; i < cameraMenu.count; i++)
//                {
//                    cameraMenu.removeItem(cameraMenu.itemAt(i));
//                }
//            }

//            //切换视频输入要
//            function dataIndexChanged(value,index)
//            {
//                if(mediaDevices.defaultVideoInput !== mediaDevices.videoInputs[index])
//                {
//                    mediaDevices.defaultVideoInput = mediaDevices.videoInputs[index];
//                }
//            }
//        }
//        onButtonClicked:
//        {
//            cameraMenu.clearItem();
//            var cameraSize = mediaDevices.videoInputs.length;
//            if(cameraSize)
//            {
//                for(var i = 0; i < mediaDevices.videoInputs.length; i++)
//                {
//                    var component = Qt.createComponent("qrc:/Qml/CustomItem/MyMenuItem.qml");
//                    if (component.status === Component.Ready)
//                    {
//                        var obje = component.createObject(cameraMenu,{"text":mediaDevices.videoInputs[i].description,
//                                                          "dataIndex":i});
//                        obje.indexChanged.connect(cameraMenu.dataIndexChanged); //信号实现
//                        cameraMenu.addAction(obje)
//                    }
//                }
//                cameraMenu.open();
//            }
//        }
//    }
}
