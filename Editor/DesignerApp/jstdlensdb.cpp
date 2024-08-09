#include "jstdlensdb.h"
#include <QDate>
#include <QMutex>
#include <QSql>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>

#include <QSettings>

namespace jltmoco
{

JStdLensDb* JStdLensDb::handle = Q_NULLPTR;

JStdLensDb* JStdLensDb::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JStdLensDb;
        mutex.unlock();
    }
    return handle;
}

JStdLensDb::JStdLensDb()
{

}


void JStdLensDb::init()
{
    this->db = new QSqlDatabase;
    *db = QSqlDatabase::addDatabase("QSQLITE");
    this->db->setUserName("root");
    this->db->setPassword("123456");
}

void JStdLensDb::release()
{
    this->disconnect();
}

void JStdLensDb::setDbFileName(const QString &fileName)
{
    QSettings settings("JConfig.ini", QSettings::IniFormat);
    settings.setValue("JStdLensDb/DbFileName",fileName);
}

QString JStdLensDb::getDbFileName() const
{
    QSettings settings("JConfig.ini", QSettings::IniFormat);
    return settings.value("JStdLensDb/DbFileName").toString();
}

void JStdLensDb::setCommitDir(const QString &dir)
{
    QSettings settings("JConfig.ini", QSettings::IniFormat);
    settings.setValue("JStdLensDb/CommitDir",dir);
}

QString JStdLensDb::getCommitDir() const
{
    QSettings settings("JConfig.ini", QSettings::IniFormat);
    return settings.value("JStdLensDb/CommitDir").toString();
}


/**
* @brief 连接数据库
**/
bool JStdLensDb::connect(const QString &dbFile)
{
    this->db->setDatabaseName(dbFile);
    return this->db->open();
}

/**
* @brief 数据库连接状态
**/
bool JStdLensDb::connected() const
{
    return this->db->open();
}
/**
* @brief 断开数据库
**/
void JStdLensDb::disconnect()
{
    this->db->close();
}

/**
* @brief 镜头是否存在
* @param lensCode 镜头代码
**/
bool JStdLensDb::exist(const QString &lensCode)
{
    QString str = QString("SELECT * FROM StdLens WHERE LensCode == '%1'").arg(lensCode);
    QSqlQuery query(str);
    return query.next();
}

/**
* @brief 添加镜头
* @param obj 内容
**/
bool JStdLensDb::append(const QString &code,int state,const QString &remark)
{
    qDebug() << "JStdLensDb::append >" << code << state << remark;
    QString str = QString("INSERT INTO StdLens (ID,LensCode,LensState,FileName,Time,Remark)"
                          " VALUES (hex(randomblob(16)),'%1','%2','%3','%4','%5');")
            .arg(code).arg(state).arg(QString("%1.json").arg(code)).arg(QDate::currentDate().toString("yyyy:MM:dd")).arg(remark);

    QSqlQuery query;
    return query.exec(str);
}

/**
* @brief 删除镜头
* @return lensCode 镜头代码
**/
bool JStdLensDb::remove(const QString &lensCode)
{
    QString str = QString("DELETE FROM StdLens WHERE LensCode = '%1';").arg(lensCode);

    QSqlQuery query;
    return query.exec(str);
}

/**
* @brief 更新镜头
* @return obj 内容
**/
bool JStdLensDb::update(const QString &code,int state,const QString &remark)
{
    qDebug() << "JStdLensDb::update >" << code << state << remark;
    QString str = QString("UPDATE StdLens SET LensState = '%1', FileName = '%2', Time = '%3', Remark = '%4' WHERE LensCode = '%5';")
            .arg(state).arg(QString("%1.json").arg(code)).arg(QDate::currentDate().toString("yyyy:MM:dd")).arg(remark).arg(code);

    QSqlQuery query;
    return query.exec(str);
}

/**
* @brief 查找单个镜头
**/
QJsonObject JStdLensDb::searchOne(const QString &lensCode)
{
    QString strCode = lensCode.trimmed();
    QJsonObject obj;

    QString str = QString("SELECT * FROM StdLens WHERE LensCode = '%1';").arg(strCode);
    QSqlQuery query(str);
    if (query.next())
    {
        obj["LensCode"] = query.value(1).toString();
        obj["LensState"] = query.value(2).toBool();
        obj["FileName"] = query.value(3).toString();
        obj["Time"] = query.value(4).toString();
        obj["Remark"] = query.value(5).toString();
    }
    return obj;
}

/**
* @brief 查找多镜头
**/
QJsonObject JStdLensDb::search(const QString &lensCode)
{
    QString strCode = lensCode.trimmed();
    QJsonObject obj;
//    QString str = QString("SELECT * FROM StdLens WHERE LensCode LIKE '%%1%';").arg(strCode);
    QString str = QString("SELECT * FROM StdLens WHERE LensCode = '%1';").arg(strCode);
    QSqlQuery query(str);
    while (query.next())
    {
        obj["LensCode"] = query.value(1).toString();
        obj["LensState"] = query.value(2).toBool();
        obj["FileName"] = query.value(3).toString();
        obj["Time"] = query.value(4).toString();
        obj["Remark"] = query.value(5).toString();
    }
    return obj;
}

}
