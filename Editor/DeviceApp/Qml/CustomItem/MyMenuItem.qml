import QtQuick 6.2
import QtQuick.Controls 6.2

Action
{
    id: root

    property int dataIndex: -1

    signal indexChanged(string value,int index);

    onTriggered:
    {
        indexChanged(root.text,root.dataIndex);
    }
}
