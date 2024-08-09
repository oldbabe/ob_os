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
#ifndef JFREED_H
#define JFREED_H

#include <QObject>
#include <QUdpSocket>
#include "../global.h"

namespace jltmoco {

class FreeDServer;
class DEVICECONTROLLER_EXPORT JFreed : public QObject
{
    Q_OBJECT
public:
    static JFreed* getInstance();

    Q_INVOKABLE void init();
    Q_INVOKABLE void release();

    Q_INVOKABLE void setIpAddress(const QString &ip,bool flag = true);
    Q_INVOKABLE void setPort(int port,bool flag = true);
    Q_INVOKABLE void setFrame(int value,bool flag = true);
    Q_INVOKABLE void setFocusDeleyFrame(int count,bool flag = true);
    Q_INVOKABLE void setZoomDeleyFrame(int count,bool flag = true);

    Q_INVOKABLE void setFocusMinValue(float min);
    Q_INVOKABLE void setFocusMaxValue(float max);
    Q_INVOKABLE void setZoomMinValue(float min);
    Q_INVOKABLE void setZoomMaxValue(float max);

    Q_INVOKABLE void setCameraRotate(float a,float b,float c,bool flag = true);
    Q_INVOKABLE void setCameraTransform(int a,int b,int c,bool flag = true);
    Q_INVOKABLE void setCoordinateOffset(float x,float y,float z,bool flag = true);
    Q_INVOKABLE void setCoordinateUnity(float x,float y,float z,bool flag = true);
    Q_INVOKABLE void setCoordinateTransform(int x,int y,int z,bool flag = true);

    Q_INVOKABLE QString getIpAddress() const;
    Q_INVOKABLE int getPort() const;
    Q_INVOKABLE int getFrame() const;
    Q_INVOKABLE int getFocusDeleyFrame() const;
    Q_INVOKABLE int getZoomDeleyFrame() const;

    Q_INVOKABLE float getFocusMinValue() const;
    Q_INVOKABLE float getFocusMaxValue() const;
    Q_INVOKABLE float getZoomMinValue() const;
    Q_INVOKABLE float getZoomMaxValue() const;
    Q_INVOKABLE QVector<float> getCameraRotate() const;
    Q_INVOKABLE QVector<int> getCameraTransform() const;
    Q_INVOKABLE QVector<float> getCoordinateOffset() const;
    Q_INVOKABLE QVector<float> getCoordinateUnity() const;
    Q_INVOKABLE QVector<int> getCoordinateTransform() const;

    Q_INVOKABLE  void setAutoFlag(bool enable,bool flag = true);
    Q_INVOKABLE  bool getAutoFlag() const;
    Q_INVOKABLE  void startServer();
    Q_INVOKABLE  void stopServer();
    Q_INVOKABLE bool isRunning() const;

protected:
    virtual void timerEvent(QTimerEvent *event);

private:
    static JFreed* handle;
    JFreed();

    bool autoFlag;
    int freedTimerId;
    int freedFrame;

    int udpPort;
    QString udpAddress;
    QUdpSocket *mUdpSocket;//UDP套接字

    QVector<float> cameraRotate;
    QVector<int> cameraTransform;
    QVector<float> coordinateOffset;
    QVector<float> coordinateUnits;
    QVector<int> coordinateTransform;
    FreeDServer *mFreeDServer;
    QByteArray freedBuffer;

    float focusMinValue;
    float focusMaxValue;
    float zoomMinValue;
    float zoomMaxValue;

    void transformCameraBuffer(QByteArray &buffer,int axis,float value);
    void transformCoordinateBuffer(QByteArray &buffer,int axis,float value);

    QByteArray generatePan(float angle);
    QByteArray generateTile(float angle);
    QByteArray generateRoll(float angle);
    QByteArray angleToByte(float angle);

    QByteArray generatePos(float pos);
    QByteArray generateZoom(float value);
    QByteArray generateFocus(float value);

    char generateCheckSum(const QByteArray &buffer);

    QByteArray focusZoomBuffer;
    int delayFrame;
    QByteArray delayBuffer;

    int delayFoucsFrame;
    int delayZoomFrame;
    QList<float> delayFoucsList;
    QList<float> delayZoomList;

};

}

#endif // JFREED_H
