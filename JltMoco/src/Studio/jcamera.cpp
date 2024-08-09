#include "Studio/jcamera.h"
#include "Studio/jcamerainstall.h"
#include "Interface/abstractcamera.h"
#include "Studio/studiocontroller.h"

#include <QMutex>
#include <QDebug>
#include <QJsonArray>
#include <QVideoFrame>
#include <QTransform>
#include <QSettings>

using namespace jltmoco;

JCamera* JCamera::handle = Q_NULLPTR;

JCamera* JCamera::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JCamera;
        mutex.unlock();
    }
    return handle;
}

JCamera::JCamera()
{
    this->pluginHandle = nullptr;
    this->connected = false;
    this->mTransferState = 0;
    this->mCameraName = "undefined";
    this->downloadDir.clear();
}

/**
 * @brief 初始化
 */
void JCamera::init()
{
    QObject *obj = loadPlugin("Plugins/CameraDevice.dll");
    if(obj)
    {
        this->pluginHandle = qobject_cast<AbstractCamera *>(obj);
        this->pluginHandle->registerFunc(std::bind(&JCamera::pluginCallBack,this,std::placeholders::_1));
        this->pluginHandle->setup();
    }
}

/**
 * @brief 释放
 */
void JCamera::release()
{
    if(pluginHandle)
    {
        this->pluginHandle->uninstall();
    }
    JCameraInstall::getInstance()->release();
}

void JCamera::setProperty(int key,int index)
{
    QJsonObject obj;
    obj["code"] = 1;
    obj["deviceId"] = 2;
    QJsonArray datas;
    QJsonObject cmd;
    cmd["key"] = key;
    cmd["currentIndex"] = index;
    datas.append(cmd);
    obj["data"] = datas;
    this->sendCommandData(obj);
}

void JCamera::setDownloadDirectory(const QString &dir)
{
    QJsonObject obj;
    obj["code"] = 2;
    obj["deviceId"] = 2;
    obj["data"] = dir;
    this->sendCommandData(obj);
}

void JCamera::shooting(int mode)
{
    QJsonObject obj;
    obj["code"] = 3;
    obj["deviceId"] = 2;
    obj["data"] = mode;
    this->sendCommandData(obj);
}

void JCamera::s1Shooting(bool mode)
{
    QJsonObject obj;
    obj["code"] = 3;
    obj["deviceId"] = 2;
    obj["data"] = mode==true?2:3;
    this->sendCommandData(obj);
}

void JCamera::filmRecording(bool state)
{
    QJsonObject obj;
    obj["code"] = 4;
    obj["deviceId"] = 2;
    obj["data"] = state;
    this->sendCommandData(obj);
}

void JCamera::quickFormat()
{
    QJsonObject obj;
    obj["code"] = 5;
    obj["deviceId"] = 2;
    this->sendCommandData(obj);
}

void JCamera::downloadEndFile()
{
    QJsonObject obj;
    obj["code"] = 7;
    obj["deviceId"] = 2;
    this->sendCommandData(obj);
}

void JCamera::realTimeImageDownload(const QString &fileName)
{
    QJsonObject obj;
    obj["code"] = 8;
    obj["deviceId"] = 2;
    obj["data"] = fileName;
    this->sendCommandData(obj);
}

void JCamera::setFocusPosition(qreal x,qreal y,int mode)
{
    QJsonObject obj;
    obj["code"] = 10;
    obj["deviceId"] = 2;
    obj["x"] = x;
    obj["y"] = y;
    obj["mode"] = mode;
    this->sendCommandData(obj);
}

void JCamera::nearFarOperation(int value)
{
    QJsonObject obj;
    obj["code"] = 11;
    obj["deviceId"] = 2;
    obj["step"] = value;
    this->sendCommandData(obj);
}

void JCamera::zoomOperation(int value)
{
    QJsonObject obj;
    obj["code"] = 12;
    obj["deviceId"] = 2;
    obj["step"] = value;
    this->sendCommandData(obj);
}

/**
 * @brief 返回状态数据
 * @return QJsonObject
 */
QJsonObject JCamera::getStatusData()
{
    QJsonObject root;
    if(pluginHandle){
        root = pluginHandle->getStatusData();
    }
    root["loaded"] = getLoaded();
    root["power"] = getPower();
    root["deviceId"] = 2;
    this->setConnected(getLoaded());
    this->setState(root["state"].toInt());
    return root;
}


/**
 * @brief Server->Client->setStatusData
 * @param obj
 */
void JCamera::setStatusData(const QJsonObject &obj)
{
    int code = obj["code"].toInt();
    //相机属性改变
    if(code == 0)
    {
        this->setPower(obj["power"].toInt());
        this->setLoaded(obj["loaded"].toBool());
        this->setConnected(obj["connected"].toBool());
        this->setState(obj["state"].toInt());
    }
    else if(code == 1)
    {
        this->propUpdate(obj);
    }
    else if(code == 2)
    {
        this->setCameraName(obj["cameraName"].toString());
    }
    else if(code == 3)
    {
        emit downloadDirSetResult(obj["result"].toBool());
        this->setDownloadDir(obj["downloadDir"].toString());
    }
    else if(code == 4)
    {
        this->setDownloadFileName(obj["fileName"].toString());
    }
    else if(code == 5)
    {
        int progress = obj["progress"].toInt();
        this->setTransferState(progress);
        if(progress == 0){
            this->setDownloadFileName(obj["fileName"].toString());
        }
    }
}

/**
 * @brief Server->Client->设置静态数据
 * @param obj
 */
void JCamera::setStaticData(const QJsonObject &obj)
{
    ;
}

/**
 * @brief 相机指令处理
 * @param data
 */
void JCamera::sendCommandData(const QJsonObject &data)
{
    if(StudioController::getInstance()->getControllerType() == StudioController::RemoteControllerOnly)
    {
        emit dataChanged(data);
    }
    else
    {
        if(getLoaded() && pluginHandle)
        {
            this->pluginHandle->parseUserCommand(data);
        }
    }
}

/**
 * @brief 设置连接状态
 * @param value
 */
void JCamera::setConnected(bool value)
{
    if(value != connected)
    {
        this->connected = value;
        emit connectedChanged();
    }
}

/**
 * @brief 重加载相机属性
 */
void JCamera::reloadProperties()
{
    if(!getLoaded())
        return;

    if(pluginHandle)
    {
        pluginHandle->updatePropertys();
    }
}

/**
 * @brief 指令处理
 * @param obj
 */
void JCamera::commandProcessing(const QJsonObject &obj)
{
    if(!getLoaded() || !pluginHandle)
        return;
    pluginHandle->parseUserCommand(obj);
}

/**
 * @brief 插件回调
 * @param obj
 */
void JCamera::pluginCallBack(const QJsonObject &obj)
{
    if(obj["code"].toInt() == 0x2000)
    {
        QJsonObject data = obj["data"].toObject();
        //相机属性改变
        int code = data["code"].toInt();
        if(code == 1)
        {
            this->propUpdate(data);
        }
        else if(code == 2)
        {
            this->setCameraName(data["cameraName"].toString());
        }
        else if(code == 3)
        {
            this->setDownloadDir(data["downloadDir"].toString());
            emit downloadDirSetResult(data["result"].toBool());
        }
        else if(code == 4)
        {
            this->setDownloadFileName(data["fileName"].toString());
        }
        else if(code == 5)
        {
            int progress = data["progress"].toInt();
            this->setTransferState(progress);
            if(progress == 0){
                this->setDownloadFileName(data["fileName"].toString());
            }
        }
    }
    emit dataChanged(obj);
}

void JCamera::setCameraName(const QString &name)
{
    this->mCameraName = name;
    emit cameraNameChanged();
}

void JCamera::setDownloadDir(const QString &name)
{
    if(downloadDir != name)
    {
        if(downloadDir.isEmpty())
            emit showDownloadDirWindow();
        this->downloadDir = name;
        emit downloadDirChanged();
    }
}

void JCamera::setTransferState(int state)
{
    if(mTransferState != state)
    {
        this->mTransferState = state;
        emit transferStateChanged();
    }
}

void JCamera::setDownloadFileName(const QString &fileName)
{
    if(mDownloadFileName != fileName)
    {
        this->mDownloadFileName = fileName;
        emit downloadFileNameChanged();
    }
}

/**
 * @brief 相机属性更新
 * @param data
 */
void JCamera::propUpdate(const QJsonObject &data)
{
    QJsonArray props = data["properties"].toArray();
    for (int i = 0; i < props.size(); i++)
    {
        QJsonObject prop = props.at(i).toObject();
        int key = prop["key"].toInt();
        switch (key) {
        case 1797:this->recordingState.setContent(prop);break;
        case 1829:this->remoteMode.setContent(prop);break;
        case 256:this->fNumber.setContent(prop);break;
        case 259:this->shutterSpeed.setContent(prop);break;
        case 260:this->isoSensitivity.setContent(prop);break;
        case 261:this->programMode.setContent(prop);break;
        case 262:this->fileType.setContent(prop);break;
        case 263:this->jpegQuality.setContent(prop);break;
        case 264:this->whiteBalance.setContent(prop);break;
        case 265:this->focusMode.setContent(prop);break;
        case 295:this->movieFileFormat.setContent(prop);break;
        case 296:this->movieRecording.setContent(prop);break;
        case 297:this->movieRecordingFrameRate.setContent(prop);break;
        case 305:this->rawFileCompressionType.setContent(prop);break;
        case 270:this->driveMode.setContent(prop);break;
        case 275:this->focusArea.setContent(prop);break;
        case 257:this->mExposureBiasAompensation.setContent(prop);break;
        case 258:this->mFlashAompensation.setContent(prop);break;
        case 1794:this->mBatteryRemaining.setContent(prop);break;
        case 319:this->mDispMode.setContent(prop);break;
        case 273:this->mAspectRatio.setContent(prop);break;
        case 287:this->mNearFar.setContent(prop);break;
        case 293:this->mZoomSetting.setContent(prop);break;
        case 1822:this->mZoomOperationStatus.setContent(prop);break;
        case 1828:this->mZoomRange.setContent(prop);break;
        case 1893:
        {
            this->mLensName = prop["value"].toString();
            emit lensNameChanged();
            break;
        }
        case 280:this->mLiveViewDisplayEffect.setContent(prop);break;
        case 1288:this->mLiveViewImageQuality.setContent(prop);break;
        default:
            break;
        }
    }
}
