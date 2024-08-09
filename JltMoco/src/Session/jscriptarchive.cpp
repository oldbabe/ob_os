#include "Session/jscriptarchive.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDateTime>

namespace jltmoco
{
/**
 * @brief JScriptArchive::JScriptArchive
 * @param type = true表示移除7天以前的文件 =false表示存档文件 默认是false
 * @param parent
 */
JScriptArchive::JScriptArchive(bool type,QObject *parent)
    : QThread(parent)
{
    this->mTaskType = type;
    this->mFiles.clear();
    //任务结束后删除
    connect(this, &QThread::finished, this, &QObject::deleteLater);
}

JScriptArchive::~JScriptArchive()
{
}

/**
 * @brief 添加待存档的文件地址
 * @param fileName
 */
void JScriptArchive::append(const QString &fileName)
{
    this->mFiles.append(fileName);
}

/**
 * @brief 线程入口
 */
void JScriptArchive::run()
{
    QDir dir;
    QString archivePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/Archive";

    if(mTaskType)
    {
        this->removeArchives(archivePath);
    }
    else
    {
        if(!dir.exists(archivePath))
        {
            if(dir.mkpath(archivePath))
                this->archives(archivePath);
        }
        else
        {
            this->archives(archivePath);
        }
    }
}

/**
 * @brief 移除旧存档
 * @param path
 */
void JScriptArchive::removeArchives(const QString &path)
{
    QDir dir(path);
    QStringList dirs = dir.entryList(QStringList(),QDir::Dirs|QDir::NoDotAndDotDot);
    while (!dirs.isEmpty())
    {
        dir.setPath(path+"/"+dirs.takeFirst());
        QStringList files = dir.entryList(QStringList(),QDir::Files|QDir::NoDotAndDotDot);
        while (!files.isEmpty())
        {
            QFileInfo fileInfo(dir.path()+"/"+files.takeFirst());
            QDateTime fileTime = fileInfo.lastModified();
            if(fileTime.daysTo(QDateTime::currentDateTime()) >= 14)
                QFile::remove(fileInfo.filePath());
        }
        if(files.isEmpty())
            dir.rmdir(dir.path());
    }
}

/**
 * @brief 存档任务执行
 * @param path
 */
void JScriptArchive::archives(const QString &path)
{
    while (!mFiles.isEmpty())
    {
        QString fileName = mFiles.takeFirst();
        QFileInfo fileInfo(fileName);
        if(fileInfo.isFile())
        {
            QFileInfo pathInfo(fileInfo.path());
            QString archivePath = path+"/"+pathInfo.baseName();
            QDir fileDir(archivePath);
            QString archiveFileName = fileDir.path()+"/"+fileInfo.fileName();
            if(!fileDir.exists(archivePath))
            {
                if(fileDir.mkpath(archivePath))
                {
                    if(QFile::exists(archiveFileName))
                    {
                        if(QFile::remove(archiveFileName))
                            QFile::copy(fileName,archiveFileName);
                    }
                    else
                    {
                        QFile::copy(fileName,archiveFileName);
                    }
                }
            }
            else
            {
                if(QFile::exists(archiveFileName))
                {
                    if(QFile::remove(archiveFileName))
                        QFile::copy(fileName,archiveFileName);
                }
                else
                {
                    QFile::copy(fileName,archiveFileName);
                }
            }
        }
    }
}

}

