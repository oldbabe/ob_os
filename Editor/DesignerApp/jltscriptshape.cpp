#include "jltscriptshape.h"
#include "jltscriptnode.h"
#include <QPainter>
#include <QPainterPath>

JltScriptShape::JltScriptShape(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    this->mActiveConnector = NULL;
    this->mNodes.clear();
    this->mScriptScene = NULL;
}

JltScriptShape::~JltScriptShape()
{
}

void JltScriptShape::setScriptScene(JltScriptScene* scene)
{
    if(mScriptScene != scene)
    {
        this->mScriptScene = scene;
        emit scriptSceneChanged();
    }
}

void JltScriptShape::setActiveConnector(JltScriptConnector *connector)
{
    this->mActiveConnector = connector;
}

void JltScriptShape::updateActiveConnectorEndF(const QPointF &endF)
{
    this->mActiveEndF = endF;
    this->update();
}

void JltScriptShape::clearActiveConnector()
{
    this->mActiveConnector = NULL;
    this->mActiveEndF = QPointF(0,0);
    this->update();
}

void JltScriptShape::appendNode(JltScriptNode *node)
{
    this->mNodes.append(node);
    this->update();
    connect(node,&QQuickItem::xChanged,this,[=]{
        this->update();
    });
    connect(node,&QQuickItem::yChanged,this,[=]{
        this->update();
    });
    connect(node,&QQuickItem::destroyed,this,[=]{
        this->mNodes.removeOne(node);
        this->update();
    });
}

void JltScriptShape::clearNode()
{
    qDeleteAll(mNodes);
    mNodes.clear();
    this->update();
}

void JltScriptShape::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBackground(QColor("transparent"));

    // 绘制活跃的手动连接线
    auto list = mNodes;
    while(!list.isEmpty())
    {
        auto node = list.first();
        while(node)
        {
            list.removeOne(node);
            auto connector = node->getOutputConnector();
            auto bindConnector = node->getOutputConnector()->getBindConnector();
            if(bindConnector)
            {
                //计算起始点
                qreal scale_t = connector->getBindNode()->scale();
                QPointF centerF = QPointF(-(connector->width())/2,-connector->height()/2);
                QPointF itemPosF = -connector->mapFromItem(connector->getBindNode(),centerF)*scale_t;
                QPointF startF = QPointF(connector->getBindNode()->x()+itemPosF.x(),connector->getBindNode()->y()+itemPosF.y());
                //计算终止点
                scale_t = bindConnector->getBindNode()->scale();
                centerF = QPointF(-(bindConnector->width())/2,-bindConnector->height()/2);
                itemPosF = -bindConnector->mapFromItem(bindConnector->getBindNode(),centerF)*scale_t;
                QPointF endF = QPointF(bindConnector->getBindNode()->x()+itemPosF.x(),bindConnector->getBindNode()->y()+itemPosF.y());
                //绘制
                this->drawCubic(painter,startF,endF,5*scale_t,connector->getDragPenStyle());
                //loop next
                node = bindConnector->getBindNode();
            }
            else
            {
                node = NULL;
            }
        }
    }

    if(mActiveConnector && mActiveConnector->getDragActive())
    {
        qreal scale_t = mActiveConnector->getBindNode()->scale();
        QPointF startF = -mActiveConnector->mapFromItem(this,QPointF(-mActiveConnector->width()/2,-mActiveConnector->height()/2))*scale_t;
        if(mActiveConnector->getConnectorType() != JltScriptConnector::ConnectorType_Input)
            this->drawCubic(painter,startF,mActiveEndF,5*scale_t,Qt::DashDotDotLine);
        else
            this->drawCubic(painter,mActiveEndF,startF,5*scale_t,Qt::DashDotDotLine);
    }
}

void JltScriptShape::drawCubic(QPainter *painter,const QPointF &startF,const QPointF &endF,qreal scaleF,int penType)
{
    qreal pWidth = qAbs(startF.x()-endF.x());
    qreal pHeight = qAbs(startF.y()-endF.y());
    qreal ctrlWidth = (pWidth/2)>80?80:(pWidth/2);
    qreal ctrlHeight = (pHeight/2)>80?80:(pHeight/2);
    qreal ctrlLength = (ctrlWidth+ctrlHeight)>80?80:(ctrlWidth+ctrlHeight);

    QPen pen;
    pen.setStyle((Qt::PenStyle)penType);
    pen.setWidth(scaleF);
    if(penType == 2)
        pen.setColor(QColor("lawngreen"));
    else
        pen.setColor(QColor(168,168,168));
    painter->setPen(pen);
    QPainterPath path;
    path.moveTo(startF);
    path.cubicTo(startF.x()+ctrlLength,startF.y(),endF.x()-ctrlLength,endF.y(),endF.x(),endF.y());
    painter->drawPath(path);
}
