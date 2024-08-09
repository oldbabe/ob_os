#include "workerthread.h"
#include "cameradevice.h"
#include <QImage>

#include <QStandardPaths>
#include <QDebug>
#include <QJsonArray>

#include <QUuid>
#include <windows.h>
#include <SetupAPI.h>

namespace SDK = SCRSDK;
using namespace jltmoco;
//using namespace cv;

//连接系统库-读取 系统设备管理器 内容
#pragma comment(lib, "setupapi.lib")

WorkerThread::WorkerThread()
{
    this->runFlag = false;
    this->realTimeImageEnable = false;
    this->connectedMode = 0;
    this->downloadDir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    this->statusJson["connected"] = false;
    this->setDataState(DeviceStatus_Null);
}

void WorkerThread::runStart()
{
    this->runFlag = true;
    this->start();
}

void WorkerThread::runStop()
{
    this->runFlag = false;
    this->wait();
}

void WorkerThread::appendCommand(const QJsonObject &cmd)
{
    this->commandList.append(cmd);
}

void WorkerThread::callbackMsg(QJsonObject &data)
{
    QJsonObject root;
    root["code"] = 0x2000;

    data["deviceId"] = 2;

    root["data"] = data;
    emit callbackChanged(root);
}

void WorkerThread::setTransferState(int state,const QString &fileName)
{
    QJsonObject data;
    data["code"] = 5;
    data["fileName"] = fileName;
    data["progress"] = state;
    this->callbackMsg(data);
    this->mTransferState = state;
}

void WorkerThread::run()
{
    SDK::Init();
   // CrInt32u version = SDK::GetSDKVersion();
   // int major = (version & 0xFF000000) >> 24;
   // int minor = (version & 0x00FF0000) >> 16;
   // int patch = (version & 0x0000FF00) >> 8;
   // qDebug() << QString("ver %1.%2.%3").arg(major).arg(minor).arg(patch);

    //查找计数器
    quint8 lookingCounter = 0;
    //skipWaitting 跳过设备查找的等待时间
    bool skipWaitting = true;
    //sony camera uuid
    QUuid sonyClassGuid("{ecfb0cfd-74c4-4f52-bbf7-343461cd72ac}");
    while(runFlag)
    {
        //查找循环等待时间
        if(skipWaitting)
        {
            skipWaitting = false;
        }
        else
        {
            QThread::msleep(3000);
        }
        //查找状态更新
        if(lookingCounter >= 15){
            this->setDataState(DeviceStatus_LookingTimeout);
        }else{
            lookingCounter++;
            this->setDataState(DeviceStatus_Looking);
        }

        statusJson["connected"] = false;

        //获取设备信息的集合
        HDEVINFO hdevinfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
        if (hdevinfo != INVALID_HANDLE_VALUE)
        {
            DWORD MemberIndex = 0;
            SP_DEVINFO_DATA sp_devinfo_data;
            //内存填充
            ZeroMemory(&sp_devinfo_data, sizeof(sp_devinfo_data));
            sp_devinfo_data.cbSize = sizeof(sp_devinfo_data);
            //读取设备的信息数据
            while(SetupDiEnumDeviceInfo(hdevinfo, MemberIndex, &sp_devinfo_data) && runFlag)
            {
                QUuid devClassGuid(sp_devinfo_data.ClassGuid.Data1,sp_devinfo_data.ClassGuid.Data2,sp_devinfo_data.ClassGuid.Data3,
                                sp_devinfo_data.ClassGuid.Data4[0],
                                sp_devinfo_data.ClassGuid.Data4[1],
                                sp_devinfo_data.ClassGuid.Data4[2],
                                sp_devinfo_data.ClassGuid.Data4[3],
                                sp_devinfo_data.ClassGuid.Data4[4],
                                sp_devinfo_data.ClassGuid.Data4[5],
                                sp_devinfo_data.ClassGuid.Data4[6],
                                sp_devinfo_data.ClassGuid.Data4[7]);
                if(devClassGuid == sonyClassGuid)
                {
                    this->setDataState(DeviceStatus_Connecting);
                    //flag:连接设备
                    SCRSDK::ICrEnumCameraObjectInfo* devList = nullptr;
                    auto enum_status = SDK::EnumCameraObjects(&devList);
                    if (CR_FAILED(enum_status) || devList == nullptr)
                    {
                        qDebug() << "devList error 1";
                        break;
                    }
                    if(devList->GetCount() < 1)
                    {
                        qDebug() << "devList error 2";
                        break;
                    }
                    //实例化第一个相机设备
                    auto* camera_info = devList->GetCameraObjectInfo(0);
                    CameraDevice *sonyCamera = new CameraDevice(this,1,nullptr,camera_info);
                    //连接
                    if(connectedMode == 0)
                        statusJson["connected"] = sonyCamera->connect(SDK::CrSdkControlMode_Remote, SDK::CrReconnecting_OFF);
                    else
                        statusJson["connected"] = sonyCamera->connect(SDK::CrSdkControlMode_ContentsTransfer, SDK::CrReconnecting_OFF);
                    //阻塞等待连接
                    QThread::msleep(1000);
                    if(sonyCamera->isConnected())
                    {
                        QJsonObject root;
                        this->execSetDownloadDirectory(sonyCamera,downloadDir);
                        if(connectedMode == 1)
                        {
                            root["code"] = 7;
                            commandList.append(root);
                        }

                        root["code"] = 2;
                        root["cameraName"] = QString::fromStdWString(std::basic_string(camera_info->GetModel()));
                        this->callbackMsg(root);
                    }

                    devList->Release();

                    //就绪->等待指令
                    while (sonyCamera->isConnected() && runFlag)
                    {
                        this->setDataState(DeviceStatus_Ready);
                        this->execCommand(sonyCamera);
                        this->execGetRealTimeImage(sonyCamera);
                        QThread::msleep(5);
                    }
                    this->setDataState(DeviceStatus_Closing);
                    //断开连接
                    if(sonyCamera->isConnected())
                    {
                        if (!sonyCamera->disconnect())
                        {
                            sonyCamera->disconnect();// try again
                        }
                    }
                    //释放相机
                    sonyCamera->release();
                    skipWaitting = true;
                    lookingCounter = 0;
                    break;
                }
                MemberIndex++;
            }
        }
    }

    //SDK 释放
    SDK::Release();
}

void WorkerThread::setDataState(DeviceStatus state)
{
    this->statusJson["state"] = state;
}

/**
 * @brief 指令执行
 */
void WorkerThread::execCommand(CameraDevice *camera)
{
    if(commandList.isEmpty()){
        return;
    }

    QJsonObject cmd = commandList.takeFirst();
    switch (cmd["code"].toInt())
    {
    case -1:camera->load_properties();
        break;
    case 1:execPropSetting(camera,cmd);
        break;
    case 2:this->execSetDownloadDirectory(camera,cmd["data"].toString());
        break;
    case 3:this->execShooting(camera,cmd["data"].toInt());
        break;
    case 4:camera->execute_movie_rec(cmd["data"].toBool());
        break;
    case 5:camera->execute_quickFormat_slot1();
        break;
    case 7:this->execDownloadEndFile(camera);
        break;
    case 8:this->execRealTimeImageDownload(camera,cmd["data"].toString());
        break;
    case 9:this->realTimeImageEnable = cmd["data"].toBool();
        break;
    case 10:this->execSetFocusPosition(camera,cmd["x"].toDouble(),cmd["y"].toDouble(),cmd["mode"].toInt());
        break;
    case 11:
        camera->nearFarOperation(cmd["step"].toInt());
        break;
    case 12:
        camera->zoomOperation(cmd["step"].toInt());
        break;
    default:
        break;
    }
}

/**
 * @brief 属性设置
 * @param obj
 */
void WorkerThread::execPropSetting(CameraDevice *camera,const QJsonObject &obj)
{
    QJsonArray datas = obj["data"].toArray();
    for(int i = 0; i < datas.count(); i++)
    {
        QJsonObject item = datas.at(i).toObject();
        int key = item["key"].toInt();
        int index = item["currentIndex"].toInt();
        int delayTime = item["delayTime"].toInt();
        switch (key)
        {
        case SDK::CrDevicePropertyCode::CrDeviceProperty_ExposureProgramMode:
            camera->setExposureProgramMode(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_FocusMode:
            camera->setFocusMode(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_FNumber:
            camera->setFNumber(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSpeed:
            camera->setShutterSpeed(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_IsoSensitivity:
            camera->setIso(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_FileType:
            camera->setImageFileType(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_JpegQuality:
            camera->setJpegQuality(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_WhiteBalance:
            camera->setWhiteBalance(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_File_Format:
            camera->setMovieFileType(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_Setting:
            camera->setMovieRecordType(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_FrameRateSetting:
            camera->setMovieRecordFrameRota(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_DriveMode:
            camera->setDriveMode(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_RAW_FileCompressionType:
            camera->setRawFileCompressionType(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_FocusArea:
            camera->setFoucsArea(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_FlashCompensation:
            camera->setFlashCompensation(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_ExposureBiasCompensation:
            camera->setExposureBiasCompensation(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_DispMode:
            camera->setDispMode(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_AspectRatio:
            camera->setAspectRatio(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Setting:
            camera->setZoomSetting(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_LiveViewDisplayEffect:
            camera->setLiveViewDisplayEffect(index);
            break;
        case SDK::CrDevicePropertyCode::CrDeviceProperty_LiveView_Image_Quality:
            camera->setLiveViewImageQuality(index);
            break;
        default:
            break;
        }
        QThread::msleep(delayTime);
    }
}

void WorkerThread::execSetDownloadDirectory(CameraDevice *camera,const QString &dir)
{
    bool res = camera->set_save_info(dir);
    if(res)
    {
        this->downloadDir = dir;
    }
    QJsonObject data;
    data["code"] = 3;
    data["result"] = res;
    data["downloadDir"] = downloadDir;
    this->callbackMsg(data);
}

void WorkerThread::execShooting(CameraDevice *camera,int mode)
{
    //直接拍摄
    if(mode == 0)
        camera->capture_image();
    //自动AF
    else if(mode == 1)
        camera->af_shutter();
    //半按快门(按下)
    else if(mode == 2)
        camera->s1_shooting(true);
    //半按快门(松开)
    else if(mode == 3)
        camera->s1_shooting(false);
}

void WorkerThread::execDownloadEndFile(CameraDevice *camera)
{
    if(connectedMode == 0)
    {
        this->connectedMode = 1;
        camera->disconnect();
    }
    else
    {
        QJsonObject data;
        data["code"] = 5;
        data["progress"] = 3;
        this->callbackMsg(data);
        int len = camera->getContentsSize();
        if(len <= 0)
        {
            //相机文件列表是空的
            data["progress"] = -2;
            this->callbackMsg(data);
        }
        else
        {
            int error = camera->downloadIndexFile(len-1);
            if(error != 0)
            {
                QJsonObject data;
                data["code"] = 5;
                data["progress"] = error;
                this->callbackMsg(data);
            }
            else
            {
                this->mTransferState = 1;
                while(runFlag && mTransferState == 1)
                {
                    QThread::msleep(10);
                }
                QThread::msleep(500);
                this->connectedMode = 0;
                camera->disconnect();
            }
        }
    }
}

void WorkerThread::execRealTimeImageDownload(CameraDevice *camera,const QString &fileName)
{
    int res = camera->realTimeImage(fileName);
    QJsonObject data;
    data["code"] = 6;
    data["fileName"] = fileName;
    data["result"] = res;
    this->callbackMsg(data);
}

void WorkerThread::execSetFocusPosition(CameraDevice *camera,qreal x,qreal y,int mode)
{
    int sX = 639*x;
    int sY = 478*y;
    camera->set_af_area_position(sX,sY);
    if(mode == 1)
    {
        camera->s1_shooting(true);
        QThread::msleep(500);
        camera->s1_shooting(false);
        QThread::msleep(100);
    }
    else if(mode == 2)
    {
        camera->af_shutter();
    }
}

void WorkerThread::execGetRealTimeImage(CameraDevice *camera)
{
    if(realTimeImageEnable){
        camera->updateFrameData();
    }
}
