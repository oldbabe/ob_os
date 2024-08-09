# **JSession Class**

C++ -> JltMoco > Followfocus
QML > JFollowfocusRemote

## 描述

### JFollowfocusRemote 跟焦器遥控端设备管理

当方法 setup() 被调用后,将自动连接到已设置的端口号

* 继承：QObject

---

## 属性说明

> connected : bool

当跟焦器遥控器连接成功时=true，反之为false

> portName : string

端口名称

> focus : int

对焦值0~7200

> zoom : int

变焦值0~7200

> iris : int

光圈值0~7200

---

## 方法说明

> void setup();

* 描述: 初始化
  
> void uninstall();

* 描述: 释放
