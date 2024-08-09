.pragma library

var lastgamedata =
{
    "X":"0",
    "Y":"0",
    "Z":"0",
    "A":"0",
    "B":"0",
    "C":"0",
    "E1":"0",
}
var robotGameData =
{
    "deviceId": 1,
    "code": 3,
    "data":
    {
        "P1":"0",
        "P2":"0",
        "P3":"0",
        "P4":"0",
        "P5":"0",
        "P6":"0",
        "P7":"0"
    }
}

function gameRunAll(obj,mode,speed)
{
    var nowdata = gameDataReturn(obj)
    if(lastORnow(nowdata))
    {
        lastgamedata = nowdata
        runRobot(nowdata,mode,speed)
        return 1
    }
    else
    {return 0}
}

function lastORnow(nowdata)
{
    if(lastgamedata["X"]!==nowdata["X"])
    {return 1}
    else if(lastgamedata["Y"]!==nowdata["Y"])
    {return 1}
    else if(lastgamedata["Z"]!==nowdata["Z"])
    {return 1}
    else if(lastgamedata["A"]!==nowdata["A"])
    {return 1}
    else if(lastgamedata["B"]!==nowdata["B"])
    {return 1}
    else if(lastgamedata["C"]!==nowdata["C"])
    {return 1}
    else if(lastgamedata["E1"]!==nowdata["E1"])
    {return 1}
    else
    {return 0}
}

function gameDataReturn(obj)
{
    var data =
    {
        "X":axisClassify(obj["axisLeftY"]),
        "Y":axisClassify(obj["axisLeftX"]),
        "Z":keyClassify(obj["down"],obj["up"]),
        "A":axisClassify(obj["axisRightX"]),
        "B":axisClassify(obj["axisRightY"]),
        "C":keyClassify(obj["l1"],obj["r1"]),
        "E1":keyClassify(obj["left"],obj["right"]),
    }
    return data;
}
function axisClassify(axis)
{
    var data
    if(-0.2<=axis&&axis<=0.2)
    {data = 0}
    else if(0.2<axis&&axis<=0.4)
    {data = 0.3}
    else if(0.4<axis&&axis<=0.6)
    {data = 0.5}
    else if(0.6<axis&&axis<=0.8)
    {data = 0.7}
    else if(0.8<axis&&axis<=1)
    {data = 0.9}
    else if(-0.4<=axis&&axis<-0.2)
    {data = -0.3}
    else if(-0.6<=axis&&axis<-0.4)
    {data = -0.5}
    else if(-0.8<=axis&&axis<-0.6)
    {data = -0.7}
    else if(-1<=axis&&axis<-0.8)
    {data = -0.9}
    return data;
}
function keyClassify(key1,key2)
{
    var data
    if(key1 && !key2)
    {data = -1}
    else if(!key1 && key2)
    {data = 1}
    else
    {data = 0}
    return data
}
function runRobot(obj,mode,speed)
{
    if(mode ===1)
    {
        var robodata =
        {
            "P1":String(obj["X"]),
            "P2":String(obj["Y"]*-1),
            "P3":String(obj["Z"]*speed/100),
            "P4":String(obj["A"]*-1),
            "P5":String(obj["B"]*-1),
            "P6":String(obj["C"]*speed/100),
            "P7":String(obj["E1"]*speed/100)
        }

        robotGameData =
        {
            "deviceId": 1,
            "code": 3,
            "data": robodata
        }
    }
    else if(mode===2)
    {
        var robodata1 =
        {
            "P1":String(obj["X"]),
            "P2":String(obj["Y"]*-1),
            "P3":String(obj["Z"]*speed/100),
            "P4":String(obj["A"]*-1),
            "P5":String(obj["B"]*-1),
            "P6":String(obj["C"]*speed/100),
            "P7":String(obj["E1"]*speed/100)
        }

        robotGameData =
        {
            "deviceId": 1,
            "code": 9,
            "data": robodata1
        }
    }
}
//"axisLeftX":0,"axisLeftY":0,"axisRightX":0,"axisRightY":0,"back":false,"down":false,
//"keyA":false,"keyB":false,"keyX":false,"keyY":false,"l1":false,"l2":1,"l3":false,
//"left":false,"r1":false,"r2":0,"r3":false,"right":false,"start":false,"up":false
