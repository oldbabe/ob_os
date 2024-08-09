#include "Core/jsessionmodel.h"
#include "Session/jsession.h"
#include <QJsonObject>
#include <QQmlEngine>

namespace jltmoco
{

JSessionModel::JSessionModel(QObject *parent)
    : QAbstractListModel{parent}
{
    this->mSession = NULL;
    this->mScriptList.clear();
    this->mRoleName.insert(Qt::UserRole,"fileName");
    this->mRoleName.insert(Qt::UserRole+1,"scriptType");
    this->mRoleName.insert(Qt::UserRole+2,"changed");
}

int JSessionModel::rowCount(const QModelIndex &parent) const
{
    return mScriptList.count();
}

QVariant JSessionModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(mScriptList.isEmpty())
        return QVariant();
    if(index.row() >= mScriptList.count() || index.row() < 0)
        return QVariant();

    if(role == Qt::UserRole)
        return mScriptList.at(index.row())->getFileName();
    else if(role == Qt::UserRole+1)
        return mScriptList.at(index.row())->getScriptType();
    else if(role == Qt::UserRole+2)
        return mScriptList.at(index.row())->getChanged();

    return QVariant();
}

bool JSessionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
    if(mScriptList.isEmpty())
        return false;
    if(index.row() < 0 || index.row() >= mScriptList.count())
        return false;

    if(role == Qt::UserRole)
        mScriptList[index.row()]->setFileName(value.toString());
    else if(role == Qt::UserRole+1)
        mScriptList[index.row()]->setScriptType(value.toInt());
    else if(role == Qt::UserRole+2)
        mScriptList[index.row()]->setChanged(value.toBool());

    emit dataChanged(index,index,QList<int>()<<role);
    return true;
}

QHash<int, QByteArray> JSessionModel::roleNames() const
{
    return mRoleName;
}

void JSessionModel::clear()
{
    beginResetModel();
    qDeleteAll(mScriptList);
    mScriptList.clear();
    endResetModel();
}

JScript* JSessionModel::getScript(int index) const
{
    return mScriptList[index];
}

void JSessionModel::setSession(JSession *session)
{
    this->mSession = session;
}

int JSessionModel::indexOf(const QString &fileName) const
{
    for (int var = 0; var < mScriptList.size(); ++var)
    {
        JScript* script = mScriptList[var];
        if(script->getFileName()==fileName)
            return var;
    }
    return -1;
}

void JSessionModel::updateList(const QStringList &files)
{
    beginResetModel();
    QList<JScript*> list;
    foreach (const QString &fileName, files)
    {
        int position = indexOf(fileName);
        if(position != -1)
        {
            list.append(mScriptList.takeAt(position));
        }
        else
        {
            //创建脚本对象
            JScript* script = new JScript();
            script->setFileName(fileName);
            //脚本内容改变后更新JSessionModel数据
            connect(script,&JScript::fileNameChanged,this,[=]{
                int row = mScriptList.indexOf(script);
                emit dataChanged(index(row),index(row),QList<int>()<<Qt::UserRole);
            });
            connect(script,&JScript::scriptTypeChanged,this,[=]{
                int row = mScriptList.indexOf(script);
                emit dataChanged(index(row),index(row),QList<int>()<<Qt::UserRole+1);
            });
            connect(script,&JScript::changedChanged,this,[=]{
                int row = mScriptList.indexOf(script);
                emit dataChanged(index(row),index(row),QList<int>()<<Qt::UserRole+2);
            });
            //保证qml调用后不删除
            QQmlEngine::setObjectOwnership(script, QQmlEngine::CppOwnership);
            list.append(script);
        }
    }
    //交换
    this->mScriptList.swap(list);

    //删除不存在脚本内存
    foreach (JScript* script, list) {
        if(script == mSession->getCurrentScript())
            mSession->setCurrentScript(NULL);

        script->deleteLater();
    }

    endResetModel();
}

}

