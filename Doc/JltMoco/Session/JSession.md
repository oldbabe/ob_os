# **JSession Class**

## 描述

### JSession是对脚本文件进行管理的单例类

* 继承：QObject
* Qml对象名：JSession
  
---

## 属性说明

> opened : bool

会话打开时=true,关闭为=false

> dirName : string

会话文件夹地址

> baseName : string

会话名

> fileList : ListModel

会话的脚本文件列表.

> currentFileName : string

会话选中的文件名.

> script : JScript

会话已打开的脚本数据对象

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


## 信号说明

> void sessionChanged(const QString &path)

* 描述: 会话改变
* 参数：path 会话目录

---

## 方法说明

> QString getExistingDir();

* 描述: 返回最近一次创建会话的根目录
* 参数：fileName 脚本文件地址(绝对地址)
* 返回值：QString
  
> QString getExistingDirectory(const QString &title,const QString &path);

* 描述: 选择系统目录
* 参数：title 系统管理器标题
* 参数：path 系统路径
* 返回值：QString

> QString getExistingFile(const QString &title,const QString &path,const QString &filter);

* 描述: 选择系统文件
* 参数：title 目录标题 => "打开脚本"
* 参数：path 打开的目录 => "C:\\Users\\yxh\\Desktop"
* 参数：filter 文件后缀过滤器 => "脚本(*.json)"
* 返回值：QString 文件地址

> void openExistingDirectory(const QString &path);

* 描述: 打开系统目录
* 参数：path 系统路径

> bool dirExists(const QString &path);

* 描述: 判定系统目录是否存在
* 参数：path 给定目录路径
* 返回值：=true存在

> int createSession(const QString &path,const QString &name);

* 描述: 创建会话[会话已打开时,自动保存已打开脚本]
* 参数：path 路径
* 参数：name 会话名
* 返回值：=0成功 =1会话文件夹创建失败 =2下载文件夹创建失败

> int openSession(const QString &path);

* 描述: 打开会话[会话已打开时,自动保存已打开脚本]
* 参数：path 路径
* 返回值：=0成功 =1会话文件夹不存在 =2已打开当前会话
  
> void closeSession();

* 描述: 关闭会话
  
> int createScript(const QString &path,const QString &name,int cameraType,real w,real h);

* 描述: 创建脚本 [会话已打开时,自动保存已打开脚本]
* 参数：path 路径
* 参数：name 脚本名称
* 参数：cameraType 拍摄类型 =1照片 =3视频
* 参数：w 节点宽度
* 参数：h 节点高度
* 返回值：=0成功 =1脚本已经存在 =2脚本写入失败
  
> void deleteScript();

* 描述: 删除脚本  
  
> bool renameScript(const QString &newName);

* 描述: 重命名脚本  
* 返回: true重命名成功
  
> QJsonObject loadScript(const QString &fileName);

* 描述: 加载脚本  
* 参数：fileName 文件地址
  
> bool saveScript(const QString &fileName,const QJsonObject &obj);

* 描述: 保存脚本  
* 参数：fileName 文件地址
* 参数：obj 脚本内容

> void setMode(unsigned int mode,bool enable = true);

* 描述: 设置模式  
* 参数：mode =0影棚模式=1直播模式
* 参数：enable =true保存到配置文件
  
> int getMode();

* 描述: 返回模式

> int switchScript(const QString &fileName);

* 描述: 后台进行脚本数据切换
* fileName: 文件地址
* 返回值： =0成功 =1地址是空的 =2文件不存在 =3打开失败 =4转换为JSON格式时错误  =5内容为空 =6无法识别
