# **JCameraDevice Class**

QML > JCameraDevice

## 描述

### 采集卡视频流设备

* 继承：QThread

---

## 属性说明

> currentIndex : int

* 描述: 相机索引(只读)

> videoSink : QVideoSink

* 描述: 若要使用视频流,则需要提前赋值

> rotateFlag : RotateFlags

* 描述: 视频旋转角度
* RotateFlags enum{
  RotateFlag_0, //0°
  RotateFlag_90, //90°
  RotateFlag_180, //180°
  RotateFlag_270 //270°
  }

> horizontalMirrored : bool

* 描述: 水平镜像

> verticalMirrored : bool

* 描述: 垂直镜像

> stopImage : QString

* 描述: 视频关闭时需要显示的预览图像

> centerEnable : bool

* 描述: 居中使能；=true启动图像识别遥控 =false关闭；注意需要存在相机视频流。

> gridFlag : GridFlags

* 描述: 视频旋转角度
* GridFlags enum {
  GridFlags_Close,  //关闭网格
  GridFlags_Trisector,  //三等分网格
  GridFlags_Square, //方形网格
  GridFlags_Diagonal    //方向+对角网格
  }

---

## 方法说明

> QStringList cameraList();

* 描述: 返回可用相机列表
  
> void play(int index);

* 描述: 启动播放相机
* 参数: index 相机索引

> void stop();

* 描述: 停止播放相机
