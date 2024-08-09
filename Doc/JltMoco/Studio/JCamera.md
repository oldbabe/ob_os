# **JSession Class**

JltMoco > Studio > DeviceCamera
QML > JCamera

## 描述

### DeviceCamera是影棚的相机管理对象

* 继承：QObject

---

## 属性说明

> connected : bool

* 描述: 连接状态 =true连接

> cameraName : string

* 描述: 相机名

> downloadDir : string

* 描述: 下载目录

> downloadFileName : string

* 描述: 最近时间下载的文件名

> transferState : int

* 描述: 文件传输状态-1文件传输被禁用 -2文件列表是空的 -3无存储卡 -4读取错误 =1开始下载 =0下载完成 =2下载失败 =3读取相机文件列表 =其它错误

> remoteMode : DeviceCameraProperty

* 描述: 遥控模式
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> fNumber : DeviceCameraProperty

* 描述: 光圈
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> shutterSpeed : DeviceCameraProperty

* 描述: 快门速度
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> isoSensitivity : DeviceCameraProperty

* 描述: ISO
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> programMode : DeviceCameraProperty

* 描述: 程序模式
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> fileType : DeviceCameraProperty

* 描述: 静态影像文件格式
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> jpegQuality : DeviceCameraProperty

* 描述: jpeg质量
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> whiteBalance : DeviceCameraProperty

* 描述: 白平衡
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> movieFileFormat : DeviceCameraProperty

* 描述: 动态影像文件格式
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> movieRecording : DeviceCameraProperty

* 描述: 动态影像记录设置
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> movieRecordingFrameRate : DeviceCameraProperty

* 描述: 动态影像记录帧速率
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> rawFileCompressionType : DeviceCameraProperty

* 描述: raw文件类型
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> focusMode : DeviceCameraProperty

* 描述: 对焦模式
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> recordingState : DeviceCameraProperty

* 描述: 录制状态
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> driveMode : DeviceCameraProperty

* 描述: 拍摄模式
* 子属性：DeviceCameraProperty=> key:int,writable:int,value:QString,values:QStringList

> focusArea : DeviceCameraProperty

* 描述: 对焦区域

> exposureBiasAompensation : DeviceCameraProperty

* 描述: 曝光补偿 EV值 (相机设置要求:ISO 必须为AUT)

> flashAompensation : DeviceCameraProperty

* 描述: 闪光补偿

> batteryRemaining : DeviceCameraProperty

* 描述: 剩余电量.(相机设置要求:显示类型为百分比)

> dispMode : DeviceCameraProperty

* 描述: DISP

> aspectRatio : DeviceCameraProperty

* 描述: 长宽比
  
> nearFar : DeviceCameraProperty

* 描述: 对焦操作 ["-7","7","1"]
  
> zoomSetting : DeviceCameraProperty

* 描述: 变焦模式
  
> zoomOperationStatus : DeviceCameraProperty

* 描述: 变焦是否可以操作(writeable = "1"可以操作)
  
> zoomRange : DeviceCameraProperty

* 描述: 变焦范围 ["-8","8","1"]
  
> liveViewDisplayEffect : DeviceCameraProperty

* 描述: 实时取景显示
  
> liveViewImageQuality : DeviceCameraProperty

* 描述: 实时图像质量

---

## 信号说明

> downloadDirSetResult(bool result);

* 描述: 相机设置下载目录结果.=true设置成功 =false设置失败

---

## 方法说明

> void setProperty(int key,int index);

* 描述: 设置相机属性
  
> void setDownloadDirectory(const QString &dir);

* 描述: 设置相机下载目录

> void shooting(int mode);

* 描述: 快门操作=0直接拍摄 =1自动AF拍摄 =2半按快门(按下) =3半按快门(松开)

> void s1Shooting(bool mode);

* 描述: 半按快门=true按下 =false松开

> void filmRecording(bool state);

* 描述: 录制=true启动录制

> void quickFormat();

* 描述: 快速格式化

> void downloadEndFile();

* 描述: 下载末尾文件

> void realTimeImageDownload(const QString &fileName);

* 描述: 实时图像下载
* 参数：fileName文件地址 示例： "B:/example.PNG"

> void setFocusPosition(qreal x,qreal y,int mode = 0);

* 描述: 设置焦点位置
* 参数：x 0~1.0
* 参数：y 0~1.0
* 参数：mode=0仅设置对焦点 =1设置对焦点并对焦 =2设置对焦点并对焦并自动拍摄

> void nearFarOperation(int value);

* 描述: 对焦拉近拉远
* 参数：value -7~-1,1~7.

> void zoomOperation(int value);

* 描述: 变焦操作
* 参数：value -8~8
  