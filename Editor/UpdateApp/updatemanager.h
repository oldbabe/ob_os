#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QThread>

class QZipWriter;
class UpdateManager : public QThread
{
    Q_OBJECT
    Q_PROPERTY(int to READ getTo NOTIFY toChanged)
    Q_PROPERTY(int value READ getValue NOTIFY valueChanged)
    Q_PROPERTY(QString scheduleText READ getScheduleText NOTIFY scheduleTextChanged)
    Q_PROPERTY(bool updateEnable READ getUpdateEnable NOTIFY updateEnableChanged)
    Q_PROPERTY(QString version WRITE setVersion READ getVersion NOTIFY versionChanged)
    Q_PROPERTY(QString nasVersion READ getNasVersion NOTIFY nasVersionChanged)
    Q_PROPERTY(QString writerBaseZip READ getWriterBaseZip NOTIFY writerBaseZipChanged )
    Q_PROPERTY(QString writerSrcDir WRITE setWriterSrcDir READ getWriterSrcDir NOTIFY writerSrcDirChanged)
    Q_PROPERTY(QString writerTargetDir WRITE setWriterTargetDir READ getWriterTargetDir NOTIFY writerTargetDirChanged)


signals:
    void valueChanged();
    void toChanged();
    void scheduleTextChanged();
    void updateEnableChanged();
    void versionChanged();
    void nasVersionChanged();
    void writerBaseZipChanged();
    void writerSrcDirChanged();
    void writerTargetDirChanged();
    void quitApp();
    void packagingFinished();

public:
    static UpdateManager* getInstance();

    enum TaskCode{
        TaskCode_NULL = 0,
        TaskCode_Packaging,
        TaskCode_UpdateProgram
    };

    void updateEnableCacl();

    Q_INVOKABLE QString getDesktopDirectory() const;
    Q_INVOKABLE QString getSystemDirectory(const QString &title,const QString &path);

    Q_INVOKABLE void packaging();
    Q_INVOKABLE void updateProgram();

    void setTo(int value);
    int getTo() const {return mTo;}
    void setValue(int value);
    void setVersion(const QString &str);
    void setNasVersion(const QString &str);
    void setWriterSrcDir(const QString &path);
    void setWriterTargetDir(const QString &path);
    void setUpdateEnable(bool enable);
    void setQuitApp(const QString &name);

    int getValue() const {return mValue;}
    QString getVersion() const {return mVersion;}
    QString getNasVersion() const {return mNasVersion;}
    QString getWriterBaseZip() const {return mWriterBaseZip;}
    QString getWriterSrcDir() const {return mWriterSrcDir;}
    QString getWriterTargetDir() const {return mWriterTargetDir;}
    QString getScheduleText() const {return mScheduleText;}
    bool getUpdateEnable() const {return mUpdateEnable;}
    QString getQuitApp() const {return mQuitApp;}

protected:
    virtual void run();

private:
    static UpdateManager* handle;
    UpdateManager();

    int mTo;
    int mValue;
    QString mScheduleText;
    TaskCode mTaskCode;

    QString mVersion;
    QString mOldVersion;
    QString mNasVersion;
    QString mWriterBaseZip;
    QString mWriterSrcDir;
    QString mWriterTargetDir;

    bool mUpdateEnable;
    QString mQuitApp;

    void TaskPackaging();
    void TaskUpdateProgram();
    bool versionVerify();
    void setProgramLnk(const QString &exeFileName, const QString &lnkFileName);
    void Decompression(const QString &zip, const QString &path);
    void Compression(const QString &srcDir, const QString &targetDir, const QString &ver);

    void zipWriterSize(const QString &dirPath, int &size);
    void zipWriterAddFile(QZipWriter *writer,const QString &filePath,int &number);
    void setScheduleText(const QString &text);
    QJsonObject readJson(const QString &fileName);
    void saveJson(const QString &fileName,const QJsonObject &obj);
};

#endif // UPDATEMANAGER_H
