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
#ifndef PROPERTYVALUETABLE_H
#define PROPERTYVALUETABLE_H

#include <CameraRemote_SDK.h>
#include <QJsonObject>
#include <QJsonArray>
#include <cstdint>
#include <vector>

namespace cli
{

inline errno_t MemCpyEx(void* result, const void* source, size_t type_size)
{
#if (defined(_WIN32) || defined(_WIN64))
    return memcpy_s(result, type_size, source, type_size);
#else
    std::memcpy(result, source, type_size);
    return 0;
#endif
}

QString fromat_fNumber(std::uint16_t value);
QString fromat_fileType(std::uint16_t value);
QString fromat_JpegQuality(std::uint16_t value);
QString format_white_balance(std::uint16_t value);
QString format_fileType_movie(std::uint16_t value);
QString format_recording_setting(std::uint16_t value);
QString format_movie_recording_frameRateSetting(std::uint8_t value);
QString fromat_iso_sensitivity(std::uint32_t iso);
QString fromat_ShutterSpeed(std::uint32_t value);
QString format_exposure_program_mode(std::uint32_t exposure_program_mode);
QString format_raw_compressionFileFormatStill(std::uint16_t value);
QString format_focus_mode(std::uint16_t focus_mode);
QString format_drive_mode(std::uint32_t mode);
QString format_zoom_type_status(std::uint8_t value);
QString format_zoom_setting(std::uint8_t value);
QString format_focus_area(std::uint16_t value);
QString format_BatteryRemainDisplayUnit(std::uint8_t value);
QString format_MediaSLOT_Status(std::uint16_t value);
QString format_PC_Save_Image(std::uint16_t value);
QString format_DispMode(std::uint8_t value);
QString format_AspectRatio(std::uint16_t value);
QString format_LiveViewDisplayEffect(std::uint16_t value);
QString format_LiveViewImageQuality(std::uint16_t value);

template <typename T>
QString formatValue(T value,int code)
{
    QString content;
    switch (code)
    {
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_S1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AEL:
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FEL:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Reserved1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AWBL:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FNumber:
        content = fromat_fNumber(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ExposureBiasCompensation:
        content = QString::number(value/1000.0f);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FlashCompensation:
        content = QString::number(value/1000.0f);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSpeed:
        content = fromat_ShutterSpeed(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IsoSensitivity:
        content = fromat_iso_sensitivity(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ExposureProgramMode:
        content = format_exposure_program_mode(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FileType:
        content = fromat_fileType(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_StillImageQuality:
        content = fromat_JpegQuality(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_WhiteBalance:
        content = format_white_balance(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusMode:
        content = format_focus_mode(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MeteringMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FlashMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_WirelessFlash:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RedEyeReduction:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DriveMode:
        content = format_drive_mode(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DRO:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ImageSize:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AspectRatio:
        content = format_AspectRatio(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureEffect:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusArea:
        content = format_focus_area(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved4:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Colortemp:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ColorTuningAB:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ColorTuningGM:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LiveViewDisplayEffect:
        content = format_LiveViewDisplayEffect(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_StillImageStoreDestination:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PriorityKeySettings:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AFTrackingSensitivity:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved6:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Focus_Magnifier_Setting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DateTime_Settings:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NearFar:
        content = QString::number(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved7:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AF_Area_Position:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved8:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved9:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Scale:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Setting:
        content = format_zoom_setting(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Operation:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_File_Format:
        content = format_fileType_movie(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_Setting:
        content = format_recording_setting(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_FrameRateSetting:
        content = format_movie_recording_frameRateSetting(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CompressionFileFormatStill:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_FileType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_FileType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_ImageQuality:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_ImageQuality:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_ImageSize:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_ImageSize:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RAW_FileCompressionType:
        content = format_raw_compressionFileFormatStill(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_RAW_FileCompressionType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_RAW_FileCompressionType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ZoomAndFocusPosition_Save:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ZoomAndFocusPosition_Load:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IrisModeSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterModeSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_GainControlSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_GainBaseIsoSensitivity:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_GainBaseSensitivity:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ExposureIndex:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BaseLookValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PlaybackMedia:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DispModeSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DispMode:
        content = format_DispMode(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_TouchOperation:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SelectFinder:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AutoPowerOffTemperature:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BodyKeyLock:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ImageID_Num_Setting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ImageID_Num:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ImageID_String:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ExposureCtrlType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MonitorLUTSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocalDistanceInMeter:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocalDistanceInFeet:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocalDistanceUnitSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DigitalZoomScale:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ZoomDistance:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ZoomDistanceUnitSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterModeStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSlow:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSlowFrames:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_ResolutionForMain:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_ResolutionForProxy:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_Recording_FrameRateProxySetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BatteryRemainDisplayUnit:
        content = format_BatteryRemainDisplayUnit(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PowerSource:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieShootingMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieShootingModeColorGamut:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieShootingModeTargetDisplay:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DepthOfFieldAdjustmentMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ColortempStep:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_WhiteBalanceModeSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_WhiteBalanceTint:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_WhiteBalanceTintStep:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Focus_Operation:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterECSSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterECSNumber:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterECSNumberStep:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterECSFrequency:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderControlProxySetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable2:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable3:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable4:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable5:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable6:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable7:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable8:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable9:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentLensAssignable1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton2:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton3:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton4:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton5:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton6:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton7:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton8:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton9:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LensAssignableButton1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusModeSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterAngle:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSpeedValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NDFilter:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NDFilterModeSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NDFilterValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_GainUnitSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_GaindBValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AWB:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SceneFileIndex:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MoviePlayButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MoviePlayPauseButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MoviePlayStopButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieForwardButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieRewindButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieNextButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MoviePrevButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieRecReviewButton:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SubjectRecognitionAF:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AFTransitionSpeed:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AFSubjShiftSens:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AFAssist:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NDFilterSwitchingSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RemoteTouchOperation:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FollowFocusPositionSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusBracketShotNumber:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusBracketFocusRange:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ExtendedInterfaceMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SQRecordingFrameRateSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SQFrameRate:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SQRecordingSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AudioRecording:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AudioInputMasterLevel:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_TimeCodePreset:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_TimeCodeFormat:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_TimeCodeRun:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_TimeCodeMake:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_UserBitPreset:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_UserBitTimeRec:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ImageStabilizationSteadyShot:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_ImageStabilizationSteadyShot:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SilentMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SilentModeApertureDriveInAF:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SilentModeShutterWhenPowerOff:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SilentModeAutoPixelMapping:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_BlackLevel:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_Gamma:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_BlackGammaRange:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_BlackGammaLevel:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_KneeMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_KneeAutoSet_MaxPoint:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_KneeAutoSet_Sensitivity:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_KneeManualSet_Point:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_KneeManualSet_Slope:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_Saturation:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorPhase:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorDepthRed:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorDepthGreen:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorDepthBlue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorDepthCyan:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorDepthMagenta:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_ColorDepthYellow:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_DetailLevel:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_DetailAdjustMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_DetailAdjustVHBalance:
        break;       //Picture Profile Detail Adjust V/H Balance
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_DetailAdjustBWBalance:
        break;       //Picture Profile Detail Adjust B/W Balance
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_DetailAdjustLimit:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_DetailAdjustCrispening:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_DetailAdjustHiLightDetail:
        break;   //Picture Profile Detail Adjust Hi-Light Detail
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfile_Copy:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_Contrast:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_Highlights:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_Shadows:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_Fade:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_Saturation:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_Sharpness:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_SharpnessRange:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_Clarity:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLook_CustomLook:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_ProxyFileFormat:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ProxyRecordingSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FunctionOfTouchOperation:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_HighResolutionShutterSpeedSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DeleteUserBaseLook:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SelectUserBaseLookToEdit:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SelectUserBaseLookToSetInPPLUT:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_UserBaseLookInput:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_UserBaseLookAELevelOffset:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BaseISOSwitchEI:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FlickerLessShooting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PlaybackVolumeSettings:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AutoReview:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AudioSignals:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_HDMIResolutionStillPlay:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutputRecMedia:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutputResolution:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutput4KSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutputRAW:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutputRawSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutputTimeCode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutputRecControl:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved56:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MonitoringOutputDisplayHDMI:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_HDMIOutputAudioCH:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_IntervalRec_IntervalTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_IntervalRec_FrameRateSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_IntervalRec_RecordingSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_EframingScaleAuto:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_EframingSpeedAuto:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_EframingModeAuto:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_EframingRecordingImageCrop:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_EframingHDMICrop:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CameraEframing:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_USBPowerSupply:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LongExposureNR:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_HighIsoNR:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_HLGStillImage:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ColorSpace:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BracketOrder:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusBracketOrder:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusBracketExposureLock1stImg:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusBracketIntervalUntilNextShot:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IntervalRec_ShootingStartTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IntervalRec_ShootingInterval:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IntervalRec_ShootIntervalPriority:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IntervalRec_NumberOfShots:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IntervalRec_AETrackingSensitivity:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IntervalRec_ShutterType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_WindNoiseReduct:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecordingSelfTimer:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecordingSelfTimerCountTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecordingSelfTimerContinuous:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecordingSelfTimerStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BulbTimerSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BulbExposureTimeSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AutoSlowShutter:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IsoAutoMinShutterSpeedMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IsoAutoMinShutterSpeedManual:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IsoAutoMinShutterSpeedPreset:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusPositionSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SoftSkinEffect:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PrioritySetInAF_S:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PrioritySetInAF_C:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusMagnificationTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SubjectRecognitionInAF:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecognitionTarget:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RightLeftEyeSelect:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SelectFTPServer:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SelectFTPServerID:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTP_Function:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTP_AutoTransfer:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTP_AutoTransferTarget:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_FTP_AutoTransferTarget:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTP_TransferTarget:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_FTP_TransferTarget:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTP_PowerSave:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable10:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ButtonAssignmentAssignable11:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved14:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved15:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved16:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved17:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton10:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButton11:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved37:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved38:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved39:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved40:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NDFilterUnitSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NDFilterOpticalDensityValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_TNumber:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IrisDisplayUnit:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_ImageStabilizationLevel:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ImageStabilizationSteadyShotAdjust:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ImageStabilizationSteadyShotFocalLength:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_S2:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved10:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved11:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved12:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved13:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Interval_Rec_Mode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Still_Image_Trans_Size:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RAW_J_PC_Save_Image:
        content = format_PC_Save_Image(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LiveView_Image_Quality:
        content = format_LiveViewImageQuality(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CustomWB_Capture_Standby:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CustomWB_Capture_Standby_Cancel:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CustomWB_Capture:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Remocon_Zoom_Speed_Type:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_GetOnly:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SnapshotInfo:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BatteryRemain:
        content = QString::number(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BatteryLevel:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_EstimatePictureSize:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecordingState:
        content = QString::number(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LiveViewStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusIndication:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_Status:
        content = format_MediaSLOT_Status(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_RemainingNumber:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_RemainingTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_FormatEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved20:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_Status:
        content = format_MediaSLOT_Status(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_FormatEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_RemainingNumber:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_RemainingTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved22:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Media_FormatProgressRate:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTP_ConnectionStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTP_ConnectionErrorInfo:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LiveView_Area:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved26:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved27:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Interval_Rec_Status:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CustomWB_Execution_State:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CustomWB_Capturable_Area:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CustomWB_Capture_Frame_Size:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CustomWB_Capture_Operation:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved32:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Operation_Status:
        content = QString::number(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Bar_Information:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Type_Status:
        content = format_zoom_type_status(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_QuickFormatEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_QuickFormatEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Cancel_Media_FormatEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Zoom_Speed_Range:
        content = QString::number(value);
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SdkControlMode:
        content = QString::number(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ContentsTransferStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ContentsTransferCancelEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ContentsTransferProgress:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IsoCurrentSensitivity:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CameraSetting_SaveOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CameraSetting_ReadOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CameraSetting_SaveRead_State:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CameraSettingsResetEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_APS_C_or_Full_SwitchingSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_APS_C_or_Full_SwitchingEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DispModeCandidate:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_ShutterSpeedCurrentValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Focus_Speed_Range:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_NDFilterMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MoviePlayingSpeed:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1Player:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2Player:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BatteryRemainingInMinutes:
        content = QString::number(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BatteryRemainingInVoltage:
        content = QString::number(value);
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DCVoltage:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MoviePlayingState:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusTouchSpotStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusTrackingStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DepthOfFieldAdjustmentInterlockingMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderClipName:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderControlMainSetting:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderStartMain:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderStartProxy:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderMainStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderProxyStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderExtRawStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RecorderSaveDestination:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator2:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator3:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator4:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator5:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator6:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator7:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator8:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator9:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LensAssignableButtonIndicator1:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_GaindBCurrentValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SoftwareVersion:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CurrentSceneFileEdited:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MovieRecButtonToggleEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_RemoteTouchOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CancelRemoteTouchOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LensInformationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FollowFocusPositionCurrentValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusBracketShootingStatus:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PixelMappingEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_TimeCodePresetResetEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_UserBitPresetResetEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_SensorCleaningEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PictureProfileResetEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CreativeLookResetEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LensVersionNumber:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_DeviceOverheatingState:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_IntervalRec_CountDownIntervalTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_Movie_IntervalRec_RecordingDuration:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_HighResolutionShutterSpeed:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_BaseLookImportOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_LensModelName:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusPositionCurrentValue:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusDrivingStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FlickerScanStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FlickerScanEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTPServerSettingVersion:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTPServerSettingOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTPTransferSetting_SaveOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTPTransferSetting_ReadOperationEnableStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTPTransferSetting_SaveRead_State:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FTPJobListDataVersion:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CameraShakeStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_UpdateBodyStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved35:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_WritingState:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_WritingState:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved36:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT1_RecordingAvailableType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT2_RecordingAvailableType:
        break;

    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT3_RecordingAvailableType:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_CameraOperatingMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_PlaybackViewMode:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator10:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_AssignableButtonIndicator11:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved41:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved42:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved43:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved44:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT3_Status:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved45:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MediaSLOT3_RemainingTime:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved46:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_reserved47:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MonitoringDeliveringStatus:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MonitoringIsDelivering:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MonitoringSettingVersion:
        break;
    case SCRSDK::CrDevicePropertyCode::CrDeviceProperty_MonitoringDeliveryTypeSupportInfo:
        break;
    default:break;
    }

    return content;
}

//数据记录的结构体
template <typename T>
struct PropertyValueEntry
{
    CrInt32u key; // 0:undefined
    int writable; // -1:Iniitial, 0:false, 1:true
    T current;
    std::vector<T> possible;
    PropertyValueEntry()
    {
        key = 0;
        writable = -1;
    }

    void parse(SCRSDK::CrDeviceProperty &prop)
    {
        std::uint32_t nval = prop.GetValueSize() / sizeof(T);
        key = prop.GetCode();
        writable = prop.IsSetEnableCurrentValue();
        current = static_cast<T>(prop.GetCurrentValue());

        if(nval > 0)
        {
            constexpr std::size_t const type_size = sizeof(T);
            T const* source = reinterpret_cast<T const*>(prop.GetValues());
            std::vector<T> result(nval);
            for (std::uint32_t i = 0; i < nval; ++i, ++source) {
                MemCpyEx(&result[i], source, type_size);
            }
            possible.swap(result);
        }
    }

    QJsonObject toJson()
    {
        QJsonObject obj;
        obj["writable"] = writable;
        obj["key"] = (int)key;
        obj["value"] = formatValue<T>(current,key);
        if(possible.size() > 0)
        {
            QJsonArray values;
            for(int i = 0; i < possible.size(); i++){
                values.append(formatValue<T>(possible[i],key));
            }
            obj["values"] = values;
        }
        return obj;
    }
};


struct PropertyValueTable
{
    PropertyValueEntry<std::uint32_t> sdk_mode;
    PropertyValueEntry<std::uint16_t> f_number;
    PropertyValueEntry<std::uint32_t> iso_sensitivity;
    PropertyValueEntry<std::uint16_t> file_format;
    PropertyValueEntry<std::uint16_t> movie_file_format;
    PropertyValueEntry<std::uint16_t> movie_recording_setting;
    PropertyValueEntry<std::uint8_t> movie_recording_frame_rate_setting;
    PropertyValueEntry<std::uint16_t> jpeg_quality;
    PropertyValueEntry<std::uint32_t> shutter_speed;
    PropertyValueEntry<std::uint16_t> position_key_setting;
    PropertyValueEntry<std::uint32_t> exposure_program_mode;
    PropertyValueEntry<std::uint32_t> still_capture_mode;
    PropertyValueEntry<std::uint16_t> focus_mode;
    PropertyValueEntry<std::uint16_t> focus_mode_setting;
    PropertyValueEntry<std::uint16_t> focus_area;
    PropertyValueEntry<std::int16_t> exposure_bias_compensation;
    PropertyValueEntry<std::int16_t> flash_compensation;
    PropertyValueEntry<std::uint16_t> raw_compressionFileFormatStill;
    PropertyValueEntry<std::uint32_t> drive_mode;
    PropertyValueEntry<std::uint8_t> batteryRemainDisplayUnit;
    PropertyValueEntry<std::uint16_t> batteryRemainingPercent;
    PropertyValueEntry<std::uint32_t> batteryRemainingMinutes;
    PropertyValueEntry<std::uint32_t> batteryRemainingVoltage;
    PropertyValueEntry<std::uint16_t> pcSaveSetting;
    PropertyValueEntry<std::uint8_t> dispmode;
    PropertyValueEntry<std::uint16_t> aspectRatio;

    PropertyValueEntry<std::uint16_t> media_slot1_status;
    PropertyValueEntry<std::uint16_t> media_slot2_status;
    PropertyValueEntry<std::uint32_t> zoom_scale;
    PropertyValueEntry<std::uint8_t> zoom_setting;
    PropertyValueEntry<std::uint8_t> zoom_types_status;
    PropertyValueEntry<std::int8_t> zoom_speed_range;
    PropertyValueEntry<std::uint8_t> zoom_operation_status;
    PropertyValueEntry<std::int16_t> focusNearFar;
    PropertyValueEntry<std::uint16_t> liveViewDisplayEffect;
    PropertyValueEntry<std::uint16_t> live_view_image_quality;

    PropertyValueEntry<std::uint64_t> media_slot1_remaining_number;
    PropertyValueEntry<std::uint64_t> media_slot2_remaining_number;
    PropertyValueEntry<std::uint8_t> media_slot1_full_format_enable_status;
    PropertyValueEntry<std::uint8_t> media_slot2_full_format_enable_status;
    PropertyValueEntry<std::uint8_t> media_slot1_quick_format_enable_status;
    PropertyValueEntry<std::uint8_t> media_slot2_quick_format_enable_status;
    PropertyValueEntry<std::uint16_t> white_balance;
    PropertyValueEntry<std::uint16_t> customwb_capture_stanby;
    PropertyValueEntry<std::uint16_t> customwb_capture_stanby_cancel;
    PropertyValueEntry<std::uint16_t> customwb_capture_operation;
    PropertyValueEntry<std::uint16_t> customwb_capture_execution_state;
    PropertyValueEntry<std::uint8_t> save_zoom_and_focus_position;
    PropertyValueEntry<std::uint8_t> load_zoom_and_focus_position;
    PropertyValueEntry<std::uint8_t> remocon_zoom_speed_type;
    PropertyValueEntry<std::uint8_t> aps_c_of_full_switching_setting;
    PropertyValueEntry<std::uint8_t> aps_c_of_full_switching_enable_status;
    PropertyValueEntry<std::uint8_t> camera_setting_save_read_state;
    PropertyValueEntry<std::uint8_t> camera_setting_save_operation;
    PropertyValueEntry<std::uint8_t> camera_setting_read_operation;
    PropertyValueEntry<std::uint8_t>  camera_setting_reset_enable_status;
    PropertyValueEntry<std::uint8_t> gain_base_sensitivity;
    PropertyValueEntry<std::uint8_t> gain_base_iso_sensitivity;
    PropertyValueEntry<std::uint8_t>  monitor_lut_setting;
    PropertyValueEntry<std::uint16_t>  exposure_index;
    PropertyValueEntry<std::uint16_t> baselook_value;
    PropertyValueEntry<std::uint8_t> playback_media;
    PropertyValueEntry<std::uint8_t> iris_mode_setting;
    PropertyValueEntry<std::uint8_t> shutter_mode_setting;
    PropertyValueEntry<std::uint8_t> gain_control_setting;
    PropertyValueEntry<std::uint8_t> exposure_control_type;
    PropertyValueEntry<std::uint32_t> iso_current_sensitivity;
    PropertyValueEntry<std::uint16_t> recording_setting;
    PropertyValueEntry<std::uint32_t> dispmode_candidate;
    PropertyValueEntry<std::uint32_t> dispmode_setting;
    PropertyValueEntry<std::int8_t> gain_db_value;
    PropertyValueEntry<std::int8_t> white_balance_tint;
    PropertyValueEntry<std::int16_t> white_balance_tint_step;
    PropertyValueEntry<std::uint64_t> shutter_speed_value;
    PropertyValueEntry<std::uint16_t> movie_recording_status;
    PropertyValueEntry<std::uint8_t> movie_rec_button_toggle_enable_status;
    PropertyValueEntry<std::uint16_t> focus_bracket_shot_num;
    PropertyValueEntry<std::uint8_t> focus_bracket_focus_range;
};



}
#endif // PROPERTYVALUETABLE_H
