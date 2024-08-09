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
#ifndef JNODE_H
#define JNODE_H

#include "Session/jnoderobot.h"
#include "Session/jnodecamera.h"
#include "Session/jnodefollowfocus.h"
#include "Session/jnodeturnplate.h"

namespace jltmoco
{

#define NODE_START_NAME "-"

class JScript;
class DEVICECONTROLLER_EXPORT JNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(JScript *script READ getScript NOTIFY scriptChanged)
    Q_PROPERTY(JNode *next WRITE setNextNode READ getNextNode NOTIFY nextChanged())
    Q_PROPERTY(JNode *last WRITE setLastNode READ getLastNode NOTIFY lastChanged())

    Q_PROPERTY(bool checked WRITE setChecked READ getChecked NOTIFY checkedChanged)
    Q_PROPERTY(int type WRITE setType READ getType NOTIFY typeChanged)
    Q_PROPERTY(qreal x WRITE setX READ getX NOTIFY xChanged)
    Q_PROPERTY(qreal y WRITE setY READ getY NOTIFY yChanged)
    Q_PROPERTY(QString title WRITE setTitle READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(QString preview WRITE setPreview READ getPreview NOTIFY previewChanged)

    Q_PROPERTY(JNodeRobot* robot READ getRobot CONSTANT)
    Q_PROPERTY(JNodeCamera* camera READ getCamera CONSTANT)
    Q_PROPERTY(JNodeFollowFocus* followfocus READ getFollowFocus CONSTANT)
    Q_PROPERTY(JNodeTurnplate* trunplate READ getTrunplate CONSTANT)

    Q_PROPERTY(int frameCounts READ getFrameCounts NOTIFY frameCountsChanged)

public:
    explicit JNode(QObject *parent = nullptr);
    ~JNode();

    enum NodeType
    {
        NodeType_Move = 0,  //运动节点
        NodeType_Erp,       //Erp标定
        NodeType_StopMotionAnimation //定格动画
    };
    Q_ENUM(NodeType)

    void setScript(JScript *script);
    void setData(const QJsonObject &nodeData);
    void setNextNode(JNode *node);
    void setLastNode(JNode *node);

    void setChecked(bool value);
    void setType(int value);
    void setX(qreal value);
    void setY(qreal value);
    void setTitle(const QString &value);
    void setPreview(const QString &value);

    void setFrameCounts(int value);
    int getFrameCounts() const {return mFrameCounts;}

    JScript *getScript() const {return mScript;};
    bool getChecked() const {return mChecked;}
    int getType() const {return mType;}
    qreal getX() const {return mX;}
    qreal getY() const {return mY;}
    QString getTitle() const {return mTitle;}
    QString getPreview() const {return mPreview;}

    JNode* getNextNode() {return mNextNode;}
    JNode* getLastNode() {return mLastNode;}
    JNodeRobot *getRobot() {return &mRobot;}
    JNodeCamera *getCamera() {return &mCamera;}
    JNodeFollowFocus *getFollowFocus() {return &mFollowfocus;}
    JNodeTurnplate *getTrunplate() {return &mTrunplate;}

    Q_INVOKABLE void frameMotion(int frameIndex);
    Q_INVOKABLE void updateFrameCounts();
    Q_INVOKABLE QJsonObject toJson();
    Q_INVOKABLE void updataRobotTarget();
    Q_INVOKABLE void updataRobotAssist();
    Q_INVOKABLE void updateCenterCircle();
    Q_INVOKABLE void updatePreview();

private:
    bool mChecked;
    int mType;
    qreal mX;
    qreal mY;
    JNode *mNextNode;
    JNode *mLastNode;

    QString mTitle;
    QString mPreview;

    JScript *mScript;
    JNodeRobot mRobot;
    JNodeCamera mCamera;
    JNodeFollowFocus mFollowfocus;
    JNodeTurnplate mTrunplate;

    int mFrameCounts;

signals:
    void scriptChanged();
    void nextChanged();
    void lastChanged();
    void smaChanged();

    void checkedChanged();
    void typeChanged();
    void xChanged();
    void yChanged();
    void titleChanged();
    void previewChanged();
    void previewVisibleChanged();
    void frameCountsChanged();

};

}

#endif // JSCRIPTMODEL_H
