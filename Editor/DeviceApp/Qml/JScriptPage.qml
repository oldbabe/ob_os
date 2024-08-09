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
    MouseArea
    {
        anchors.fill: parent
        onClicked: root.focus=true
    }
    Component.onCompleted:
    {
        MJSCript.scriptBuffer = JSession.loadScript("C:\\Users\\yxh\\Desktop\\TestSession\\视频1.json");
        runDurationDataTextField.dataTextField.text = MJSCript.scriptBuffer["RecordingDuration"];
        var nodes = MJSCript.scriptBuffer.Nodes;
        for(var i = 0; i < nodes.length; i++)
        {
            if(i > 0)
                nodeListModel.addNodeData(i,nodes[i],nodes[i-1]);
            else
                nodeListModel.addNodeData(i,nodes[i],null);
        }
    }
    Component.onDestruction:
    {
        JSession.saveScript("C:\\Users\\yxh\\Desktop\\TestSession\\视频1.json",MJSCript.scriptBuffer);
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
    //时间轴
    Rectangle
    {
        id:midRectangle
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topRectangle.bottom
        height: 80
        color: "#282828"

        Slider
        {
            id: frameSlider
            from:0
            value:JScript.frameCounter
            to: Number(runDurationDataTextField.dataTextField.text)*100
            live:false
            stepSize: 1;
            snapMode:Slider.SnapOnRelease
            anchors.fill: parent
            property int baseValue: 0

            background: Item
            {
                x: frameSlider.leftPadding
                y: frameSlider.topPadding + frameSlider.availableHeight / 2 - height / 2
                width: frameSlider.availableWidth
                height: frameSlider.availableHeight

                Canvas
                {
                    id:canvas
                    anchors.fill: parent
                    onPaint:
                    {
                        var ctx = getContext("2d")
                        ctx.clearRect(0, 0, width, height)

                        ctx.strokeStyle = "#bdbebf"
                        ctx.lineWidth = 1

                        var runDuration = Number(runDurationDataTextField.dataTextField.text);
                        //绘制时间刻度
                        ctx.beginPath()
                        var secCount = getPaintCount(width,runDuration);
                        for(var i = 0;i < secCount; i++)
                        {
                            //绘制秒刻度
                            var secPaintX = i*width/secCount;
                            ctx.moveTo(secPaintX, height)
                            ctx.lineTo(secPaintX, height*0.7)
                            //绘制帧刻度
                            var secPaintNextX = (i+1)*width/secCount;
                            var secWidth = secPaintNextX-secPaintX;
                            var frameCount = getPaintCount(secPaintNextX-secPaintX,100);
                            for(var j = 0;j < frameCount; j++)
                            {
                                var framePaintX = secPaintX+j*secWidth/frameCount;
                                if(secPaintNextX - framePaintX > 5 && framePaintX - secPaintX > 5)
                                {
                                    ctx.moveTo(framePaintX, height)
                                    ctx.lineTo(framePaintX, height*0.85)
                                }
                            }
                        }
                        ctx.stroke();

                        //绘制节点刻度
                        ctx.beginPath()
                        ctx.strokeStyle = "#21be2b"
                        var nodeDuration = 0;
                        for(var node = 0;node < nodeListModel.count; node++)
                        {
                            nodeDuration += (nodeListModel.get(node).runDuration)
                            var nodePaintX = nodeDuration/runDuration*width;
                            ctx.moveTo(nodePaintX, height)
                            ctx.lineTo(nodePaintX, height*0.7)
                            if(Math.abs(nodePaintX-width)<20)
                                ctx.text("["+(node+1)+"]",nodePaintX-20,height*0.7)
                            else
                                ctx.text("["+(node+1)+"]",nodePaintX,height*0.7)
                        }
                        ctx.stroke();
                    }
                    function getPaintCount(w,count)
                    {
                        if(w < 1 || count < 1)
                            return 0;

                        var paintWidth = w/count;
                        if(paintWidth < 5)
                        {
                            count--;
                            return getPaintCount(w,count)
                        }
                        return count;
                    }
                }
            }

            handle: Rectangle
            {
                x: frameSlider.leftPadding + frameSlider.visualPosition * (frameSlider.availableWidth - width)
                y: frameSlider.topPadding + frameSlider.availableHeight / 2 - height / 2
                implicitWidth: 26
                implicitHeight: 26
                radius: 13
                color: frameSlider.pressed ? "#f0f0f0" : "#f6f6f6"
                border.color: "#bdbebf"
            }

        }

        DataTextField
        {
            id:runDurationDataTextField
            width: 120
            titleText: "运动时长/s";
            titleLabel.horizontalAlignment: Text.AlignHCenter
            dataTextField.validator: DoubleValidator{bottom: 1}
            dataTextField.selectByMouse: true
            dataTextField.onAccepted:
            {
                dataTextField.focus = false;
                MJSCript.scriptBuffer["RecordingDuration"] = Number(dataTextField.text)
            }
            function setDuration(frameCount)
            {
                dataTextField.text = frameCount/Number(cameraFPSText.dataComBox.currentText)
                canvas.requestPaint();
            }
        }
    }

    Rectangle
    {
        id:bottomItem
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: midRectangle.bottom
        anchors.bottom: parent.bottom
        color: "#202020"

        //遥控
        JRobotStatusRemoteItem
        {
            id: jRobotStatusRemoteItem
        }
        //节点数据+视图
        ListModel
        {
            id:nodeListModel
            onCountChanged: canvas.requestPaint();

            function addNodeData(index,node,nodeLast)
            {
//                console.log("addNodeData,",JSON.stringify(node))
                var target = node["1"]["target"];
                var param = node["1"]["param"];
                var type = node["1"]["type"];

                var nodeData = {};
                nodeData["X"] = target["X"];
                nodeData["Y"] = target["Y"];
                nodeData["Z"] = target["Z"];
                nodeData["A"] = target["A"];
                nodeData["B"] = target["B"];
                nodeData["C"] = target["C"];
                nodeData["E1"] = target["E1"];
                nodeData["runDuration"] = 0;
                nodeData["cicrAngle"] = 0;
                nodeData["cicrRadius"] = 0;
                nodeData["tsValue"] = param["TsValue"];
                nodeData["nodeType"] = type;

                nodeData["fX"] = "0";
                nodeData["fY"] = "0";
                nodeData["fZ"] = "0";
                nodeData["fA"] = "0";
                nodeData["fB"] = "0";
                nodeData["fC"] = "0";
                nodeData["fE1"] = "0";
                nodeData["cicrAngle"] = 0;
                nodeData["cicrRadius"] = 0;
                var assist = node["1"]["assist"];
                if(assist !== undefined)
                {
                    nodeData["fX"] = assist["X"];
                    nodeData["fY"] = assist["Y"];
                    nodeData["fZ"] = assist["Z"];
                    nodeData["fA"] = assist["A"];
                    nodeData["fB"] = assist["B"];
                    nodeData["fC"] = assist["C"];
                    nodeData["fE1"] = assist["E1"];
                    nodeData["cicrAngle"] = param["AssistCA"];
                    nodeData["cicrRadius"] = param["Radius"];
                }

                if(index === 0)
                {
                    nodeData["runDuration"] = MJSCript.scriptBuffer.MoveDelay;
                }
                else
                {
                    var targetLast = nodeLast["1"]["target"];
                    var prgv = param["PrgV"],robotV = param["RobotV"],angle = param["AssistCA"],radius = param["Radius"];
                    nodeData["runDuration"] = JRobot.durationCalc3d(targetLast["X"],targetLast["Y"],targetLast["Z"],
                                                         target["X"],target["Y"],target["Z"],(prgv*robotV/10000.0),type,angle,radius);
                }

                nodeListModel.append(nodeData);
            }
        }
        ListView
        {
            id:nodeListView
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: jRobotStatusRemoteItem.right
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            spacing: 10
            clip: true
            orientation: ListView.Horizontal
            model: nodeListModel
            delegate:JRobotNodeItem
            {
                id:jRobotNodeItem
                height: nodeListView.height
                Component.onCompleted:
                {
                    runDurationChanged.connect(canvas.requestPaint);
                    addNodeDataChanged.connect(nodeListModel.addNodeData);
                }
                Component.onDestruction:
                {
                    runDurationChanged.disconnect(canvas.requestPaint);
                    addNodeDataChanged.disconnect(nodeListModel.addNodeData);
                }
            }
        }
    }
}
