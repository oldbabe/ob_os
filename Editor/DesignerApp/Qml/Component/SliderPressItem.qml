import QtQuick 6.2
import QtQuick.Controls 6.2

Slider {
    id: control
    value: 0.5

    property double positions: sliderRect.x / (processBar.width - sliderRect.radius)
    property int toValue: 100
    property int fromValue: 0
    property int removeValue: minValue + (maxValue - minValue)*positions
    signal movedValue(int valuea)

    function setValue(num)
    {
        if(num>toValue)
        {
            sliderRect.x = processBar.width - sliderRect.radius
        }
        else if(num<fromValue)
        {
            sliderRect.x = 0
        }
        else
        {
            sliderRect.x =(num - fromValue)/(toValue-fromValue)*(processBar.width - sliderRect.radius)
        }
        processBarDone.width = sliderRect.x
    }

    background: Rectangle {
        id:processBar
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 4
        width: control.availableWidth
        height: implicitHeight
        radius: 2
        color: "#bdbebf"

        Rectangle {
            id:processBarDone
            width: control.positions * parent.width
            height: parent.height
            color: control.enabled ? "#21be2b" :"#aaaaaa"
            radius: 2
        }
    }

    handle: Rectangle {
        id:sliderRect
        implicitWidth: 18
        implicitHeight: 18
        radius: 9
        color: control.enabled ? (mouseAra.pressed ? "#21ba22" : "#f6f6f6"):"#aaaaaa"
        border.color: control.enabled ? "#bdbebf" :"#666666"
        anchors.verticalCenter: parent.verticalCenter

        MouseArea
        {
            id:mouseAra
            anchors.fill: parent
            onMouseXChanged:
            {
                if(pressed)
                {
                    sliderRect.x += mouseX - sliderRect.radius
                    //限制滑块不能超出父控件的边界
                    if(sliderRect.x < 0)
                        sliderRect.x = 0
                    if(sliderRect.x > (processBar.width - sliderRect.radius))
                        sliderRect.x = processBar.width - sliderRect.radius

                    //设置已加载部分的颜色
                    processBarDone.width = sliderRect.x
                    //产生信号
                    movedValue(removeValue)
                }
            }

        }
    }
}
