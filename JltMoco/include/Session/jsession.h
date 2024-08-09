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
#ifndef JSESSION_H
#define JSESSION_H

#include "Core/jsessionmodel.h"
#include <QRegularExpression>
#include <QFileSystemWatcher>

namespace jltmoco
{

class DEVICECONTROLLER_EXPORT JSession : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool opened READ getOpened NOTIFY openedChanged)
    Q_PROPERTY(QString dirName READ getDirName NOTIFY dirNameChanged)
    Q_PROPERTY(QString baseName READ getBaseName NOTIFY baseNameChanged)

    Q_PROPERTY(JSessionModel *model READ getModel CONSTANT)
    Q_PROPERTY(JScript *currentScript WRITE setCurrentScript READ getCurrentScript NOTIFY currentScriptChanged)

public:
    static JSession* getInstance();

    Q_INVOKABLE void init();
    Q_INVOKABLE QString getExistingDirectory(const QString &title,const QString &path = "");
    Q_INVOKABLE QString getExistingFile(const QString &title,const QString &path,const QString &filter);
    Q_INVOKABLE void openExistingDirectory(const QString &path);

    Q_INVOKABLE int createSession(const QString &path,const QString &name);
    Q_INVOKABLE int openSession(const QString &path);
    Q_INVOKABLE void closeSession();
    Q_INVOKABLE void saveSession();

    Q_INVOKABLE int createScript(const QString &path,const QString &name,int cameraType);
    Q_INVOKABLE int createCopyScript(JScript *script);

    Q_INVOKABLE QJsonObject loadScript(const QString &fileName);
    Q_INVOKABLE bool saveScript(const QString &fileName,const QJsonObject &obj);
    Q_INVOKABLE bool importScript(const QString &fileName);
    Q_INVOKABLE int copyFile(const QString &fileName, const QString &newName);
    Q_INVOKABLE void removeScript(const QString &fileName);
    Q_INVOKABLE bool renameScript(const QString &oldName,const QString &newName);

    void setOpened(bool enable);
    void setDirName(const QString &dirName);
    void setBaseName(const QString &name);
    void setCurrentScript(JScript *script);

    bool getOpened() const{return mOpened;}
    QString getDirName() const{return mDirName;}
    QString getBaseName() const{return mBaseName;}
    JSessionModel *getModel() {return &mModel;}
    JScript *getCurrentScript() {return mCurrentScript;}


private:
    static JSession* handle;
    JSession();

    bool mOpened;
    QString mDirName;
    QString mBaseName;

    JSessionModel mModel;
    JScript *mCurrentScript;

    QFileSystemWatcher mWatcher;
    QRegularExpression mExpression;
    QRegularExpressionMatch mExpressionMatch;

private slots:
    void onDirectoryChanged(const QString &path);
    void onScriptStateChanged();
    void onScriptIndexChanged();

signals:
    void openedChanged();
    void currentScriptChanged();
    void dirNameChanged();
    void baseNameChanged();

};

}

#endif // JSESSION_H
