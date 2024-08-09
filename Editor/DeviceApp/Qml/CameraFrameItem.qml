import QtQuick 6.2
import CppService 1.0

Rectangle
{
    id: root
    radius: 5
    implicitHeight: 80
    implicitWidth: 80

    color: "#81d3f8f1"

    property var videoSink
    property int autoCount: 0

    Connections
    {
        target: root.videoSink
        function onVideoFrameChanged(frame)
        {
            if(EditorQml.getDebugFlag())
            {
                root.autoCount++;
                if(root.autoCount > 4)
                {
                    EditorQml.videoFrameUpdate(frame);
                    root.autoCount = 0;
                }
            }
            else
            {
                EditorQml.videoFrameUpdate(frame);
            }

            frame.destroy();
        }
    }
}
