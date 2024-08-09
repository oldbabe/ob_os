#include "cameradevice.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QImage>
#include <QBuffer>
#include "workerthread.h"

namespace SDK = SCRSDK;
using namespace jltmoco;

CameraDevice::CameraDevice(WorkerThread *parent,std::int32_t no, CRLibInterface const* cr_lib, SCRSDK::ICrCameraObjectInfo const* camera_info)
    : m_cr_lib(cr_lib)
    , m_number(no)
{
    this->m_info = SDK::CreateCameraObjectInfo(
        camera_info->GetName(),
        camera_info->GetModel(),
        camera_info->GetUsbPid(),
        camera_info->GetIdType(),
        camera_info->GetIdSize(),
        camera_info->GetId(),
        camera_info->GetConnectionTypeName(),
        camera_info->GetAdaptorName(),
        camera_info->GetPairingNecessity(),
        camera_info->GetSSHsupport()
    );
    this->m_conn_type = ConnectionType::USB;
    this->m_usb_info.pid = m_info->GetUsbPid();
    this->m_device_handle = 0;
    this->m_connected.store(false);
    this->m_modeSDK = SCRSDK::CrSdkControlMode_Remote;
    this->mThread = parent;
}

CameraDevice::~CameraDevice()
{
    if (m_info) m_info->Release();
}


/**
 * @brief 相机连接
 * @param openMode 遥控模式
 * @param reconnect 重新连接设置
 * @return
 */
bool CameraDevice::connect(SCRSDK::CrSdkControlMode openMode, SCRSDK::CrReconnectingSet reconnect)
{
    const char* inputId = "admin";
    m_spontaneous_disconnection = false;
    CrError connect_status = SDK::Connect(m_info, this, &m_device_handle, openMode, reconnect,
                                          inputId, m_userPassword.c_str(), m_fingerprint.c_str(), m_fingerprint.size());
    if (CR_FAILED(connect_status))
    {
        qDebug() << "CameraDevice connect failed";
        return false;
    }
    return true;
}
/**
 * @return 连接状态
 */
bool CameraDevice::isConnected() const
{
    return m_connected.load();
}

/**
 * @brief 返回连接模式
 * @return
 */
int CameraDevice::getConnectMode()
{
    return (int)m_prop.sdk_mode.current;
}

/**
 * @brief 相机断开
 * @return 断开结果
 */
bool CameraDevice::disconnect()
{
    m_spontaneous_disconnection = true;
    auto disconnect_status = SDK::Disconnect(m_device_handle);
    if (CR_FAILED(disconnect_status))
    {
        qDebug() << "CameraDevice disconnect failed";
        return false;
    }
    return true;
}
/**
 * @brief 释放
 * @return 结果
 */
bool CameraDevice::release()
{
    auto finalize_status = SDK::ReleaseDevice(m_device_handle);
    m_device_handle = 0;
    if (CR_FAILED(finalize_status))
    {
        return false;
    }
    return true;
}

/**
 * @brief 设置保存路径
 * @param path
 * @param prefix
 * @return
 */
bool CameraDevice::set_save_info(const QString &path,const QString &) const
{
    QString time1 = QDateTime::currentDateTime().date().toString("yyyyMMdd");
    QString time2 = QTime::currentTime().toString("hhmmss");

    std::wstring data = path.toStdWString();
    const wchar_t* str1 = data.c_str();
    QString pix = time1+time2+"_";
    std::wstring pixdata = pix.toStdWString();
    const wchar_t* str2 = pixdata.c_str();

    auto save_status = SDK::SetSaveInfo(m_device_handle
        , const_cast<wchar_t*>(str1), const_cast<wchar_t*>(str2), -1);

    if (CR_FAILED(save_status))
    {
        qDebug() << "Failed to set camera save path";
        return false;
    }
    return true;
}

/**
 * @brief 更新帧数据
 */
void CameraDevice::updateFrameData()
{
    static CrInt32u frameNumber = 0;

    SDK::CrImageInfo inf;
    auto err = SDK::GetLiveViewImageInfo(m_device_handle, &inf);
    if (CR_FAILED(err))
        return ;

    CrInt32u bufSize = inf.GetBufferSize();
    if (bufSize < 1)
        return ;

    auto* image_data = new SDK::CrImageDataBlock();
    if (!image_data)
        return ;
    CrInt8u* image_buff = new CrInt8u[bufSize];
    if (!image_buff)
    {
        delete image_data;
        return;
    }
    //初始化一块空图
    image_data->SetSize(bufSize);
    image_data->SetData(image_buff);

    err = SDK::GetLiveViewImage(m_device_handle, image_data);
    if (CR_FAILED(err) || frameNumber == image_data->GetFrameNo())
    {
        delete[] image_buff;
        delete image_data;
        return ;
    }

    QImage image = QImage::fromData((uchar *)image_data->GetImageData(),image_data->GetImageSize());


    QByteArray imageData;  		//保存图片数据的字符数组
    QBuffer buffer(&imageData);	//将字符数组与buffer缓存区绑定，以便写入数据
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer,"JPEG");
    buffer.close();

    QJsonObject data;
    data["code"] = 6;
    data["image"] = QString(imageData.toBase64());
    this->mThread->callbackMsg(data);

    frameNumber = image_data->GetFrameNo();
    delete[] image_buff;
    delete image_data;
}

/**
 * @brief 实时图像获取
 * @param fileName
 */
int CameraDevice::realTimeImage(const QString &fileName) const
{
    CrInt32 num = 0;
    SDK::CrLiveViewProperty* property = nullptr;
    auto err = SDK::GetLiveViewProperties(m_device_handle, &property, &num);
    if (CR_FAILED(err))
    {
        return 0;
    }
    SDK::ReleaseLiveViewProperties(m_device_handle, property);

    SDK::CrImageInfo inf;
    err = SDK::GetLiveViewImageInfo(m_device_handle, &inf);
    if (CR_FAILED(err))
    {
        return 0;
    }

    CrInt32u bufSize = inf.GetBufferSize();
    if (bufSize < 1)
    {
        return 0;
    }

    auto* image_data = new SDK::CrImageDataBlock();
    if (!image_data)
    {
        return 0;
    }
    //申请内存
    CrInt8u* image_buff = new CrInt8u[bufSize];
    if (!image_buff)
    {
        delete image_data;
        return 0;
    }
    //初始化一块空图
    image_data->SetSize(bufSize);
    image_data->SetData(image_buff);

    err = SDK::GetLiveViewImage(m_device_handle, image_data);
    if (CR_FAILED(err))
    {
        // FAILED
        delete[] image_buff; // Release
        delete image_data; // Release
        return 0;
    }
    else
    {
        if (0 < image_data->GetSize())
        {
            QFile file(fileName);
            if (file.open(QIODevice::ReadWrite))
            {
                file.write((char*)image_data->GetImageData(), image_data->GetImageSize());
                file.close();

                delete[] image_buff; // Release
                delete image_data; // Release
                return 1;
            }
            delete[] image_buff; // Release
            delete image_data; // Release
            return 0;
        }
        else
        {
            // FAILED
            delete[] image_buff; // Release
            delete image_data; // Release
            return 0;
        }
    }
}

void CameraDevice::capture_image() const
{
    QThread::msleep(35);
    // m_cr_lib->SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_Release, SDK::CrCommandParam_Down);
    SDK::SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_Release, SDK::CrCommandParam_Down);

    // Wait, then send shutter up
    QThread::msleep(35);
    // m_cr_lib->SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_Release, SDK::CrCommandParam_Up);
    SDK::SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_Release, SDK::CrCommandParam_Up);
}

void CameraDevice::s1_shooting(bool flag) const
{
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_S1);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16);

    if(flag)
    {
        prop.SetCurrentValue(SDK::CrLockIndicator::CrLockIndicator_Locked);
    }
    else
    {
        prop.SetCurrentValue(SDK::CrLockIndicator::CrLockIndicator_Unlocked);
    }

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

/**
 * @brief CameraDevice::af_capture_image
 */
void CameraDevice::af_capture_image() const
{

}

void CameraDevice::af_shutter() const
{
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_S1);
    prop.SetCurrentValue(SDK::CrLockIndicator::CrLockIndicator_Locked);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16);
    SDK::SetDeviceProperty(m_device_handle, &prop);

    // Wait, then send shutter down
    QThread::msleep(500);
    SDK::SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_Release, SDK::CrCommandParam::CrCommandParam_Down);

    // Wait, then send shutter up
    QThread::msleep(35);
    SDK::SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_Release, SDK::CrCommandParam::CrCommandParam_Up);

    // Wait, then send shutter up
    QThread::msleep(1000);
    prop.SetCurrentValue(SDK::CrLockIndicator::CrLockIndicator_Unlocked);
    SDK::SetDeviceProperty(m_device_handle, &prop);
}

/**
 * @brief 录制操作
 * @param toggle=true启动
 */
void CameraDevice::execute_movie_rec(bool toggle)
{
    CrInt64u ptpValue = 0;
    if(toggle)
    {
        ptpValue = SDK::CrCommandParam::CrCommandParam_Down;
    }
    else
    {
        ptpValue = SDK::CrCommandParam::CrCommandParam_Up;
    }
    SDK::SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_MovieRecord, (SDK::CrCommandParam)ptpValue);
}


void CameraDevice::execute_quickFormat_slot1()
{
    SDK::SendCommand(m_device_handle, SDK::CrCommandId::CrCommandId_MediaQuickFormat,SDK::CrCommandParam::CrCommandParam_Up);
}

/**
 * @brief 变焦操作
 * @param value
 */
// void CameraDevice::set_zoom_operation(int value)
// {
//     SDK::CrDeviceProperty prop;
//     prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Operation);
//     prop.SetCurrentValue((CrInt64u)value);
//     prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);
//     SDK::SetDeviceProperty(m_device_handle, &prop);
// }

/**
 * @brief 设置焦点位置
 * @param x
 * @param y
 */
void CameraDevice::set_af_area_position(int x, int y)
{
    int x_y = x << 16 | y;

    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_AF_Area_Position);
    prop.SetCurrentValue((CrInt64u)x_y);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt32);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

/**
 * @brief 返回内容列表长度
 * @return
 */
int CameraDevice::getContentsSize()
{
    //确认存储模式是否开启
    std::int32_t nprop = 0;
    SDK::CrDeviceProperty* prop_list = nullptr;
    CrInt32u getCode = SDK::CrDevicePropertyCode::CrDeviceProperty_ContentsTransferStatus;
    SDK::CrError res = SDK::GetSelectDeviceProperties(m_device_handle, 1, &getCode, &prop_list, &nprop);
    bool bExec = false;
    if (CR_SUCCEEDED(res) && (1 == nprop))
    {
        if ((getCode == prop_list[0].GetCode()) && (SDK::CrContentsTransfer_ON == prop_list[0].GetCurrentValue()))
        {
            bExec = true;
        }
        SDK::ReleaseDeviceProperties(m_device_handle, prop_list);
    }
    if (false == bExec)
    {
        //获取内容功能被禁用
        return -1;
    }
    //清空m_foldList 目录缓存
    for (CRFolderInfos* pF : m_foldList)
    {
        delete pF;
    }
    m_foldList.clear();
    //清空m_contentList 目录内容缓存
    for (SCRSDK::CrMtpContentsInfo* pC : m_contentList)
    {
        delete pC;
    }
    //清空缓存
    m_contentList.clear();
    //读取目录列表
    CrInt32u f_nums = 0;//目录数量
    CrInt32u c_nums = 0;//文件数量
    SDK::CrMtpFolderInfo* f_list = nullptr;//目录列表
    SDK::CrError err = SDK::GetDateFolderList(m_device_handle, &f_list, &f_nums);//目录读取
    if (CR_SUCCEEDED(err) && 0 < f_nums)
    {
        if (f_list)
        {
            //更新m_foldList 数据
            for (int i = 0; i < f_nums; ++i)
            {
                auto pFold = new SDK::CrMtpFolderInfo();
                pFold->handle = f_list[i].handle;
                pFold->folderNameSize = f_list[i].folderNameSize;
                CrInt32u lenByOS = sizeof(CrChar) * pFold->folderNameSize;
                pFold->folderName = new CrChar[lenByOS];
                MemCpyEx(pFold->folderName, f_list[i].folderName, lenByOS);
                CRFolderInfos* pCRF = new CRFolderInfos(pFold, 0); // 2nd : fill in later
                m_foldList.push_back(pCRF);
            }
            SDK::ReleaseDateFolderList(m_device_handle, f_list);
        }
        //空目录
        if (0 == m_foldList.size())
        {
            return -2;
        }
        //目录遍历
        MtpFolderList::iterator it = m_foldList.begin();
        for (; it != m_foldList.end(); ++it)
        {
            SDK::CrContentHandle* c_list = nullptr;//内容列表
            //获取目录内容列表
            err = SDK::GetContentsHandleList(m_device_handle, (*it)->pFolder->handle, &c_list, &c_nums);
            if (CR_SUCCEEDED(err) && 0 < c_nums)
            {
                if (c_list)
                {
                    (*it)->numOfContents = c_nums;
                    for (int i = 0; i < c_nums; i++)
                    {
                        SDK::CrMtpContentsInfo* pConntents = new SDK::CrMtpContentsInfo();
                        err = SDK::GetContentsDetailInfo(m_device_handle, c_list[i], pConntents);
                        if (CR_SUCCEEDED(err))
                        {
                            m_contentList.push_back(pConntents);
                        }
                        else
                        {
                            break;
                        }
                    }
                    //释放局部变量
                    SDK::ReleaseContentsHandleList(m_device_handle, c_list);
                }
            }
            if (CR_FAILED(err))
            {
                break;
            }
        }
        return m_contentList.size();
    }
    else if (CR_SUCCEEDED(err) && 0 == f_nums)
    {
        return -3;
    }
    else
    {
        // err
        return -4;
    }
}

/**
 * @brief 下载指定索引文件
 */
int CameraDevice::downloadIndexFile(int index)
{
    if(index > -1 && index < m_contentList.size())
    {
        auto targetHandle = m_contentList[index]->handle;
        return pullContents(targetHandle);
    }
    return -1;
}


QString CameraDevice::getIndexFileName(int index)
{
    if(index > -1 && index < m_contentList.size())
    {
        return QString::fromWCharArray(m_contentList[index]->fileName);
    }
    return "";
}

/**
 * @brief 下载文件
 * @param content
 */
int CameraDevice::pullContents(SDK::CrContentHandle content)
{
    return SDK::PullContentsFile(m_device_handle, content);
}

/**
 * @brief 返回下载文件列表
 */
QJsonObject CameraDevice::getContentsListData(int index,int count)
{
    if(index>m_contentList.size()-1
            || index < 0 || count < 0)
    {
        return QJsonObject();
    }

    QJsonObject root;
    for(int i = index; i < (count+index); i++)
    {
        if(i>(m_contentList.size()-1))
        {
            break;
        }
        QJsonObject total;
        total["name"] = QString::fromWCharArray(m_contentList[i]->fileName);
        root[QString::number(i)] = total;
    }
    return root;
}

void CameraDevice::OnConnected(DeviceConnectionVersioin)
{
    this->m_connected.store(true);
    this->load_properties();
}

void CameraDevice::OnDisconnected(CrInt32u )
{
    this->m_connected.store(false);
}

void CameraDevice::OnPropertyChanged()
{
    ;
}

void CameraDevice::OnLvPropertyChanged()
{
    ;
}

/**
 * @brief 文件下载完成回调
 */
void CameraDevice::OnCompleteDownload(CrChar* recvChar, CrInt32u type)
{
    QJsonObject data;
    data["code"] = 4;
    data["fileName"] = QString::fromWCharArray(recvChar);
    this->mThread->callbackMsg(data);
}

void CameraDevice::OnWarning(CrInt32u warning)
{
    QJsonObject data;
    data["code"] = 8;
    data["data"] = QString::number(warning);
    this->mThread->callbackMsg(data);
}

void CameraDevice::OnWarningExt(CrInt32u warning, CrInt32 param1, CrInt32 param2, CrInt32 param3)
{
    ;
}

/**
 * @brief 相机报错
 */
void CameraDevice::OnError(CrInt32u error)
{
    QJsonObject data;
    data["code"] = 9;
    data["data"] = QString::number(error);
    this->mThread->callbackMsg(data);
}

void CameraDevice::OnPropertyChangedCodes(CrInt32u num, CrInt32u* codes)
{
    this->load_properties(num,codes);
}

void CameraDevice::OnLvPropertyChangedCodes(CrInt32u num, CrInt32u* )
{
    // qDebug() << "OnLvPropertyChangedCodes" << num;
}

/**
 * @brief 文件传输过程
 */
void CameraDevice::OnNotifyContentsTransfer(CrInt32u notify, CrContentHandle , CrChar* fileName)
{
    // Start
    if (SDK::CrNotify_ContentsTransfer_Start == notify)
    {
        this->mThread->setTransferState(1,"");
    }
    // Complete
    else if (SDK::CrNotify_ContentsTransfer_Complete == notify)
    {
        this->mThread->setTransferState(0,QString::fromWCharArray(fileName));
    }
    // Other
    else
    {
        this->mThread->setTransferState(2,"");
    }
}

/**
 * @brief 加载设备属性
 * @param num 需要读取的属性属性
 * @param codes 需要读取的属性编号列表
 */
void CameraDevice::load_properties(CrInt32u num, CrInt32u* codes)
{
    std::int32_t nprop = 0;
    SDK::CrDeviceProperty* prop_list = nullptr;

    m_prop.media_slot1_quick_format_enable_status.writable = -1;
    m_prop.media_slot2_quick_format_enable_status.writable = -1;

    //!属性读取
    SDK::CrError status = SDK::CrError_Generic;
    if (0 == num)
        status = SDK::GetDeviceProperties(m_device_handle, &prop_list, &nprop);//! get all
    else
        status = SDK::GetSelectDeviceProperties(m_device_handle, num, codes, &prop_list, &nprop);//! get dirrerence

    //读取失败
    if (CR_FAILED(status))
    {
        qDebug() << "Failed to get camera propertys";
        return;
    }

    //! 遍历-待读取的属性列表
    if (prop_list && nprop > 0)
    {
        // Got properties list
        QJsonArray array;
        for (std::int32_t i = 0; i < nprop; ++i)
        {
            auto prop = prop_list[i];
            switch (prop.GetCode())
            {
            case SDK::CrDevicePropertyCode::CrDeviceProperty_SdkControlMode:
            {
                m_prop.sdk_mode.parse(prop);
                m_modeSDK = (SDK::CrSdkControlMode)m_prop.sdk_mode.current;
                array.append(m_prop.sdk_mode.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_FNumber:
            {
                m_prop.f_number.parse(prop);
                array.append(m_prop.f_number.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSpeed:
            {
                m_prop.shutter_speed.parse(prop);
                array.append(m_prop.shutter_speed.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_IsoSensitivity:
            {
                m_prop.iso_sensitivity.parse(prop);
                array.append(m_prop.iso_sensitivity.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_ExposureProgramMode:
            {
                m_prop.exposure_program_mode.parse(prop);
                array.append(m_prop.exposure_program_mode.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_FileType:
            {
                m_prop.file_format.parse(prop);
                array.append(m_prop.file_format.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_StillImageQuality:
            {
                m_prop.jpeg_quality.parse(prop);
                array.append(m_prop.jpeg_quality.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_WhiteBalance:
            {
                m_prop.white_balance.parse(prop);
                array.append(m_prop.white_balance.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_File_Format:
            {
                m_prop.movie_file_format.parse(prop);
                array.append(m_prop.movie_file_format.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_Setting:
            {
                m_prop.movie_recording_setting.parse(prop);
                array.append(m_prop.movie_recording_setting.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_FrameRateSetting:
            {
                m_prop.movie_recording_frame_rate_setting.parse(prop);
                array.append(m_prop.movie_recording_frame_rate_setting.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_RAW_FileCompressionType:
            {
                m_prop.raw_compressionFileFormatStill.parse(prop);
                array.append(m_prop.raw_compressionFileFormatStill.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_FocusMode:
            {
                m_prop.focus_mode.parse(prop);
                array.append(m_prop.focus_mode.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_DriveMode:
            {
                m_prop.drive_mode.parse(prop);
                array.append(m_prop.drive_mode.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_FocusArea:
            {
                m_prop.focus_area.parse(prop);
                array.append(m_prop.focus_area.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_ExposureBiasCompensation:
            {
                m_prop.exposure_bias_compensation.parse(prop);
                array.append(m_prop.exposure_bias_compensation.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_FlashCompensation:
            {
                m_prop.flash_compensation.parse(prop);
                array.append(m_prop.flash_compensation.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_BatteryRemain:
            {
                m_prop.batteryRemainingPercent.parse(prop);
                array.append(m_prop.batteryRemainingPercent.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_RecordingState:
            {
                m_prop.movie_recording_status.parse(prop);
                array.append(m_prop.movie_recording_status.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_DispMode:
            {
                m_prop.dispmode.parse(prop);
                array.append(m_prop.dispmode.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_AspectRatio:
            {
                m_prop.aspectRatio.parse(prop);
                array.append(m_prop.aspectRatio.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_NearFar:
            {
                m_prop.focusNearFar.parse(prop);
                array.append(m_prop.focusNearFar.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Setting:
            {
                m_prop.zoom_setting.parse(prop);
                array.append(m_prop.zoom_setting.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Operation_Status:
            {
                m_prop.zoom_operation_status.parse(prop);
                array.append(m_prop.zoom_operation_status.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Speed_Range:
            {
                m_prop.zoom_speed_range.parse(prop);
                array.append(m_prop.zoom_speed_range.toJson());
                break;
            }

            case SDK::CrDevicePropertyCode::CrDeviceProperty_LensModelName:
            {
                CrInt16u* pCurrentStr = prop.GetCurrentStr();
                QJsonObject lensObj;
                lensObj["writable"] = (int)prop.IsSetEnableCurrentValue();
                lensObj["key"] = 1893;
                lensObj["value"] = QString::fromWCharArray((CrChar*)&pCurrentStr[1]);
                array.append(lensObj);
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_LiveViewDisplayEffect:
            {
                m_prop.liveViewDisplayEffect.parse(prop);
                array.append(m_prop.liveViewDisplayEffect.toJson());
                break;
            }
            case SDK::CrDevicePropertyCode::CrDeviceProperty_LiveView_Image_Quality:
            {
                m_prop.live_view_image_quality.parse(prop);
                array.append(m_prop.live_view_image_quality.toJson());
                break;
            }
            default:
                break;
            }
        }
        //释放
        SDK::ReleaseDeviceProperties(m_device_handle, prop_list);
        //回调
        if(!array.isEmpty())
        {
            QJsonObject root;
            root["code"] = 1;
            root["properties"] = array;
            this->mThread->callbackMsg(root);
        }
    }
}

void CameraDevice::setExposureProgramMode(int index)
{
    auto& values = m_prop.exposure_program_mode.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_ExposureProgramMode);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt32Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setFNumber(int index)
{
    auto& values = m_prop.f_number.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_FNumber);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setShutterSpeed(int index)
{
    auto& values = m_prop.shutter_speed.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSpeed);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt32Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);

}

void CameraDevice::setIso(int index)
{
    auto& values = m_prop.iso_sensitivity.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_IsoSensitivity);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt32Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setWhiteBalance(int index)
{
    auto& values = m_prop.white_balance.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_WhiteBalance);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setImageFileType(int index)
{
    auto& values = m_prop.file_format.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_FileType);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setJpegQuality(int index)
{
    auto& values = m_prop.jpeg_quality.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_JpegQuality);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setMovieFileType(int index)
{
    auto& values = m_prop.movie_file_format.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_File_Format);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setMovieRecordType(int index)
{
    auto& values = m_prop.movie_recording_setting.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_Setting);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setMovieRecordFrameRota(int index)
{
    auto& values = m_prop.movie_recording_frame_rate_setting.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_FrameRateSetting);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt8Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}


void CameraDevice::setFocusMode(int index)
{
    auto& values = m_prop.focus_mode.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_FocusMode);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setDriveMode(int index)
{
    auto& values = m_prop.drive_mode.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_DriveMode);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt32Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setRawFileCompressionType(int index)
{
    auto& values = m_prop.raw_compressionFileFormatStill.possible;
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_RAW_FileCompressionType);
    prop.SetCurrentValue(values[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}


void CameraDevice::setFoucsArea(int index)
{
    if(m_prop.focus_area.writable == 1)
    {
        SDK::CrDeviceProperty prop;
        prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_FocusArea);
        prop.SetCurrentValue(m_prop.focus_area.possible[index]);
        prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

        SDK::SetDeviceProperty(m_device_handle, &prop);
    }
}

void CameraDevice::setExposureBiasCompensation(int index)
{
    if(m_prop.exposure_bias_compensation.writable == 1)
    {
        SDK::CrDeviceProperty prop;
        prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_ExposureBiasCompensation);
        prop.SetCurrentValue(m_prop.exposure_bias_compensation.possible[index]);
        prop.SetValueType(SDK::CrDataType::CrDataType_Int16Array);

        SDK::SetDeviceProperty(m_device_handle, &prop);
    }
}

void CameraDevice::setFlashCompensation(int index)
{
    if(m_prop.flash_compensation.writable == 1)
    {
        SDK::CrDeviceProperty prop;
        prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_FlashCompensation);
        prop.SetCurrentValue(m_prop.flash_compensation.possible[index]);
        prop.SetValueType(SDK::CrDataType::CrDataType_Int16Array);

        SDK::SetDeviceProperty(m_device_handle, &prop);
    }
}


void CameraDevice::setDispMode(int index)
{
    if(m_prop.dispmode.writable == 1)
    {
        SDK::CrDeviceProperty prop;
        prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_DispMode);
        prop.SetCurrentValue(m_prop.dispmode.possible[index]);
        prop.SetValueType(SDK::CrDataType::CrDataType_UInt8Array);

        SDK::SetDeviceProperty(m_device_handle, &prop);
    }
}

void CameraDevice::setAspectRatio(int index)
{
    if(m_prop.aspectRatio.writable == 1)
    {
        SDK::CrDeviceProperty prop;
        prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_AspectRatio);
        prop.SetCurrentValue(m_prop.aspectRatio.possible[index]);
        prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);

        SDK::SetDeviceProperty(m_device_handle, &prop);
    }
}


void CameraDevice::setZoomSetting(int index)
{
    if(m_prop.zoom_setting.writable == 1)
    {
        SDK::CrDeviceProperty prop;
        prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Setting);
        prop.SetCurrentValue(m_prop.zoom_setting.possible[index]);
        prop.SetValueType(SDK::CrDataType::CrDataType_UInt8Array);

        SDK::SetDeviceProperty(m_device_handle, &prop);
    }
}

void CameraDevice::nearFarOperation(int step)
{
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_NearFar);
    prop.SetCurrentValue(step);
    prop.SetValueType(SDK::CrDataType::CrDataType_Int16Range);

    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::zoomOperation(int step)
{
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Operation);
    prop.SetCurrentValue((CrInt64u)step);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);
    SDK::SetDeviceProperty(m_device_handle, &prop);
}

void CameraDevice::setLiveViewDisplayEffect(int index)
{
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_LiveViewDisplayEffect);
    prop.SetCurrentValue(m_prop.liveViewDisplayEffect.possible[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);
    SDK::SetDeviceProperty(m_device_handle, &prop);
}


void CameraDevice::setLiveViewImageQuality(int index)
{
    SDK::CrDeviceProperty prop;
    prop.SetCode(SDK::CrDevicePropertyCode::CrDeviceProperty_LiveView_Image_Quality);
    prop.SetCurrentValue(m_prop.live_view_image_quality.possible[index]);
    prop.SetValueType(SDK::CrDataType::CrDataType_UInt16Array);
    SDK::SetDeviceProperty(m_device_handle, &prop);
}
