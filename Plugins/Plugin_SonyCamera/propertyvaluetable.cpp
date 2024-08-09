#include "propertyvaluetable.h"

#include <cmath>
#include <cstring>

namespace SDK = SCRSDK;

//namespace impl
//{

//template <typename T>
//std::vector<T> parse(unsigned char const* buf, std::uint32_t nval)
//{
//    constexpr std::size_t const type_size = sizeof(T);
//    std::vector<T> result(nval);
//    std::uint32_t i = 0; T* source = static_cast<T*>(buf);
//    for (; i < nval; ++i, ++source) {
//        MemCpyEx(&result[i], source, type_size);
//    }
//}

//} // namespace impl

namespace cli
{

//四舍五入
double Round(double value, int figure)
{
    bool isNegative = ( value < 0 );
    if (isNegative == true) value = -value;

    double rate = std::pow(10.0, figure);
    //double value1 = value * rate + 0.5;

    long tmp = (long)(value * rate + 0.5);
    value = tmp/rate;

    if (isNegative == true) value = -value;

    return value;
}

// 获取32位数据的高位数据(16位)
// Retrieve the hi-order word (16-bit value) of a dword (32-bit value)
constexpr std::uint16_t HIWORD(std::uint32_t dword)
{
    return static_cast<std::uint16_t>((dword >> 16) & 0xFFFF);
}

// 获取32位数据的低位数据(16位)
// Retrieve the low-order word (16-bit value) of a dword (32-bit value)
constexpr std::uint16_t LOWORD(std::uint32_t dword)
{
    return static_cast<std::uint16_t>(dword & 0xFFFF);
}


QString fromat_fNumber(std::uint16_t value)
{
    if(value > 0)
       return QString::number(Round((value/100.0),1));
    else
       return QString::number(value/100);
}

QString fromat_fileType(std::uint16_t value)
{
    if(value == SDK::CrFileType::CrFileType_RawJpeg)
        return "RAW+JPEG";
    else if(value == SDK::CrFileType::CrFileType_Jpeg)
        return "JPEG";
    else if(value == SDK::CrFileType::CrFileType_Raw)
        return "RAW";
    else if(value == SDK::CrFileType::CrFileType_RawHeif)
        return "RAW+HEIF";
    else if(value == SDK::CrFileType::CrFileType_Heif)
        return "HEIF";
    else
        return "error";
}

QString fromat_JpegQuality(std::uint16_t value)
{
    if(value == SDK::CrJpegQuality::CrJpegQuality_Light)
        return "LIGHT 小";
    else if(value == SDK::CrJpegQuality::CrJpegQuality_Standard)
        return "STD 标准";
    else if(value == SDK::CrJpegQuality::CrJpegQuality_Fine)
        return "FINE 精细";
    else if(value == SDK::CrJpegQuality::CrJpegQuality_ExFine)
        return "X.FINE 超精细";
    else
        return "error";
}


QString format_white_balance(std::uint16_t value)
{
    switch (value) {
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_AWB:
        return "AWB";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Underwater_Auto:
        return "Underwater_Auto";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Daylight:
        return "Daylight";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Shadow:
        return "Shadow";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Cloudy:
        return "Cloudy";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Tungsten:
        return "Tungsten";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Fluorescent:
        return "Fluorescent";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Fluorescent_WarmWhite:
        return "Fluorescent_WarmWhite";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Fluorescent_CoolWhite:
        return "Fluorescent_CoolWhite";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Fluorescent_DayWhite:
        return "Fluorescent_DayWhite";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Fluorescent_Daylight:
        return "Fluorescent_Daylight";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Flush:
        return "Flush";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_ColorTemp:
        return "ColorTemp";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Custom_1:
        return "Custom_1";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Custom_2:
        return "Custom_2";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Custom_3:
        return "Custom_3";
        break;
    case SDK::CrWhiteBalanceSetting::CrWhiteBalance_Custom:
        return "Custom";
        break;
    default:
        return "error";
        break;
    }
}


QString format_fileType_movie(std::uint16_t value)
{
    switch (value) {
    case SDK::CrFileFormatMovie::CrFileFormatMovie_AVCHD:
        return "AVCHD";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_MP4:
        return "MP4";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_S_4K:
        return "XAVC S 4K";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_S_HD:
        return "XAVC S HD";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_HS_8K:
        return "XAVC HS 8K";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_HS_4K:
        return "XAVC HS 4K";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_S_L_4K:
        return "XAVC S-L 4K";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_S_L_HD:
        return "XAVC S-L HD";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_S_I_4K:
        return "XAVC S-I 4K";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_S_I_HD:
        return "XAVC S-I HD";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_I:
        return "XAVC I";
        break;
    case SDK::CrFileFormatMovie::CrFileFormatMovie_XAVC_L:
        return "XAVC L";
        break;
    default:
        return "error";
        break;
    }
}

QString format_recording_setting(std::uint16_t value)
{
    switch (value) {
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_60p_50M:
        return "60p_50M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_30p_50M:
        return "30p_50M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_24p_50M:
        return "24p_50M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50p_50M:
        return "50p_50M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_25p_50M:
        return "25p_50M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_60i_24M:
        return "60i_24M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50i_24M_FX:
        return "50i_24M_FX";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_60i_17M_FH:
        return "60i_17M_FH";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50i_17M_FH:
        return "50i_17M_FH";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_60p_28M_PS:
        return "60p_28M_PS";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50p_28M_PS:
        return "50p_28M_PS";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_24p_24M_FX:
        return "24p_24M_FX";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_25p_24M_FX:
        return "25p_24M_FX";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_24p_17M_FH:
        return "24p_17M_FH";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_25p_17M_FH:
        return "25p_17M_FH";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_120p_50M_1280x720:
        return "120p_50M_1280x720";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_100p_50M_1280x720:
        return "100p_50M_1280x720";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_1920x1080_30p_16M:
        return "1920x1080_30p_16M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_1920x1080_25p_16M:
        return "1920x1080_25p_16M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_1280x720_30p_6M:
        return "1280x720_30p_6M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_1280x720_25p_6M:
        return "1280x720_25p_6M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_1920x1080_60p_28M:
        return "1920x1080_60p_28M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_1920x1080_50p_28M:
        return "1920x1080_50p_28M";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_60p_25M_XAVC_S_HD:
        return "60p_25M_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50p_25M_XAVC_S_HD:
        return "50p_25M_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_30p_16M_XAVC_S_HD:
        return "30p_16M_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_25p_16M_XAVC_S_HD:
        return "25p_16M_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_120p_100M_1920x1080_XAVC_S_HD:
        return "120p_100M_1920x1080_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_100p_100M_1920x1080_XAVC_S_HD:
        return "100p_100M_1920x1080_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_120p_60M_1920x1080_XAVC_S_HD:
        return "120p_60M_1920x1080_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_100p_60M_1920x1080_XAVC_S_HD:
        return "100p_60M_1920x1080_XAVC_S_HD";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_30p_100M_XAVC_S_4K:
        return "30p_100M_XAVC_S_4K";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_25p_100M_XAVC_S_4K:
        return "25p_100M_XAVC_S_4K";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_24p_100M_XAVC_S_4K:
        return "24p_100M_XAVC_S_4K";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_30p_60M_XAVC_S_4K:
        return "30p_60M_XAVC_S_4K";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_25p_60M_XAVC_S_4K:
        return "25p_60M_XAVC_S_4K";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_24p_60M_XAVC_S_4K:
        return "24p_60M_XAVC_S_4K";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_600M_422_10bit:
        return "600M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_500M_422_10bit:
        return "500M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_400M_420_10bit:
        return "400M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_300M_422_10bit:
        return "300M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_280M_422_10bit:
        return "280M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_250M_422_10bit:
        return "250M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_240M_422_10bit:
        return "240M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_222M_422_10bit:
        return "222M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_200M_422_10bit:
        return "200M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_200M_420_10bit:
        return "200M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_200M_420_8bit:
        return "200M_4:2:0_8bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_185M_422_10bit:
        return "185M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_150M_420_10bit:
        return "150M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_150M_420_8bit:
        return "150M_4:2:0_8bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_140M_422_10bit:
        return "140M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_111M_422_10bit:
        return "111M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_100M_422_10bit:
        return "100M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_100M_420_10bit:
        return "100M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_100M_420_8bit:
        return "100M_4:2:0_8bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_93M_422_10bit:
        return "93M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_89M_422_10bit:
        return "89M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_75M_420_10bit:
        return "75M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_60M_420_8bit:
        return "60M_4:2:0_8bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50M_422_10bit:
        return "50M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50M_420_10bit:
        return "50M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_50M_420_8bit:
        return "50M_4:2:0_8bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_45M_420_10bit:
        return "45M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_30M_420_10bit:
        return "30M_4:2:0_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_25M_420_8bit:
        return "25M_4:2:0_8bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_16M_420_8bit:
        return "16M_4:2:0_8bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_520M_422_10bit:
        return "520M_4:2:2_10bit";
    case SDK::CrRecordingSettingMovie::CrRecordingSettingMovie_260M_422_10bit:
        return "260M_4:2:2_10bit";
    default:
        return "error";
    }
}


QString format_movie_recording_frameRateSetting(std::uint8_t value)
{
    switch (value) {
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_120p:
        return "120P";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_100p:
        return "100p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_60p:
        return "60p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_50p:
        return "50p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_30p:
        return "30p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_25p:
        return "25p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_24p:
        return "24p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_23_98p:
        return "23_98p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_29_97p:
        return "29_97p";
    case SDK::CrRecordingFrameRateSettingMovie::CrRecordingFrameRateSettingMovie_59_94p:
        return "59_94p";
    default:
        return "error";
        break;
    }
}

QString fromat_iso_sensitivity(std::uint32_t iso)
{
    //    std::uint32_t iso_ext = (iso >> 24) & 0x000000F0;  // bit 28-31
    //    std::uint32_t iso_mode = (iso >> 24) & 0x0000000F; // bit 24-27
    std::uint32_t iso_value = (iso & 0x00FFFFFF);      // bit  0-23

    //    if (iso_mode == SDK::CrISO_MultiFrameNR) {
    //        return TEXT("Multi Frame NR ");
    //    }
    //    else if (iso_mode == SDK::CrISO_MultiFrameNR_High) {
    //        return TEXT("Multi Frame NR High ");
    //    }

    if (iso_value == SDK::CrISO_AUTO) {
        return "AUTO";
    }
    else {
        return QString::number(iso_value);
    }

}


QString fromat_ShutterSpeed(std::uint32_t value)
{
    QString str;

    CrInt16u numerator = HIWORD(value);
    CrInt16u denominator = LOWORD(value);
    if(value == 0)
        str = "Bulb";
    else if(numerator == 1)
        str = QString("%1/%2").arg(numerator).arg(denominator);
    else if((numerator%denominator) == 0)
        str = QString::number(numerator/denominator);
    else
    {
        CrInt32 numdevision = numerator/denominator;
        CrInt32 numremainder = numerator%denominator;
        str = QString("%1.%2").arg(numdevision).arg(numremainder);
    }

    return str;
}

QString format_exposure_program_mode(std::uint32_t exposure_program_mode)
{
    switch (exposure_program_mode) {
    case SDK::CrExposureProgram::CrExposure_M_Manual:
        return "M_Manual";
        break;
    case SDK::CrExposureProgram::CrExposure_P_Auto:
        return "P_Auto";
        break;
    case SDK::CrExposureProgram::CrExposure_A_AperturePriority:
        return "A_AperturePriority";
        break;
    case SDK::CrExposureProgram::CrExposure_S_ShutterSpeedPriority:
        return "S_ShutterSpeedPriority";
        break;
    case SDK::CrExposureProgram::CrExposure_Program_Creative:
        return "ProgramCreative";
        break;
    case SDK::CrExposureProgram::CrExposure_Program_Action:
        return "ProgramAction";
        break;
    case SDK::CrExposureProgram::CrExposure_Portrait:
        return "Portrait";
        break;
    case SDK::CrExposureProgram::CrExposure_Auto:
        return "Auto";
        break;
    case SDK::CrExposureProgram::CrExposure_Auto_Plus:
        return "Auto_Plus";
        break;
    case SDK::CrExposureProgram::CrExposure_P_A:
        return "P_A";
        break;
    case SDK::CrExposureProgram::CrExposure_P_S:
        return "P_S";
        break;
    case SDK::CrExposureProgram::CrExposure_Sports_Action:
        return "Sports_Action";
        break;
    case SDK::CrExposureProgram::CrExposure_Sunset:
        return "Sunset";
        break;
    case SDK::CrExposureProgram::CrExposure_Night:
        return "Night";
        break;
    case SDK::CrExposureProgram::CrExposure_Landscape:
        return "Landscape";
        break;
    case SDK::CrExposureProgram::CrExposure_Macro:
        return "Macro";
        break;
    case SDK::CrExposureProgram::CrExposure_HandheldTwilight:
        return "HandheldTwilight";
        break;
    case SDK::CrExposureProgram::CrExposure_NightPortrait:
        return "NightPortrait";
        break;
    case SDK::CrExposureProgram::CrExposure_AntiMotionBlur:
        return "AntiMotionBlur";
        break;
    case SDK::CrExposureProgram::CrExposure_Pet:
        return "Pet";
        break;
    case SDK::CrExposureProgram::CrExposure_Gourmet:
        return "Gourmet";
        break;
    case SDK::CrExposureProgram::CrExposure_Fireworks:
        return "Fireworks";
        break;
    case SDK::CrExposureProgram::CrExposure_HighSensitivity:
        return "HighSensitivity";
        break;
    case SDK::CrExposureProgram::CrExposure_MemoryRecall:
        return "MemoryRecall";
        break;
    case SDK::CrExposureProgram::CrExposure_ContinuousPriority_AE_8pics:
        return "ContinuousPriority_AE_8pics";
        break;
    case SDK::CrExposureProgram::CrExposure_ContinuousPriority_AE_10pics:
        return "ContinuousPriority_AE_10pics";
        break;
    case SDK::CrExposureProgram::CrExposure_ContinuousPriority_AE_12pics:
        return "ContinuousPriority_AE_12pics";
        break;
    case SDK::CrExposureProgram::CrExposure_3D_SweepPanorama:
        return "3D_SweepPanorama";
        break;
    case SDK::CrExposureProgram::CrExposure_SweepPanorama:
        return "SweepPanorama";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_P:
        return "Movie_P";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_A:
        return "Movie_A";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_S:
        return "Movie_S";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_M:
        return "Movie_M";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_Auto:
        return "Movie_Auto";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_F:
        return "Movie_F";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_SQMotion_P:
        return "Movie_SQMotion_P";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_SQMotion_A:
        return "Movie_SQMotion_A";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_SQMotion_S:
        return "Movie_SQMotion_S";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_SQMotion_M:
        return "Movie_SQMotion_M";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_SQMotion_AUTO:
        return "Movie_SQMotion_AUTO";
        break;
    case SDK::CrExposureProgram::CrExposure_Movie_SQMotion_F:
        return "Movie_SQMotion_F";
        break;
    case SDK::CrExposureProgram::CrExposure_Flash_Off:
        return "FlashOff";
        break;
    case SDK::CrExposureProgram::CrExposure_PictureEffect:
        return "PictureEffect";
        break;
    case SDK::CrExposureProgram::CrExposure_HiFrameRate_P:
        return "HiFrameRate_P";
        break;
    case SDK::CrExposureProgram::CrExposure_HiFrameRate_A:
        return "HiFrameRate_A";
        break;
    case SDK::CrExposureProgram::CrExposure_HiFrameRate_S:
        return "HiFrameRate_S";
        break;
    case SDK::CrExposureProgram::CrExposure_HiFrameRate_M:
        return "HiFrameRate_M";
        break;
    case SDK::CrExposureProgram::CrExposure_SQMotion_P:
        return "SQMotion_P";
        break;
    case SDK::CrExposureProgram::CrExposure_SQMotion_A:
        return "SQMotion_A";
        break;
    case SDK::CrExposureProgram::CrExposure_SQMotion_S:
        return "SQMotion_S";
        break;
    case SDK::CrExposureProgram::CrExposure_SQMotion_M:
        return "SQMotion_M";
        break;
    case SDK::CrExposureProgram::CrExposure_MOVIE:
        return "MOVIE";
        break;
    case SDK::CrExposureProgram::CrExposure_STILL:
        return "STILL";
        break;
    case SDK::CrExposureProgram::CrExposure_F_MovieOrSQMotion:
        return "F(Movie or S&Q)";
        break;
    default:
        return "";
        break;
    }

}

QString format_raw_compressionFileFormatStill(std::uint16_t value)
{
    switch (value)
    {
    case SDK::CrRAWFileCompressionType::CrRAWFile_Uncompression:
        return "Uncompression";
        break;
    case SDK::CrRAWFileCompressionType::CrRAWFile_Compression:
        return "Compression";
        break;
    case SDK::CrRAWFileCompressionType::CrRAWFile_LossLess:
        return "LossLess Compression";
        break;
    case SDK::CrRAWFileCompressionType::CrRAWFile_LossLessS:
        return "LossLess S";
        break;
    case SDK::CrRAWFileCompressionType::CrRAWFile_LossLessM:
        return "LossLess M";
        break;
    case SDK::CrRAWFileCompressionType::CrRAWFile_LossLessL:
        return "LossLess L";
        break;
    default:
        return "";
        break;
    }
}

QString format_focus_mode(std::uint16_t focus_mode)
{
    QString str;
    switch (focus_mode) {
    case SDK::CrFocusMode::CrFocus_MF:str="MF";break;
    case SDK::CrFocusMode::CrFocus_AF_S:str="AF_S";break;
    case SDK::CrFocusMode::CrFocus_AF_C:str="AF_C";break;
    case SDK::CrFocusMode::CrFocus_AF_A:str="AF_A";break;
    case SDK::CrFocusMode::CrFocus_DMF:str="DMF";break;
    case SDK::CrFocusMode::CrFocus_AF_D:str="AF_D";break;
    case SDK::CrFocusMode::CrFocus_PF:str="PF";break;
    default:str="error"; break;
    }
    return str;
}

QString format_drive_mode(std::uint32_t mode)
{
    QString str;
    switch (mode) {
    case SDK::CrDriveMode::CrDrive_Single:str="单张拍摄";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Hi:str="Continuous Shot hi";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Hi_Plus:str="Cont. Shooting Hi+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Hi_Live:str="Cont. Shooting Hi-Live";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Lo:str="Continuous Shot lo";break;
    case SDK::CrDriveMode::CrDrive_Continuous:str="Continuous Shot";break;
    case SDK::CrDriveMode::CrDrive_Continuous_SpeedPriority:str="Continuous Shot Speed Priority";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Mid:str="Continuous Shot mid";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Mid_Live:str="Cont. Shooting Mid-Live";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Lo_Live:str="Cont. Shooting Lo-Live";break;
    case SDK::CrDriveMode::CrDrive_Timelapse:str="Timelapse";break;
    case SDK::CrDriveMode::CrDrive_Timer_5s:str="Self Timer 5sec";break;
    case SDK::CrDriveMode::CrDrive_Timer_10s:str="Self Timer 10sec";break;
    case SDK::CrDriveMode::CrDrive_Timer_2s:str="Self Timer 2sec";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_03Ev_3pics:str="Continuous Bracket 0.3EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_03Ev_5pics:str="Continuous Bracket 0.3EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_03Ev_9pics:str= "Continuous Bracket 0.3EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_05Ev_3pics:str="Continuous Bracket 0.5EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_05Ev_5pics:str="Continuous Bracket 0.5EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_05Ev_9pics:str="Continuous Bracket 0.5EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_07Ev_3pics:str="Continuous Bracket 0.7EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_07Ev_5pics:str="Continuous Bracket 0.7EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_07Ev_9pics:str="Continuous Bracket 0.7EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_10Ev_3pics:str="Continuous Bracket 1.0EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_10Ev_5pics:str="Continuous Bracket 1.0EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_10Ev_9pics:str="Continuous Bracket 1.0EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_20Ev_3pics:str="Continuous Bracket 2.0EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_20Ev_5pics:str="Continuous Bracket 2.0EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_30Ev_3pics:str="Continuous Bracket 3.0EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_30Ev_5pics:str="Continuous Bracket 3.0EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_03Ev_3pics:str="Single Bracket 0.3EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_03Ev_5pics:str="Single Bracket 0.3EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_03Ev_9pics:str="Single Bracket 0.3EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_05Ev_3pics:str="Single Bracket 0.5EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_05Ev_5pics:str="Single Bracket 0.5EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_05Ev_9pics:str="Single Bracket 0.5EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_07Ev_3pics:str="Single Bracket 0.7EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_07Ev_5pics:str="Single Bracket 0.7EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_07Ev_9pics:str="Single Bracket 0.7EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_10Ev_3pics:str="Single Bracket 1.0EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_10Ev_5pics:str="Single Bracket 1.0EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_10Ev_9pics:str="Single Bracket 1.0EV 9pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_20Ev_3pics:str="Single Bracket 2.0EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_20Ev_5pics:str="Single Bracket 2.0EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_30Ev_3pics:str="Single Bracket 3.0EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_30Ev_5pics:str="Single Bracket 3.0EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_WB_Bracket_Lo:str="WhiteBalance Bracket Lo";break;
    case SDK::CrDriveMode::CrDrive_WB_Bracket_Hi:str="WhiteBalance Bracket Hi";break;
    case SDK::CrDriveMode::CrDrive_DRO_Bracket_Lo:str="DRO Bracket Lo";break;
    case SDK::CrDriveMode::CrDrive_DRO_Bracket_Hi:str="DRO Bracket Hi";break;
    case SDK::CrDriveMode::CrDrive_LPF_Bracket:str="LPF Bracket";break;
    case SDK::CrDriveMode::CrDrive_RemoteCommander:str="Remote Commander";
    case SDK::CrDriveMode::CrDrive_MirrorUp:str="Mirror Up";break;
    case SDK::CrDriveMode::CrDrive_SelfPortrait_1:str="Self Portrait 1 Person";break;
    case SDK::CrDriveMode::CrDrive_SelfPortrait_2:str="Self Portrait 2 Person";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Timer_3pics:str="Continuous Self Timer 3pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Timer_5pics:str="Continuous Self Timer 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Timer_5s_3pics:str="Continuous Self Timer 3pics 5sec";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Timer_5s_5pics:str="Continuous Self Timer 5pics 5sec";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Timer_2s_3pics:str="Continuous Self Timer 2pics 3sec";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Timer_2s_5pics:str="Continuous Self Timer 2pics 5sec";break;
    case SDK::CrDriveMode::CrDrive_SingleBurstShooting_lo:str="Spot Burst Shooting Lo";break;
    case SDK::CrDriveMode::CrDrive_SingleBurstShooting_mid:str="Spot Burst Shooting Mid";break;
    case SDK::CrDriveMode::CrDrive_SingleBurstShooting_hi:str="Spot Burst Shooting Hi";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_03Ev_2pics_Plus:str="Continuous Bracket 0.3EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_03Ev_2pics_Minus:str="Continuous Bracket 0.3EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_03Ev_7pics:str="Continuous Bracket 0.3EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_05Ev_2pics_Plus:str="Continuous Bracket 0.5EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_05Ev_2pics_Minus:str="Continuous Bracket 0.5EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_05Ev_7pics:str="Continuous Bracket 0.5EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_07Ev_2pics_Plus:str="Continuous Bracket 0.7EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_07Ev_2pics_Minus:str="Continuous Bracket 0.7EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_07Ev_7pics:str="Continuous Bracket 0.7EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_10Ev_2pics_Plus:str="Continuous Bracket 1.0EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_10Ev_2pics_Minus:str="Continuous Bracket 1.0EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_10Ev_7pics:str="Continuous Bracket 1.0EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_13Ev_2pics_Plus:str="Continuous Bracket 1.3EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_13Ev_2pics_Minus:str="Continuous Bracket 1.3EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_13Ev_3pics:str="Continuous Bracket 1.3EV 3ics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_13Ev_5pics:str="Continuous Bracket 1.3EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_13Ev_7pics:str="Continuous Bracket 1.3EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_15Ev_2pics_Plus:str="Continuous Bracket 1.5EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_15Ev_2pics_Minus:str="Continuous Bracket 1.5EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_15Ev_3pics:str="Continuous Bracket 1.5EV 3ics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_15Ev_5pics:str="Continuous Bracket 1.5EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_15Ev_7pics:str="Continuous Bracket 1.5EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_17Ev_2pics_Plus:str="Continuous Bracket 1.7EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_17Ev_2pics_Minus:str="Continuous Bracket 1.7EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_17Ev_3pics:str="Continuous Bracket 1.7EV 3ics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_17Ev_5pics:str="Continuous Bracket 1.7EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_17Ev_7pics:str="Continuous Bracket 1.7EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_20Ev_2pics_Plus:str="Continuous Bracket 2.0EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_20Ev_2pics_Minus:str="Continuous Bracket 2.0EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_20Ev_7pics:str="Continuous Bracket 2.0EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_23Ev_2pics_Plus:str="Continuous Bracket 2.3EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_23Ev_2pics_Minus:str="Continuous Bracket 2.3EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_23Ev_3pics:str="Continuous Bracket 2.3EV 3ics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_23Ev_5pics:str="Continuous Bracket 2.3EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_25Ev_2pics_Plus:str="Continuous Bracket 2.5EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_25Ev_2pics_Minus:str="Continuous Bracket 2.5EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_25Ev_3pics:str="Continuous Bracket 2.5EV 3ics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_25Ev_5pics:str="Continuous Bracket 2.5EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_27Ev_2pics_Plus:str="Continuous Bracket 2.7EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_27Ev_2pics_Minus:str="Continuous Bracket 2.7EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_27Ev_3pics:str="Continuous Bracket 2.7EV 3ics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_27Ev_5pics:str="Continuous Bracket 2.7EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_30Ev_2pics_Plus:str="Continuous Bracket 3.0EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Continuous_Bracket_30Ev_2pics_Minus:str="Continuous Bracket 3.0EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_03Ev_2pics_Plus:str="Single Bracket 0.3EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_03Ev_2pics_Minus:str="Single Bracket 0.3EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_03Ev_7pics:str="Single Bracket 0.3EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_05Ev_2pics_Plus:str="Single Bracket 0.5EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_05Ev_2pics_Minus:str="Single Bracket 0.5EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_05Ev_7pics:str="Single Bracket 0.5EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_07Ev_2pics_Plus:str="Single Bracket 0.7EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_07Ev_2pics_Minus:str="Single Bracket 0.7EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_07Ev_7pics:str="Single Bracket 0.7EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_10Ev_2pics_Plus:str="Single Bracket 1.0EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_10Ev_2pics_Minus:str="Single Bracket 1.0EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_10Ev_7pics:str="Single Bracket 1.0EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_13Ev_2pics_Plus:str="Single Bracket 1.3EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_13Ev_2pics_Minus:str="Single Bracket 1.3EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_13Ev_3pics:str="Single Bracket 1.3EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_13Ev_5pics:str="Single Bracket 1.3EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_13Ev_7pics:str="Single Bracket 1.3EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_15Ev_2pics_Plus:str="Single Bracket 1.5EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_15Ev_2pics_Minus:str="Single Bracket 1.5EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_15Ev_3pics:str="Single Bracket 1.5EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_15Ev_5pics:str="Single Bracket 1.5EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_15Ev_7pics:str="Single Bracket 1.5EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_17Ev_2pics_Plus:str="Single Bracket 1.7EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_17Ev_2pics_Minus:str="Single Bracket 1.7EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_17Ev_3pics:str="Single Bracket 1.7EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_17Ev_5pics:str="Single Bracket 1.7EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_17Ev_7pics:str="Single Bracket 1.7EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_20Ev_2pics_Plus:str="Single Bracket 2.0EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_20Ev_2pics_Minus:str="Single Bracket 2.0EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_20Ev_7pics:str="Single Bracket 2.0EV 7pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_23Ev_2pics_Plus:str="Single Bracket 2.3EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_23Ev_2pics_Minus:str="Single Bracket 2.3EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_23Ev_3pics:str="Single Bracket 2.3EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_23Ev_5pics:str="Single Bracket 2.3EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_25Ev_2pics_Plus:str="Single Bracket 2.5EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_25Ev_2pics_Minus:str="Single Bracket 2.5EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_25Ev_3pics:str="Single Bracket 2.5EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_25Ev_5pics:str="Single Bracket 2.5EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_27Ev_2pics_Plus:str="Single Bracket 2.7EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_27Ev_2pics_Minus:str="Single Bracket 2.7EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_27Ev_3pics:str="Single Bracket 2.7EV 3pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_27Ev_5pics:str="Single Bracket 2.7EV 5pics";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_30Ev_2pics_Plus:str="Single Bracket 3.0EV 2pics+";break;
    case SDK::CrDriveMode::CrDrive_Single_Bracket_30Ev_2pics_Minus:str="Single Bracket 3.0EV 2pics-";break;
    case SDK::CrDriveMode::CrDrive_FocusBracket:str="Focus Bracket";break;
    default:str="error";break;
    }
    return str;
}

QString format_focus_area(std::uint16_t value)
{
    QString str;
    switch (value) {
    case SDK::CrFocusArea::CrFocusArea_Unknown:
        str="Unknown";
        break;
    case SDK::CrFocusArea::CrFocusArea_Wide:
        str="广域";
        break;
    case SDK::CrFocusArea::CrFocusArea_Zone:
        str="区";
        break;
    case SDK::CrFocusArea::CrFocusArea_Center:
        str="中心";
        break;
    case SDK::CrFocusArea::CrFocusArea_Flexible_Spot_S:
        str="点S";
        break;
    case SDK::CrFocusArea::CrFocusArea_Flexible_Spot_M:
        str="点M";
        break;
    case SDK::CrFocusArea::CrFocusArea_Flexible_Spot_L:
        str="点L";
        break;
    case SDK::CrFocusArea::CrFocusArea_Expand_Flexible_Spot:
        str="扩展点";
        break;
    case SDK::CrFocusArea::CrFocusArea_Flexible_Spot:
        str="点";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Wide:
        str="跟踪-广域";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Zone:
        str="跟踪-区";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Center:
        str="跟踪-中心";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Flexible_Spot_S:
        str="跟踪-点S";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Flexible_Spot_M:
        str="跟踪-点M";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Flexible_Spot_L:
        str="跟踪-点L";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Expand_Flexible_Spot:
        str="跟踪-扩展点";
        break;
    case SDK::CrFocusArea::CrFocusArea_Tracking_Flexible_Spot:
        str="跟踪-点";
        break;
    default:
        str="error";
        break;
    }
    return str;
}

QString format_zoom_type_status(std::uint8_t value)
{
    QString str;
    switch (value) {
    case SDK::CrZoomTypeStatus::CrZoomTypeStatus_ClearImageZoom:str="清晰图像变焦";break;
    case SDK::CrZoomTypeStatus::CrZoomTypeStatus_DigitalZoom:str="数字变焦";break;
    case SDK::CrZoomTypeStatus::CrZoomTypeStatus_OpticalZoom:str="仅光学变焦";break;
    case SDK::CrZoomTypeStatus::CrZoomTypeStatus_SmartZoom:str="仅智能变焦";break;
    default:str="error"; break;
    }
    return str;
}


QString format_zoom_setting(std::uint8_t value)
{
    QString str;
    switch (value) {
    case SDK::CrZoomSettingType::CrZoomSetting_On_ClearImageZoom:str="清晰图像缩放";break;
    case SDK::CrZoomSettingType::CrZoomSetting_On_DigitalZoom:str="数字变焦";break;
    case SDK::CrZoomSettingType::CrZoomSetting_OpticalZoomOnly:str="仅光学变焦";break;
    case SDK::CrZoomSettingType::CrZoomSetting_SmartZoomOnly:str="仅智能变焦";break;
    default:str="error"; break;
    }
    return str;
}

QString format_BatteryRemainDisplayUnit(std::uint8_t value)
{
    QString str;
    switch (value)
    {
        case SDK::CrBatteryRemainDisplayUnit::CrBatteryRemainDisplayUnit_minute:str="min";break;
        case SDK::CrBatteryRemainDisplayUnit::CrBatteryRemainDisplayUnit_percent:str="%";break;
        case SDK::CrBatteryRemainDisplayUnit::CrBatteryRemainDisplayUnit_voltage:str="V";break;
        default:str=""; break;
    }
    return str;
}

QString format_MediaSLOT_Status(std::uint16_t value)
{
    QString str;
    switch (value)
    {
    case SDK::CrSlotStatus_OK:str="OK";break;
    case SDK::CrSlotStatus_NoCard:str="No card";break;
    case SDK::CrSlotStatus_CardError:str="Card error";break;
    case SDK::CrSlotStatus_RecognizingOrLockedError:str="Card error";break;
    default:str=""; break;
    }
    return str;
}


QString format_PC_Save_Image(std::uint16_t value)
{
    QString str;
    switch (value)
    {
    case SDK::CrPropertyRAWJPCSaveImage_RAWAndJPEG:str="RAW & JPEG";break;
    case SDK::CrPropertyRAWJPCSaveImage_JPEGOnly:str="JPEG Only";break;
    case SDK::CrPropertyRAWJPCSaveImage_RAWOnly:str="RAW Only";break;
    case SDK::CrPropertyRAWJPCSaveImage_RAWAndHEIF:str="RAW & HEIF";break;
    case SDK::CrPropertyRAWJPCSaveImage_HEIFOnly:str="HEIF Only";break;
    default:str=""; break;
    }
    return str;
}


QString format_DispMode(std::uint8_t value)
{
    QString str;
    switch (value)
    {
    case SDK::CrDispMode::CrDispMode_GraphicDisplay:str="图像显示";break;
    case SDK::CrDispMode::CrDispMode_DisplayAllInfo:str="显示全部";break;
    case SDK::CrDispMode::CrDispMode_NoDispInfo:str="不显示";break;
    case SDK::CrDispMode::CrDispMode_Histogram:str="直方图";break;
    case SDK::CrDispMode::CrDispMode_Level:str="水平线";break;
    case SDK::CrDispMode::CrDispMode_ForViewFinder:str="取景器";break;
    case SDK::CrDispMode::CrDispMode_MonitorOff:str="关闭";break;
    default:str=""; break;
    }
    return str;
}

QString format_AspectRatio(std::uint16_t value)
{
    QString str;
    switch (value)
    {
    case SDK::CrAspectRatioIndex::CrAspectRatio_3_2:str="3:2";break;
    case SDK::CrAspectRatioIndex::CrAspectRatio_16_9:str="16:9";break;
    case SDK::CrAspectRatioIndex::CrAspectRatio_4_3:str="4:3";break;
    case SDK::CrAspectRatioIndex::CrAspectRatio_1_1:str="1:1";break;
    default:str=""; break;
    }
    return str;
}

QString format_LiveViewDisplayEffect(std::uint16_t value)
{
    QString str;
    switch (value)
    {
    case SDK::CrLiveViewDisplayEffect::CrLiveViewDisplayEffect_Unknown:str="Unknown";break;
    case SDK::CrLiveViewDisplayEffect::CrLiveViewDisplayEffect_ON:str="开";break;
    case SDK::CrLiveViewDisplayEffect::CrLiveViewDisplayEffect_OFF:str="关";break;
    default:str=""; break;
    }
    return str;
}

QString format_LiveViewImageQuality(std::uint16_t value)
{
    QString str;
    switch (value)
    {
    case SDK::CrPropertyLiveViewImageQuality::CrPropertyLiveViewImageQuality_Low:str="低画质";break;
    case SDK::CrPropertyLiveViewImageQuality::CrPropertyLiveViewImageQuality_High:str="高画质";break;
    default:str=""; break;
    }
    return str;
}

}
