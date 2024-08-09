/*
* 软件名称   BOBS 操作系统
* 版权所有   上海倔老头智能科技有限公司
* 本软件由上海倔老头智能科技有限公司开发并且开源 使用GPL V3（GNU General Public License） 开源协议
* 如收费请告知他人本软件可免费获得并说明收费缘由（如服务费）
* 联系方式
* vx 号    z1273305587
* 电话号   15536506659
* bilibili： 倔老头的会议室  UID: 3546726275221982
* 软件开源地址 https://github.com/oldbabe/ob_os
*
* Software name BOBS Operating system
*
* Copyright (C) 2024  Shanghai OldBaby technology Co., LTD
*
* This program is free software;you can redistribute it and/or modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation;either version 3 of the License, or (at your option) any later version.
*
* If there is a charge, please inform others that the software is available free of charge and explain the reason for the charge (e.g. service fee).
* Contact information
* Open source address https://github.com/oldbabe/ob_os
*/
#ifndef ABSTRACTROBOT_H
#define ABSTRACTROBOT_H


#include <QObject>
#include <QJsonObject>

namespace jltmoco
{

class AbstractRobot
{
public:
    virtual ~AbstractRobot() = default;

    /**
    * @brief  注册回调函数
    **/
    virtual void registerFunc(std::function<void (const QJsonObject &)>) = 0;

    /**
    * @brief 安装服务
    **/
    virtual void setup() = 0;
    /**
    * @brief 卸载服务
    **/
    virtual void uninstall() = 0;
    /**
    * @brief 连接
    **/
    virtual bool connect(const QString &robotIp,const QString &railIp) = 0;
    /**
    * @brief 连接状态
    **/
    virtual bool connected() const = 0;
    /**
    * @brief 断开
    **/
    virtual void disconnect() = 0;
    /**
    * @brief 获得设备状态数据
    **/
    virtual QJsonObject getStatusData() = 0;
    /**
    * @brief 获得设备静态数据
    **/
    virtual QJsonObject getStaticData() = 0;
    /**
    * @brief 解析用户指令(机械臂)
    * @param cmd 指令内容
    **/
    virtual void parseUserCommand(const QJsonObject &cmd) = 0;

};

}


#define AbstractRobot_iid "AbstractRobotInterface"

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(jltmoco::AbstractRobot, AbstractRobot_iid)

QT_END_NAMESPACE

#endif // ABSTRACTROBOT_H
