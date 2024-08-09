.pragma library


function getJogCommand(p1,p2,p3,p4,p5,p6,p7)
{
    var cmd = {
        "P1":p1,
        "P2":p2,
        "P3":p3,
        "P4":p4,
        "P5":p5,
        "P6":p6,
        "P7":p7
    }
    return cmd;
}

function getNode1Data(fNumber)
{
    var param = {
        "AssistCA": 30,
        "PathA": 30,
        "PathV": 30,
        "PrgV": 100,
        "RobotA": 30,
        "RobotV": 30,
        "TsValue": 0,
        "Waiting": 0
    };
    var target = {
        "X": "-698.874",
        "Y": "-314.147",
        "Z": "593.583",
        "A": "-1.25166",
        "B": "3.65284",
        "C": "-127.03",
        "A1": "33.7176",
        "A2": "100.916",
        "A3": "102.917",
        "A4": "69.2047",
        "A5": "-272.386",
        "A6": "-70.7693",
        "E1": "1118.19"
    };

    var node = {
        "param":param,
        "target":target,
        "type":2,
        "frameNumber":fNumber
    }
    return node;
}

function getNode2Data(fNumber)
{
    var param = {
        "AssistCA": 30,
        "PathA": 30,
        "PathV": 30,
        "PrgV": 100,
        "RobotA": 30,
        "RobotV": 30,
        "TsValue": 0,
        "Waiting": 0
    };
    var target = {
        "X": "-500",
        "Y": "0",
        "Z": "593.583",
        "A": "-1.25166",
        "B": "3.65284",
        "C": "-127.03",
        "A1": "-16.034",
        "A2": "102.24",
        "A3": "101.924",
        "A4": "65.9767",
        "A5": "-273.858",
        "A6": "-20.9593",
        "E1": "1118.19"
    };

    var node = {
        "param":param,
        "target":target,
        "type":2,
        "frameNumber":fNumber
    }
    return node;
}

function getNode3Data(fNumber)
{
    var param = {
        "AssistCA": 30,
        "PathA": 30,
        "PathV": 30,
        "PrgV": 100,
        "RobotA": 30,
        "RobotV": 30,
        "TsValue": 0,
        "Waiting": 0
    };
    var target = {
        "X": "-698.874",
        "Y": "329.853",
        "Z": "593.583",
        "A": "-1.25166",
        "B": "3.65284",
        "C": "-127.03",
        "A1": "-16.034",
        "A2": "102.24",
        "A3": "101.924",
        "A4": "65.9767",
        "A5": "-273.858",
        "A6": "-20.9593",
        "E1": "1118.19"
    };

    var node = {
        "param":param,
        "target":target,
        "type":2,
        "frameNumber":fNumber
    }
    return node;
}
