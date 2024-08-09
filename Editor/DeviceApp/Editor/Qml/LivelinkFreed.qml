import QtQuick 6.2
import QtQuick.Controls 6.2
import CppService 1.0
import Jlt.Moco 1.0
import "./CustomItem"

Rectangle
{
    id:root
    color: "black"

    implicitHeight: 200
    implicitWidth: 200

    //退出页面
    signal quitPage();

    Component.onCompleted:
    {
        autoStartSwitch.setSwitchState(JLiveLinkFreeD.getAutoFlag());
        freedStateSwitch.setSwitchState(JLiveLinkFreeD.isRunning());

        ipDataTextField.dataTextField.text = JLiveLinkFreeD.getIpAddress();
        portDataTextField.dataTextField.text = JLiveLinkFreeD.getPort();
        frameTextField.dataTextField.text = JLiveLinkFreeD.getFrame();

        focusRangeItem.setMinValue(JLiveLinkFreeD.getFocusMinValue().toString());
        focusRangeItem.setMaxValue(JLiveLinkFreeD.getFocusMaxValue().toString());
        zoomRangeItem.setMinValue(JLiveLinkFreeD.getZoomMinValue().toString());
        zoomRangeItem.setMaxValue(JLiveLinkFreeD.getZoomMaxValue().toString());

        var rotates = JLiveLinkFreeD.getCameraRotate();
        cameraRotateInput.setVlaue(0,rotates[0]);
        cameraRotateInput.setVlaue(1,rotates[1]);
        cameraRotateInput.setVlaue(2,rotates[2]);

        var transforms = JLiveLinkFreeD.getCameraTransform();
        cameraTransformItem.setTransForm(transforms[0],transforms[1],transforms[2])

        var offset = JLiveLinkFreeD.getCoordinateOffset();
        worldCoordinateInput.setVlaue(0,offset[0]);
        worldCoordinateInput.setVlaue(1,offset[1]);
        worldCoordinateInput.setVlaue(2,offset[2]);

        var unitys = JLiveLinkFreeD.getCoordinateUnity();
        coordinateUnitItem.setUnits(unitys[0],unitys[1],unitys[2])

        var axistransforms = JLiveLinkFreeD.getCoordinateTransform();
        coordinateTransFormItem.setTransForm(axistransforms[0],axistransforms[1],axistransforms[2])
    }

    MouseArea
    {
        anchors.fill: parent
        onPressed: root.focus=true;
    }
    //退出按钮
    ToolButton
    {
        id: quitButton
        showText: "×"
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left:  parent.left
        anchors.leftMargin: 15
        onButtonClicked:  root.quitPage();
    }
    //标题
    Text
    {
        id: setTitleText
        font.pixelSize: 14
        color: "#f1f1f1"
        anchors.verticalCenter: quitButton.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("偏好设置->基本设置")
    }
    //发送IP
    DataTextField
    {
        id:ipDataTextField
        anchors.top: setTitleText.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "IP地址";
        dataTextField.selectByMouse: true
        dataTextField.validator: RegularExpressionValidator { regularExpression: /((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}/ }
        dataTextField.onEditingFinished:
        {
            dataTextField.focus = false;
            JLiveLinkFreeD.setIpAddress(ipDataTextField.dataTextField.text)
        }
    }
    //发送Port
    DataTextField
    {
        id:portDataTextField
        anchors.top: ipDataTextField.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "端口号";
        dataTextField.validator: IntValidator{bottom: 0}
        dataTextField.selectByMouse: true
        dataTextField.onEditingFinished:
        {
            dataTextField.focus = false;
            JLiveLinkFreeD.setPort(Number(portDataTextField.dataTextField.text))
        }
    }
    //帧率
    DataTextField
    {
        id:frameTextField
        anchors.top: portDataTextField.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "帧率";
        dataTextField.validator: IntValidator{bottom: 0}
        dataTextField.selectByMouse: true
        dataTextField.onEditingFinished:
        {
            dataTextField.focus = false;
            JLiveLinkFreeD.setFrame(Number(frameTextField.dataTextField.text))
        }
    }
    //相机旋转
    CoordinateInput
    {
        id:cameraRotateInput
        anchors.top: frameTextField.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "相机旋转";
        suffix: "度"
        onValueChanged: (value1,value2,value3)=>{JLiveLinkFreeD.setCameraRotate(Number(value1),Number(value2),Number(value3));}
    }
    //相机变换
    CameraTransformItem
    {
        id:cameraTransformItem
        anchors.top: cameraRotateInput.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        titleText: "相机轴转换";
        onValueChanged: (value1,value2,value3)=>{JLiveLinkFreeD.setCameraTransform(value1,value2,value3);}
    }

    //世界坐标偏移
    CoordinateInput
    {
        id:worldCoordinateInput
        anchors.top: cameraTransformItem.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "坐标偏移";
        suffix: "毫米"
        onValueChanged: (value1,value2,value3)=>{JLiveLinkFreeD.setCoordinateOffset(Number(value1),Number(value2),Number(value3));}
    }
    //坐标单位
    CoordinateUnitItem
    {
        id:coordinateUnitItem
        anchors.top: worldCoordinateInput.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "坐标单位";
        onUnitChanged:(xIndex,yIndex,zIndex)=>
                      {
                          var xValue = 1.0,yValue = 1.0,zValue = 1.0;
                          if(xIndex === 1)
                            xValue = 10.0;
                          else if(xIndex === 2)
                            xValue = 100.0;

                          if(yIndex === 1)
                            yValue = 10.0;
                          else if(yIndex === 2)
                            yValue = 100.0;

                          if(zIndex === 1)
                            zValue = 10.0;
                          else if(zIndex === 2)
                            zValue = 100.0;
                          JLiveLinkFreeD.setWorldCoordinateUnity(xValue,yValue,zValue)
                      }
    }

    CoordinateTransFormItem
    {
        id:coordinateTransFormItem
        anchors.top: coordinateUnitItem.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "坐标系转换";
        onValueChanged: (value1,value2,value3)=>{JLiveLinkFreeD.setCoordinateTransform(value1,value2,value3);}
    }

    RangeItem
    {
        id: focusRangeItem
        anchors.top: coordinateTransFormItem.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "焦距范围"
        onMinValueEditingFinished: (value)=>{setFocus(0,false);JLiveLinkFreeD.setFocusMinValue(Number(value))}
        onMaxValueEditingFinished: (value)=>{setFocus(1,false);JLiveLinkFreeD.setFocusMaxValue(Number(value))}
    }
    RangeItem
    {
        id: zoomRangeItem
        anchors.top: focusRangeItem.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "变焦范围"
        onMinValueEditingFinished: (value)=>{setFocus(0,false);JLiveLinkFreeD.setZoomMinValue(Number(value))}
        onMaxValueEditingFinished: (value)=>{setFocus(1,false);JLiveLinkFreeD.setZoomMaxValue(Number(value))}

    }

    //自动开启服务
    SwitchTitleItem
    {
        id:autoStartSwitch
        anchors.top: zoomRangeItem.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "自动开启";
        onToSwitchState: JLiveLinkFreeD.setAutoFlag(switchState);
    }
    //开启/关闭服务
    SwitchTitleItem
    {
        id:freedStateSwitch
        anchors.top: autoStartSwitch.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        titleText: "状态";
        onToSwitchState:
        {
            if(JLiveLinkFreeD.isRunning())
                JLiveLinkFreeD.stopServer();
            else
                JLiveLinkFreeD.startServer();
        }
    }


}
