.pragma library

//选中的脚本地址
var selectScript = "";
//脚本数据缓存
var scriptData;

//获取脚本名字
function getSessionName()
{
    var nameArray =selectScript.split("/");
    var pathName = nameArray.pop();
    var name = pathName.replace(".json","");
    return name;
}

function getSessionFile()
{
    var nameArray =selectScript.split("/");
    var pathName = nameArray.pop();
    return pathName;
}

function getRobotTempData(type)
{
    var data =
    {
        "param":
        {
         "AssistCA": 30,
         "PathA": 30,
         "PathV": 30,
         "PrgV": 30,
         "RobotA": 30,
         "RobotV": 30,
         "TsValue": 0,
         "Waiting": 0
        },
        "target":
        {
         "A": "0",
         "A1": "0",
         "A2": "0",
         "A3": "0",
         "A4": "0",
         "A5": "0",
         "A6": "0",
         "B": "0",
         "C": "0",
         "E1": "0",
         "X": "0",
         "Y": "0",
         "Z": "0"
        },
        "assist":
        {
         "A": "0",
         "A1": "0",
         "A2": "0",
         "A3": "0",
         "A4": "0",
         "A5": "0",
         "A6": "0",
         "B": "0",
         "C": "0",
         "E1": "0",
         "X": "0",
         "Y": "0",
         "Z": "0"
        },
        "type": type
    }

    if(type !== 3)
        delete data.assist;

    return data;
}

function getCameraTempData()
{
    var data =
    {
        "ImageInterval": 0,
        "ImageNum": 1,
        "ShootMode": 0
    }
    return data;
}

function getFocusTempData()
{
    var data =
    {
        "Length":0,
        "FocusValue" : 3000,
        "FocusMode":0,
        "FocusRecord":{},
        "ZoomValue" : 3000,
        "ZoomMode":0,
        "ZoomRecord":{},
        "IrisValue" : 3000,
        "IrisMode":0,
        "IrisRecord":{}
    }
    return data;
}

function getTurnplateTempData()
{
    var data =
    {
        "Acc": 30,
        "Speed": 30,
        "target": "0"
    }
    return data;
}

function getNodeTempData(type)
{
    var node =
    {
        "1" : getRobotTempData(type),
        "2" : getCameraTempData(),
        "3" : getFocusTempData(),
        "4" : getTurnplateTempData()
    }
    return node;
}

function appendNodeData(type)
{
    if((scriptData.Nodes.length-1) > -1)
    {

        var item = getNodeTempData(type);


        scriptData.Nodes.push(item);
    }
}

function getTurnplateVidoData()
{
    var data =
    {
        "Acc": 30,
//        "Angle": "0",
        "Duration": 10,
        "Dec":30,
        "Ori": 1,
        "Speed": 30,
        "StartTime": 0
    }
    return data;
}

function delLastNodeData()
{
    if(scriptData.Nodes.length > 1)
        scriptData.Nodes.pop();
}

function getNodeData(index)
{
    var nodes = scriptData.Nodes;
    return nodes[index];
}

function setGlobalParam(key,value)
{
    scriptData[key] = value;
}

function setRobotParam(key,value)
{

    scriptData.Nodes[scriptData.CurrentIndex]["1"]["param"][key] = value;
}

function setRobotTarget(key,value)
{
    scriptData.Nodes[scriptData.CurrentIndex]["1"]["target"][key] = value;
}

function setRobotAssist(key,value)
{
    scriptData.Nodes[scriptData.CurrentIndex]["1"]["assist"][key] = value;
}

function setRobotGlobalParam(key,value)
{
    //
    for(var i = 0; i < scriptData.Nodes.length; i++)
        scriptData.Nodes[i]["1"]["param"][key] = value;
}

function setCameraParam(key,value)
{
    scriptData.Nodes[scriptData.CurrentIndex]["2"][key] = value;
}

function setFollowFocusParam(key,value)
{
    scriptData.Nodes[scriptData.CurrentIndex]["3"][key] = value;
}
function setFollowFocusIndex(index,key,value)
{
    scriptData.Nodes[index]["3"][key] = value;
}
//function setFollowFocusObj(index,obj)
//{
//    if(obj["FocusMode"]===2)
//    {
//        scriptData.Nodes[index]["3"]["FocusRecord"] =obj["FocusRecord"];
//        scriptData.Nodes[index]["3"]["FocusValue"] =obj["FocusValue"];
//        scriptData.Nodes[index]["3"]["FocusMode"] = 3 ;
//    }
//    if(obj["ZoomMode"]===2)
//    {
//        scriptData.Nodes[index]["3"]["ZoomRecord"] =obj["ZoomRecord"];
//        scriptData.Nodes[index]["3"]["ZoomValue"] =obj["ZoomValue"];
//        scriptData.Nodes[index]["3"]["ZoomMode"] = 3 ;
//    }
//    if(obj["IrisMode"]===2)
//    {
//        scriptData.Nodes[index]["3"]["IrisRecord"] =obj["IrisRecord"];
//        scriptData.Nodes[index]["3"]["IrisValue"] =obj["IrisValue"];
//        scriptData.Nodes[index]["3"]["IrisMode"] = 3 ;
//    }
//    scriptData.Nodes[index]["3"]["Length"] =obj["Length"]
//}
function setTurnplateParam(key,value)
{
    scriptData.Nodes[scriptData.CurrentIndex]["4"][key] = value;
}

function setTurnplateVParam(key,value)
{
    scriptData.Turnplates[key] = value;
}

//对焦值添加
function setFocusValue(value)
{
//    scriptData.FocusValues.push(value)
    scriptData.FocusRecording.focus.push(value)
}
//变焦值添加
function setZoomValue(value)
{
//    scriptData.ZoomValues.push(value)
    scriptData.FocusRecording.zoom.push(value)
}
//光圈添加
function setIrisValue(value)
{
//    scriptData.ZoomValues.push(value)
    scriptData.FocusRecording.Iris.push(value)
}

//相机控制
function setCameraValue(key,value)
{
    var dataValue =
            [
             {"key":key,
              "currentIndex":value,
              "delayTime":0
             }
            ]
    var data =
    {
       "deviceId": 2,
       "code": 1,
       "data":dataValue
    }
    return data;
}
function downCameraImage()
{
    var data =
    {
       "deviceId": 2,
       "code": 7,
    }
    return data;
}
function delCameraImage()
{
    var data =
    {
       "deviceId": 2,
       "code": 5,
    }
    return data;
}
function imageTake(mode)
{
    var data =
    {
        "deviceId": 2,
        "code": 3,
        "data": mode
    }
    return data;
}
function setCameraFocus(x,y)
{
    var data =
    {
        "deviceId": 2,
        "code": 10,
        "x": x,
        "y": y
    }
    return data;
}
//相机预设 -261 程序模式优先 - 264白平衡（修改会改变光圈和ISO） - 256光圈 - iso 260 -265对焦模式  快门速度":259 视频格式":295,录制格式":296
// function caremaConfi(value)
// {
//     var dataValue =[]

//     if(value["261W"] === true)
//     {dataValue.push(
//           {
//           "key":261,
//           "currentIndex":value["261"],
//           "delayTime":100
//           })}
//     if(value["264W"] === true)
//     {dataValue.push(
//           {
//           "key":264,
//           "currentIndex":value["264"],
//           "delayTime":100
//           })}
//     if(value["265W"] === true)
//     {dataValue.push(
//           {
//           "key":265,
//           "currentIndex":value["265"],
//           "delayTime":100
//           })}
//     if(value["262W"] === true)
//     {dataValue.push(
//           {
//           "key":262,
//           "currentIndex":value["262"],
//           "delayTime":100
//           })}
//     if(value["263W"] === true)
//     {dataValue.push(
//           {
//           "key":263,
//           "currentIndex":value["263"],
//           "delayTime":100
//           })}
//     if(value["260W"] === true)
//     {dataValue.push(
//           {
//           "key":260,
//           "currentIndex":value["260"],
//           "delayTime":100
//           })}
//     if(value["270W"] === true)
//     {dataValue.push(
//           {
//           "key":270,
//           "currentIndex":value["270"],
//           "delayTime":100
//           })}
//     if(value["275W"] === true)
//     {dataValue.push(
//           {
//           "key":275,
//           "currentIndex":value["275"],
//           "delayTime":100
//           })}
//     if(value["295W"] === true)
//     {dataValue.push(
//           {
//           "key":295,
//           "currentIndex":value["295"],
//           "delayTime":100
//           })}
//     if(value["296W"] === true)
//     {dataValue.push(
//           {
//           "key":296,
//           "currentIndex":value["296"],
//           "delayTime":100
//           })}
//     if(value["256W"] === true)
//     {dataValue.push(
//           {
//           "key":256,
//           "currentIndex":value["256"],
//           "delayTime":100
//           })}
//     if(value["297W"] === true)
//     {dataValue.push(
//           {
//           "key":297,
//           "currentIndex":value["297"],
//           "delayTime":100
//           })}
//     if(value["305W"] === true)
//     {dataValue.push(
//           {
//           "key":305,
//           "currentIndex":value["305"],
//           "delayTime":100
//           })}
//     if(value["259W"] === true)
//     {dataValue.push(
//           {
//           "key":259,
//           "currentIndex":value["259"],
//           "delayTime":100
//           })}


//     var data =
//     {
//        "deviceId": 2,
//        "code": 1,
//        "data":dataValue
//     }
//     return data;
// }

//机械臂控制
function getPosValue(type,p1,p2,p3,p4,p5,p6,p7)
{
    var mode =
    {
        "P1":p1,
        "P2":p2,
        "P3":p3,
        "P4":p4,
        "P5":p5,
        "P6":p6,
        "P7":p7
    }

    var data =
    {
        "deviceId": 1,
        "code": type,
        "data": mode
    }
    return data;
}
function getAxisValue(p1,p2,p3,p4,p5,p6,p7)
{
    var mode =
    {
        "P1":p1,
        "P2":p2,
        "P3":p3,
        "P4":p4,
        "P5":p5,
        "P6":p6,
        "P7":p7
    }

    var data =
    {
        "deviceId": 1,
        "code": 2,
        "data": mode
    }
    return data;
}
function jogStop()
{
    var data =
    {
        "deviceId": 1,
        "code": 1,
    }
    return data;
}

function getRevale(mode)
{
    var data =
    {
        "deviceId": 1,
        "code": 5,
        "data": mode
    }
    return data;
}

function setJAKAIncX(num)
{
    var data =
    {
        "deviceId": 1,
        "code": 10,
        "data":
        {
            "X":-num,
            "Y":0.0,
            "Z":0.0,
            "A":0.0,
            "B":0.0,
            "C":0.0

        }
    }
    return data;
}
function setToolIncX(num)
{
    var data =
    {
        "deviceId": 1,
        "code": 10,
        "data":
        {
            "X":-num,
            "Y":0.0,
            "Z":0.0,
            "A":0.0,
            "B":0.0,
            "C":0.0

        }
    }
    return data;
}
function setToolZeroX()
{
    var data =
    {
        "deviceId": 1,
        "code": 12,
        "data":
        {
            "X":0.0,
            "Y":0.0,
            "Z":0.0,
            "A":180.0,
            "B":0.0,
            "C":180.0

        }
    }
    return data;
}
function getAxisClassify(axis)
{
    var data
    if(-10<=axis&&axis<=10)
    {data = 0}
    else if(10<axis&&axis<=40)
    {data = 0.2}
    else if(40<axis&&axis<=80)
    {data = 0.4}
    else if(80<axis&&axis<=120)
    {data = 0.6}
    else if(-40<=axis&&axis<-10)
    {data = -0.2}
    else if(-80<=axis&&axis<-40)
    {data = -0.4}
    else if(-120<=axis&&axis<-80)
    {data = -0.6}

    return data;
}
//转盘控制
function turnplateRun(dir,speed,acc,dec)
{
    var data =
    {
        "deviceId": 4,
        "code":3,
        "angle":0,
        "speed":speed,
        "direction":dir,
        "acc":acc,
        "dec":dec,
    }
    return data
}
function turnplateStop()
{
    var data =
    {
        "deviceId": 4,
        "code":2,
        "angle":0,
        "speed":1,
        "direction":0,
        "acc":1,
        "dec":1,
    }
    return data
}

//跟焦器控制
function followRun(code,fvalue,zvalue,ivalue)
{
    var data = {}
    if(code ===1)
        data =
        {
            "deviceId": 3,
            "code":1,
            "data":{}
        }
    else if(code ===2)
        data =
        {
            "deviceId": 3,
            "code":2,
            "data":{"FocusValue":fvalue}
        }
    else if(code ===3)
        data =
        {
            "deviceId": 3,
            "code":3,
            "data":{"ZoomValue":zvalue}
        }
    else if(code ===4)
        data =
        {
            "deviceId": 3,
            "code":4,
            "data":{"FocusValue":fvalue,"ZoomValue":zvalue,"IrisValue":ivalue}
        }
    else if(code ===5)
        data =
        {
            "deviceId": 3,
            "code":5,
            "data":{"IrisValue":ivalue}
        }
    return data
}
//判断绝对值大小
function getMaxNumber(a,b)
{
    var c
    var d
    var data = [0,0]
    if(a !==0 && b !==0)
    {
        if(a<0)
        {c = -a}
        else
        {c = a}
        if(b<0)
        {d = -b}
        else
        {d = b}
        if(c>d)
        {data = [1,a]}
        else
        {data = [2,b]}
    }
    return data
}
