# **JScript Class**

JltMoco > Studio > DeviceScript
QML > JScriptController

## 描述

### DeviceScript是影棚的脚本管理对象

* 继承：QObject

---

## 属性说明

> index : int

* 描述: 脚本执行时运动序号

> frameCounter : quint64

* 描述: 执行帧序号

## 信号说明

> followFocusNodeDataChanged(int index,jsonobject nodeData)

* 视频和平面节点脚本的统一修改为一下内容. 其中 (FocusMode/ZoomMode/IrisMode) =0固定值 =1手动遥控 =2手动&记录 =3记录回放;
该信号仅在节点数据的(FocusMode/ZoomMode/IrisMode)=2时发出.

* index 脚本节点的索引

* nodeData内容如下(仅当#Mode=3时,#Value和#Record才会被定义):
{
    "Length":0,
    "FocusValue : 0,
    "FocusMode":0,
    "FocusRecord":{},
    "ZoomValue : 0,
    "ZoomMode":0,
    "ZoomRecord":{},
    "IrisValue : 0,
    "IrisMode":0,
    "IrisRecord":{}
}
