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
#ifndef JLTSCRIPTCONNECTOR_H
#define JLTSCRIPTCONNECTOR_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class JltScriptNode;
class JltScriptConnector : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int dragPenStyle WRITE setDragPenStyle READ getDragPenStyle NOTIFY dragPenStyleChanged)
    Q_PROPERTY(bool dragActive READ getDragActive NOTIFY dragActiveChanged)
    Q_PROPERTY(bool dropActive READ getDropActive NOTIFY dropActiveChanged)
    Q_PROPERTY(ConnectorType connectorType WRITE setConnectorType READ getConnectorType NOTIFY connectorTypeChanged)
    Q_PROPERTY(JltScriptConnector *disableConnector WRITE setDisableConnector READ getDisableConnector NOTIFY disableConnectorChanged)
    Q_PROPERTY(JltScriptConnector *bindConnector WRITE setBindConnector READ getBindConnector NOTIFY bindConnectorChanged)

signals:
    void dragPenStyleChanged();
    void dragActiveChanged();
    void dropActiveChanged();
    void connectorTypeChanged();
    void disableConnectorChanged();
    void bindConnectorChanged();
    void bindNodeChanged();
    void dragMove(const QPointF &point);
    void bindUpdate();

public:
    JltScriptConnector(QQuickItem *parent = nullptr);
    ~JltScriptConnector();

    enum ConnectorType
    {
        ConnectorType_Null = 0,
        ConnectorType_Input,
        ConnectorType_Output
    };
    Q_ENUM(ConnectorType);

    Q_INVOKABLE void startDrag();
    Q_INVOKABLE void stopDrag();

    void setDragPenStyle(int value);
    int getDragPenStyle() const {return mDragPenStyle;}
    void setDragActive(bool value);
    bool getDragActive() const {return mDragActive;}
    void setDropActive(bool value);
    bool getDropActive() const {return mDropActive;}
    void setConnectorType(ConnectorType type);
    ConnectorType getConnectorType() const {return mConnectorType;}
    void setBindNode(JltScriptNode *node);
    Q_INVOKABLE JltScriptNode *getBindNode() const {return mBindNode;}
    void setDisableConnector(JltScriptConnector *connector);
    JltScriptConnector *getDisableConnector() const {return mDisableConnector;}
    void setBindConnector(JltScriptConnector *connector);
    JltScriptConnector *getBindConnector() const {return mBindConnector;}

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);

private:
    int mDragPenStyle;
    bool mDragActive;
    bool mDropActive;
    ConnectorType mConnectorType;
    JltScriptNode *mBindNode;
    JltScriptConnector *mDisableConnector;
    JltScriptConnector *mBindConnector;
};

#endif // JLTSCRIPTCONNECTOR_H
