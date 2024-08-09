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
#ifndef JLTSCRIPTSHAPE_H
#define JLTSCRIPTSHAPE_H

#include <QQmlEngine>
#include <QQuickPaintedItem>
#include "jltscriptscene.h"

class JltScriptNode;
class JltScriptConnector;
class JltScriptShape : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(JltScriptScene* scriptScene WRITE setScriptScene READ getScriptScene NOTIFY scriptSceneChanged)

signals:
    void scriptSceneChanged();

public:
    JltScriptShape(QQuickItem *parent = nullptr);
    ~JltScriptShape();

    void setScriptScene(JltScriptScene* scene);
    JltScriptScene* getScriptScene() {return mScriptScene;}

    Q_INVOKABLE void setActiveConnector(JltScriptConnector *connector);
    Q_INVOKABLE void updateActiveConnectorEndF(const QPointF &endF);
    Q_INVOKABLE void clearActiveConnector();

    Q_INVOKABLE void appendNode(JltScriptNode *node);
    Q_INVOKABLE void clearNode();

    virtual void paint(QPainter *painter);

private:
    JltScriptConnector *mActiveConnector;
    QPointF mActiveEndF;

    QList<JltScriptNode *>mNodes;
    JltScriptScene* mScriptScene;

    void drawCubic(QPainter *painter,const QPointF &startF,const QPointF &endF,qreal scaleF = 5,int penType = 1);


};

#endif // JSCRIPTSHAPE_H
