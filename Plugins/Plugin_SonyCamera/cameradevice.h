/*
* 软件名称   BOBS 操作系统
* 版权所有   上海倔老头智能科技有限公司
* 本软件由上海倔老头智能科技有限公司开发并且开源 使用GPL V3（GNU General Public License） 开源协议
* 如收费请告知他人本软件可免费获得并说明收费缘由（如服务费）
* 联系方式
* vx 号    z1273305587
* 电话号   15536506659
* bilibili： 倔老头的会议室  UID: 3546726275221982
* 软件开源地址 https://github.com/oldbabe/ob_os
*
* Software name BOBS Operating system
*
* Copyright (C) 2024  Shanghai OldBaby technology Co., LTD
*
* This program is free software;you can redistribute it and/or modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation;either version 3 of the License, or (at your option) any later version.
*
* If there is a charge, please inform others that the software is available free of charge and explain the reason for the charge (e.g. service fee).
* Contact information
* Open source address https://github.com/oldbabe/ob_os
*/
#ifndef CAMERADEVICE_H
#define CAMERADEVICE_H

#include <atomic>
#include <cstdint>
#include <CameraRemote_SDK.h>
#include <IDeviceCallback.h>
#include <CrDefines.h>
#include <QJsonObject>

#include "propertyvaluetable.h"

namespace jltmoco
{

using namespace SCRSDK;

enum class ConnectionType
{
    UNKNOWN,
    NETWORK,
    USB
};

struct UsbInfo
{
    std::int16_t pid;
};

class CRFolderInfos
{
public:
    CRFolderInfos(SCRSDK::CrMtpFolderInfo* info, int32_t nums)
        : pFolder(info)
        , numOfContents(nums)
    {};
    ~CRFolderInfos()
    {
        delete[] pFolder->folderName;
        pFolder->folderName = NULL;
        delete pFolder;
        pFolder = NULL;
    };
public:
    SCRSDK::CrMtpFolderInfo* pFolder;
    int32_t numOfContents;
};

typedef std::vector<CRFolderInfos*> MtpFolderList;
typedef std::vector<SCRSDK::CrMtpContentsInfo*> MtpContentsList;

// Forward declarations
struct CRLibInterface;

class WorkerThread;
class CameraDevice :public IDeviceCallback
{
public:
    CameraDevice(WorkerThread *parent,std::int32_t no, CRLibInterface const* cr_lib, ICrCameraObjectInfo const* camera_info);
    ~CameraDevice();

    bool connect(CrSdkControlMode openMode, CrReconnectingSet reconnect);
    bool isConnected() const;
    int getConnectMode();
    bool disconnect();
    bool release();

    void updateSavePath(const QString &path,const QString &prefix = "camera_");
    bool set_save_info(const QString &path,const QString &prefix = "camera_") const;
    QString getLastFileAddress() const;

    void updateFrameData();
    int realTimeImage(const QString &fileName) const;

    void capture_image() const;
    void s1_shooting(bool) const;
    void af_shutter() const;
    void af_capture_image() const;

    void execute_movie_rec(bool toggle);
    void execute_quickFormat_slot1();
    void set_af_area_position(int x, int y);

    int getContentsSize();
    int downloadIndexFile(int index);
    QString getIndexFileName(int index);
    int pullContents(SCRSDK::CrContentHandle content);
    QJsonObject getContentsListData(int index,int count);

    void load_properties(CrInt32u num = 0, CrInt32u* codes = nullptr);

    void setExposureProgramMode(int index);
    void setFNumber(int index);
    void setShutterSpeed(int index);
    void setIso(int index);
    void setWhiteBalance(int index);
    void setImageFileType(int index);
    void setJpegQuality(int index);
    void setMovieFileType(int index);
    void setMovieRecordType(int index);
    void setMovieRecordFrameRota(int index);
    void setFocusMode(int index);
    void setDriveMode(int index);
    void setRawFileCompressionType(int index);
    void setFoucsArea(int index);
    void setExposureBiasCompensation(int index);
    void setFlashCompensation(int index);
    void setDispMode(int index);
    void setAspectRatio(int index);
    void setZoomSetting(int index);
    void nearFarOperation(int step);
    void zoomOperation(int step);
    void setLiveViewDisplayEffect(int index);
    void setLiveViewImageQuality(int index);

public:
    virtual void OnConnected(DeviceConnectionVersioin version) override;
    virtual void OnDisconnected(CrInt32u error) override;
    virtual void OnPropertyChanged() override;
    virtual void OnLvPropertyChanged() override;
    virtual void OnCompleteDownload(CrChar* filename, CrInt32u type) override;
    virtual void OnWarning(CrInt32u warning) override;
    virtual void OnWarningExt(CrInt32u warning, CrInt32 param1, CrInt32 param2, CrInt32 param3) override;
    virtual void OnError(CrInt32u error)override;
    virtual void OnPropertyChangedCodes(CrInt32u num, CrInt32u* codes) override;
    virtual void OnLvPropertyChangedCodes(CrInt32u num, CrInt32u* codes) override;
    virtual void OnNotifyContentsTransfer(CrInt32u notify, CrContentHandle handle, CrChar* filename = 0) override;

private:
    CRLibInterface const* m_cr_lib;
    std::int32_t m_number;
    SCRSDK::ICrCameraObjectInfo* m_info;
    ConnectionType m_conn_type;
    UsbInfo m_usb_info;
    cli::PropertyValueTable m_prop;
    bool m_spontaneous_disconnection;
    std::int64_t m_device_handle;
    std::atomic<bool> m_connected;
    std::string m_fingerprint;
    std::string m_userPassword;
    SCRSDK::CrSdkControlMode m_modeSDK;
    MtpFolderList   m_foldList;
    MtpContentsList m_contentList;

    WorkerThread *mThread;
};


inline errno_t MemCpyEx(void* result, const void* source, size_t type_size)
{
#if (defined(_WIN32) || defined(_WIN64))
    return memcpy_s(result, type_size, source, type_size);
#else
    std::memcpy(result, source, type_size);
    return 0;
#endif
}


}



#endif // CAMERADEVICE_H
