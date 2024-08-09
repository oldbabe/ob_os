#ifndef JSTDLENSDB_H
#define JSTDLENSDB_H

#include <QObject>
#include <QJsonObject>

class QSqlDatabase;

namespace jltmoco
{

class JStdLensDb : public QObject
{
    Q_OBJECT
public:
    static JStdLensDb* getInstance();

    Q_INVOKABLE void init();
    Q_INVOKABLE void release();

    Q_INVOKABLE void setDbFileName(const QString &fileName);
    Q_INVOKABLE QString getDbFileName() const;
    Q_INVOKABLE void setCommitDir(const QString &dir);
    Q_INVOKABLE QString getCommitDir() const;

    Q_INVOKABLE bool connect(const QString &dbFile);
    Q_INVOKABLE bool connected() const;
    Q_INVOKABLE void disconnect();

    Q_INVOKABLE bool exist(const QString &lensCode);
    Q_INVOKABLE bool append(const QString &lensCode,int lensState,const QString &remark);
    Q_INVOKABLE bool remove(const QString &lensCode);
    Q_INVOKABLE bool update(const QString &code,int state,const QString &remark);
    Q_INVOKABLE QJsonObject searchOne(const QString &lensCode);
    QJsonObject search(const QString &lensCode);


private:
    static JStdLensDb* handle;
    JStdLensDb();

    QSqlDatabase *db;//数据库
};

}

#endif // JStdLensDb_H
