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
#ifndef JLTSCRIPTSCENE_H
#define JLTSCRIPTSCENE_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class JltScriptScene : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qreal originX WRITE setOriginX READ getOriginX NOTIFY originXChanged)
    Q_PROPERTY(qreal originY WRITE setOriginY READ getOriginY NOTIFY originYChanged)
    Q_PROPERTY(qreal gridWidth WRITE setGridWidth READ getGridWidth NOTIFY gridWidthChanged)
    Q_PROPERTY(qreal axisScale READ getAxisScale NOTIFY axisScaleChanged)
    Q_PROPERTY(bool dragActive READ getDragActive NOTIFY dragActiveChanged)

signals:
    void originXChanged();
    void originYChanged();
    void gridWidthChanged();
    void axisScaleChanged();
    void dragActiveChanged();
    void menuOpened(qreal x,qreal y);
    void originChanged(const QPointF &point);
    void wheelChanged(qreal value);

public:
    JltScriptScene(QQuickItem *parent = nullptr);

    void setOriginX(qreal x);
    void setOriginY(qreal y);
    void setAxisScale(qreal value);
    void setGridWidth(qreal value);
    void setDragActive(bool value);

    qreal getOriginX() {return mOriginPointF.x();}
    qreal getOriginY() {return mOriginPointF.y();}
    qreal getGridWidth() {return mGridWidth;}
    qreal getAxisScale() {return mAxisScale;}
    bool getDragActive() {return mDragActive;}

    virtual void paint(QPainter *painter);


    Q_INVOKABLE void mouseMove(const QPointF &position);
    Q_INVOKABLE void mousePress(const QPointF &position);
    Q_INVOKABLE void mouseRelease(const QPointF &position);
    Q_INVOKABLE void wheelMove(const QPointF &position,const QPointF &angleDelta);

private:
    bool mPressed;
    bool mDragActive;
    qreal mAxisScale;
    QPointF mPressedPointF;
    QPointF mOriginPointF;
    QPointF mSaveOriginPointF;
    QPointF mMousePointF;
    QPointF mDragPointF;
    qreal mGridWidth;
    void drawGrid(QPainter *painter,qreal interval = 16);

};

#endif // JLTSCRIPTSCENE_H
