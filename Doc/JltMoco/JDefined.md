# **JDefined**

JltMoco > JDefined

## 描述

命名空间: JMOCO

QML环境中属性调用示例： JMOCO.Device_Robot

### 枚举数据集合

* 继承：QObject

---

## 属性说明

> 设备编号列表

|  值       |  属性             | 描述      |
| :----:    |  :----            | :----:    |
|1          | Device_Robot      | 机械臂    |
|2          | Device_Camera     | 相机  |
|3          | Device_FollowFocus     | 跟焦器  |
|4          | Device_Turntable     | 转盘  |
|5          | Device_Laserlight     | 激光  |
|6          | Device_OpenCv     | 跟随  |

> 影棚控制状态

|  值       |  属性                     | 描述      |
| :----:    |  :----                    | :----:    |
|0          | StudioCtrlCode_None       | 影棚未连接的状态    |
|256        | StudioCtrlCode_Remote     | 设备遥控状态(连接成功 或 复位完成后 或 运行完成后的状态)    |
|257        | StudioCtrlCode_JogStop    | 手动停止    |
|258        | StudioCtrlCode_Img_AutoFollow    | 平面自动跟随    |
|259        | StudioCtrlCode_Img_AutoFollowStop    | 平面自动跟随停止    |
|512        | StudioCtrlCode_NodeReset    | 复位状态(数据验证成功后的状态)    |
|513        | StudioCtrlCode_NodeReset_Start    | 复位运动启动    |
|514        | StudioCtrlCode_NodeReset_Complete    | 复位运动完成    |
|768        | StudioCtrlCode_ScriptExec    | 执行状态(接口调用成功,并开始)    |
|784        | StudioCtrlCode_ScriptExec_Image_Start    | 平面脚本执行运动启动    |
|785        | StudioCtrlCode_ScriptExec_Image_Complete    | 平面脚本执行运动完成    |
|786        | StudioCtrlCode_ScriptExec_Image_BootFailed    | 平面脚本执行运动失败(复位运动从准备后的1s内未启动,则表示启动失败)   |
|800        | StudioCtrlCode_ScriptExec_Movie_Start    | 视频脚本执行运动启动   |
|801        | StudioCtrlCode_ScriptExec_Movie_Complete    | 视频执行运动完成    |
|802        | StudioCtrlCode_ScriptExec_Movie_BootFailed    | 视频脚本执行运动失败(复位运动从准备后的1s内未启动,则表示启动失败)    |
