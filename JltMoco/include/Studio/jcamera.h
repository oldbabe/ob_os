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
#ifndef JCAMERA_H
#define JCAMERA_H

#include "Core/jcameraproperty.h"
#include "Studio/deviceabstrcat.h"
#include <QVideoSink>

namespace jltmoco
{

class AbstractCamera;
class DEVICECONTROLLER_EXPORT JCamera : public DeviceAbstract
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ getConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString cameraName READ getCameraName NOTIFY cameraNameChanged)
    Q_PROPERTY(QString downloadDir READ getDownloadDir NOTIFY downloadDirChanged)
    Q_PROPERTY(int transferState READ getTransferState NOTIFY transferStateChanged)
    Q_PROPERTY(QString downloadFileName READ getDownloadFileName NOTIFY downloadFileNameChanged)

    Q_PROPERTY(JCameraProperty *remoteMode READ getRemoteMode CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *fNumber READ getFNumber CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *shutterSpeed READ getShutterSpeed CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *isoSensitivity READ getIsoSensitivity CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *programMode READ getProgramMode CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *fileType READ getFileType CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *jpegQuality READ getJpegQuality CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *whiteBalance READ getWhiteBalance CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *movieFileFormat READ getMovieFileFormat CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *movieRecording READ getMovieRecording CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *movieRecordingFrameRate READ getMovieRecordingFrameRate CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *rawFileCompressionType READ getRawFileCompressionType CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *focusMode READ getFocusMode CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *recordingState READ getRecordingState CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *driveMode READ getDriveMode CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *focusArea READ getFocusArea CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *exposureBiasAompensation READ getExposureBiasAompensation CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *flashAompensation READ getFlashAompensation CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *batteryRemaining READ getBatteryRemaining CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *dispMode READ getDispMode CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *aspectRatio READ getAspectRatio CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *nearFar READ getNearFar CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *zoomSetting READ getZoomSetting CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *zoomOperationStatus READ getZoomOperationStatus CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *zoomRange READ getZoomRange CONSTANT FINAL)
    Q_PROPERTY(QString lensName READ getLensName NOTIFY lensNameChanged)
    Q_PROPERTY(JCameraProperty *liveViewDisplayEffect READ getLiveViewDisplayEffect CONSTANT FINAL)
    Q_PROPERTY(JCameraProperty *liveViewImageQuality READ getLiveViewImageQuality CONSTANT FINAL)

signals:
    void connectedChanged();
    void cameraNameChanged();
    void showDownloadDirWindow();
    void downloadDirChanged();
    void downloadDirSetResult(bool );
    void transferStateChanged();
    void downloadFileNameChanged();
    void lensNameChanged();

    void dataChanged(const QJsonObject &data,int index = -1);

public:
    static JCamera* getInstance();

    void init();
    void release();

    Q_INVOKABLE void setProperty(int key,int index);
    Q_INVOKABLE void setDownloadDirectory(const QString &dir);
    Q_INVOKABLE void shooting(int mode);
    Q_INVOKABLE void s1Shooting(bool mode);
    Q_INVOKABLE void filmRecording(bool state);
    Q_INVOKABLE void quickFormat();
    Q_INVOKABLE void downloadEndFile();
    Q_INVOKABLE void realTimeImageDownload(const QString &fileName);
    Q_INVOKABLE void setFocusPosition(qreal x,qreal y,int mode = 0);
    Q_INVOKABLE void nearFarOperation(int value);
    Q_INVOKABLE void zoomOperation(int value);

    QJsonObject getStatusData();
    void setStatusData(const QJsonObject &obj);
    void setStaticData(const QJsonObject &obj);
    bool getConnected() const{return this->connected;};
    void reloadProperties();

    void commandProcessing(const QJsonObject &obj);

    void setConnected(bool value);
    void setCameraName(const QString &name);
    void setDownloadDir(const QString &name);
    void setTransferState(int state);
    void setDownloadFileName(const QString &fileName);

    int getTransferState() const{return mTransferState;}
    QString getDownloadDir() const{return downloadDir;}
    QString getCameraName() const{return mCameraName;}
    QString getDownloadFileName() const{return mDownloadFileName;}
    JCameraProperty *getRemoteMode(){return &remoteMode;}
    JCameraProperty *getFNumber(){return &fNumber;}
    JCameraProperty *getShutterSpeed(){return &shutterSpeed;}
    JCameraProperty *getIsoSensitivity(){return &isoSensitivity;}
    JCameraProperty *getProgramMode(){return &programMode;}
    JCameraProperty *getFileType(){return &fileType;}
    JCameraProperty *getJpegQuality(){return &jpegQuality;}
    JCameraProperty *getWhiteBalance(){return &whiteBalance;}
    JCameraProperty *getMovieFileFormat(){return &movieFileFormat;}
    JCameraProperty *getMovieRecording(){return &movieRecording;}
    JCameraProperty *getMovieRecordingFrameRate(){return &movieRecordingFrameRate;}
    JCameraProperty *getRawFileCompressionType(){return &rawFileCompressionType;}
    JCameraProperty *getFocusMode(){return &focusMode;}
    JCameraProperty *getFocusArea(){return &focusArea;}
    JCameraProperty *getRecordingState(){return &recordingState;}
    JCameraProperty *getDriveMode(){return &driveMode;}
    JCameraProperty *getExposureBiasAompensation(){return &mExposureBiasAompensation;}
    JCameraProperty *getFlashAompensation(){return &mFlashAompensation;}
    JCameraProperty *getBatteryRemaining(){return &mBatteryRemaining;}
    JCameraProperty *getDispMode(){return &mDispMode;}
    JCameraProperty *getAspectRatio(){return &mAspectRatio;}
    JCameraProperty *getNearFar(){return &mNearFar;}
    JCameraProperty *getZoomSetting(){return &mZoomSetting;}
    JCameraProperty *getZoomOperationStatus(){return &mZoomOperationStatus;}
    JCameraProperty *getZoomRange(){return &mZoomRange;}
    QString getLensName(){return mLensName;}
    JCameraProperty *getLiveViewDisplayEffect(){return &mLiveViewDisplayEffect;}
    JCameraProperty *getLiveViewImageQuality(){return &mLiveViewImageQuality;}


private:
    static JCamera* handle;
    JCamera();

    AbstractCamera *pluginHandle;
    bool connected;
    int mTransferState;
    void sendCommandData(const QJsonObject &data);
    void pluginCallBack(const QJsonObject &obj);
    void liveViewParse( QImage &image);
    void propUpdate(const QJsonObject &data);

    QString mCameraName;
    QString mLensName;
    QString downloadDir;
    QString mDownloadFileName;

    JCameraProperty remoteMode;
    JCameraProperty fNumber;
    JCameraProperty shutterSpeed;
    JCameraProperty isoSensitivity;
    JCameraProperty programMode;
    JCameraProperty fileType;
    JCameraProperty jpegQuality;
    JCameraProperty whiteBalance;
    JCameraProperty movieFileFormat;
    JCameraProperty movieRecording;
    JCameraProperty movieRecordingFrameRate;
    JCameraProperty rawFileCompressionType;
    JCameraProperty focusMode;
    JCameraProperty focusArea;
    JCameraProperty recordingState;
    JCameraProperty driveMode;
    JCameraProperty mExposureBiasAompensation;
    JCameraProperty mFlashAompensation;
    JCameraProperty mBatteryRemaining;
    JCameraProperty mDispMode;
    JCameraProperty mAspectRatio;
    JCameraProperty mNearFar;
    JCameraProperty mZoomRange;
    JCameraProperty mZoomSetting;
    JCameraProperty mZoomOperationStatus;
    JCameraProperty mLiveViewDisplayEffect;
    JCameraProperty mLiveViewImageQuality;
};



}

#endif // DEVICEMANAGER_H
