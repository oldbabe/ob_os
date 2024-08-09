# **JSession Class**

JltMoco > Studio > StudioConfig
QML > JStudioConfig

## 描述

### StudioConfig是影棚的配置信息管理对象

* 继承：QObject

---

## 属性说明

> serverAddr : string

* 描述: 服务器地址

> robotAddr : string

* 描述: 机械臂地址

> railAddr : string

* 描述: 轨道地址

> number : int

* 描述: 影棚编号

> type : int

* 描述: 影棚类型

> followfocusPortName : string

* 描述: 跟焦器端口名

> turnplatePortName : string

* 描述: 转盘端接名

> railDeviceAddr : string

* 描述: 轨道地址

---

## 方法说明

> void setCtrlEnable(bool state);

* 描述: 设置本地控制状态
* 参数：state=true时启用本地影棚控制器
  
> bool getCtrlEnable();

* 描述: 读取本地控制状态

> void setJsonConfig(const QString &key,const QJsonObject &obj);

* 描述: 设置JSON内容配置
* 参数：唯一识别钥匙key
* 参数：obj JSON内容

> QJsonObject getJsonConfig(const QString &key)

* 描述: 读取JSON内容配置
* 参数：唯一识别钥匙key
  