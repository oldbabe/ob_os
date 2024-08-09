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
#ifndef JCAMERADEVICE_H
#define JCAMERADEVICE_H

#include "global.h"
#include <QThread>
#include <QVideoSink>
#include <QRectF>

namespace cv{
class Mat;
class HOGDescriptor;
}
namespace jltmoco
{
class DEVICECONTROLLER_EXPORT JCameraDevice : public QThread
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QVideoSink* videoSink READ getVideoSink WRITE setVideoSink NOTIFY videoSinkChanged)
    Q_PROPERTY(bool horizontalMirrored WRITE setHorizontalMirrored READ getHorizontalMirrored NOTIFY horizontalMirroredChanged)
    Q_PROPERTY(bool verticalMirrored WRITE setVerticalMirrored READ getVerticalMirrored NOTIFY verticalMirroredChanged)
    Q_PROPERTY(RotateFlags rotateFlag WRITE setRotateFlag READ getRotateFlag NOTIFY rotateFlagChanged)
    Q_PROPERTY(GridFlags gridFlag WRITE setGridFlag READ getGridFlag NOTIFY gridFlagChanged)
    Q_PROPERTY(ControlFlags controlFlag WRITE setControlFlag READ getControlFlag NOTIFY controlFlagChanged)

signals:
    void currentIndexChanged();
    void videoSinkChanged();
    void rotateFlagChanged();
    void horizontalMirroredChanged();
    void verticalMirroredChanged();
    void stopImageChanged();
    void gridFlagChanged();
    void controlFlagChanged();

public:
    static JCameraDevice* getInstance();

    enum RotateFlags
    {
        RotateFlag_0 = 0,
        RotateFlag_90,
        RotateFlag_180,
        RotateFlag_270
    };
    Q_ENUM(RotateFlags)
    enum GridFlags
    {
        GridFlags_Close = 0,
        GridFlags_Trisector,    //  三等分
        GridFlags_Square,       //  方形
        GridFlags_Diagonal      //对角线
    };
    Q_ENUM(GridFlags)
    enum ControlFlags
    {
        ControlFlags_NULL = 0,
        ControlFlags_Focus, //仅对焦
        ControlFlags_FocusShoot, //对焦拍摄
    };
    Q_ENUM(ControlFlags)

    Q_INVOKABLE QStringList cameraList();
    Q_INVOKABLE void play(int index);
    Q_INVOKABLE void stop();

    int getCurrentIndex() const {return mCurrentIndex;}
    void setVideoSink(QVideoSink *newVideoSink);
    QVideoSink *getVideoSink() const{return mVideoSink;}
    QImage getFrameImage();

    RotateFlags getRotateFlag() const {return mRotateFlag;}
    void setRotateFlag(RotateFlags flag);
    bool getHorizontalMirrored() const {return mHorizontalMirrored;}
    void setHorizontalMirrored(bool value);
    bool getVerticalMirrored() const {return mVerticalMirrored;}
    void setVerticalMirrored(bool value);
    GridFlags getGridFlag() const {return mGridFlag;}
    void setGridFlag(GridFlags flag);
    ControlFlags getControlFlag() const {return mControlFlag;}
    void setControlFlag(ControlFlags flag);

protected:
    virtual void run();

private:
    static JCameraDevice* handle;
    JCameraDevice();

    bool runEnable;
    int mCurrentIndex;
    bool mPlaying;
    QVideoSink *mVideoSink;
    RotateFlags mRotateFlag;
    bool mHorizontalMirrored;
    bool mVerticalMirrored;
    GridFlags mGridFlag;
    ControlFlags mControlFlag;

    void cameraFrameProcessing(cv::Mat &frame,cv::HOGDescriptor hog);
    void updateVideoFrame(QImage &img);
    void setCurrentIndex(int index);

private:
    void onCenterRemoteTimeout();

};

}

#endif // JCAMERADEVICE_H
