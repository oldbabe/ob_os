import QtQuick 6.2
import QtQuick.Controls 6.2
import CppService 1.0

Window
{
    id:window
    height: 100
    width: 400
    maximumHeight: 100
    maximumWidth: 400
    minimumHeight: 100
    minimumWidth: 400
    visible: true
    title: "倔老头-"+(UpdateManager.updateEnable?("更新(远端"+UpdateManager.nasVersion+"=>本地"+UpdateManager.version+")"):("打包(本地"+UpdateManager.version+"=>远端"+UpdateManager.nasVersion+")"))

    Component.onCompleted:
    {
        if(UpdateManager.updateEnable)
        {
            UpdateManager.updateProgram();
        }
    }

    Connections
    {
        target: UpdateManager
        function onQuitApp()
        {
            Qt.quit();
        }
    }

    Rectangle
    {
        anchors.fill: parent
        color: "#202020"
        Column
        {
            id: column
            spacing: 10
            anchors.fill: parent
            anchors.margins: 10

            Item
            {
                height: 30
                width: parent.width
                Text
                {
                    color: "#f1f1f1"
                    text: UpdateManager.scheduleText
                    font.pixelSize: 14
                    anchors.centerIn: parent
                }
                Button
                {
                    id: srcDirButton
                    width: 50
                    height: 25
                    text: "源程序"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    enabled: versionTextField.verEnable
                    visible: !UpdateManager.updateEnable

                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("被压缩文件夹地址\n")+UpdateManager.writerSrcDir

                    onClicked:
                    {
                        var path = UpdateManager.getSystemDirectory("获取被压缩文件夹",UpdateManager.getDesktopDirectory());
                        if(path.length > 0)
                        {
                            UpdateManager.writerSrcDir = path;
                        }
                    }
                }

                Button
                {
                    id: targetButton
                    width: 35
                    height: 25
                    text: "目标"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: srcDirButton.right
                    anchors.leftMargin: 5
                    enabled: versionTextField.verEnable
                    visible: !UpdateManager.updateEnable

                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("打包到的文件夹地址\n")+UpdateManager.writerTargetDir

                    onClicked:
                    {
                        var path = UpdateManager.getSystemDirectory("获取打包到的文件夹",UpdateManager.getDesktopDirectory());
                        if(path.length > 0)
                        {
                            UpdateManager.writerTargetDir = path;
                        }
                    }
                }

                Button
                {
                    id: packButton
                    width: 35
                    height: 25
                    text: "打包"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: targetButton.right
                    anchors.leftMargin: 5
                    enabled: versionTextField.verEnable
                    visible: !UpdateManager.updateEnable

                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("打包源程序到目标地址,并更新版本文件")
                    onClicked:UpdateManager.packaging();
                }
                TextField
                {
                    id:versionTextField
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: packButton.right
                    anchors.leftMargin: 10
                    height: 30
                    width: 80
                    verticalAlignment: Text.AlignVCenter
                    leftPadding:5
                    color: "#f1f1f1"
                    placeholderText:"输入版本号"
                    placeholderTextColor:"#888888"
                    validator: RegularExpressionValidator { regularExpression: /((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}/ }

                    property bool verEnable: false
                    visible: !UpdateManager.updateEnable
                    text: UpdateManager.version;

                    background: Rectangle
                    {
                        color: "#363636"
                        radius: 3
                    }

                    onAccepted:
                    {
                        focus = false;
                        UpdateManager.version = text;
                        verEnable = true;
                    }
                }
            }

            Slider
            {
                id:slider
                width: parent.width
                height: 30
                from:0
                to:UpdateManager.to
                value: UpdateManager.value
                focusPolicy:Qt.NoFocus
                enabled: false


                background: Rectangle
                {
                    x: slider.leftPadding
                    y: slider.topPadding + slider.availableHeight / 2 - height / 2
                    width: slider.availableWidth
                    height: slider.height
                    radius: 2
                    color: "#bdbebf"

                    Rectangle
                    {
                        width: slider.visualPosition * parent.width
                        height: parent.height
                        color: "#21be2b"
                        radius: 2
                    }
                }

                handle: Item
                {
                    x: slider.visualPosition*(slider.availableWidth - width)
                    y: 0
                    implicitWidth: 26
                    implicitHeight: slider.availableHeight
                    Text {
                        anchors.centerIn: parent
                        color: "yellow"
                        text: Math.round(slider.position*100).toFixed(0)+"%"
                    }
                }
            }
        }
    }
}



