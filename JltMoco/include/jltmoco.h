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
#ifndef JLTMOCO_H
#define JLTMOCO_H

#include "global.h"
#include <QObject>

namespace jltmoco
{
Q_NAMESPACE_EXPORT(DEVICECONTROLLER_EXPORT);
//Q_NAMESPACE

//设备控制权限
enum DeviceCtrlPower
{
    DeviceCtrlPower_User = 0,      //用户
    DeviceCtrlPower_Script,        //脚本
    DeviceCtrlPower_All,           //全部
};
Q_ENUM_NS(DeviceCtrlPower);

//设备编号
enum DeviceNumber
{
    Device_Robot = 1,      //机械臂&轨道
    Device_Camera,         //相机
    Device_FollowFocus,    //跟焦器
    Device_Turntable,      //转盘
    Device_Laserlight,     //激光
    Device_OpenCv,         //OpenCv
    Device_ScriptController         //ScriptController
};
Q_ENUM_NS(DeviceNumber);

//脚本指令编码
enum ScriptCommandCode  : int
{
    ScriptCommandCode_Null = 0,         //空
    ScriptCommandCode_Stop,             //停止运行
    ScriptCommandCode_NodeReset,        //节点复位
    ScriptCommandCode_ScriptExec,       //脚本执行
    ScriptCommandCode_ScriptExecImage,        //脚本执行-静态影像拍摄
    ScriptCommandCode_ScriptExecMovie,        //脚本执行-动态影像拍摄
    ScriptCommandCode_NodeDataChanged,        //脚本节点数据改变
};
//影棚控制状态编码
enum StudioCtrlCode
{
    StudioCtrlCode_None = 0,                //禁用状态(影棚未连接的状态)

    StudioCtrlCode_Remote = 0x100,          //设备待机状态(连接成功 或 复位完成后 或 运行完成后的状态)
    StudioCtrlCode_JogStop,                 //手动停止
    StudioCtrlCode_Img_AutoFollow,          //平面自动跟随
    StudioCtrlCode_Img_AutoFollowStop,      //平面自动跟随停止

    StudioCtrlCode_NodeReset = 0x200,       //复位状态(数据验证成功后的状态)
    StudioCtrlCode_NodeReset_Start,         //复位运动启动
    StudioCtrlCode_NodeReset_Complete,      //复位运动完成

    StudioCtrlCode_ScriptExec = 0x300,      //执行状态(接口调用成功,并开始)

    StudioCtrlCode_ScriptExec_Image_Start = 0x310,      //平面脚本执行运动启动
    StudioCtrlCode_ScriptExec_Image_Complete,           //平面脚本执行运动完成
    StudioCtrlCode_ScriptExec_Image_BootFailed,         //平面脚本执行运动失败(复位运动从准备后的1s内未启动,则表示启动失败)

    StudioCtrlCode_ScriptExec_Movie_Start = 0x320,      //平面脚本执行运动启动
    StudioCtrlCode_ScriptExec_Movie_Complete,           //视频执行运动完成
    StudioCtrlCode_ScriptExec_Movie_BootFailed,         //平面脚本执行运动失败(复位运动从准备后的1s内未启动,则表示启动失败)
};
Q_ENUM_NS(StudioCtrlCode);

//脚本运行模式
enum ScriptRunModeCode  : int
{
    ScriptRunModeCode_MotionOnly = 0,        //仅运动
    ScriptRunModeCode_ShootAndMotion,        //拍摄+运动
};

//脚本拍摄模式
enum ScriptShootModeCode  : int
{
    ScriptShootModeCode_Image = 1,          //平面拍摄
    ScriptShootModeCode_Moive,              //视频拍摄
};

//脚本运行模式
enum ScriptRunErrorCode  : int
{
    ScriptRunErrorCode_Data = 0,        //脚本数据错误
    ScriptRunErrorCode_StudioDisconnected,//影棚未连接
    ScriptRunErrorCode_RobotDisconnected,//影棚的机械臂未连接
    ScriptRunErrorCode_CameraDisconnected,//影棚的相机未连接
};


//机械臂返回编码
enum RobotRequestCode  : int
{
    RobotRequestCode_StateChanged = 1,//状态改变
};

//机械臂状态编码
enum RobotStateCode  : int
{
    RobotStateCode_Stop = 0,//0停止状态
    RobotStateCode_Jog, //1手动运动状态
    RobotStateCode_Abs,//2绝对运动状态
    RobotStateCode_Continuous,//3绝对运动状态(仅运动)
    RobotStateCode_Continuous_Load,//4绝对运动状态(加载next node)
};
//机械臂操作编码
enum RobotRemoteCode  : int
{
    RobotRemote_Stop = 1,//停止
    RobotRemote_JogAxis,//2手动axis
    RobotRemote_JogPos,//3手动pos
    RobotRemote_AbsAxis,//4绝对axis
    RobotRemote_AbsPos,//5绝对pos
    RobotRemote_ContinuousLoad,//6连续运动
    RobotRemote_ContinuousLoadFinished,//7连续运动数据加载结束(节点数小于3时必须显示的发送)
    RobotRemote_ContinuousRunning,//8连续运行中
    RobotRemote_JogPosTool, //9手动pos 参考坐标系tool
    RobotRemote_SetToolCoordAdd   //设置工具坐标系增量
};
//相机状态编码
enum CameraStateCode
{
    CameraStateCode_Remote = 1, //空闲状态可以遥控
    CameraStateCode_Shoot,      //拍摄状态
    CameraStateCode_Record,     //录制状态
};
//相机返回编码
enum CameraRequestCode : int
{
    CameraRequestCode_Property = 1,         // 属性设置
    CameraRequestCode_State,                //
    CameraRequestCode_SetSaveDir,           //设置保存目录结果
    CameraRequestCode_ImageDownload,        //静态影像下载完成
    CameraRequestCode_MovieDownload,        //动态影像下载完成
    CameraRequestCode_RealTimeImg,          //实时图像操作反馈
};

//相机操作编码
enum CameraOperationCode : int
{
    CameraOperationCode_PropertySet = 1,    //属性设置
    CameraOperationCode_SaveDir,            //保存路径设置
    CameraOperationCode_ImageShoot,         //平面拍摄(单张拍摄)
    CameraOperationCode_FilmRecording,      //电影录制
    CameraOperationCode_SLOT1_QuickFormat,          //slot1快速格式化
    CameraOperationCode_SLOT2_QuickFormat,          //slot2快速格式化
    CameraOperationCode_SLOT1_LastFileDownload,     //slot1最后拍摄文件下载
    CameraOperationCode_RealTimeImg_Local,          //本地更新实时图像
    CameraOperationCode_RealTimeImg_NAS,            //NAS更新实时图像
    CameraOperationCode_FoucsPosition,            //设置角度位置
};

//跟焦器操作编码
enum FollowfocusCommand  : int
{
    FollowfocusCommand_Init = 1,       //校准
    FollowfocusCommand_FocusRemote,    //对焦控制
    FollowfocusCommand_ZoomRemote,     //变焦控制
    FollowfocusCommand_AllRemote,      //跟焦控制("FocusValue":0,"ZoomValue":0,"IrisValue":0)
    FollowfocusCommand_Connect,        //连接
    FollowfocusCommand_Disonnect,      //断开
    FollowfocusCommand_IrisRemote,      //光圈控制
    FollowfocusCommand_FocusEnable,    //对焦使能
    FollowfocusCommand_ZoomEnable,     //变焦使能
    FollowfocusCommand_IrisEnable      //光圈使能
};

//跟焦器状态编码
enum FollowfocusStateCode  : int
{
    FollowfocusStateCode_Init = 0,       //初始化状态
    FollowfocusStateCode_Remote,         //待遥控状态
    FollowfocusStateCode_Calibration,    //校准状态
    FollowfocusStateCode_Abs,            //绝对运动状态
};

//跟焦器状态编码
enum FollowFocusScriptMode  : int
{
    FollowFocusScriptMode_Fix = 0,      //固定值
    FollowFocusScriptMode_Remote,       //遥控
    FollowFocusScriptMode_Record,       //记录遥控
    FollowFocusScriptMode_Playback,     //记录回放
    FollowFocusScriptMode_Curve,       //自定义曲线
};

//转盘操作编码
enum TurnplateOperationCode  : int
{
    TurnplateOperationCode_Init = 1,       //校准
    TurnplateOperationCode_Stop,            //运动停止
    TurnplateOperationCode_SpeedMode,       //速度模式控制
    TurnplateOperationCode_PosMode,         //位置模式控制
    TurnplateOperationCode_PortName = 10    //端口号com
};

//跟焦器操作编码
enum TurnplateStateCode  : int
{
    TurnplateStateCode_Init = 1,       //校准
    TurnplateStateCode_Stop,            //运动停止
    TurnplateStateCode_SpeedMode,       //速度模式控制
    TurnplateStateCode_PosMode,         //位置模式控制
};

//影棚客户端任务编码
enum RunTaskCode  : int
{
    RunTaskCode_AbsPos = 1,     //绝对运动任务
    RunTaskCode_ImageShoot,     //平面拍摄任务
    RunTaskCode_Delay,          //延迟任务
    RunTaskCode_Contine,        //连续运动加载任务
    RunTaskCode_ContineDelay,   //连续运动加载任务(满足机械臂预读的节点数)
    RunTaskCode_ContineStart,   //连续运动启动任务
    RunTaskCode_CameraRealTimeImg,//相机实时图像
};

}

#endif // JLTMOCO_H
