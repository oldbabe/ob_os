# **JScript Class**

## 描述

### JScript是对脚本文件进行管理的单例类

* 继承：QObject
* Qml对象名： JScript
  
---

## 属性说明

> fileName : string

脚本文件地址

> version : string

脚本文件版本

> scriptType : ScriptType
QML可调用并设置列表:
[
    JScript.ScriptType_Image = 1,
    JScript.ScriptType_Video,
    JScript.ScriptType_Other
]

脚本类型

> remoteMode : RemoteMode
QML可调用并设置列表:
[
    JScript.RemoteMode_MoveOnly = 0,//仅运动
    JScript.RemoteMode_MoveShooting//运动并拍摄
]

遥控模式

> recordingDuration : int

录制时长

> moveDelay : int

运动准备时间

> currentIndex : int

选中的索引

> currentNode : JNode

选中的节点数据对象

> acc : int

视频脚本的转盘加速度 1~100

> dec : int

视频脚本的转盘减速度 1~100

> speed : int

视频脚本的转盘速度 1~100

> duration : int

视频脚本的转盘运动时间

> direction : int

视频脚本的转盘运动方向 1正向 -1反向

> startTime : int

视频脚本的转盘运动开始时间

> sceneX : real

场景在视图的x坐标

> sceneY : real

场景在视图的y坐标

> sceneWidth : real

场景宽度

> sceneHeigth : real

场景高度

---

## 方法说明

> int count();

* 描述: 返回脚本节点的数量
  
> JNode* get(int index)

* 描述: 返回index的节点数组的项
* 参数：index 节点数组索引

> JNode *appendLast(real w,real h)

* 描述: 节点数组的末尾添加一个项,并返回该数据对象。最大速度自动更新为前一个节点的数据,当机械臂已加载并连接时,机械臂target自动更新和assist数据自动更新,反之则更新为前一个节点数据.
* 参数：w 节点宽度
* 参数：h 节点高度

> void removeLast();

* 描述: 节点数组的末尾删除一个项

> void save();

* 描述: 当文件地址存在时,则保存文件内容

> QJsonObject toJson();

* 描述: 返回脚本数据(JSON格式)

> void indexReset(int index);

* 描述: 给定索引的节点进行就位
* 参数：index 给定索引

> void resetStop();

* 描述: 就位停止

> void runStart(int runmode);

* 描述: 脚本运行启动
* 参数：runmode =0仅运动=1录制且运动

> void runStop();

* 描述: 脚本运行停止