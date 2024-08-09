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
import "../Component"
import JMoco 1.0

Column
{
    id: column
    spacing: 1

    Component.onCompleted:
    {
        updateTimer.start();
    }

    //使用定时器原因： 直接属性绑定Slider的位置会出现错误
    Timer
    {
        id: updateTimer
        interval: 10
        onTriggered:
        {
            prgV.newValue = Qt.binding(function(){return JGlobalRemoteParam.robotPrgV;})
            robotV.newValue = Qt.binding(function(){return JGlobalRemoteParam.robotV;})
            robotA.newValue = Qt.binding(function(){return JGlobalRemoteParam.robotA;})
            railV.newValue = Qt.binding(function(){return JGlobalRemoteParam.railV;})
            railA.newValue = Qt.binding(function(){return JGlobalRemoteParam.railA;})
        }
    }

    TagItem
    {
        id: tagItem
        tagText: "绝对运动速度(节点就位和影棚复位的速度)"
        width: parent.width
        zoomFlag: true
    }
    SliderInputItem
    {
        id: prgV
        visible: tagItem.zoomFlag
        width: parent.width
        tagText: "最大速度"
        titleText: "V"
        onHandleMove: function(value)
        {
            JGlobalRemoteParam.robotPrgV = value;
        }
    }
    SliderInputItem
    {
        id: robotV
        visible: tagItem.zoomFlag
        width: parent.width
        tagText: "速度"
        titleText: "V"
        onHandleMove: function(value)
        {
            JGlobalRemoteParam.robotV = value;
        }
    }
    SliderInputItem
    {
        id: robotA
        visible: tagItem.zoomFlag
        width: parent.width
        tagText: "加速度"
        titleText: "A"
        onHandleMove: function(value)
        {
            JGlobalRemoteParam.robotA = value;
        }
    }
    SliderInputItem
    {
        id: railV
        visible: tagItem.zoomFlag
        width: parent.width
        tagText: "轨道速度"
        titleText: "V"
        onHandleMove: function(value)
        {
            JGlobalRemoteParam.railV = value;
        }
    }
    SliderInputItem
    {
        id: railA
        visible: tagItem.zoomFlag
        width: parent.width
        tagText: "轨道加速度"
        titleText: "A"
        onHandleMove: function(value)
        {
            JGlobalRemoteParam.railA = value;
        }
    }
}
