# **JRobotInstall Class**

QML > JRobotInstall

## 描述

### JRobotInstall管理机械臂安装方式的类

* 继承：QObject

---

## 属性说明

> currentIndex : int

* 描述: 当前应用的索引

> titleModel : listModel

* 描述: 安装方式数组
委托属性:
    dataTitle : string
方法:
    int count();返回数量
    QJsonObject get(int index);返回Index数据
    void setProperty(int index,string roleName, var value);index索引 roleName属性名, value值

> worldModel : listModel

世界坐标系数据列表你;
委托属性:
    dataX : double
    dataY : double
    dataZ : double
    dataA : double
    dataB : double
    dataC : double
方法:
    int count();返回数量
    QJsonObject get(int index);返回Index数据
    void setProperty(int index,string roleName, var value);index索引 roleName属性名, value值

> toolModel : listModel

工具数据列表你;
委托属性:
    dataX : double
    dataY : double
    dataZ : double
    dataA : double
    dataB : double
    dataC : double
方法:
    int count();返回数量
    QJsonObject get(int index);返回Index数据
    void setProperty(int index,string roleName, var value);index索引 roleName属性名, value值

> loadModel : listModel

负载数据列表你;
委托属性:
    dataX : double
    dataY : double
    dataZ : double
    dataA : double
    dataB : double
    dataC : double
    dataMass : double
    dataJX : double
    dataJY : double
    dataJZ : double
方法:
    int count();返回数量
    QJsonObject get(int index);返回Index数据
    void setProperty(int index,string roleName, var value);index索引 roleName属性名, value值

> resetModel : listModel

复位数据列表你;
委托属性:
    dataX : string
    dataY : string
    dataZ : string
    dataA : string
    dataB : string
    dataC : string
    dataE1 : string
    dataA1 : string
    dataA2 : string
    dataA3 : string
    dataA4 : string
    dataA5 : string
    dataA6 : string
方法:
    int count();返回数量
    QJsonObject get(int index);返回Index数据
    void setProperty(int index,string roleName, var value);index索引 roleName属性名, value值
信号:
    rowDataChanged(int row);
    给定行(row)被后台修改时发送
    
> robotPrgV : int

* 描述: 机械臂程序速度[1~100]

> robotV : int

* 描述: 机械臂速度[1~100]

> robotA : int

* 描述: 机械臂加速度[1~100]

> railV : int

* 描述: 轨道速度[1~100]

> railA : int

* 描述: 轨道加速度[1~100]

> turnplateV : int

* 描述: 转盘速度[1~100]

> turnplateA : int

* 描述: 转盘加速度[1~100]

---

## 方法说明
  
> [void setIndexTitle(int index，const QString &str);] [该方法已经删除]

* 描述: 设置给定索引的标题
* 参数：index 给定索引

> void refreshIndexResetData(int index);

* 描述: 刷新给定索引数据
* 参数：index 给定索引

> void moveToCurrentIndexPosition();

* 描述: 移动到已应用索引位置

> void moveStop();

* 描述: 停止移动
