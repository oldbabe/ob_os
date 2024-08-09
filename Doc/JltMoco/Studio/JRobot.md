# **JSession Class**

JltMoco > Studio > DeviceRobot
QML > JRobot

## 描述

### DeviceRobot是影棚的机械臂管理对象

* 继承：QObject

---

## 属性说明

> connected : bool

* 描述: 连接状态 =true已连接

> runNumber : int

* 描述: 机械臂的运行编号

> position : JRobotArray

实时位置数据 .x .y .z  .rx .ry .rz .a1 .a2 .a3 .a4 .a5 .a6 .a7

> model : string

机械臂型号(只读)

> address : string

机械臂IPV4地址

> railAddress : string

机械臂附加的轨道IPV4地址

---

## 信号说明

void railConnectedChanged(bool state);

轨道的连接状态改变=true已连接 =false连接失败

---

## 方法说明

> void centerCircle3d(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

* 描述: 圆弧计算
* 参数：x1 起始点空间位置X
* 参数：y1 起始点空间位置Y
* 参数：z1 起始点空间位置Z
* 参数：x2 辅助点空间位置X
* 参数：y2 辅助点空间位置Y
* 参数：z2 辅助点空间位置Z
* 参数：x3 目标点空间位置X
* 参数：y3 目标点空间位置Y
* 参数：z3 目标点空间位置Z
* 返回值：[圆心x,圆心y,圆心z,半径,圆心角]
  