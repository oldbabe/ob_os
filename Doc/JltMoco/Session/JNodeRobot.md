# **JNodeRobot Class**

## 描述

### JNodeRobot是对脚本节点管理的数据类

* 继承：QObject
* Qml对象名： JNodeRobot
  
---

## 属性说明

> type : int

运动类型=1 PTP =2 LINE =3 ARCO

> prgV : int

程序速度1~100

> robotV : int

机械臂速度1~100

> robotA : int

机械臂速度1~100

> pathV : int

轨道速度1~100

> pathA : int

轨道速度1~100

> tsValue : int

过度值0~500

> waiting : int

等待数据/s

> assistCA : int

圆弧运动的圆心角

> target : JRobotArray

目标点数据对象 .x .y .z  .rx .ry .rz .a1 .a2 .a3 .a4 .a5 .a6 .a7

> assist : JRobotArray

辅助点数据对象 .x .y .z  .rx .ry .rz .a1 .a2 .a3 .a4 .a5 .a6 .a7

---

## 方法说明

> void updataTarget();

* 描述: 更新目标数据

> void updataAssist();

* 描述: 更新辅助数据
