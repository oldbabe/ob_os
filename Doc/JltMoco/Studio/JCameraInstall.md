# **JRobotInstall Class**

QML > JCameraInstall

## 描述

### JCameraInstall相机预设

* 继承：QObject

---

## 属性说明

> currentIndex : int

* 描述: 当前应用的索引

## 信号说明

> started()

* 描述: 应用开始
  
> finished()

* 描述: 应用结束

---

## 方法说明
  
> void count(const QString &cameaName)

* 描述: 给定相机名的title预设数量

> void init(const QString &cameaName);

* 描述: 初始化给定相机名的title预设

> QJsonObject get(const QString &cameaName,int index);

* 描述: 返回给定相机名和索引的预设数据

> void setTitle(const QString &cameaName,int index,const QString &title);

* 描述: 设置给定相机名和index的title文本

> void setProperty(const QString &cameaName,int index,int key,int writable,const QString &value);

* 描述: 设置给定相机名和index的属性数据
* cameaName: 相机名称
* index: title索引

> QJsonArray getProperty(const QString &cameaName,int index);

* 描述: 设置给定相机名和index的属性数据
* cameaName: 相机名称
* index: title索引

> void apply(const QString &cameaName,int index);

* 描述: 应用给定相机名和index的属性数据
* cameaName: 相机名称
* index: title索引
