#include "updatemanager.h"

#include <QMutex>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

#include "QtGui/private/qzipreader_p.h"
#include "QtGui/private/qzipwriter_p.h"

UpdateManager* UpdateManager::handle = Q_NULLPTR;

UpdateManager* UpdateManager::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new UpdateManager;
        mutex.unlock();
    }
    return handle;
}

UpdateManager::UpdateManager()
{
    this->mTo = 100;
    this->mValue = 0;
    this->mScheduleText = "";
    this->mQuitApp = "";

    this->mTaskCode = TaskCode_NULL;
    this->setWriterSrcDir(QDir::currentPath());
    this->setWriterTargetDir("B:/JltApp");
    this->mWriterBaseZip = "B:/JltApp/base.zip";

    connect(this,&UpdateManager::packagingFinished,this,[this]{
        QMessageBox::information(NULL,tr("打包"),tr("打包任务结束!"),QMessageBox::Ok);
        emit quitApp();
    });
}

/**
 * @brief 无参数启动时更新使能昨天判断
 */
void UpdateManager::updateEnableCacl()
{
    QDir exeDir(QDir::currentPath());
    if(exeDir.dirName() != "Release" && exeDir.dirName() != "Debug")
        this->setUpdateEnable(true);
    else
        this->setUpdateEnable(false);
}

/**
 * @brief 返回桌面地址
 * @return
 */
QString UpdateManager::getDesktopDirectory() const
{
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

/**
 * @brief 返回选中的系统目录
 * @return
 */
QString UpdateManager::getSystemDirectory(const QString &title,const QString &path)
{
    return QFileDialog::getExistingDirectory(nullptr,title,path);
}

/**
 * @brief 打包源程序到目标地址
 */
void UpdateManager::packaging()
{
    if(isRunning())
        return;

#ifdef QT_DEBUG
    QMessageBox::information(NULL,tr("打包错误"),tr("构建版本:Debug. 无法打包"),QMessageBox::Ok);
#else
    QDir dir;
    if(!dir.exists(getWriterSrcDir()))
    {
        QMessageBox::information(NULL,tr("打包"),tr("源程序地址不存在,无法打包!"),QMessageBox::Ok);
        return;
    }
    if(!dir.exists(getWriterTargetDir()))
    {
        QMessageBox::information(NULL,tr("打包"),tr("打包的目标地址不存在,无法打包!"),QMessageBox::Ok);
        return;
    }
    if(mVersion.isEmpty())
    {
        QMessageBox::information(NULL,tr("打包"),tr("打包的版本号错误,无法打包!"),QMessageBox::Ok);
        return;
    }
    QStringList nasVers = mNasVersion.split(".");
    QStringList locationVers = mVersion.split(".");
    bool packagingFlag = false;
    for (int i = 0; i < 4; ++i)
    {
        if(locationVers[i].toInt() > nasVers[i].toInt())
        {
            packagingFlag = true;
            break;
        }
    }
    if(!packagingFlag)
    {
        QMessageBox::information(NULL,tr("打包"),tr("打包版不高于目标版本,无法打包!"),QMessageBox::Ok);
        return;
    }
    this->mTaskCode = TaskCode_Packaging;
    this->start();
#endif
}

void UpdateManager::updateProgram()
{
    if(!isRunning())
    {
        this->setUpdateEnable(true);
        this->mTaskCode = TaskCode_UpdateProgram;
        this->start();
    }
}

/**
 * @brief 任务线程
 */
void UpdateManager::run()
{
    if(mTaskCode == TaskCode_Packaging)
    {
        this->TaskPackaging();
    }
    else if(mTaskCode == TaskCode_UpdateProgram)
    {
        this->TaskUpdateProgram();
    }
}

/**
 * @brief 打包任务
 */
void UpdateManager::TaskPackaging()
{
    //版本解析
    QJsonObject root;
    QStringList list = mVersion.split(".");
    if(list.length() == 4)
    {
        root["versionMajor"] = list[0].toInt();
        root["versionMinor"] = list[1].toInt();
        root["versionDeployed"] = list[2].toInt();
        root["versionRevision"] = list[3].toInt();
        root["zip"] = mVersion+".zip";
        //版本文件保存到本地
        this->saveJson(mWriterSrcDir+"/version.json",root);
    }
    //压缩到目标目录
    this->Compression(mWriterSrcDir,mWriterTargetDir,mVersion);
    //版本文件保存到目标目录
    this->saveJson(mWriterTargetDir+"/version.json",root);
    this->mTaskCode = TaskCode_NULL;
    //打包完成
    emit packagingFinished();
}

/**
 * @brief 更新程序包
 */
void UpdateManager::TaskUpdateProgram()
{
#ifdef QT_NO_DEBUG
    this->setScheduleText("更新App:"+mQuitApp);
    if(versionVerify())
    {
        QJsonObject nasVersion = readJson(getWriterTargetDir()+"/version.json");
        QString zipFileName = getWriterTargetDir()+"/"+nasVersion["zip"].toString();
        //解压缩
        this->Decompression(zipFileName,getWriterSrcDir());
        QThread::msleep(500);
        //更新桌面快捷方式
        this->setProgramLnk("DesignerApp.exe","设计端.lnk");
        this->setProgramLnk("DeviceApp.exe","控制服务器.lnk");
        this->setProgramLnk("WorkerApp.exe","工作端.lnk");
        this->setProgramLnk("ImageApp.exe","照片.lnk");

        this->setScheduleText("更新完成,启动:"+mQuitApp);
    }
    QThread::msleep(200);
    this->setTo(100);
    this->setValue(100);
    this->setScheduleText("更新完成,等待启动:"+mQuitApp);
#else
    this->setTo(100);
    this->setValue(100);
    this->setScheduleText("构建版本:Debug,更新失败");
#endif

    QThread::msleep(2000);
    emit quitApp();
}

/**
 * @brief 版本验证
 * @return =true通过
 */
bool UpdateManager::versionVerify()
{
    //远程版本
    QStringList list = mNasVersion.split(".");
    int versionMajorNas = list[0].toInt();
    int versionMinorNas = list[1].toInt();
    int versionDeployedNas = list[2].toInt();
    int versionRevisionNas = list[3].toInt();
    //本地版本
    list = mVersion.split(".");
    int versionMajorLocation = list[0].toInt();
    int versionMinorLocation = list[1].toInt();
    int versionDeployedLocation = list[2].toInt();
    int versionRevisionLocation = list[3].toInt();
    if(versionMajorNas>versionMajorLocation ||
        versionMinorNas>versionMinorLocation ||
        versionDeployedNas>versionDeployedLocation ||
        versionRevisionNas>versionRevisionLocation)
    {
        return true;
    }
    return false;
}

/**
 * @brief 设置程序快捷方式
 * @param exe 程序文件址
 * @param lnk 快捷方式文件地址
 */
void UpdateManager::setProgramLnk(const QString &exeName, const QString &lnkName)
{
    QString exeFileName = getWriterSrcDir()+"/"+exeName;
    QString lnFilekName = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/"+lnkName;
    QFile::link(exeFileName,lnFilekName);
}

/**
 * @brief 解压压缩包
 * @param zip 压缩包文件地址
 * @param path 解压目录
 */
void UpdateManager::Decompression(const QString &zip, const QString &path)
{
    QZipReader reader(zip);
    if(!reader.exists())
    {
        return;
    }

    this->setTo(reader.count());
    for(int i = 0; i < reader.fileInfoList().count(); i++)
    {
        QZipReader::FileInfo fileInfo = reader.fileInfoList().at(i);
        if(fileInfo.isFile)
        {
            //"UpdateApp.exe.jlt"=>UpdateApp.exe
            QFile file;
            if(file.exists(getWriterSrcDir()+"/UpdateApp.exe.jlt"))
            {
                file.rename(getWriterSrcDir()+"/UpdateApp.exe.jlt",getWriterSrcDir()+"/UpdateApp.exe");
            }

            file.setFileName(path+"/"+fileInfo.filePath);
            if(file.open(QIODevice::WriteOnly))
            {
                QByteArray dt = fileInfo.filePath.toUtf8();
                QString strtemp = QString::fromLocal8Bit(dt);
                QByteArray array = reader.fileData(strtemp);
                file.write(array);
                file.close();
                this->setValue(i+1);
            }
        }
        else if(fileInfo.isDir)
        {
            QDir dir;
            dir.mkpath(path+"/"+fileInfo.filePath.toUtf8());
        }
    }
    reader.close();
}

/**
 * @brief 压缩目录
 * @param srcDir 被压缩目录
 * @param targetDir 压缩的目标目录
 * @param ver 版本
 */
void UpdateManager::Compression(const QString &srcDir, const QString &targetDir, const QString &ver)
{
    //! 计算被压缩目录大小
    int size = 0;
    this->zipWriterSize(srcDir,size);
    this->setTo(size);
    this->setValue(0);
    //! 创建压缩文件
    QZipWriter *writer = new QZipWriter(targetDir+"/"+ver+".zip");
    //! 压缩文件添加文件
    int scheduleNumber = 0;
    this->zipWriterAddFile(writer,srcDir,scheduleNumber);
    //! 压缩文件添加文件完成
    writer->close();
    delete writer;
}

/**
 * @brief 递归计算被压缩目录内文件数量
 * @param dirPath 被压缩目录
 * @param size
 */
void UpdateManager::zipWriterSize(const QString &dirPath,int &size)
{
    QDir dir(dirPath);
    dir.setFilter(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);

    QFileInfoList infoList = dir.entryInfoList();
    foreach (QFileInfo fileInfo, infoList)
    {
        //判断过滤器
        QString fileName = fileInfo.fileName();
        QStringList filter = {".manifest",".exp",".lib"};
        bool continueFlag = false;
        foreach (const QString &value, filter)
        {
            if(fileName.contains(value))
            {
                continueFlag = true;
                break;
            }
        }
        if(continueFlag)
        {
            continue;
        }

        //更新计数器
        if(fileInfo.isFile())
        {
            size++;
        }
        else if(fileInfo.isDir())
        {
            zipWriterSize(dirPath+"/"+fileInfo.fileName(),size);
        }
    }
}

/**
 * @brief 压缩包添加文件和目录
 * @param writer 压缩包对象
 * @param filePath 被压缩的文件路径
 * @param number 压缩进度序号
 */
void UpdateManager::zipWriterAddFile(QZipWriter *writer,const QString &filePath,int &number)
{
    QDir dir(filePath);
    dir.setFilter(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    QFileInfoList infoList = dir.entryInfoList();
    foreach (QFileInfo fileInfo, infoList)
    {
        if(fileInfo.isFile())
        {
            //判断过滤器
            QString fileName = fileInfo.fileName();
            QStringList filter = {".manifest",".exp",".lib"};
            bool continueFlag = false;
            foreach (const QString &value, filter)
            {
                if(fileName.contains(value))
                {
                    continueFlag = true;
                    break;
                }
            }
            if(continueFlag)
            {
                continue;
            }

            //添加到压缩包
            QString childFile = filePath+"/"+fileInfo.fileName();
            QFile file(filePath+"/"+fileInfo.fileName());
            if (file.open(QIODevice::ReadOnly))
            {
                childFile.replace(getWriterSrcDir()+"/","");
                if(childFile == "UpdateApp.exe")
                    childFile = "UpdateApp.exe.jlt";
                writer->addFile(childFile, file.readAll());

                file.close();
                this->setValue(++number);
            }
        }
        else if(fileInfo.isDir())
        {
            //跳过日志目录
            if(fileInfo.fileName() != "JltLog")
            {
                QString childDir = filePath+"/"+fileInfo.fileName();
                childDir.replace(getWriterSrcDir()+"/","");
                writer->addDirectory(childDir);
                zipWriterAddFile(writer,filePath+"/"+fileInfo.fileName(),number);
            }
        }
    }
}

void UpdateManager::setTo(int value)
{
    if(value != mTo)
    {
        this->mTo = value;
        emit toChanged();
    }
}

/**
 * @brief 设置进度
 * @param value
 */
void UpdateManager::setValue(int value)
{
    if(value != mValue)
    {
        this->mValue = value;
        emit valueChanged();
    }
}

/**
 * @brief 设置版本号
 * @param str
 */
void UpdateManager::setVersion(const QString &str)
{
    if(str != mVersion)
    {
        this->mOldVersion = str;
        this->mVersion = str;
        emit versionChanged();
    }
}

/**
 * @brief 设置NAS端的版本号
 * @param str
 */
void UpdateManager::setNasVersion(const QString &str)
{
    if(str != mNasVersion)
    {
        this->mNasVersion = str;
        emit nasVersionChanged();
    }
}

/**
 * @brief 设置被压缩的目录
 * @param str
 */
void UpdateManager::setWriterSrcDir(const QString &path)
{
    if(path != mWriterSrcDir)
    {
        this->mWriterSrcDir = path;
        emit writerSrcDirChanged();

        QJsonObject ver = readJson(getWriterSrcDir()+"/version.json");
        this->setVersion(QString("%1.%2.%3.%4").arg(ver["versionMajor"].toInt()).
                         arg(ver["versionMinor"].toInt()).
                         arg(ver["versionDeployed"].toInt()).
                         arg(ver["versionRevision"].toInt()));

    }
}

/**
 * @brief 设置压缩的目标目录
 * @param str
 */
void UpdateManager::setWriterTargetDir(const QString &path)
{
    if(path != mWriterTargetDir)
    {
        this->mWriterTargetDir = path;
        emit writerTargetDirChanged();

        QJsonObject verNas = readJson(getWriterTargetDir()+"/version.json");
        this->setNasVersion(QString("%1.%2.%3.%4").arg(verNas["versionMajor"].toInt()).
                            arg(verNas["versionMinor"].toInt()).
                            arg(verNas["versionDeployed"].toInt()).
                            arg(verNas["versionRevision"].toInt()));
    }
}

/**
 * @brief 设置更新状态使能
 * @param enable
 */
void UpdateManager::setUpdateEnable(bool enable)
{
    if(enable != mUpdateEnable)
    {
        this->mUpdateEnable = enable;
        emit updateEnableChanged();
    }
}

/**
 * @brief 设置程序退出时待启动的程序
 * @param name
 */
void UpdateManager::setQuitApp(const QString &name)
{
    this->mQuitApp = name;
}

/**
 * @brief 设置进度文本
 * @param text
 */
void UpdateManager::setScheduleText(const QString &text)
{
    if(mScheduleText != text)
    {
        this->mScheduleText = text;
        emit scheduleTextChanged();
    }
}

/**
 * @brief 读取JSON文件
 * @param fileName
 * @return
 */
QJsonObject UpdateManager::readJson(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return QJsonObject();

    QJsonParseError *error = new QJsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(),error);
    file.close();

    if(error->error==QJsonParseError::NoError)
        return doc.object();
    else
        return QJsonObject();
}

void UpdateManager::saveJson(const QString &fileName,const QJsonObject &obj)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return ;
    QJsonDocument doc;
    doc.setObject(obj);
    file.write(doc.toJson());
    file.close();
}
