.pragma library
var roboReady
//0点坐标参数
var zeroPosition
//初始点坐标参数
var firstPosition
//速度设置参数
var speedData
//回正速度
var rightSpeed
//相机默认下载地址
var cameraDownSite = ""
//相机指定下载地址
var cameraSetSite = ""
//相机指定下载是否开启
var cameraSetBool = false
//相机预设使用
// var caremaPreinstall = 0
//0点坐标函数
function setNumber1()
{
    zeroPosition =
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
            "target":  {
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
            "Speed": 60,
            "target": 0
        }
    }
}
function setNumber2()
{
    firstPosition =
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
            "target":  {
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
            "Speed": 60,
            "target": 0
        }
    }
}
function setNumber3()
{
    speedData =
    {
        "1":30,
        "2":70,
        "3":30,
        "4":70,
        "5":30,
        "6":70,
        "7":30,
        "8":70,
        "9":30,
        "10":70,
        "11":30,
        "12":70,
        "13":30,
        "14":70,
        "15":30,
        "16":70,
        "17":30,
        "18":70,
        "19":30,
        "20":70,
        "21":30,
        "22":70,
        "23":30,
        "24":70,
        "25":30,
        "26":70,
    }
}
function setNumber5()
{
    rightSpeed=
    {
        "BSpeed":30,
        "CSpeed":30,
        "gameSpeed":30
    }
}

function setZeroDataRobot(x,y,z,a,b,c,a1,a2,a3,a4,a5,a6,e1)
{
    zeroPosition["1"]["target"]["X"] = x;
    zeroPosition["1"]["target"]["Y"] = y;
    zeroPosition["1"]["target"]["Z"] = z;
    zeroPosition["1"]["target"]["A"] = a;
    zeroPosition["1"]["target"]["B"] = b;
    zeroPosition["1"]["target"]["C"] = c;
    zeroPosition["1"]["target"]["A1"] = a1;
    zeroPosition["1"]["target"]["A2"] = a2;
    zeroPosition["1"]["target"]["A3"] = a3;
    zeroPosition["1"]["target"]["A4"] = a4;
    zeroPosition["1"]["target"]["A5"] = a5;
    zeroPosition["1"]["target"]["A6"] = a6;
    zeroPosition["1"]["target"]["E1"] = e1;
}
function setZeroDataTurnP(target)
{
    zeroPosition["4"]["target"]=target;
}
function setZeroPosRobo(key,value)
{
    zeroPosition["1"]["target"][key]=value;
}
function setZeroPosRoboV(value)
{
    zeroPosition["1"]["param"]["RobotV"]=value;
    zeroPosition["1"]["param"]["PathV"]=value;
}
function setZeroPosTurn(value)
{
    zeroPosition["4"]["target"]=value;
}
//初始点坐标函数
function setFirstDataRobot(x,y,z,a,b,c,a1,a2,a3,a4,a5,a6,e1)
{
    firstPosition["1"]["target"]["X"] = x;
    firstPosition["1"]["target"]["Y"] = y;
    firstPosition["1"]["target"]["Z"] = z;
    firstPosition["1"]["target"]["A"] = a;
    firstPosition["1"]["target"]["B"] = b;
    firstPosition["1"]["target"]["C"] = c;
    firstPosition["1"]["target"]["A1"] = a1;
    firstPosition["1"]["target"]["A2"] = a2;
    firstPosition["1"]["target"]["A3"] = a3;
    firstPosition["1"]["target"]["A4"] = a4;
    firstPosition["1"]["target"]["A5"] = a5;
    firstPosition["1"]["target"]["A6"] = a6;
    firstPosition["1"]["target"]["E1"] = e1;
}
function setFirstDataTurnP(target)
{
    firstPosition["4"]["target"]=target;
}
function setFirstPosRobo(key,value)
{
    firstPosition["1"]["target"][key]=value;
}
function setFirstPosRoboV(value)
{
    firstPosition["1"]["param"]["RobotV"]=value;
    firstPosition["1"]["param"]["PathV"]=value;
}
function setFirstPosTurn(value)
{
    firstPosition["4"]["target"]=value;
}
//速度设置函数
function setSpeedData(xmPer,xkPer,ymPer,ykPer,zmPer,zkPer,amPer,akPer,bmPer,bkPer,cmPer,ckPer,a1mPer,a1kPer,a2mPer,a2kPer,a3mPer,a3kPer,a4mPer,a4kPer,a5mPer,a5kPer,a6mPer,a6kPer,e1mPer,e1kPer)
{
    var data =
    {
        "1":xmPer,
        "2":xkPer,
        "3":ymPer,
        "4":ykPer,
        "5":zmPer,
        "6":zkPer,
        "7":amPer,
        "8":akPer,
        "9":bmPer,
        "10":bkPer,
        "11":cmPer,
        "12":ckPer,
        "13":a1mPer,
        "14":a1kPer,
        "15":a2mPer,
        "16":a2kPer,
        "17":a3mPer,
        "18":a3kPer,
        "19":a4mPer,
        "20":a4kPer,
        "21":a5mPer,
        "22":a5kPer,
        "23":a6mPer,
        "24":a6kPer,
        "25":e1mPer,
        "26":e1kPer,

    }
    return data
}
function setSpeedValue(key,value)
{
    speedData[key] = value;
}
//回正速度设置
function setRightSpeed(key,value)
{
    rightSpeed[key] = value;
}
