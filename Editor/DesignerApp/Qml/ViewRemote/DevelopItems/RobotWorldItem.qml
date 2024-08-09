import QtQuick 6.2
import "../../Component"
import JMoco 1.0
Item
{
    id: root

    implicitHeight: tagItem.height + dataColumn.height + 1
    implicitWidth: 200

    TagItem
    {
        id: tagItem
        tagText: "世界坐标"
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
        id: dataColumn
        columns: 3
        spacing: 2
        anchors.top: tagItem.bottom
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
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).world.tran.x).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).world.tran.x = Number(value);
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
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).world.tran.y).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).world.tran.y = Number(value);
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
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).world.tran.z).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).world.tran.z = Number(value);
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
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).world.rpy.rx).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).world.rpy.rx = Number(value);
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
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).world.rpy.ry).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).world.rpy.ry = Number(value);
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
            valueText: parseFloat(JRobot.installGet(JRobot.installIndex).world.rpy.rz).toFixed(2);
            onTextEditFinished: function(value)
            {
                JRobot.installGet(JRobot.installIndex).world.rpy.rz = Number(value);
                JRobot.installApply(JRobot.installIndex);
            }
        }
    }
}
