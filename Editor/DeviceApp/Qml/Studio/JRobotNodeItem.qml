import QtQuick
import QtQuick.Controls

import JMoco 1.0
import CppService 1.0
import "../CustomItem"
import "../Js/JSDeviceScript.js" as MJSCript

Item
{
    id: root
    implicitWidth:  ((nodeType===3)?(180):140)
    implicitHeight: 300

    signal runDurationChanged();
    signal addNodeDataChanged(int index,var node,var nodeLast);

    function getBeginTime()
    {
        if(index > 0)
        {
            var duration = 0;
            for(var i = 1; i <= index; i++)
            {
                duration+=nodeListModel.get(i).runDuration;
            }
            return duration;
        }
        return 0;
    }

    Rectangle
    {
        anchors.fill: parent
        color: (root.ListView.view.currentIndex === index) ? "#252525" : "#202020"
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                root.ListView.view.currentIndex = index;
                JScript.setBeginTime(root.getBeginTime());
            }
        }
    }

    Row
    {
        id:row
        width: parent.width

        Column
        {
            id:assistColumn
            width: ((nodeType===3)?(parent.width/2):0)
            visible: ((nodeType===3)?true:false)
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: ((nodeType===3)?Number(fX).toFixed(2):0)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: ((nodeType===3)?Number(fY).toFixed(2):0)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: ((nodeType===3)?Number(fZ).toFixed(2):0)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: ((nodeType===3)?Number(fA).toFixed(2):0)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: ((nodeType===3)?Number(fB).toFixed(2):0)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: ((nodeType===3)?Number(fC).toFixed(2):0)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: ((nodeType===3)?Number(fE1).toFixed(2):0)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                ToolButton
                {
                    showText: "更新"
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    onButtonClicked:
                    {
                        if(!JRobot.connected)
                            return;

                        fX = JRobot.x;
                        fY = JRobot.y;
                        fZ = JRobot.z;
                        fA = JRobot.rx;
                        fB = JRobot.ry;
                        fC = JRobot.rz;
                        fE1 = JRobot.a7;
                        //更新辅助点数据
                        MJSCript.scriptBuffer.Nodes[index]["1"]["assist"]["X"] = JRobot.x;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["assist"]["Y"] = JRobot.y;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["assist"]["Z"] = JRobot.z;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["assist"]["A"] = JRobot.rx;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["assist"]["B"] = JRobot.ry;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["assist"]["C"] = JRobot.rz;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["assist"]["E1"] = JRobot.a7;
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                ToolButton
                {
                    showText: "就位"
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                }
            }
        }

        Column
        {
            id:targetColumn
            width: ((nodeType===3)?(parent.width/2):parent.width)
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: Number(X).toFixed(2)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: Number(Y).toFixed(2)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: Number(Z).toFixed(2)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: Number(A).toFixed(2)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: Number(B).toFixed(2)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: Number(C).toFixed(2)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                TextField
                {
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    verticalAlignment: TextInput.AlignVCenter
                    text: Number(E1).toFixed(2)
                    color: "#f1f1f1"
                    selectByMouse:true
                    background: Rectangle {
                        color: "#202020"
                        radius: 4
                        border.width: 1
                        border.color: "#565656"
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                ToolButton
                {
                    showText: "更新"
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    onButtonClicked:
                    {
                        if(!JRobot.connected)
                            return;
                        X = JRobot.x;
                        Y = JRobot.y;
                        Z = JRobot.z;
                        A = JRobot.rx;
                        B = JRobot.ry;
                        C = JRobot.rz;
                        E1 = JRobot.a7;
                        //更新目标点数据
                        MJSCript.scriptBuffer.Nodes[index]["1"]["target"]["X"] = JRobot.x;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["target"]["Y"] = JRobot.y;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["target"]["Z"] = JRobot.z;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["target"]["A"] = JRobot.rx;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["target"]["B"] = JRobot.ry;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["target"]["C"] = JRobot.rz;
                        MJSCript.scriptBuffer.Nodes[index]["1"]["target"]["E1"] = JRobot.a7;
                    }
                }
            }
            Item
            {
                width: parent.width
                height: 40
                ToolButton
                {
                    showText: "就位"
                    width: parent.width-10
                    height: 30
                    anchors.centerIn: parent
                    onButtonPressed:
                    {
                        root.ListView.view.currentIndex = index;
                        JScript.nodeResetExec(index,MJSCript.scriptBuffer.Nodes[index],root.getBeginTime());
                    }
                    onButtonRelease:
                    {
                        JScript.stopExec();
                    }
                }
            }
        }
    }

    DataTextField
    {
        id:caTextField
        anchors.top: row.bottom
        anchors.left: row.left
        anchors.leftMargin: 5
        anchors.right: row.right
        anchors.rightMargin: 5
        visible: (nodeType===3)?true:false
        titleText: "圆心角/°";
        labelWidth:45
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: Number(cicrAngle).toFixed(2)
        dataTextField.validator: DoubleValidator{bottom:0;decimals:3}
        dataTextField.selectByMouse: true
        dataTextField.onPressAndHold:
        {
            if(nodeType!==3)
                return;
            var lastNodeX = MJSCript.scriptBuffer.Nodes[index-1]["1"]["target"]["X"];
            var lastNodeY = MJSCript.scriptBuffer.Nodes[index-1]["1"]["target"]["Y"];
            var lastNodeZ = MJSCript.scriptBuffer.Nodes[index-1]["1"]["target"]["Z"];

            var array = JRobot.centerCircle3d(lastNodeX,lastNodeY,lastNodeZ,fX,fY,fZ,X,Y,Z);
            if(array.length === 5)
            {
                cicrAngle = array[4];
                MJSCript.scriptBuffer.Nodes[index]["1"]["param"]["AssistCA"] = cicrAngle;
                MJSCript.scriptBuffer.Nodes[index]["1"]["param"]["Radius"] = array[3];
            }
        }
    }

    DataTextField
    {
        id:durationTextField
        anchors.top: (nodeType===3)?caTextField.bottom:row.bottom
        anchors.left: (nodeType===3)?caTextField.left:row.left
        anchors.right: (nodeType===3)?caTextField.right:row.right
        titleText: "时长/s";
        labelWidth:45
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: runDuration.toFixed(1)
        dataTextField.validator: DoubleValidator{bottom:0;decimals:3}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            dataTextField.focus = false;
            var duration = Number(dataTextField.text);
            if(index === 0)
            {
                MJSCript.scriptBuffer.MoveDelay = duration;
                runDuration = duration;
            }
            else if(index > 0)
            {
                var lastNode = MJSCript.scriptBuffer.Nodes[index-1]["1"];
                var velRate = JRobot.speedCalc3d(X,Y,Z,lastNode["target"]["X"],lastNode["target"]["Y"],lastNode["target"]["Z"],
                                           duration,nodeType,cicrAngle,cicrRadius);
                //计算成功
                if(velRate <= 1.0 && velRate > 0)
                {
                    runDuration = duration;
                    MJSCript.scriptBuffer.Nodes[index]["1"]["param"]["VelRate"] = velRate;
                    //根据PrgV计算
                    var prgv = MJSCript.scriptBuffer.Nodes[index]["1"]["param"]["PrgV"];
                    var resArray = JRobot.parseVelArray(prgv/100,velRate);
                    if(resArray.length === 2 && Math.abs(resArray[0]-(prgv/100)) < 0.05)
                    {
                        var robotV = resArray[1];
                        if(robotV > 0 && robotV <= 1)
                        {
                            //计算成功
                            MJSCript.scriptBuffer.Nodes[index]["1"]["param"]["RobotV"] = Math.round(robotV*100);
                        }
                    }
                }
                //计算失败
                {
                    dataTextField.text = runDuration;
                }
            }
            root.runDurationChanged();
        }
    }

    DataTextField
    {
        id:tsValueTextField
        anchors.top: durationTextField.bottom
        anchors.left: durationTextField.left
        anchors.right: durationTextField.right
        titleText: "过渡/mm"
        labelWidth:45
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: tsValue
        dataTextField.validator: IntValidator{bottom:0;top:500}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            MJSCript.scriptBuffer.Nodes[index]["1"]["param"]["TsValue"] = Number(dataTextField.text);
            dataTextField.focus = false;
        }
    }

    ToolButton
    {
        id:runButton
        anchors.top: tsValueTextField.bottom
        anchors.topMargin: 5
        anchors.left: tsValueTextField.left
        anchors.right: tsValueTextField.right
        showText: "执行"
        onButtonPressed:
        {
            root.ListView.view.currentIndex = index;
            MJSCript.scriptBuffer["CurrentIndex"] = index;
            if(index === 0)
                JScript.scriptExec(MJSCript.scriptBuffer,0);
            else if(index > 0)
                JScript.scriptExec(MJSCript.scriptBuffer,root.getBeginTime());
        }
        onButtonRelease: JScript.stopExec();
    }

    Row
    {
        spacing: 3
        anchors.top: runButton.bottom
        anchors.topMargin: 10
        anchors.left: runButton.left
        anchors.right: runButton.right
        visible: (index===(root.ListView.view.count-1))?true:false

        ToolButton
        {
            showText: "删除"
            visible: (index!==0)?true:false
            onButtonClicked:
            {
                if(EditorQml.showDialog("删除节点","确认删除?"))
                {
                    var nodes = MJSCript.scriptBuffer["Nodes"].pop();
                    nodeListModel.remove(index);
                }
            }
        }
        ToolButton
        {
            showText: "+线"
            onButtonClicked:
            {
                var nodeLastData = {};
                if(index > 0)
                {
                    nodeLastData = MJSCript.scriptBuffer["Nodes"][index-1];
                }

                var nodeData = MJSCript.scriptBuffer["Nodes"][index];
                var nodeNextData ={
                    "1": {
                        "param": {
                            "Radius": 0,
                            "AssistCA": 0,
                            "PathA": (index > 0)?nodeLastData["1"]["param"]["PathA"]:30,
                            "PathV": (index > 0)?nodeLastData["1"]["param"]["PathV"]:30,
                            "PrgV": (index > 0)?nodeLastData["1"]["param"]["PrgV"]:30,
                            "RobotA": (index > 0)?nodeLastData["1"]["param"]["RobotA"]:30,
                            "RobotV": (index > 0)?nodeLastData["1"]["param"]["RobotV"]:30,
                            "TsValue": 0,
                            "Waiting": 0
                        },
                        "target": {
                            "A": JRobot.rx,
                            "B": JRobot.ry,
                            "C": JRobot.rz,
                            "X": JRobot.x,
                            "Y": JRobot.y,
                            "Z": JRobot.z,
                            "E1": JRobot.a7
                        },
                        "type": 2
                    },
                    "2": {
                        "ImageInterval": 0,
                        "ImageNum": 1,
                        "ShootMode": 0
                    },
                    "3": {
                        "FocusValue": 3000,
                        "ZoomValue": 3000
                    },
                    "4": {
                        "Acc": 30,
                        "Speed": 30,
                        "target": "0"
                    }
                }
                MJSCript.scriptBuffer["Nodes"].push(nodeNextData);
                root.addNodeDataChanged(index+1,nodeNextData,nodeData)
            }
        }
        ToolButton
        {
            showText: "+弧"
            onButtonClicked:
            {
                var mx = "0",my = "0",mz = "0",mfx = "0",mfy = "0",mfz = "0",mca = 0,mra = 0;
                if(JRobot.connected)
                {
                    mx = JRobot.x;
                    my = JRobot.y;
                    mz = JRobot.z;
                    var resArray = JRobot.betweenPoint3d(X,Y,Z,mx,my,mz);
                    if(resArray.length === 3)
                    {
                        if(ciroCombox.currentIndex == 0)
                            resArray[0] += 100;
                        else if(ciroCombox.currentIndex == 1)
                            resArray[1] += 100;
                        else if(ciroCombox.currentIndex == 2)
                            resArray[2] += 100;

                        mfx = Number(resArray[0]).toString();
                        mfy = Number(resArray[1]).toString();
                        mfz = Number(resArray[2]).toString();

                        //计算圆心角半径

                        var circArray = JRobot.centerCircle3d(X,Y,Z,mfx,mfy,mfz,mx,my,mz);
                        if(circArray.length === 5)
                        {
                            mra = circArray[3];
                            mca = circArray[4];
                        }
                    }
                }

                var nodeData = MJSCript.scriptBuffer["Nodes"][index];
                var nodeNextData ={
                    "1": {
                        "param": {
                            "Radius": mra,
                            "AssistCA": mca,
                            "PathA": (index>0)?nodeData["1"]["param"]["PathA"]:30,
                            "PathV": (index>0)?nodeData["1"]["param"]["PathV"]:30,
                            "PrgV": (index>0)?nodeData["1"]["param"]["PrgV"]:30,
                            "RobotA": (index>0)?nodeData["1"]["param"]["RobotA"]:30,
                            "RobotV": (index>0)?nodeData["1"]["param"]["RobotV"]:30,
                            "TsValue": 0,
                            "Waiting": 0
                        },
                        "target": {
                            "A": JRobot.rx,
                            "B": JRobot.ry,
                            "C": JRobot.rz,
                            "X": mx,
                            "Y": my,
                            "Z": mz,
                            "E1": JRobot.a7
                        },
                        "assist": {
                            "A": JRobot.rx,
                            "B": JRobot.ry,
                            "C": JRobot.rz,
                            "X": mfx,
                            "Y": mfy,
                            "Z": mfz,
                            "E1": JRobot.a7
                        },
                        "type": 3
                    },
                    "2": {
                        "ImageInterval": 0,
                        "ImageNum": 1,
                        "ShootMode": 0
                    },
                    "3": {
                        "FocusValue": 3000,
                        "ZoomValue": 3000
                    },
                    "4": {
                        "Acc": 30,
                        "Speed": 30,
                        "target": "0"
                    }
                }
                MJSCript.scriptBuffer["Nodes"].push(nodeNextData);
                root.addNodeDataChanged(index+1,nodeNextData,nodeData)
            }
        }
        ComboBox
        {
            id:ciroCombox
            implicitHeight: 30
            implicitWidth: 30
            model: ["X", "Y", "Z"]
        }
    }
}

