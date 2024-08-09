#include "jltscriptdrop.h"
#include "jltscriptconnector.h"
#include <QMimeData>
#include <QCursor>

JltScriptDrop::JltScriptDrop(QQuickItem *parent)
    : QQuickItem(parent)
{
    this->mDrapConnector = NULL;
    this->setFlag(QQuickItem::ItemAcceptsDrops);
}

void JltScriptDrop::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData *data = event->mimeData();
    if(data->data("ItemName") == "JLT")
    {
        event->accept();
    }
}

void JltScriptDrop::dragLeaveEvent(QDragLeaveEvent *event)
{
    // qDebug() << "dragLeaveEvent";
}

void JltScriptDrop::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
    emit dragMove(mapFromGlobal(QCursor::pos()));
}

void JltScriptDrop::dropEvent(QDropEvent *event)
{
    const QMimeData *data = event->mimeData();
    if(data->data("ItemName") == "JLT" && data->data("ItemType") == "JltScriptConnector")
    {
        //拖拽对象不为空
        if(!event->source())
        {
            event->ignore();
            return;
        }
        mDrapConnector = qobject_cast<JltScriptConnector *>(event->source());
        if(mDrapConnector)
        {
            auto point = mapFromGlobal(QCursor::pos());
            auto item = childAt(point.x(),point.y());
            if(!item)
            {
                emit menuOpened(point.x(),point.y());
                event->setDropAction(Qt::MoveAction);
                event->accept();
            }
        }
    }
}
