# **JSession Class**

C++ -> JltMoco > Gamepad
QML > JGamepad

## 描述

### JGamepad是接收手柄数据的单例类

* 继承：QObject

---

## 属性说明

> connected : bool

* 描述: 影棚连接状态 =true连接 =false未连接

---
  
## 信号说明

> void statusChanged(const QJsonObject &status)

* 描述: 手柄状态数据改变
* 参数： status JSON数据

手柄状态数据说明
'''
{
    "up >bool":false,
    "down >bool":false,
    "left >bool":false,
    "right >bool":false,
    "start >bool":false,
    "back >bool":false,
    "l3 >bool":false,
    "r3 >bool":false,
    "l1 >bool":false,
    "r1 >bool":false,
    "l2 >real":0,
    "r2 >real":0,
    "keyA >bool":false,
    "keyB >bool":false,
    "keyX >bool":false,
    "keyY >bool":false,
    "axisLeftX >real":0,
    "axisLeftY >real":0,
    "axisRightX >real":0,
    "axisRightY >real":0,
}
'''

---

## 方法说明

> void init();

* 描述: 手柄初始化,必须在使用前调用
  
> void release();

* 描述: 手柄释放,必须在退出前调用
