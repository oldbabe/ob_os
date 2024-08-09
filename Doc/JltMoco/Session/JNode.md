# **JNode Class**

## 描述

### JNode是对脚本节点管理的数据类

* 继承：QObject
* Qml对象名： JNode
  
---

## 属性说明

> index : int

节点索引

> robot : JNodeRobot

节点中机械臂的数据对象

> camera : JNodeCamera

节点中相机的数据对象

> followfocus : JNodeFollowFocus

节点中跟焦器的数据对象

> trunplate : JNodeTurnplate

节点中转盘的数据对象

> x : real

节点在场景的x坐标

> y : real

节点在场景的y坐标

> width : real

节点在场景的宽度

> heigth : real

节点在场景的高度

> title : string

节点标题

> preview : string

节点预览图地址

---

## 方法说明

> QJsonObject toJson();

* 描述: 返回节点数据(JSON格式)
