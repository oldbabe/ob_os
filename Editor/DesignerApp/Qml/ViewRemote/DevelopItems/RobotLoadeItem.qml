import QtQuick 6.2
import "../../Component"
import JMoco 1.0

Item
{
    id: root

    implicitHeight: tagItem.height + loaditem.height +dataColumn.height + 1
    implicitWidth: 200

    // function setDatas(obj)
    // {
    //     weightitem.valueText = parseFloat(obj["mass"]).toFixed(2);
    //     xitem.valueText = parseFloat(obj["X"]).toFixed(2);
    //     yitem.valueText = parseFloat(obj["Y"]).toFixed(2);
    //     zitem.valueText = parseFloat(obj["Z"]).toFixed(2);
    //     aitem.valueText = parseFloat(obj["A"]).toFixed(2);
    //     bitem.valueText = parseFloat(obj["B"]).toFixed(2);
    //     citem.valueText = parseFloat(obj["C"]).toFixed(2);
    //     jxitem.valueText = parseFloat(obj["JX"]).toFixed(2);
    //     jyitem.valueText = parseFloat(obj["JY"]).toFixed(2);
    //     jzitem.valueText = parseFloat(obj["JZ"]).toFixed(2);
    // }

    TagItem
    {
        id: tagItem
        tagText: "负载"
        norColor: "#404040"
        hovColor: "#444444"
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        zoomFlag: true
    }
    Grid
    {
        id: loaditem
        columns: 1
        spacing: 2
        leftPadding: 2
        anchors.top: tagItem.bottom
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right
        BaseTextItemDouble
        {
            id: weightitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width-2
            titleText: "LC"
            enterText:"双击修改"
            lastText: "KG"
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.mass).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.mass = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
    }
    Grid
    {
        id: dataColumn
        columns: 3
        spacing: 2
        anchors.top: loaditem.bottom
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right

        BaseTextItemDouble
        {
            id: xitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "X"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.tran.x).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.tran.x = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: yitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "Y"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.tran.y).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.tran.y = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: zitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "Z"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.tran.z).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.tran.z = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: aitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "A"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.rpy.rx).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.rpy.rx = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: bitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "B"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.rpy.ry).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.rpy.ry = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: citem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "C"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.rpy.rz).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.rpy.rz = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: jxitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "JX"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.inertia.x).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.inertia.x = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: jyitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "JY"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.inertia.y).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.inertia.y = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
        BaseTextItemDouble
        {
            id: jzitem
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "JZ"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).load.inertia.z).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).load.inertia.z = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
    }
}

