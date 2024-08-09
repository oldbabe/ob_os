import QtQuick
import QtQuick.Controls

import JMoco 1.0
import "../CustomItem"
import "../Js/JSDeviceRobot.js" as MJSRobot

//状态＋遥控
Column
{
    id: column
    width: yDataTextField.width+80
    DataTextField
    {
        id:xDataTextField
        titleText: "X";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.x
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            dataTextField.focus = false;
        }
        ToolButton
        {
            id:xLeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("-0.3","0","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: xLeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0.3","0","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:yDataTextField
        titleText: "Y";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.y
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            dataTextField.focus = false;
        }
        ToolButton
        {
            id:yLeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","-0.5","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: yLeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0.5","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:zDataTextField

        titleText: "Z";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.z
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            dataTextField.focus = false;
        }
        ToolButton
        {
            id:zLeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","-0.5","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: zLeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","0.5","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:aDataTextField

        titleText: "A";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.rx
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            dataTextField.focus = false;
        }
        ToolButton
        {
            id:aLeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","0","-0.5","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: aLeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","0","0.5","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:bDataTextField

        titleText: "B";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.ry
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            dataTextField.focus = false;
        }
        ToolButton
        {
            id:bLeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","0","0","-0.5","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: bLeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","0","0","0.5","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:cDataTextField

        titleText: "C";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.rz
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:
        {
            dataTextField.focus = false;
        }
        ToolButton
        {
            id:cLeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","0","0","0","-0.5","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: cLeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(3,MJSRobot.getJogCommand("0","0","0","0","0","0.5","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:e1DataTextField
        titleText: "E1";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.a7
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:dataTextField.focus = false;
        ToolButton
        {
            id:e1LeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","0","0","0","-0.5"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: e1LeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","0","0","0","0.5"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:a1DataTextField
        titleText: "A1";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.a1
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:dataTextField.focus = false;
        ToolButton
        {
            id:a1LeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("-0.5","0","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: a1LeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0.5","0","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:a2DataTextField
        titleText: "A2";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.a2
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:dataTextField.focus = false;
        ToolButton
        {
            id:a2LeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","-0.5","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: a2LeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0.5","0","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:a3DataTextField
        titleText: "A3";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.a3
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:dataTextField.focus = false;
        ToolButton
        {
            id:a3LeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","-0.5","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: a3LeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0.5","0","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:a4DataTextField
        titleText: "A4";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.a4
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:dataTextField.focus = false;
        ToolButton
        {
            id:a4LeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","-0.5","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: a4LeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","0.5","0","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:a5DataTextField
        titleText: "A5";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.a5
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:dataTextField.focus = false;
        ToolButton
        {
            id:a5LeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","0","-0.5","0","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: a5LeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","0","0.5","0","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
    DataTextField
    {
        id:a6DataTextField
        titleText: "A6";
        titleLabel.width: 40
        titleLabel.horizontalAlignment: Text.AlignHCenter
        dataTextField.text: JRobot.position.a6
        dataTextField.validator: IntValidator{}
        dataTextField.selectByMouse: true
        dataTextField.onAccepted:dataTextField.focus = false;
        ToolButton
        {
            id:a6LeftButton
            showText: "-"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","0","0","-0.5","0"))
            onButtonRelease: JRobot.runStop();
        }
        ToolButton
        {
            showText: "+"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: a6LeftButton.right
            anchors.leftMargin: 10
            onButtonPressed: JRobot.jogMovement(2,MJSRobot.getJogCommand("0","0","0","0","0","0.5","0"))
            onButtonRelease: JRobot.runStop();
        }
    }
}
