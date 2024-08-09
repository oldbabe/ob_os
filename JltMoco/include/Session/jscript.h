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
#ifndef JSCRIPT_H
#define JSCRIPT_H

#include <QJsonArray>
#include "Session/jnode.h"
#include "Session/jscriptfollowfocus.h"
#include "Session/jscriptturnplate.h"
#include "Session/jscriptrobot.h"
#include "Session/jscriptcamera.h"
#include "Session/jscriptscene.h"

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JScript : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int fileState READ getFileState NOTIFY fileStateChanged)
    Q_PROPERTY(bool changed WRITE setChanged READ getChanged NOTIFY changedChanged)
    Q_PROPERTY(bool editEnable WRITE setEditEnable READ getEditEnable NOTIFY editEnableChanged)

    Q_PROPERTY(QString fileName WRITE setFileName READ getFileName NOTIFY fileNameChanged)
    Q_PROPERTY(int remoteMode WRITE setRemoteMode READ getRemoteMode NOTIFY remoteModeChanged)
    Q_PROPERTY(QString version WRITE setVersion READ getVersion NOTIFY versionChanged)
    Q_PROPERTY(int scriptType WRITE setScriptType READ getScriptType NOTIFY scriptTypeChanged)

    Q_PROPERTY(JScriptFollowFocus *glFollowFocus READ getGlFollowFocus CONSTANT)
    Q_PROPERTY(JScriptTurnplate *glTurnplate READ getGlTurnplate CONSTANT)
    Q_PROPERTY(JScriptRobot *glRobot READ getGlRobot CONSTANT)
    Q_PROPERTY(JScriptCamera *glCamera READ getGlCamera CONSTANT)
    Q_PROPERTY(JScriptScene *glScene READ getGlScene CONSTANT)

    Q_PROPERTY(JNode *currentNode WRITE setCurrentNode READ getCurrentNode NOTIFY currentNodeChanged)

public:
    explicit JScript(QObject *parent = nullptr);
    ~JScript();

    enum ScriptType{
        ScriptType_Other = 0,        //其它
        ScriptType_Image,   //平面脚本
        ScriptType_Video,       //视频脚本
    };
    Q_ENUM(ScriptType)
    enum RemoteMode{
        RemoteMode_MoveOnly = 0,    //仅运动
        RemoteMode_MoveShooting,    //运动并拍摄
    };
    Q_ENUM(RemoteMode)
    enum FileState{
        FileState_NULL = 0,     //未加载
        FileState_Ready,        //加载完成
        FileState_Loading,      //加载中
        FileState_Error         //加载错误
    };
    Q_ENUM(FileState)

    void setFileState(int state);
    void setChanged(bool value);
    void setEditEnable(bool enable);
    void setFileName(const QString &fileName);
    void setRemoteMode(int mode);
    void setVersion(const QString &version);
    void setScriptType(int type);
    void setCurrentNode(JNode* node);
    void setRunningNode(JNode* node);

    int getFileState() const {return mFileState;}
    bool getChanged() const {return mChanged;}
    int getEditEnable() const {return mEditEnable;}
    QString getFileName() const {return mFileName;}
    int getRemoteMode() const {return mRemoteMode;}
    QString getVersion() const {return mVersion;}
    int getScriptType() const {return mScriptType;}

    JScriptFollowFocus *getGlFollowFocus() {return &mGlFollowFocus;}
    JScriptTurnplate *getGlTurnplate() {return &mGlTurnplate;}
    JScriptRobot *getGlRobot() {return &mGlRobot;}
    JScriptCamera *getGlCamera() {return &mGlCamera;}
    JScriptScene *getGlScene() {return &mGlScene;}
    JNode* getCurrentNode() {return mCurrentNode;}
    JNode* getRunningNode() {return mRunningNode;}

    JNode *createNextNodeData(const QJsonObject &nodeData,JNode *parent = nullptr);
    Q_INVOKABLE int loadFile();
    Q_INVOKABLE QList<JNode *> getNodes();
    Q_INVOKABLE JNode* getNode(const QString &key);

    Q_INVOKABLE void removeNode(JNode *node);
    Q_INVOKABLE JNode* createNode(qreal x,qreal y,int robotType,int nodeType = JNode::NodeType_Move);
    Q_INVOKABLE QString previewUpdate(const QString &path,JNode *node);
    Q_INVOKABLE void setNodeTitle(JNode *node,const QString &title);

    Q_INVOKABLE int save();
    Q_INVOKABLE QJsonObject toJson();

    void clear();
    QByteArray getRandomKey(int length = 4);
    QJsonObject getNodeJson(JNode *node, int defaultRobotType = 0);
    int getRunningDirection() const {return mRunningDirection;}

    Q_INVOKABLE void assistNodeReset(int code = 5);
    Q_INVOKABLE void targetNodeReset(int code = 5);
    Q_INVOKABLE void scriptRun(int skipCount = 0, bool direction = true);
    Q_INVOKABLE void stopRun();

private slots:
    void onRobotConnectedChanged();

private:
    int mFileState;
    bool mChanged;
    bool mEditEnable;

    QString mFileName;
    int mRemoteMode;

    QString mVersion;
    int mScriptType;

    JScriptFollowFocus mGlFollowFocus;
    JScriptTurnplate mGlTurnplate;
    JScriptRobot mGlRobot;
    JScriptCamera mGlCamera;
    JScriptScene mGlScene;

    JNode* mCurrentNode;
    JNode* mRunningNode;
    int mRunningDirection;

signals:
    void fileStateChanged();
    void changedChanged();
    void editEnableChanged();

    void fileNameChanged();
    void remoteModeChanged();
    void versionChanged();
    void scriptTypeChanged();

    void currentNodeChanged();
    void runningNodeChanged();
};

}

#endif // JSCRIPT_H
