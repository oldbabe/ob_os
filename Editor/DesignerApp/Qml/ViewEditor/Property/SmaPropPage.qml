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
import "../../JltComponent"
import JMoco 1.0

//定格动画属性页面
Rectangle
{
    id: root
    clip: true
    color: "#363636"

    Component.onCompleted:
    {
        root.viewUpdate();
    }

    function viewUpdate()
    {
        if(JSession.currentScript === null
                || JSession.currentScript.currentNode === null
                || JSession.currentScript.currentNode.type !== JNode.NodeType_StopMotionAnimation)
        {
            return;
        }

        listModel.clear();
        var node = JSession.currentScript.currentNode.next;
        if(node!==null)
        {
            node = node.next;
        }
        while(node!==null)
        {
            var item = {
                "key": node.objectName
            };
            listModel.append(item);
            node = node.next;
        }
    }

    ListModel
    {
        id: listModel
    }

    ListView
    {
        id: listView
        anchors.fill: parent
        anchors.margins: 5
        model: listModel
        spacing: 2
        MouseArea
        {
            anchors.fill: parent
            propagateComposedEvents: true
        }
        delegate: Rectangle
        {
            id: mdelegate
            radius: 3
            height: 40
            width: ListView.view.width
            color: "#444444"

            property JNode nodeData: null

            Component.onCompleted:
            {
                if(JSession.currentScript === null)
                    return;
                nodeData = JSession.currentScript.getNode(key);
                if(nodeData !== null)
                {
                    frameCountItem.valueItem.text = nodeData.robot.frames;
                }
                nodeTitleItem.text = Qt.binding(function(){
                    if(mdelegate.nodeData === null)
                        return "";
                    return mdelegate.nodeData.title;
                });
            }

            Text
            {
                id: numberItem
                color: "aliceblue"
                text: index+1
                width: 40
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Rectangle
            {
                id: countRectangle
                radius: 3
                color: "#303030"
                width: 150
                height: 34
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: numberItem.right
                anchors.leftMargin: 5
                Text
                {
                    id: nodeTitleItem
                    color: "aliceblue"
                    anchors.centerIn: parent
                }
            }
            Rectangle
            {
                radius: 3
                color: "#303030"
                height: 34
                width: 120
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: countRectangle.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 5
                IntShowInput
                {
                    id: frameCountItem
                    anchors.fill: parent
                    anchors.leftMargin: 5
                    titleText: "帧数"
                    onValueChanged: function(value)
                    {
                        if(JSession.currentScript === null)
                            return;
                        if(JSession.currentScript.currentNode === null)
                            return;

                        if(mdelegate.nodeData !== null)
                        {
                            mdelegate.nodeData.robot.frames = Number(value);
                        }
                        JSession.currentScript.currentNode.updateFrameCounts();
                        JSession.currentScript.changed = true;
                    }
                }
            }
        }
    }
}
