# **JNodeCamera Class**

## 描述

### JNodeCamera是对脚本节点管理的数据类

* 继承：QObject
* Qml对象名： JNodeCamera
  
---

## 属性说明

> imageInterval : int

拍摄间隔时间/s

> imageNum : int

拍摄次数

> shootMode : int

拍摄模式=0直接拍摄 =1自动AF =2半按快门(按下) =3半按快门(松开)

---

## 方法说明

> QJsonObject toJson();

* 描述: 返回节点数据(JSON格式)
