#include "Session/jsession.h"
#include "jconfig.h"
#include "jltmoco.h"
#include "Studio/scriptcontroller.h"
#include "Studio/jrobot.h"

#include <QMutex>
#include <QDebug>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDesktopServices>
#include <QStandardPaths>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

namespace jltmoco
{

JSession* JSession::handle = Q_NULLPTR;

JSession* JSession::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JSession;
        mutex.unlock();
    }
    return handle;
}

JSession::JSession()
{
    this->mExpression.setPattern("[J][T][0-9]{6}");
    this->mOpened = false;;
    this->mDirName.clear();
    this->mBaseName.clear();
    this->mModel.clear();
    this->mModel.setSession(this);
    this->mCurrentScript = NULL;

    connect(&mWatcher,&QFileSystemWatcher::directoryChanged,
            this,&JSession::onDirectoryChanged);

    ScriptController *controller = ScriptController::getInstance();
    connect(controller,&ScriptController::stateChanged,
            this,&JSession::onScriptStateChanged);
    connect(controller,&ScriptController::indexChanged,
            this,&JSession::onScriptIndexChanged);
}

/**
 * @brief 初始化会话
 */
void JSession::init()
{
    //读取上次打开会话的路径
    QString path = JConfig::getInstance()->value("JSession/DirName").toString();
    if(path.isEmpty())
        return;
    QDir pathDir(path);
    if(!pathDir.exists())
        return;

    //打开程序关闭时已打开的目录
    this->setDirName(path);
    this->setBaseName(JConfig::getInstance()->value("JSession/BaseName").toString());
    this->setOpened(true);
    this->mWatcher.addPath(path);
    this->onDirectoryChanged(path);
}

/**
 * @brief 获取系统目录地址
 * @return
 */
QString JSession::getExistingDirectory(const QString &title,const QString &path)
{
    QString str = path;
    if(path.isEmpty())
    {
        QDir dir("B:/dataproject");
        if(dir.exists())
            str = "B:/dataproject";
        else
            str = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }
    return QFileDialog::getExistingDirectory(nullptr,title,str);
}

/**
 * @brief 读取存在文件
 * @param title
 * @param path
 * @param filter
 * @return
 */
QString JSession::getExistingFile(const QString &title,const QString &path,const QString &filter)
{
    return QFileDialog::getOpenFileName(nullptr, title,path,filter);
}

/**
 * @brief 打开系统文件目录
 * @param path
 */
void JSession::openExistingDirectory(const QString &path)
{
    if(!path.isEmpty())
    {
        QDesktopServices::openUrl(QUrl("file:"+path, QUrl::TolerantMode));
    }
}

/**
 * @brief 场景会话
 * @param path
 * @param name
 * @return
 */
int JSession::createSession(const QString &path,const QString &name)
{
    //! 创建会话文件夹
    QDir dir(path);
    if(!dir.mkdir(name))
        return 1;

    //! 保存会话文件夹地址
    QString objPath = path+"/"+name;
    dir.setPath(objPath);
    if(!dir.mkdir("download"))
        return 2;
    if(!dir.mkdir("nodeFrame"))
        return 3;

    return 0;
}

/**
 * @brief 打开会话
 * @param path
 * @return return 0成功 =1文件夹不存在 =2会话已打开 =3会话是空的
 */
int JSession::openSession(const QString &path)
{
    if(path.isEmpty())
        return 3;

    QDir dir(path);
    //文件夹不存在
    if(!dir.exists())
        return 1;

    //更新数据
    this->setDirName(path);
    this->setBaseName(dir.dirName());
    this->setOpened(true);
    //更新脚本文件列表
    this->setCurrentScript(NULL);
    this->mModel.clear();
    if(!mWatcher.directories().isEmpty())
    {
        this->mWatcher.removePaths(mWatcher.directories());
    }
    this->mWatcher.addPath(path);
    this->onDirectoryChanged(path);

    return 0;
}

/**
 * @brief 关闭会话
 */
void JSession::closeSession()
{
    this->setCurrentScript(NULL);
    this->mModel.clear();

    this->setOpened(false);
    this->setDirName("");
    this->setBaseName("");

    if(!mWatcher.directories().isEmpty())
    {
        this->mWatcher.removePaths(mWatcher.directories());
    }
}

void JSession::saveSession()
{
    qDebug() << "void JSession::saveSession()";
}

/**
 * @brief 创建脚本
 * @param path 脚本路径
 * @param name 脚本名称
 * @param cameraType 拍摄类型 =1照片 =3视频
 * @return =0成功 =1脚本已经存在 =2脚本写入失败
 */
int JSession::createScript(const QString &path,const QString &name,int cameraType)
{
    QFile file(path+"/"+name+".json");
    if(file.exists())
        return 1;
    if(!file.open(QIODevice::WriteOnly))
        return 2;

    //! [创建脚本数据]
    QJsonObject script;
    script["Version"] = "JTL_SCRIPT_WINDOW_5_0";
    script["CameraType"] = cameraType;
    script["RemoteMode"] = JScript::RemoteMode_MoveOnly;

    //! [创建脚本场景数据]
    QJsonObject scene;
    scene["X"] = 0;
    scene["Y"] = 0;
    scene["GridWidth"] = 16;

    //! [创建全局脚本数据]
    QJsonObject sceneGlobal;
    //robot
    QJsonObject robotGlobal;
    robotGlobal["PrgV"] = 30;
    robotGlobal["Model"] = JRobot::getInstance()->getModel();
    sceneGlobal[QString::number(Device_Robot)] = robotGlobal;

    if(cameraType == JScript::ScriptType_Video)
    {
        QJsonObject cameraGlobal;
        cameraGlobal["RecordingDuration"] = 30;
        cameraGlobal["MoveDelay"] = 3;
        sceneGlobal[QString::number(Device_Camera)] = cameraGlobal;

        QJsonObject followfocus;
        followfocus["FocusMode"] = JScriptFollowFocus::FollowFocusMode_OnlyRemote;
        followfocus["ZoomMode"] = JScriptFollowFocus::FollowFocusMode_OnlyRemote;
        followfocus["IrisMode"] = JScriptFollowFocus::FollowFocusMode_OnlyRemote;
        QJsonObject constant;
        constant["focus"] = 3600;
        constant["zoom"] = 3600;
        constant["iris"] = 3600;
        followfocus["Constant"] = constant;
        followfocus["PathRecord"] = QJsonObject();
        followfocus["TimeRecord"] = QJsonObject();
        followfocus["IrisRecord"] = QJsonObject();
        sceneGlobal[QString::number(Device_FollowFocus)] = followfocus;

        QJsonObject turnplate;
        turnplate["Acc"] = 30;
        turnplate["Dec"] = 30;
        turnplate["Duration"] = 10;
        turnplate["Ori"] = 1;
        turnplate["Speed"] = 30;
        turnplate["StartTime"] = 0;
        sceneGlobal[QString::number(Device_Turntable)] = turnplate;
    }
    scene["Global"] = sceneGlobal;
    scene["Nodes"] = QJsonArray();
    script["Scene"] = scene;

    //! [创建脚本文件]
    QJsonDocument doc;
    doc.setObject(script);
    file.write(doc.toJson());
    file.close();

    return 0;
}

/**
 * @brief 创建副本脚本
 * @param fileName
 * @return =1文件不存在 =2文件类型错误  =3当前会话文件已存在  =4加载失败
 */
int JSession::createCopyScript(JScript *script)
{
    if(script==NULL)
        return 1;

    int index = script->getFileName().indexOf(".json");
    QString newName = script->getFileName().insert(index," - 副本");
    if(script->getFileState() == JScript::FileState_Ready)
    {
        if(!saveScript(newName,script->toJson()))
            return 2;
    }
    else
    {
        if(!QFile::copy(script->getFileName(),newName))
            return 3;
    }

    return 0;
}

/**
 * @brief 读取脚本
 * @param fileName
 * @return
 */
QJsonObject JSession::loadScript(const QString &fileName)
{
    //打开文件
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return QJsonObject();
    }

    QJsonParseError *error = new QJsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(),error);

    //判断文件是否完整
    if(error->error!=QJsonParseError::NoError)
    {
        return QJsonObject();
    }

    file.close();

    return doc.object();
}


bool JSession::saveScript(const QString &fileName,const QJsonObject &obj)
{
    //打开文件
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument doc;
    doc.setObject(obj);

    if(file.write(doc.toJson()) == -1)
    {
        return false;
    }
    file.close();

    return true;
}
//导入脚本
bool JSession::importScript(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    QString newName = getDirName()+"/"+fileInfo.fileName();
    return QFile::copy(fileName,newName);
}
//拷贝文件
int JSession::copyFile(const QString &fileName, const QString &newName)
{
    if(!QFile::exists(fileName))
    {
        return 1;//脚本文件未发现
    }
    if(QFile::exists(newName))
    {
        if(!QFile::remove(newName))
        {
            return 2;//旧文件移除失败
        }
    }
    if(!QFile::copy(fileName,newName))
    {
        return 3;//文件拷贝失败
    }
    return 0;
}

void JSession::removeScript(const QString &fileName)
{
    QFile file(fileName);
    if(file.exists())
        file.remove();
}

bool JSession::renameScript(const QString &oldName,const QString &newName)
{
    QFile file(oldName);
    if(file.exists())
        return file.rename(newName);
    return false;
}

void JSession::setOpened(bool enable)
{
    if(mOpened != enable)
    {
        this->mOpened = enable;
        emit openedChanged();
    }
}

void JSession::setDirName(const QString &dirName)
{
    if(mDirName != dirName)
    {
        this->mDirName = dirName;
        emit dirNameChanged();
        JConfig::getInstance()->setValue("JSession/DirName",dirName);
    }
}

void JSession::setBaseName(const QString &name)
{
    if(mBaseName != name)
    {
        this->mBaseName = name;
        emit baseNameChanged();
        JConfig::getInstance()->setValue("JSession/BaseName",name);
    }
}

void JSession::setCurrentScript(JScript *script)
{
    this->mCurrentScript = script;
    emit currentScriptChanged();
}

/**
 * @brief 会话目录内容改变
 * @param path
 */
void JSession::onDirectoryChanged(const QString &path)
{
    QDir dir(path);
    //文件夹不存在
    if(!dir.exists())
        return;
    //获取最新的文件列表
    QStringList list = dir.entryList(QStringList()<<"*.json",QDir::Files,QDir::Name);
    //文件地址
    for (int var = 0; var < list.length(); ++var)
        list[var] = getDirName()+"/"+list[var];

    //更新文件列表
    this->mModel.updateList(list);
}

void JSession::onScriptStateChanged()
{
    if(!getCurrentScript())
        return;

    ScriptController* controller = ScriptController::getInstance();
    if(controller->getState() == 513 || controller->getState() == 784 || controller->getState() == 800)
    {
        this->getCurrentScript()->setEditEnable(false);
        this->getCurrentScript()->setRunningNode(getCurrentScript()->getCurrentNode());
    }
    else
    {
        this->getCurrentScript()->setEditEnable(true);
        this->getCurrentScript()->setCurrentNode(getCurrentScript()->getRunningNode());
        this->getCurrentScript()->setRunningNode(NULL);
    }
}

void JSession::onScriptIndexChanged()
{
    if(!getCurrentScript())
        return;
    if(!getCurrentScript()->getRunningNode())
        return;
    //传递
    JNode* node = getCurrentScript()->getRunningNode();
    ScriptController* controller = ScriptController::getInstance();
    if(getCurrentScript()->getRunningDirection() == 1)
    {
        for(int i = 1; i <= controller->getExecIndex(); i++)
        {
            if(node->getNextNode())
            {
                node = node->getNextNode();
            }
        }
        this->getCurrentScript()->setCurrentNode(node);
    }
    else if(getCurrentScript()->getRunningDirection() == -1)
    {
        for(int i = 1; i <= controller->getExecIndex(); i++)
        {
            if(node->getLastNode())
            {
                node = node->getLastNode();
            }
        }
        this->getCurrentScript()->setCurrentNode(node);
    }
}


}

