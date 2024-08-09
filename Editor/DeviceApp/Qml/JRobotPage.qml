import QtQuick 6.2
import QtQuick.Controls 6.2

import JMoco 1.0
import "./CustomItem"
import "./Studio"
import "./Js/JSDeviceRobot.js" as MJSRobot
import "./Js/JSDeviceScript.js" as MJSCript

//相机实时图像
Item
{
    id:root
//    color: "#202020"
    signal quitPage();

    Component.onCompleted:
    {
//         var staticJson = JRobot.getStaticData();
// //        console.log(">>>",JSON.stringify(staticJson))
//         //安装1{}  安装2{}
//         if(staticJson["base"] !== undefined)
//         {
//             var baseJson = staticJson["base"];
//             basePosInput.setValues(baseJson["X"],baseJson["Y"],baseJson["Z"])
//             baseAngleInput.setValues(baseJson["A"],baseJson["B"],baseJson["C"])
//         }
//         if(staticJson["tool"] !== undefined)
//         {
//             var toolJson = staticJson["tool"];
//             toolPosInput.setValues(toolJson["X"],toolJson["Y"],toolJson["Z"])
//             toolAngleInput.setValues(toolJson["A"],toolJson["B"],toolJson["C"])
//         }
//         if(staticJson["load"] !== undefined)
//         {
//             var loadJson = staticJson["load"];
//             loadPosInput.setValues(loadJson["X"],loadJson["Y"],loadJson["Z"])
//             loadAngleInput.setValues(loadJson["A"],loadJson["B"],loadJson["C"])
//             loadRotationInput.setValues(loadJson["JX"],loadJson["JY"],loadJson["JZ"])
//             loadQualityField.dataTextField.text = loadJson["mass"]
//         }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: root.focus=true
    }

    //顶部
    Rectangle
    {
        id:topRectangle
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 60
        color: "#363636"
        //退出按钮
        ToolButton
        {
            id:quitButton
            width: 50
            height: 50
            showText: "×"
            showTextSize: 24
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10

            onButtonClicked:root.quitPage();
        }
        //标题
        Text
        {
            id: setTitleText
            font.pixelSize: 14
            color: "#f1f1f1"
            anchors.centerIn: parent
            text: qsTr("机械臂&轨道")
        }
    }
    Rectangle
    {
        id:bottomItem
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topRectangle.bottom
        anchors.bottom: parent.bottom
        color: "#202020"

        //遥控
        JRobotStatusRemoteItem
        {
            id: jRobotStatusRemoteItem
            anchors.left: parent.left
            anchors.top: parent.top
        }

        // CoordinateInput
        // {
        //     id:toolPosInput
        //     anchors.top: parent.top
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "工具坐标";
        //     suffix: "mm"
        //     onValueChanged:{root.updateToolData();root.focus=true;}
        // }
        // CoordinateInput
        // {
        //     id:toolAngleInput
        //     anchors.top: toolPosInput.bottom
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "";
        //     suffix: "°"
        //     onValueChanged:{root.updateToolData();root.focus=true;}
        // }

        // CoordinateInput
        // {
        //     id:basePosInput
        //     anchors.top: toolAngleInput.bottom
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "基坐标";
        //     suffix: "mm"
        //     onValueChanged:{root.updateBaseData();root.focus=true;}
        // }
        // CoordinateInput
        // {
        //     id:baseAngleInput
        //     anchors.top: basePosInput.bottom
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "";
        //     suffix: "°"
        //     onValueChanged:{root.updateBaseData();root.focus=true;}
        // }

        // CoordinateInput
        // {
        //     id:loadPosInput
        //     anchors.top: baseAngleInput.bottom
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "质心";
        //     suffix: "mm"
        //     onValueChanged: {root.updateLoadData();;root.focus=true;}
        // }
        // CoordinateInput
        // {
        //     id:loadAngleInput
        //     anchors.top: loadPosInput.bottom
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "";
        //     suffix: "°"
        //     onValueChanged: {root.updateLoadData();;root.focus=true;}
        // }
        // CoordinateInput
        // {
        //     id:loadRotationInput
        //     anchors.top: loadAngleInput.bottom
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "";
        //     suffix: "kg/m²"
        //     onValueChanged: {root.updateLoadData();;root.focus=true;}
        // }
        // DataTextField
        // {
        //     id:loadQualityField
        //     anchors.top: loadRotationInput.bottom
        //     anchors.left: jRobotStatusRemoteItem.right
        //     anchors.leftMargin: 10

        //     titleText: "质量/kg";
        //     dataTextField.validator: DoubleValidator{bottom: 0}
        //     dataTextField.selectByMouse: true
        //     dataTextField.onAccepted:{root.updateLoadData();root.focus=true;}
        // }
    }

    // function updateBaseData()
    // {
    //     var data = {
    //         "X":Number(basePosInput.xTextField.text),
    //         "Y":Number(basePosInput.yTextField.text),
    //         "Z":Number(basePosInput.zTextField.text),
    //         "A":Number(baseAngleInput.xTextField.text),
    //         "B":Number(baseAngleInput.yTextField.text),
    //         "C":Number(baseAngleInput.zTextField.text)
    //     }
    //     JRobot.setBaseCoordinate(data);
    // }
    // function updateToolData()
    // {
    //     var data = {
    //         "X":Number(toolPosInput.xTextField.text),
    //         "Y":Number(toolPosInput.yTextField.text),
    //         "Z":Number(toolPosInput.zTextField.text),
    //         "A":Number(toolAngleInput.xTextField.text),
    //         "B":Number(toolAngleInput.yTextField.text),
    //         "C":Number(toolAngleInput.zTextField.text)
    //     }
    //     JRobot.setToolCoordinate(data);
    // }
    // function updateLoadData()
    // {
    //     var data = {
    //         "X":Number(loadPosInput.xTextField.text),
    //         "Y":Number(loadPosInput.yTextField.text),
    //         "Z":Number(loadPosInput.zTextField.text),
    //         "A":Number(loadAngleInput.xTextField.text),
    //         "B":Number(loadAngleInput.yTextField.text),
    //         "C":Number(loadAngleInput.zTextField.text),
    //         "JX":Number(loadRotationInput.xTextField.text),
    //         "JY":Number(loadRotationInput.yTextField.text),
    //         "JZ":Number(loadRotationInput.zTextField.text),
    //         "mass":Number(loadQualityField.dataTextField.text)
    //     }
    //     JRobot.setLoadData(data);
    // }
}
