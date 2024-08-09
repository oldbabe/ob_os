#include "Studio/deviceabstrcat.h"
#include <QMutex>
#include <QDebug>
#include <QPluginLoader>
#include "jltmoco.h"

DeviceAbstract::DeviceAbstract()
{
    this->mState = 0;
    this->mLoaded = false;
    this->mPower = jltmoco::DeviceCtrlPower_User;
}

QObject *DeviceAbstract::loadPlugin(const QString &fileName)
{
    QPluginLoader loader(fileName);
    QObject *obj = loader.instance();
    this->setLoaded(loader.isLoaded());
    this->mPluginMetaData = loader.metaData();
    return obj;
}

void DeviceAbstract::setLoaded(bool value)
{
    if(mLoaded != value)
    {
        this->mLoaded = value;
        emit loadedChanged();
    }
}

void DeviceAbstract::setState(int value)
{
    if(mState != value)
    {
        this->mState = value;
        emit stateChanged();
    }
}

void DeviceAbstract::setPower(int value)
{
    if(mPower != value)
    {
        this->mPower = value;
        emit powerChanged();
    }
}

QJsonObject DeviceAbstract::getPluginMetaData() const
{
    return mPluginMetaData;
}
