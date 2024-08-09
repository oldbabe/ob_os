# **JSession Class**

JltMoco > Studio > DeviceFollowfocus
QML > JFollowfocus

## 描述

### DeviceFollowfocus是影棚的跟焦器管理对象

* 继承：QObject

---

## 属性说明

> portName : String

* 描述: 端口号

> connected : bool

* 描述: 连接状态 =true已连接

> focus : int

* 描述: 对焦值 范围 0~7200

> zoom : int

* 描述: 变焦值  范围 0~7200
  
> iris : int

* 描述: 光圈值  范围 0~7200
  
> focusEnable : bool

* 描述: 对焦控制使能/禁用

> zoomEnable : bool

* 描述: 变焦控制使能/禁用
  
> irisEnable : bool

* 描述: 光圈控制使能/禁用

---

## 方法说明

> void connectDevice();

* 描述: 连接,需要设置端口名

> void disconnectDevice();

* 描述: 断开连接

> void calibrateDevice();

* 描述: 校准启动

> void remoteValues(int f,int z = -1,int i  = -1)

* 描述: 对焦 变焦 光圈同时控制
