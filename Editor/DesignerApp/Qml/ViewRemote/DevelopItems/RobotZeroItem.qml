import QtQuick 6.2
import "../../Component"
import "../../../JS/SetHabit.js" as SetHab
import JMoco 1.0
Item
{
    id: root

    implicitHeight: tagItem.height + loaditem.height + 3
    implicitWidth: 200

    Component.onCompleted: tagItem.zoomFlag = true;
    property int listmodelInt: 0    

    function updateVisible()
    {
        root.focus = true;
    }
    function setDatas(obj)
    {
        xitem.valueText = parseFloat(obj["X"]).toFixed(2);
        yitem.valueText = parseFloat(obj["Y"]).toFixed(2);
        zitem.valueText = parseFloat(obj["Z"]).toFixed(2);
        aitem.valueText = parseFloat(obj["A"]).toFixed(2);
        bitem.valueText = parseFloat(obj["B"]).toFixed(2);
        citem.valueText = parseFloat(obj["C"]).toFixed(2);
        e1item.valueText = parseFloat(obj["E1"]).toFixed(2);
    }


    TagItem
    {
        id: tagItem
        tagText: "复位位置"
        norColor: "#404040"
        hovColor: "#444444"
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        onZoomFlagChanged:root.updateVisible();
    }
    Grid
    {
        id: loaditem
        columns: 3
        spacing: 2
        leftPadding: 2
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
            onTextEditFinished:(textData) =>
            {
                JRobotInstall.resetModel.setProperty(root.listmodelInt,"dataX",textData);
                valueText =   textData;
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
            onTextEditFinished:(textData) =>
            {
                JRobotInstall.resetModel.setProperty(root.listmodelInt,"dataY",textData);
                valueText =   textData;
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
            onTextEditFinished:(textData) =>
            {
                JRobotInstall.resetModel.setProperty(root.listmodelInt,"dataZ",textData);
                valueText =   textData;
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
            onTextEditFinished:(textData) =>
            {
                JRobotInstall.resetModel.setProperty(root.listmodelInt,"dataA",textData);
                valueText =   textData;
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
            onTextEditFinished:(textData) =>
            {
                JRobotInstall.resetModel.setProperty(root.listmodelInt,"dataB",textData);
                valueText =   textData;
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
            onTextEditFinished:(textData) =>
            {
                JRobotInstall.resetModel.setProperty(root.listmodelInt,"dataC",textData);
                valueText =   textData;
            }
        }
        BaseTextItemDouble
        {
            id: e1item
            visible: tagItem.zoomFlag
            implicitWidth: parent.width/3-2
            titleText: "E1"
            enterText:"双击修改"
            lastText: ""
            maxNum: 100000
            minNum: -100000
            border.color: "#202020"
            border.width:1
            onTextEditFinished:(textData) =>
            {
                JRobotInstall.resetModel.setProperty(root.listmodelInt,"dataE1",textData);
                valueText =   textData;
            }
        }
    }

}

