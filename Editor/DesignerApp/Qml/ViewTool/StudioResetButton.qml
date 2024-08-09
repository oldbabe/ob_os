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
import QtQuick 6.2
import QtQuick.Controls 6.2
import JMoco 1.0

Button
{
    id: control

    implicitHeight: 34
    implicitWidth: 34

    ToolTip.visible: control.hovered
    ToolTip.text: !control.enabled?"机械臂安装方式数据未导入":"机械臂复位"

    down:false
    flat: true
    hoverEnabled: true
    icon.color: control.enabled?Qt.darker("aliceblue",(hovered?1:1.2)):"darkgray"
    icon.source: "qrc:/Image/icon_studio_reset.png"
    icon.width: 24
    icon.height: 18

    background: Rectangle
    {
        radius: 3
        color: control.pressed?"dodgerblue":"transparent"
        border.width: 1
        border.color: "#595959"
    }

    Component.onCompleted:
    {
        control.enabled = Qt.binding(function(){
            if(!JRobot.connected)
                return false;
            var install = JRobot.installGet(JRobot.installIndex);
            if(install.reset.a1==="0"&&install.reset.a2==="0"&&install.reset.a3==="0"&&
                    install.reset.a4==="0"&&install.reset.a5==="0"&&install.reset.a6==="0")
            {
                return false;
            }
            return true;
        });
    }
    onHoveredChanged: windowRoot.rest3dValue = hovered;
    onPressed:JRobot.installReset(JRobot.installIndex);
    onReleased:JRobot.runStop();
}
