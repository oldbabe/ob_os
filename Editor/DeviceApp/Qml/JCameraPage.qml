import QtQuick 6.2
import QtMultimedia 6.2
import QtQuick.Controls 6.2
import "./CustomItem"

import JMoco 1.0

Rectangle
{
    id: root
    color: "black"

    implicitHeight: 200
    implicitWidth: 200

    //退出页面
    signal quitPage();

    //鼠标接收
    MouseArea{anchors.fill: parent}

    Item
    {
        id: topToolItem
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        //退出按钮
        ToolButton
        {
            id: quitButton
            width: 40
            height: 40
            showText: "×"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
            onButtonClicked:  root.quitPage();
        }

        Row
        {
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: quitButton.right
            anchors.leftMargin: 10
            ComboBox
            {
                width: 50
                height: valueComboBox.height
                model: ["对焦","变焦","快门操作"]
                onCurrentIndexChanged:
                {
                    if(currentIndex === 0)
                    {
                        width=50
                        valueComboBox.width = 30
                        valueComboBox.model=["1","2","3","4","5","6","7"];
                    }
                    else if(currentIndex === 1)
                    {
                        width=50
                        valueComboBox.width = 30
                        valueComboBox.model=["0","1","2","3","4","5","6","7","8"];
                    }
                    else if(currentIndex === 2)
                    {
                        width=70
                        valueComboBox.width = 100
                        valueComboBox.model=["直接拍摄","(AF)拍摄","半按(按下)","半按(松开)"];
                    }
                }
            }
            ComboBox
            {
                id:valueComboBox
                width: 30
                height: 25
            }
            Button
            {
                id:leftButton
                width: 30
                height: valueComboBox.height
                text:"-"
                onClicked: JCamera.focusNearFar(-valueComboBox.currentIndex-1)
            }
            Button
            {
                id:rightButton
                width: 30
                height: valueComboBox.height
                text:"+"
                onClicked: JCamera.focusNearFar(valueComboBox.currentIndex+1)
            }
            Button
            {
                id:sendButton
                width: 50
                height: valueComboBox.height
                text:"快门"
                onClicked:JCamera.shooting(valueComboBox.currentIndex)
            }
            Button
            {
                id:recButton
                width: 50
                height: sendButton.height
                text: formatSilmRecordingStatus()
                onClicked:
                {
                    if(JCamera.recordingState.value == "0")
                        JCamera.filmRecording(true);
                    else if(JCamera.recordingState.value == "1")
                        JCamera.filmRecording(false);
                }
                function formatSilmRecordingStatus()
                {
                    if(JCamera.recordingState.value == "0")
                        return "录制";
                    else if(JCamera.recordingState.value == "1")
                        return "停止";
                }
            }
            Button
            {
                id:downloadButton
                width: 50
                height: valueComboBox.height
                text:"下载"
                onClicked: JCamera.downloadEndFile();
            }
        }
    }

    ScrollView
    {
        anchors.left: parent.left
        anchors.right: valuesListView.left
        anchors.top: topToolItem.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        Column
        {
            id:column
            width: parent.width
            spacing: 2
            CameraProperrtyItem
            {
                width: parent.width
                title:"遥控模式"
                key: JCamera.remoteMode.key
                writable: JCamera.remoteMode.writable
                value: JCamera.remoteMode.value
                values: JCamera.remoteMode.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"程序模式"
                key: JCamera.programMode.key
                writable: JCamera.programMode.writable
                value: JCamera.programMode.value
                values: JCamera.programMode.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"录制状态"
                key: JCamera.recordingState.key
                writable: JCamera.recordingState.writable
                value: (JCamera.recordingState.value==="0")?"待机":"录制中..."
                values: JCamera.recordingState.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"光圈"
                key: JCamera.fNumber.key
                writable: JCamera.fNumber.writable
                value: JCamera.fNumber.value
                values: JCamera.fNumber.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"快门速度"
                key: JCamera.shutterSpeed.key
                writable: JCamera.shutterSpeed.writable
                value: JCamera.shutterSpeed.value
                values: JCamera.shutterSpeed.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"ISO"
                key: JCamera.isoSensitivity.key
                writable: JCamera.isoSensitivity.writable
                value: JCamera.isoSensitivity.value
                values: JCamera.isoSensitivity.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"静态影像文件格式"
                key: JCamera.fileType.key
                writable: JCamera.fileType.writable
                value: JCamera.fileType.value
                values: JCamera.fileType.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"jpeg质量"
                key: JCamera.jpegQuality.key
                writable: JCamera.jpegQuality.writable
                value: JCamera.jpegQuality.value
                values: JCamera.jpegQuality.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"白平衡"
                key: JCamera.whiteBalance.key
                writable: JCamera.whiteBalance.writable
                value: JCamera.whiteBalance.value
                values: JCamera.whiteBalance.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"动态影像文件格式"
                key: JCamera.movieFileFormat.key
                writable: JCamera.movieFileFormat.writable
                value: JCamera.movieFileFormat.value
                values: JCamera.movieFileFormat.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"动态影像记录设置"
                key: JCamera.movieRecording.key
                writable: JCamera.movieRecording.writable
                value: JCamera.movieRecording.value
                values: JCamera.movieRecording.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"动态影像记录帧速率"
                key: JCamera.movieRecordingFrameRate.key
                writable: JCamera.movieRecordingFrameRate.writable
                value: JCamera.movieRecordingFrameRate.value
                values: JCamera.movieRecordingFrameRate.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});
                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"RAW文件类型"
                key: JCamera.rawFileCompressionType.key
                writable: JCamera.rawFileCompressionType.writable
                value: JCamera.rawFileCompressionType.value
                values: JCamera.rawFileCompressionType.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"对焦模式"
                key: JCamera.focusMode.key
                writable: JCamera.focusMode.writable
                value: JCamera.focusMode.value
                values: JCamera.focusMode.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"拍摄模式"
                key: JCamera.driveMode.key
                writable: JCamera.driveMode.writable
                value: JCamera.driveMode.value
                values: JCamera.driveMode.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"对焦区域"
                key: JCamera.focusArea.key
                writable: JCamera.focusArea.writable
                value: JCamera.focusArea.value
                values: JCamera.focusArea.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"曝光补偿"
                key: JCamera.exposureBiasAompensation.key
                writable: JCamera.exposureBiasAompensation.writable
                value: JCamera.exposureBiasAompensation.value
                values: JCamera.exposureBiasAompensation.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"闪光补偿"
                key: JCamera.flashAompensation.key
                writable: JCamera.flashAompensation.writable
                value: JCamera.flashAompensation.value
                values: JCamera.flashAompensation.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"剩余电量"
                key: JCamera.batteryRemaining.key
                writable: JCamera.batteryRemaining.writable
                value: JCamera.batteryRemaining.value+"%"
                values: JCamera.batteryRemaining.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"DISP"
                key: JCamera.dispMode.key
                writable: JCamera.dispMode.writable
                value: JCamera.dispMode.value
                values: JCamera.dispMode.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"长宽比"
                key: JCamera.aspectRatio.key
                writable: JCamera.aspectRatio.writable
                value: JCamera.aspectRatio.value
                values: JCamera.aspectRatio.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"对焦操作"
                key: JCamera.nearFar.key
                writable: JCamera.nearFar.writable
                value: JCamera.nearFar.value
                values: JCamera.nearFar.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"变焦模式"
                key: JCamera.zoomSetting.key
                writable: JCamera.zoomSetting.writable
                value: JCamera.zoomSetting.value
                values: JCamera.zoomSetting.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"变焦操作状态"
                key: JCamera.zoomOperationStatus.key
                writable: JCamera.zoomOperationStatus.writable
                value: JCamera.zoomOperationStatus.value
                values: JCamera.zoomOperationStatus.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"变焦范围"
                key: JCamera.zoomRange.key
                writable: JCamera.zoomRange.writable
                value: JCamera.zoomRange.value
                values: JCamera.zoomRange.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"实时取景显示"
                key: JCamera.liveViewDisplayEffect.key
                writable: JCamera.liveViewDisplayEffect.writable
                value: JCamera.liveViewDisplayEffect.value
                values: JCamera.liveViewDisplayEffect.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
            CameraProperrtyItem
            {
                width: parent.width
                title:"实时图像质量"
                key: JCamera.liveViewImageQuality.key
                writable: JCamera.liveViewImageQuality.writable
                value: JCamera.liveViewImageQuality.value
                values: JCamera.liveViewImageQuality.values
                onMousePressed:
                {
                    valuesListView.key = Qt.binding(function(){return key;});
                    valuesListView.value = Qt.binding(function(){return value;});
                    valuesListView.writable = Qt.binding(function(){return writable;});
                    valuesListView.model = Qt.binding(function(){return values;});

                    valuesListView.currentIndex=values.indexOf(value);
                    valuesListView.positionViewAtIndex(valuesListView.currentIndex,ListView.Center);
                }
            }
        }
    }

    ListView
    {
        id:valuesListView
        y:column.y
        x:root.width/2
        spacing: 1
        clip: true
        width: root.width/2
        height: root.height

        property int key: -1
        property int writable: -1
        property string value: ""

        delegate: Rectangle{
            width: ListView.view.width
            height: 40

            property bool checked: (ListView.view.value === modelData) ? true : false

            color: checked ? "#FACD91" : "#303030"
            Text {
                color: parent.checked ? "#202020" :"#f1f1f1"
                anchors.centerIn: parent
                text: modelData
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    if(!checked)
                    {
                        JCamera.setProperty(valuesListView.key,index);
                    }
                }
            }
        }
    }

    Text
    {
        id: downloadDirText
        color: "#f1f1f1"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        text: JCamera.downloadDir
    }
    Text
    {
        color: "#f1f1f1"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: downloadDirText.top
        text: JCamera.downloadFileName
    }
    Text
    {
        color: "#f1f1f1"
        text: JCamera.cameraName
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }
}
