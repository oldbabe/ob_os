# **JSession Class**

JltMoco > StdLensDb > stdlensdb

## 描述

### 标准镜头库的单例类

* 继承：QObject

---

## 方法说明

> void init();

* 描述: 数据库初始化
  
> void release();

* 描述: 数据库内存释放

> void setDbFileName(const QString &fileName);

* 描述: 设置数据库文件地址
* 参数： fileName 文件地址

> QString getDbFileName() const;

* 描述: 返回数据库文件地址

> void setCommitDir(const QString &dir);

* 描述: 设置脚本文件提交目录
* 参数： dir 目录地址

> QString getCommitDir() const;

* 描述: 返回脚本文件提交目录

> bool connect(String dbFileName);

* 描述: 连接数据库
* 参数： dbFileName 数据库文件名
* 返回值： =true连接成功

> void disconnect();

* 描述: 断开数据库连接

> bool exist(String lensCode);

* 描述: 镜头代码是否存在
* 参数： lensCode 镜头代码
* 返回值： =true存在,反之不存在

> bool append(String lensCode,int lensState,String remark);

* 描述: 添加一个镜头
* 参数: lensCode 镜头代码
* 参数: lensState 镜头状态 =0禁用 =1使用
* 参数: remark 镜头描述
* 返回值： =true添加成功

> bool remove(String lensCode);

* 描述: 删除一个镜头
* 参数: lensCode 镜头代码
* 返回值： =true删除成功

> bool update(String lensCode,int lensState,String remark);

* 描述: 更新一个镜头
* 参数: lensCode 镜头代码
* 参数: lensState 镜头状态 =0禁用 =1使用
* 参数: remark 镜头描述
* 返回值： =true更新成功

> JsonObject searchOne(String lensCode);

* 描述: 查找一个镜头
* 参数: lensCode 镜头代码
* 返回值:

'''
{
    "LensCode": "JT00000",
    "LensState": false/true,
    "FileName":"",
    "Time":"",
    "Remark":""
}
'''
