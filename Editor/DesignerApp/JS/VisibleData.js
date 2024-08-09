.pragma library
//遥控机械臂视图给到的参数
var PosValue


var AnaleValue
var GameType = 1


//脚本视图给到的参数
var currentData =
{
    "1": {
        "param": {
            "AssistCA": 30,
            "PathA": 30,
            "PathV": 30,
            "PrgV": 30,
            "RobotA": 30,
            "RobotV": 30,
            "TsValue": 0,
            "Waiting": 0
        },
        "target": {
            "A": "113.712",
            "A1": "11.6034",
            "A2": "128.755",
            "A3": "85.3145",
            "A4": "171.244",
            "A5": "110.275",
            "A6": "4.70338",
            "B": "4.21763",
            "C": "-98.774",
            "E1": "1118.19",
            "X": "-901.458",
            "Y": "-14.769",
            "Z": "141.593"
        },
        "type": 1
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

function setCurrentData(x,y,z,a,b,c,a1,a2,a3,a4,a5,a6,e1)
{
    currentData["1"]["target"]["X"] = x;
    currentData["1"]["target"]["Y"] = y;
    currentData["1"]["target"]["Z"] = z;
    currentData["1"]["target"]["A"] = a;
    currentData["1"]["target"]["B"] = b;
    currentData["1"]["target"]["C"] = c;
    currentData["1"]["target"]["A1"] = a1;
    currentData["1"]["target"]["A2"] = a2;
    currentData["1"]["target"]["A3"] = a3;
    currentData["1"]["target"]["A4"] = a4;
    currentData["1"]["target"]["A5"] = a5;
    currentData["1"]["target"]["A6"] = a6;
    currentData["1"]["target"]["E1"] = e1;
}

var current
//相机属性给到的参数
var cameraMode = 0
//var cameraWritable =
//{
//    "256":0,
//    "259":0,
//    "260":0,
//    "261":0,
//    "262":0,
//    "263":0,
//    "264":0,
//    "265":0,
//    "295":0,
//    "296":0,
//    "297":0,
//    "305":0
//}
//对焦器给到的参数
var followMode = 1
var handMode = 0
//脚本item列表
var sessionList = []
//数据库文件地址
var dataScriptPath ="D:/testdata/datascript"

//属性界面给到的数据
var assiseData =
{
    "deviceId": 1,
    "code": 5,
    "data":
    {
        "param":
        {
            "AssistCA":0,
            "PathA":50,
            "PathV":50,
            "PrgV":10,
            "RobotA":50,
            "RobotV":50,
            "TsValue":0
        },
        "target":
        {
            "A":"0",
            "A1":"0",
            "A2":"0",
            "A3":"0",
            "A4":"0",
            "A5":"0",
            "A6":"0",
            "B":"0",
            "C":"0",
            "E1":"0",
            "X":"0",
            "Y":"0",
            "Z":"0"
        },
        "type":1
    }
}

//当前节点数据
var nowPosData=
{
    "1": {
        "param": {
            "AssistCA": 30,
            "PathA": 30,
            "PathV": 30,
            "PrgV": 30,
            "RobotA": 30,
            "RobotV": 30,
            "TsValue": 1,
            "Waiting": 0
        },
        "target": {
            "A": "-86.2964",
            "A1": "0",
            "A2": "0",
            "A3": "0",
            "A4": "0",
            "A5": "0",
            "A6": "0",
            "B": "82.7550",
            "C": "89.6648",
            "E1": "737.68",
            "X": "-474.6313",
            "Y": "56.5499",
            "Z": "384.1114"
        },
        "type": 1
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

function setNowPos(data,target,speed)
{
    nowPosData["1"]["target"]=data;
    nowPosData["1"]["param"]["PathV"]=speed;
    nowPosData["1"]["param"]["RobotV"]=speed;
    nowPosData["4"]["target"]=target;

    return nowPosData;
}

function zeroData()
{
    var zeroValue =
    {

        "1": {
            "param": {
                "AssistCA": 30,
                "PathA": 30,
                "PathV": 30,
                "PrgV": 30,
                "RobotA": 30,
                "RobotV": 30,
                "TsValue": 1,
                "Waiting": 0
            },
            "target": {
                "A": "-86.2964",
                "A1": "0",
                "A2": "0",
                "A3": "0",
                "A4": "0",
                "A5": "0",
                "A6": "0",
                "B": "82.7550",
                "C": "89.6648",
                "E1": "737.68",
                "X": "-474.6313",
                "Y": "56.5499",
                "Z": "384.1114"
            },
            "type": 1
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
    return zeroValue;
}

function downPath(path)
{
    if(path!=="")
    {
        var pathArray = path.split("/");
        var pathName = pathArray.pop();
        path = path.replace(pathName,"download")
        var data =
                {
            "deviceId": 2,
            "code": 2,
            "data":path
        }
        return data;
    }
    else
    {return path;}
}

function setModo(node)
{
    var fule =
    {
        "param":node["1"]["param"],
        "target":node["1"]["target"],
        "type":2
    }

    var modo =
    {
        "1":fule,
        "2":node["2"],
        "3":node["3"],
        "4":node["4"],
    }

    return modo

}
function appirt()
{
    var mfle = (Qt.application.arguments[0]).replace("DesignerApp.exe","ModelFile");
    var ifmfle = true
    while(ifmfle)
    {
        mfle=mfle.replace("\\","/");
        ifmfle=mfle.includes("\\")
    }
    return mfle
}
function setAssiaPos(obj)
{
    assiseData["data"]["target"]["X"] = obj["x"]
    assiseData["data"]["target"]["Y"] = obj["y"]
    assiseData["data"]["target"]["Z"] = obj["z"]
    assiseData["data"]["target"]["A"] = obj["rx"]
    assiseData["data"]["target"]["B"] = obj["ry"]
    assiseData["data"]["target"]["C"] = obj["rz"]
    assiseData["data"]["target"]["E1"] = obj["a7"]
}
function setAssiaSpeed(value)
{
    assiseData["data"]["param"]["PrgV"] = value
}


