import QtQuick 6.2
import Jlt.VirtualCamera 1.0

Rectangle
{
    id: root
    color: "#262626"

    //退出页面
    signal quitPage();

//    Row
//    {
//        anchors.fill: parent

//        VirtualCamera
//        {
//            width: parent.width/2
//            height: parent.height
//        }
//    }

    VirtualCamera
    {
        anchors.fill: parent
    }
    MouseArea
    {
        anchors.fill: parent
        onClicked: root.quitPage();
    }
}
