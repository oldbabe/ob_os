#include "cameraplugin.h"

#include <QDebug>

using namespace jltmoco;

CameraPlugin::CameraPlugin()
{
    this->mThread = new WorkerThread;
    QObject::connect(mThread,&WorkerThread::callbackChanged, this,&CameraPlugin::mThreadCallbackChanged);
}

/**
    * @brief  注册回调函数
**/
void CameraPlugin::registerFunc(std::function<void (const QJsonObject &)> func)
{
    this->cameraFunc = func;
}

/**
* @brief 安装服务
**/
void CameraPlugin::setup()
{
    this->mThread->runStart();
}

/**
* @brief 卸载服务
**/
void CameraPlugin::uninstall()
{
    this->mThread->runStop();
    this->mThread->deleteLater();
}

/**
* @brief 相机连接
* @param flag =false遥控模式 =true内容模式 默认=false
**/
void CameraPlugin::connect(bool flag)
{
    ;
}
/**
* @brief 相机连接状态返回
**/
bool CameraPlugin::isConnected()
{
    return false;
}
/**
* @brief 相机断开
**/
void CameraPlugin::disconnect()
{
    ;
}

/**
    * @brief 获得设备状态数据
**/
QJsonObject CameraPlugin::getStatusData()
{
    return mThread->getStatusData();
}

/**
* @brief 更新相机的属性
**/
void CameraPlugin::updatePropertys()
{
    QJsonObject obj;
    obj["code"] = -1;
    this->mThread->appendCommand(obj);
}
/**
 * @brief 用户质量解析
 * @param cmd
 */
void CameraPlugin::parseUserCommand(const QJsonObject &cmd)
{
    this->mThread->appendCommand(cmd);
}

/**
 * @brief 设备线程数据回调
 * @param data
 */
void CameraPlugin::mThreadCallbackChanged(const QJsonObject &data)
{
    this->cameraFunc(data);
}
