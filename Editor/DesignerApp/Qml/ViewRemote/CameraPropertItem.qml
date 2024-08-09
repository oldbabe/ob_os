/*
* 软件名称   BOBS 操作系统
* 版权所有   上海倔老头智能科技有限公司
* 本软件由上海倔老头智能科技有限公司开发并且开源 使用GPL V3（GNU General Public License） 开源协议
* 如收费请告知他人本软件可免费获得并说明收费缘由（如服务费）
* 联系方式
* vx 号    z1273305587
* 电话号   15536506659
* bilibili： 倔老头的会议室  UID: 3546726275221982
* 软件开源地址 https://github.com/oldbabe/ob_os
*
* Software name BOBS Operating system
*
* Copyright (C) 2024  Shanghai OldBaby technology Co., LTD
*
* This program is free software;you can redistribute it and/or modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation;either version 3 of the License, or (at your option) any later version.
*
* If there is a charge, please inform others that the software is available free of charge and explain the reason for the charge (e.g. service fee).
* Contact information
* Open source address https://github.com/oldbabe/ob_os
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import "../Component"
import JMoco 1.0
import "../../JS/ScriptBuffer.js"  as MyScript

Item
{
    id:root
    implicitHeight: tagItem.height + column.height  +1
    implicitWidth: 200
//    property bool myPower: true

    Component.onCompleted:
    {
        tagItem.zoomFlag = true;
    }

    TagItem
    {
        id: tagItem
        tagText: "相机属性"
        norColor: "#000000"
        hovColor: "#303030"
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }


    Column
    {
        id: column
        width: parent.width
        spacing:1
        anchors.top: tagItem.bottom
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right

        CameraRemoteData
        {
            id:lensNameItem
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "镜头"
            suffixText: JCamera.lensName
        }

        CameraRemoteData
        {
            id:camera319
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "DISP"
            key:JCamera.dispMode.key
            wirtable: JCamera.dispMode.writable === 1? true : false
            suffixText: JCamera.dispMode.value
            mComboBox.model: JCamera.dispMode.values
            mComboBox.currentIndex: JCamera.dispMode.values.indexOf(JCamera.dispMode.value)
            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }
        CameraRemoteData
        {
            id:camera273
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "长宽比"
            key:JCamera.aspectRatio.key
            wirtable: JCamera.aspectRatio.writable === 1? true : false
            suffixText: JCamera.aspectRatio.value
            mComboBox.model: JCamera.aspectRatio.values
            mComboBox.currentIndex: JCamera.aspectRatio.values.indexOf(JCamera.aspectRatio.value)
            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }
        CameraRemoteData
        {
            id:camera261
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "程序模式"
            key:JCamera.programMode.key
            wirtable: JCamera.programMode.writable === 1? true : false
            suffixText: JCamera.programMode.value
            mComboBox.model: JCamera.programMode.values
            mComboBox.currentIndex: JCamera.programMode.values.indexOf(JCamera.programMode.value)
            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera256
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "光圈"
            key:JCamera.fNumber.key
            wirtable: JCamera.fNumber.writable === 1? true : false
            suffixText: JCamera.fNumber.value
            mComboBox.model: JCamera.fNumber.values
            mComboBox.currentIndex: JCamera.fNumber.values.indexOf(JCamera.fNumber.value)

            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera259
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "快门速度"
            key:JCamera.shutterSpeed.key
            wirtable: JCamera.shutterSpeed.writable === 1? true : false
            suffixText: JCamera.shutterSpeed.value
            mComboBox.model: JCamera.shutterSpeed.values
            mComboBox.currentIndex: JCamera.shutterSpeed.values.indexOf(JCamera.shutterSpeed.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera260
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "ISO"
            key:JCamera.isoSensitivity.key
            wirtable: JCamera.isoSensitivity.writable === 1? true : false
            suffixText: JCamera.isoSensitivity.value
            mComboBox.model: JCamera.isoSensitivity.values
            mComboBox.currentIndex: JCamera.isoSensitivity.values.indexOf(JCamera.isoSensitivity.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera264
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "白平衡"
            key:JCamera.whiteBalance.key
            wirtable: JCamera.whiteBalance.writable === 1? true : false
            suffixText: JCamera.whiteBalance.value
            mComboBox.model: JCamera.whiteBalance.values
            mComboBox.currentIndex: JCamera.whiteBalance.values.indexOf(JCamera.whiteBalance.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera265
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "对焦模式"
            key:JCamera.focusMode.key
            wirtable: JCamera.focusMode.writable === 1? true : false
            suffixText: JCamera.focusMode.value
            mComboBox.model: JCamera.focusMode.values
            mComboBox.currentIndex: JCamera.focusMode.values.indexOf(JCamera.focusMode.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera275
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "对焦区域"
            key:JCamera.focusArea.key
            wirtable: JCamera.focusArea.writable === 1? true : false
            suffixText: JCamera.focusArea.value
            mComboBox.model: JCamera.focusArea.values
            mComboBox.currentIndex: JCamera.focusArea.values.indexOf(JCamera.focusArea.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera293
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "变焦模式"
            key:JCamera.zoomSetting.key
            wirtable: JCamera.zoomSetting.writable === 1? true : false
            suffixText: JCamera.zoomSetting.value
            mComboBox.model: JCamera.zoomSetting.values
            mComboBox.currentIndex: JCamera.zoomSetting.values.indexOf(JCamera.zoomSetting.value)
            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }
        CameraRemoteData
        {
            id:camera262
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "静态影像文件格式"
            key:JCamera.fileType.key
            wirtable: JCamera.fileType.writable === 1? true : false
            suffixText: JCamera.fileType.value
            mComboBox.model: JCamera.fileType.values
            mComboBox.currentIndex: JCamera.fileType.values.indexOf(JCamera.fileType.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera263
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "JPEG质量"
            key:JCamera.jpegQuality.key
            wirtable: JCamera.jpegQuality.writable === 1? true : false
            suffixText: JCamera.jpegQuality.value
            mComboBox.model: JCamera.jpegQuality.values
            mComboBox.currentIndex: JCamera.jpegQuality.values.indexOf(JCamera.jpegQuality.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera270
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "拍摄模式"
            key:JCamera.driveMode.key
            wirtable: JCamera.driveMode.writable === 1? true : false
            suffixText: JCamera.driveMode.value
            mComboBox.model: JCamera.driveMode.values
            mComboBox.currentIndex: JCamera.driveMode.values.indexOf(JCamera.driveMode.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera305
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "RAW文件类型"
            key:JCamera.rawFileCompressionType.key
            wirtable: JCamera.rawFileCompressionType.writable === 1? true : false
            suffixText: JCamera.rawFileCompressionType.value
            mComboBox.model: JCamera.rawFileCompressionType.values
            mComboBox.currentIndex: JCamera.rawFileCompressionType.values.indexOf(JCamera.rawFileCompressionType.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }
        CameraRemoteData
        {
            id:camera295
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "动态影像文件格式"
            key:JCamera.movieFileFormat.key
            wirtable: JCamera.movieFileFormat.writable === 1? true : false
            suffixText: JCamera.movieFileFormat.value
            mComboBox.model: JCamera.movieFileFormat.values
            mComboBox.currentIndex: JCamera.movieFileFormat.values.indexOf(JCamera.movieFileFormat.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera296
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "动态影像记录设置"
            key:JCamera.movieRecording.key
            wirtable: JCamera.movieRecording.writable === 1? true : false
            suffixText: JCamera.movieRecording.value
            mComboBox.model: JCamera.movieRecording.values
            mComboBox.currentIndex: JCamera.movieRecording.values.indexOf(JCamera.movieRecording.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:camera297
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "动态影像帧速率"
            key:JCamera.movieRecordingFrameRate.key
            wirtable: JCamera.movieRecordingFrameRate.writable === 1? true : false
            suffixText: JCamera.movieRecordingFrameRate.value
            mComboBox.model: JCamera.movieRecordingFrameRate.values
            mComboBox.currentIndex: JCamera.movieRecordingFrameRate.values.indexOf(JCamera.movieRecordingFrameRate.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:cameraLive
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "实时取景显示"
            key:JCamera.liveViewDisplayEffect.key
            wirtable: JCamera.liveViewDisplayEffect.writable === 1? true : false
            suffixText: JCamera.liveViewDisplayEffect.value
            mComboBox.model: JCamera.liveViewDisplayEffect.values
            mComboBox.currentIndex: JCamera.liveViewDisplayEffect.values.indexOf(JCamera.liveViewDisplayEffect.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }

        CameraRemoteData
        {
            id:cameraLiveQ
            height: 30
            width: parent.width
            visible: tagItem.zoomFlag
            tagText: "实时图像质量"
            key:JCamera.liveViewImageQuality.key
            wirtable: JCamera.liveViewImageQuality.writable === 1? true : false
            suffixText: JCamera.liveViewImageQuality.value
            mComboBox.model: JCamera.liveViewImageQuality.values
            mComboBox.currentIndex: JCamera.liveViewImageQuality.values.indexOf(JCamera.liveViewImageQuality.value)


            onIndexActivated: (index)=>
            {
                if(wirtable)
                {
                    JStudioClient.sendRemoteCommand(MyScript.setCameraValue(key,index))
                }
            }
        }
    }

}
