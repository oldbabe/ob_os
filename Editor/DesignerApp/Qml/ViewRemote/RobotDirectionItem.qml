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
    id: root
    spacing: 1

    property var items: []

    Component.onCompleted:
    {
        var array = JRobot.getRemoteDirection();
        comboBox0.comboxAlias.currentIndex = Math.abs(array[0])-1;
        comboBox1.comboxAlias.currentIndex = Math.abs(array[1])-1;
        comboBox2.comboxAlias.currentIndex = Math.abs(array[2])-1;
        comboBox3.comboxAlias.currentIndex = Math.abs(array[3])-1;
        comboBox4.comboxAlias.currentIndex = Math.abs(array[4])-1;
        comboBox5.comboxAlias.currentIndex = Math.abs(array[5])-1;
        comboBox0.dataIndex = array[0];
        comboBox1.dataIndex = array[1];
        comboBox2.dataIndex = array[2];
        comboBox3.dataIndex = array[3];
        comboBox4.dataIndex = array[4];
        comboBox5.dataIndex = array[5];
        items = [];
        items.push(comboBox0);
        items.push(comboBox1);
        items.push(comboBox2);
        items.push(comboBox3);
        items.push(comboBox4);
        items.push(comboBox5);
    }

    function saveIndex()
    {
        var array = [comboBox0.dataIndex,comboBox1.dataIndex,comboBox2.dataIndex,comboBox3.dataIndex,comboBox4.dataIndex,comboBox5.dataIndex];
        JRobot.saveRemoteDirection(array);
    }

    function updateIndex(item,index,value)
    {
        for(var i = 0; i < items.length; i++)
        {
            if(items[i]===item)
                continue;
            if(Math.abs(items[i].dataIndex) === Math.abs(value))
            {
                var itemData = item.dataIndex;
                if(items[i].dataIndex > 0)
                    item.dataIndex = index+1;
                else
                    item.dataIndex = -index-1;

                items[i].comboxAlias.currentIndex = Math.abs(itemData)-1;
                items[i].dataIndex = itemData;
            }
        }
        root.saveIndex();
    }

    TagItem
    {
        id: tagItem
        tagText: "工具坐标系遥控与相机视口的关系"
        width: parent.width
        zoomFlag: true
    }
    ComboxItem
    {
        id: comboBox0
        tagText: "前-后"
        width: parent.width
        visible: tagItem.zoomFlag
        comboxAlias.width: 120
        comboxArray: ["X","Y","Z","A","B","C"]
        property int dataIndex: 0
        onIndexActivated: function(index)
        {
            var value = 0;
            if(dataIndex>0)
                value=index+1;
            else
                value=-(index+1);
            root.updateIndex(comboBox0,index,value);
        }
        ToolButtonNoClick
        {
            width: 60
            height: parent.comboxAlias.height
            showText: "翻转"
            norCheckColor: "steelblue"
            hoverCheckColor: "cornflowerblue"
            checkable: true
            checked: comboBox0.dataIndex>0?false:true
            anchors.left: parent.comboxAlias.right
            anchors.verticalCenter: parent.comboxAlias.verticalCenter
            onButtonClicked:
            {
                comboBox0.dataIndex = -comboBox0.dataIndex;
                root.saveIndex();
            }
        }
    }
    ComboxItem
    {
        id: comboBox1
        tagText: "左-右"
        width: parent.width
        visible: tagItem.zoomFlag
        comboxAlias.width: 120
        comboxArray: ["X","Y","Z","A","B","C"]
        property int dataIndex: 0
        onIndexActivated: function(index)
        {
            var value = 0;
            if(dataIndex>0)
                value=index+1;
            else
                value=-(index+1);
            root.updateIndex(comboBox1,index,value);
        }
        ToolButtonNoClick
        {
            width: 60
            height: parent.comboxAlias.height
            checkable: true
            showText: "翻转"
            norCheckColor: "steelblue"
            hoverCheckColor: "cornflowerblue"
            anchors.left: parent.comboxAlias.right
            anchors.verticalCenter: parent.comboxAlias.verticalCenter
            checked: comboBox1.dataIndex>0?false:true
            onButtonClicked:
            {
                comboBox1.dataIndex = -comboBox1.dataIndex;
                root.saveIndex();
            }
        }
    }
    ComboxItem
    {
        id: comboBox2
        tagText: "上-下"
        width: parent.width
        visible: tagItem.zoomFlag
        comboxAlias.width: 120
        comboxArray: ["X","Y","Z","A","B","C"]
        property int dataIndex: 0
        onIndexActivated: function(index)
        {
            var value = 0;
            if(dataIndex>0)
                value=index+1;
            else
                value=-(index+1);
            root.updateIndex(comboBox2,index,value);
        }
        ToolButtonNoClick
        {
            width: 60
            height: parent.comboxAlias.height
            checkable: true
            showText: "翻转"
            norCheckColor: "steelblue"
            hoverCheckColor: "cornflowerblue"
            anchors.left: parent.comboxAlias.right
            anchors.verticalCenter: parent.comboxAlias.verticalCenter
            checked: comboBox2.dataIndex>0?false:true
            onButtonClicked:
            {
                comboBox2.dataIndex = -comboBox2.dataIndex;
                root.saveIndex();
            }
        }
    }
    ComboxItem
    {
        id: comboBox3
        tagText: "左转-右转"
        width: parent.width
        visible: tagItem.zoomFlag
        comboxAlias.width: 120
        comboxArray: ["X","Y","Z","A","B","C"]
        property int dataIndex: 0
        onIndexActivated: function(index)
        {
            var value = 0;
            if(dataIndex>0)
                value=index+1;
            else
                value=-(index+1);
            root.updateIndex(comboBox3,index,value);
        }
        ToolButtonNoClick
        {
            width: 60
            height: parent.comboxAlias.height
            checkable: true
            showText: "翻转"
            norCheckColor: "steelblue"
            hoverCheckColor: "cornflowerblue"
            anchors.left: parent.comboxAlias.right
            anchors.verticalCenter: parent.comboxAlias.verticalCenter
            checked: comboBox3.dataIndex>0?false:true
            onButtonClicked:
            {
                comboBox3.dataIndex = -comboBox3.dataIndex;
                root.saveIndex();
            }
        }
    }
    ComboxItem
    {
        id: comboBox4
        tagText: "低头-抬头"
        width: parent.width
        visible: tagItem.zoomFlag
        comboxAlias.width: 120
        comboxArray: ["X","Y","Z","A","B","C"]
        property int dataIndex: 0
        onIndexActivated: function(index)
        {
            var value = 0;
            if(dataIndex>0)
                value=index+1;
            else
                value=-(index+1);
            root.updateIndex(comboBox4,index,value);
        }
        ToolButtonNoClick
        {
            width: 60
            height: parent.comboxAlias.height
            checkable: true
            showText: "翻转"
            norCheckColor: "steelblue"
            hoverCheckColor: "cornflowerblue"
            anchors.left: parent.comboxAlias.right
            anchors.verticalCenter: parent.comboxAlias.verticalCenter
            checked: comboBox4.dataIndex>0?false:true
            onButtonClicked:
            {
                comboBox4.dataIndex = -comboBox4.dataIndex;
                root.saveIndex();
            }
        }
    }
    ComboxItem
    {
        id: comboBox5
        tagText: "左翻转-右翻转"
        width: parent.width
        visible: tagItem.zoomFlag
        comboxAlias.width: 120
        comboxArray: ["X","Y","Z","A","B","C"]
        property int dataIndex: 0
        onIndexActivated: function(index)
        {
            var value = 0;
            if(dataIndex>0)
                value=index+1;
            else
                value=-(index+1);
            root.updateIndex(comboBox5,index,value);
        }
        ToolButtonNoClick
        {
            width: 60
            height: parent.comboxAlias.height
            checkable: true
            showText: "翻转"
            norCheckColor: "steelblue"
            hoverCheckColor: "cornflowerblue"
            anchors.left: parent.comboxAlias.right
            anchors.verticalCenter: parent.comboxAlias.verticalCenter
            checked: comboBox5.dataIndex>0?false:true
            onButtonClicked:
            {
                comboBox5.dataIndex = -comboBox5.dataIndex;
                root.saveIndex();
            }
        }
    }
}
