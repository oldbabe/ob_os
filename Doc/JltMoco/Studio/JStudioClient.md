# **JSession Class**

JltMoco > StudioClient > StudioClient
QML > JStudioClient

## 描述

### StudioClient是控制影棚的单例类

* 继承：QObject

---

## 属性说明

> connected : int

* 描述: 影棚连接状态 =0未连接 =1查找目标主机中 =2连接中 =3已连接

> serverAddr : string

* 描述: 服务器地址IPV4

> studioCtrlState : int

* 描述: 影棚控制状态

> number : int

* 描述: 影棚编号

> type : int

* 描述: 影棚类型 =0静物=1人像

---
  
---

## 信号说明

> void statusChanged(const QJsonObject &status)

* 描述: 影棚状态数据改变
* 参数： status JSON数据

> void followFoucsTimerChanged()

* 描述: 跟焦器遥控器的定时器改变,(跟焦器手动模式下发送10fps,自动模式下禁止前端控制跟焦器)

---

## 方法说明

> void init();

* 描述: 影棚初始化
  
> void release();

* 描述: 影棚内存释放

> void connectServer(const QString &addr);

* 描述: 连接影棚
* 参数： addr IPV4地址

> void disConnectServer();

* 描述: 断开影棚连接

> void disConnectServer();

* 描述: 断开影棚连接

> void sendRemoteCommand(jsobject obj);

* 描述: 发送遥控指令
* 参数: obj JSON数据对象

> void isTargetPos(jsobject obj);

* 描述: 节点设备是否在目标位置
* 参数: obj JSON节点数据对象

> int nodeReset(int number,jsobject obj);

* 描述: 节点复位
* 参数: number 节点序号
* 参数: obj JSON节点数据对象
* 返回值: =0发送成功 =1失败

> int scriptRun(jsobject obj,moveMode = 1,followfocusMode = 1);

* 描述: 脚本运行
* 参数: obj JSON脚本数据
* 参数: moveMode =0仅运动 =1拍摄+运动
* 参数: followfocusMode =0手动模式 =1自动模式
* 返回值: =0发送成功 =1失败

> void followfocusTimerStart(array focusValues,array zoomValues,mode = 1);

* 描述: 跟焦器计时器启动
* 参数: focusValues 对焦记录
* 参数: zoomValues 变焦记录
* 参数: mode =0手动模式 =1自动模式

> void followfocusTimerClose();

* 描述: 跟焦器计时器关闭

> void studioRunJogStop();

* 描述: 影棚运动停止

> void setJsonConfig(const QString &key,const QJsonObject &obj)

* 描述: 设置JSON类型的配置
* 参数: key 查找密钥
* 参数: obj 内容

> QJsonObject getJsonConfig(const QString &key)

* 描述: 返回JSON类型的配置
* 参数: key 查找密钥
* 返回值: JSON 内容
