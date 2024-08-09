# **StudioController Class**

JltMoco > StudioController
QML > JStudioController

## 描述

### StudioController是控制影棚的单例类

* 继承：QObject

---

## 枚举说明

> ControllerType : enum
影棚控制类型枚举说明

* LocalControllerOnly:仅本地控制器
* LocalControllerServer:本地控制器+服务器
* RemoteControllerOnly:仅远程控制器
  
---

## 属性说明

> controllerType : ControllerType

* 描述: 当前的影棚控制类型
  
---

## 方法说明

> void init();

* 描述: 当controllerType=LocalControllerOnly将初始化影棚设备,当controllerType=LocalControllerServer将初始化影棚设备并启动控制服务器,当controllerType=RemoteControllerOnly将初始化影棚客户端.
  
> void release();

* 描述: 根据 controllerType 进行设备释放

> void ports();

* 描述: 返回可用端口号列表 ["COM1",...]

> void localHostName();

* 描述: 返回当前主机的IPV4地址
  