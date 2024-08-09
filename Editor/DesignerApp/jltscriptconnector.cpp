#include "jltscriptconnector.h"
#include "jltscriptnode.h"
#include <QDrag>
#include <QMimeData>
#include <QCursor>

JltScriptConnector::JltScriptConnector(QQuickItem *parent)
    : QQuickItem(parent)
{
    this->mDragPenStyle = 1;
    this->mDragActive = false;
    this->mDropActive = false;
    this->mConnectorType = ConnectorType_Null;
    this->mDisableConnector = NULL;
    this->mBindNode = NULL;
    this->mBindConnector = NULL;

    this->setFlag(QQuickItem::ItemAcceptsDrops);
}

JltScriptConnector::~JltScriptConnector()
{
    ;
}

void JltScriptConnector::startDrag()
{
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("ItemName","JLT");
    mimeData->setData("ItemType","JltScriptConnector");
    drag->setMimeData(mimeData);
    QPixmap pix;
    pix.load(":/Image/icon_script_drag.png");
    drag->setPixmap(pix.scaled(QSize(120,30)));
    drag->setHotSpot(QPoint(-15,-10));
    this->setDragActive(true);
    auto droppAction = drag->exec(Qt::LinkAction|Qt::MoveAction);
    if(droppAction == Qt::LinkAction || droppAction == Qt::IgnoreAction)
    {
        this->stopDrag();
    }
}

void JltScriptConnector::stopDrag()
{
    this->setDragActive(false);
}

void JltScriptConnector::setDragPenStyle(int value)
{
    if(value != mDragPenStyle)
    {
        this->mDragPenStyle = value;
        emit dragPenStyleChanged();
    }
}

void JltScriptConnector::setDragActive(bool value)
{
    if(mDragActive != value)
    {
        this->mDragActive = value;
        emit dragActiveChanged();
    }
}

void JltScriptConnector::setDropActive(bool value)
{
    if(mDropActive != value)
    {
        this->mDropActive = value;
        emit dropActiveChanged();
    }
}

void JltScriptConnector::setConnectorType(ConnectorType type)
{
    if(type != mConnectorType)
    {
        this->mConnectorType = type;
        emit connectorTypeChanged();
    }
}

void JltScriptConnector::setBindNode(JltScriptNode *node)
{
    this->mBindNode = node;
}

void JltScriptConnector::setDisableConnector(JltScriptConnector *connector)
{
    if(mDisableConnector != connector)
    {
        this->mDisableConnector = connector;
        emit disableConnectorChanged();
    }
}

void JltScriptConnector::setBindConnector(JltScriptConnector *connector)
{
    this->mBindConnector = connector;
    emit bindConnectorChanged();
}

void JltScriptConnector::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData *data = event->mimeData();
    if(data->data("ItemName") == "JLT" && data->data("ItemType") == "JltScriptConnector")
    {
        event->accept();
        if(mDragActive) //拖拽模式下拖放状态重置
        {
            this->setDropActive(false);
        }
        else
        {
            this->setDropActive(true);
        }
    }
}

void JltScriptConnector::dragLeaveEvent(QDragLeaveEvent *event)
{
    this->setDropActive(false);
}

void JltScriptConnector::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
    emit dragMove(QCursor::pos());
}

void JltScriptConnector::dropEvent(QDropEvent *event)
{
    //是否连接判定
    const QMimeData *data = event->mimeData();
    if(data->data("ItemName") == "JLT" && data->data("ItemType") == "JltScriptConnector")
    {
        //拖拽对象不为空
        if(!event->source())
        {
            this->setDropActive(false);
            event->ignore();
            return;
        }
        auto connector = qobject_cast<JltScriptConnector *>(event->source());
        //转换失败
        if(!connector)
        {
            this->setDropActive(false);
            event->ignore();
            return;
        }
        //拖拽对象和拖放对象不能相同(不能自己连接自己)
        if(connector == this)
        {
            this->setDropActive(false);
            event->ignore();
            return;
        }
        //连接器类型不能相同
        if(connector->getConnectorType() == getConnectorType())
        {
            this->setDropActive(false);
            event->ignore();
            return;
        }
        //拖拽对象和被禁拖拽对象不能相同
        if(connector == mDisableConnector)
        {
            this->setDropActive(false);
            event->ignore();
            return;
        }
        //连接不能循环
        JltScriptConnector *loopConnector = this;
        while (loopConnector)
        {
            if(loopConnector->getBindNode() == connector->getBindNode())
            {
                event->ignore();
                return;
            }
            //next output
            if(loopConnector->getConnectorType() == JltScriptConnector::ConnectorType_Input)
            {
                loopConnector = loopConnector->getBindNode()->getOutputConnector()->getBindConnector();
            }
            //next input
            else
            {
                if(loopConnector->getBindNode()->getInputConnector())
                    loopConnector = loopConnector->getBindNode()->getInputConnector()->getBindConnector();
                else
                    loopConnector = NULL;
            }
        }
        //解除旧的绑定关系
        if(connector->getBindConnector())
        {
            connector->getBindConnector()->setBindConnector(NULL);
            emit connector->getBindConnector()->bindUpdate();
        }
        if(getBindConnector())
        {
            getBindConnector()->setBindConnector(NULL);
            emit getBindConnector()->bindUpdate();
        }
        //相互绑定
        connector->setBindConnector(this);
        emit connector->bindUpdate();
        this->setBindConnector(connector);
        emit bindUpdate();

        //满足以上条件则接收拖放事件
        event->setDropAction(Qt::LinkAction);
        event->accept();
    }
    //拖放状态重置
    this->setDropActive(false);
}

