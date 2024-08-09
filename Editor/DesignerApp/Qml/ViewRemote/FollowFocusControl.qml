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
import JMoco 1.0
import "../Component"

Column
{
    id: column
    spacing: 1

    Component.onCompleted:
    {
        zoomItem.newValue = JFollowfocus.zoom;
        focusItem.newValue = JFollowfocus.focus;
        irisItem.newValue = JFollowfocus.iris;
    }

    TagItem
    {
        id: tagItem
        tagText: "跟焦器"
        width: parent.width
        zoomFlag: true
    }

    SliderInputItem
    {
        id: focusItem
        enabled: JFollowfocus.focusEnable && !JFollowfocusRemote.connected
        valueAble: false
        norColor: "#404040"
        hovColor: "#444444"
        width: parent.width
        tagText: "对焦值"
        titleText: "F"
        valueText: JFollowfocus.focus
        maxValue: 7200
        minValue: 0
        enteText: "输入值0-7200"
        visible: tagItem.zoomFlag
        // onEnabledChanged:
        // {
        //     if(enabled)
        //         focusItem.setValue(JFollowfocus.focus);
        // }
        onHandleMove:function(move)
        {
            // valueText = Number(move).toString();
            JFollowfocus.focus = move;
        }
    }
    SliderInputItem
    {
        id: zoomItem
        enabled: JFollowfocus.zoomEnable && !JFollowfocusRemote.connected
        valueAble: false
        norColor: "#404040"
        hovColor: "#444444"
        width: parent.width
        tagText: "变焦值"
        titleText: "Z"
        valueText: JFollowfocus.zoom
        minValue: 0
        maxValue: 7200
        enteText: "输入值0-7200"
        visible: tagItem.zoomFlag
        // onEnabledChanged:
        // {
        //     if(enabled)
        //         zoomItem.setValue(JFollowfocus.zoom);
        // }
        onHandleMove:function(move)
        {
            valueText = Number(move).toString();
            JFollowfocus.zoom = move;
        }
    }
    SliderInputItem
    {
        id: irisItem
        enabled: JFollowfocus.irisEnable && !JFollowfocusRemote.connected
        valueAble: false
        norColor: "#404040"
        hovColor: "#444444"
        width: parent.width
        tagText: "光圈"
        titleText: "I"
        valueText: JFollowfocus.iris
        minValue: 0
        maxValue: 7200
        enteText: "输入值0-7200"
        visible: tagItem.zoomFlag
        // onEnabledChanged:
        // {
        //     if(enabled)
        //         irisItem.setValue(JFollowfocus.iris);
        // }
        onHandleMove:function(move)
        {
            valueText = Number(move).toString();
            JFollowfocus.iris = move;
        }
    }
}
