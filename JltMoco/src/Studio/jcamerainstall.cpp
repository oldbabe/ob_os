#include "Studio/jcamerainstall.h"
#include "Studio/jcamera.h"
#include <QStandardPaths>
#include <QSettings>
#include <QEventLoop>
#include <QTimer>
#include <QDir>

#include <QMutex>
#include <QDebug>

using namespace jltmoco;

JCameraInstall* JCameraInstall::handle = Q_NULLPTR;

JCameraInstall* JCameraInstall::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JCameraInstall;
        mutex.unlock();
    }
    return handle;
}

JCameraInstall::JCameraInstall()
{
    this->mCurrentIndex = 0;
    this->mTimer = new QTimer;
    this->mTimer->setSingleShot(true);
    connect(mTimer,&QTimer::timeout,this,&JCameraInstall::onTimeout);
}

void JCameraInstall::release()
{
    this->mTimer->deleteLater();
}

void JCameraInstall::setCurrentIndex(int index)
{
    if(mCurrentIndex != index)
    {
        this->mCurrentIndex = index;
        emit currentIndexChanged();
    }
}

int JCameraInstall::count(const QString &cameaName) const
{
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    int size = setting.beginReadArray(cameaName);
    setting.endArray();
    return size;
}

void JCameraInstall::init(const QString &cameaName)
{
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    setting.beginWriteArray(cameaName);
    for (int var = 0; var < 8; ++var)
    {
        setting.setArrayIndex(var);
        setting.setValue("title", "预设"+QString::number(var));
    }
    setting.endArray();
}

QJsonObject JCameraInstall::get(const QString &cameaName,int index)
{
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    int size = setting.beginReadArray(cameaName);
    if(index>-1&&index<size)
    {
        setting.setArrayIndex(index);
        QJsonObject root;
        root["title"] = setting.value("title").toString();
        return root;
    }

    return QJsonObject();
}

void JCameraInstall::setTitle(const QString &cameaName,int index,const QString &title)
{
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    setting.beginWriteArray(cameaName,8);
    setting.setArrayIndex(index);
    setting.setValue("title", title);
    setting.endArray();
}

/**
 * @brief 设置给定相机和索引的数据
 * @param cameaName
 * @param index
 * @param key
 * @param writable
 * @param value
 */
void JCameraInstall::setProperty(const QString &cameaName,int index,int key,int writable,const QString &value)
{
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    setting.beginWriteArray(cameaName+"_"+QString::number(mCurrentIndex));
    setting.setArrayIndex(index);
    setting.setValue("key", key);
    setting.setValue("writable", writable);
    setting.setValue("value", value);
    setting.endArray();
}

/**
 * @brief 返回属性列表
 * @param cameaName
 * @param index
 * @return
 */
QJsonArray JCameraInstall::getProperty(const QString &cameaName,int index)
{
    QJsonArray props;
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    int size = setting.beginReadArray(cameaName+"_"+QString::number(index));
    for (int var = 0; var < size; ++var)
    {
        setting.setArrayIndex(var);
        QJsonObject root;
        root["key"] = setting.value("key").toInt();
        root["writable"] = setting.value("writable").toInt();
        root["value"] = setting.value("value").toString();
        props.append(root);
    }

    return props;
}


void JCameraInstall::apply(const QString &cameaName,int index)
{
    this->mProps = getProperty(cameaName,index);
    this->mTimer->start(10);//10毫秒之后开始
    emit started();
}


void JCameraInstall::onTimeout()
{
    if(mProps.isEmpty())
    {
        emit finished();
        return;
    }
    QJsonObject prop = mProps.takeAt(0).toObject();
    int writable = prop["writable"].toInt();
    //递归调用
    if(writable != 1)
    {
        this->onTimeout();
    }
    else
    {
        // qDebug() << "void JCameraInstall::onTimeout()" << QDateTime::currentDateTime().toString("hh::mm::ss::zzz") << prop;
        int key = prop["key"].toInt();
        QString value = prop["value"].toString();
        JCamera *camera = JCamera::getInstance();
        if(key == 261)
        {
            if(camera->getProgramMode()->getWritable() == 1 &&
                camera->getProgramMode()->getValues().contains(value) &&
                camera->getProgramMode()->getValue() != value)
            {
                int index = camera->getProgramMode()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(600);
                }
            }
            else
            {
                this->onTimeout();
            }
        }
        else if(key == 256)
        {
            if(camera->getFNumber()->getWritable() == 1 &&
                camera->getFNumber()->getValues().contains(value) &&
                camera->getFNumber()->getValue() != value)
            {
                int index = camera->getFNumber()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getFNumber()->getWritable()
                //          << camera->getFNumber()->getValues().contains(value)
                //          << camera->getFNumber()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 260)
        {
            if(camera->getIsoSensitivity()->getWritable() == 1 &&
                camera->getIsoSensitivity()->getValues().contains(value) &&
                camera->getIsoSensitivity()->getValue() != value)
            {
                int index = camera->getIsoSensitivity()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getIsoSensitivity()->getWritable()
                //          << camera->getIsoSensitivity()->getValues().contains(value)
                //          << camera->getIsoSensitivity()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 259)
        {
            if(camera->getShutterSpeed()->getWritable() == 1 &&
                camera->getShutterSpeed()->getValues().contains(value) &&
                camera->getShutterSpeed()->getValue() != value)
            {
                int index = camera->getShutterSpeed()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getShutterSpeed()->getWritable()
                //          << camera->getShutterSpeed()->getValues().contains(value)
                //          << camera->getShutterSpeed()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 264)
        {
            if(camera->getWhiteBalance()->getWritable() == 1 &&
                camera->getWhiteBalance()->getValues().contains(value) &&
                camera->getWhiteBalance()->getValue() != value)
            {
                int index = camera->getWhiteBalance()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getWhiteBalance()->getWritable()
                //          << camera->getWhiteBalance()->getValues().contains(value)
                //          << camera->getWhiteBalance()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 262)
        {
            if(camera->getFileType()->getWritable() == 1 &&
                camera->getFileType()->getValues().contains(value) &&
                camera->getFileType()->getValue() != value)
            {
                int index = camera->getFileType()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getFileType()->getWritable()
                //          << camera->getFileType()->getValues().contains(value)
                //          << camera->getFileType()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 263)
        {
            if(camera->getJpegQuality()->getWritable() == 1 &&
                camera->getJpegQuality()->getValues().contains(value) &&
                camera->getJpegQuality()->getValue() != value)
            {
                int index = camera->getJpegQuality()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getJpegQuality()->getWritable()
                //          << camera->getJpegQuality()->getValues().contains(value)
                //          << camera->getJpegQuality()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 295)
        {
            if(camera->getMovieFileFormat()->getWritable() == 1 &&
                camera->getMovieFileFormat()->getValues().contains(value) &&
                camera->getMovieFileFormat()->getValue() != value)
            {
                int index = camera->getMovieFileFormat()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getMovieFileFormat()->getWritable()
                //          << camera->getMovieFileFormat()->getValues().contains(value)
                //          << camera->getMovieFileFormat()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 297)
        {
            if(camera->getMovieRecordingFrameRate()->getWritable() == 1 &&
                camera->getMovieRecordingFrameRate()->getValues().contains(value) &&
                camera->getMovieRecordingFrameRate()->getValue() != value)
            {
                int index = camera->getMovieRecordingFrameRate()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getMovieRecordingFrameRate()->getWritable()
                //          << camera->getMovieRecordingFrameRate()->getValues().contains(value)
                //          << camera->getMovieRecordingFrameRate()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 265)
        {
            if(camera->getFocusMode()->getWritable() == 1 &&
                camera->getFocusMode()->getValues().contains(value) &&
                camera->getFocusMode()->getValue() != value)
            {
                int index = camera->getFocusMode()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getFocusMode()->getWritable()
                //          << camera->getFocusMode()->getValues().contains(value)
                //          << camera->getFocusMode()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 270)
        {
            if(camera->getDriveMode()->getWritable() == 1 &&
                camera->getDriveMode()->getValues().contains(value) &&
                camera->getDriveMode()->getValue() != value)
            {
                int index = camera->getDriveMode()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getDriveMode()->getWritable()
                //          << camera->getDriveMode()->getValues().contains(value)
                //          << camera->getDriveMode()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 275)
        {
            if(camera->getFocusArea()->getWritable() == 1 &&
                camera->getFocusArea()->getValues().contains(value) &&
                camera->getFocusArea()->getValue() != value)
            {
                int index = camera->getFocusArea()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getFocusArea()->getWritable()
                //          << camera->getFocusArea()->getValues().contains(value)
                //          << camera->getFocusArea()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 273)
        {
            if(camera->getAspectRatio()->getWritable() == 1 &&
                camera->getAspectRatio()->getValues().contains(value) &&
                camera->getAspectRatio()->getValue() != value)
            {
                int index = camera->getAspectRatio()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getAspectRatio()->getWritable()
                //          << camera->getAspectRatio()->getValues().contains(value)
                //          << camera->getAspectRatio()->getValue();
                this->onTimeout();
            }
        }
        else if(key == 296)
        {
            if(camera->getMovieRecording()->getWritable() == 1 &&
                camera->getMovieRecording()->getValues().contains(value) &&
                camera->getMovieRecording()->getValue() != value)
            {
                int index = camera->getMovieRecording()->getValues().indexOf(value);
                if(index != -1)
                {
                    camera->setProperty(key,index);
                    this->mTimer->start(300);
                }
            }
            else
            {
                // qDebug() << "skip: " << key << camera->getMovieRecording()->getWritable()
                //          << camera->getMovieRecording()->getValues().contains(value)
                //          << camera->getMovieRecording()->getValue();
                this->onTimeout();
            }
        }
    }
}

QStringList JCameraInstall::getDownLoadList()
{
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    QStringList list = setting.value("DownLoadList").toStringList();
    if(list.isEmpty())
    {
        list.append(JCamera::getInstance()->getDownloadDir());
    }
    else
    {
        //将默认位置移动到首位
        int index = list.indexOf(JCamera::getInstance()->getDownloadDir());
        if(index != -1 && index != 0)
        {
            list.insert(0,list.takeAt(index));
        }
    }
    //移除不存在的目录地址
    QStringList resultList;
    foreach (const QString &path, list)
    {
        if(pathExists(path))
            resultList.append(path);
    }
    return resultList;
}

void JCameraInstall::setDownLoadList(const QStringList &list)
{
    QSettings setting(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JCameraInstall.ini", QSettings::IniFormat);
    setting.setValue("DownLoadList",list);
}

bool JCameraInstall::pathExists(const QString &path)
{
    if(path.isEmpty())
        return false;

    QDir dir;
    return dir.exists(path);
}

