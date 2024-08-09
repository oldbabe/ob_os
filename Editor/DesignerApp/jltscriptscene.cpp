#include "jltscriptscene.h"
#include <QPainter>

JltScriptScene::JltScriptScene(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    this->mPressed = false;
    this->mDragActive = false;
    this->mAxisScale = 1.0f;
    this->mOriginPointF = QPointF(0,0);
    this->mMousePointF = mOriginPointF;
    this->mGridWidth = 16;
    // this->setAcceptedMouseButtons(Qt::RightButton);
}

void JltScriptScene::setOriginX(qreal x)
{
    this->mOriginPointF.setX(x);
    emit originXChanged();
    this->update();
}

void JltScriptScene::setOriginY(qreal y)
{
    this->mOriginPointF.setY(y);
    emit originYChanged();
    this->update();
}

void JltScriptScene::setAxisScale(qreal value)
{
    this->mAxisScale = value;
    emit axisScaleChanged();
    this->update();
}

void JltScriptScene::setGridWidth(qreal value)
{
    this->mGridWidth = value;
    this->mAxisScale = mGridWidth/16;
    this->update();
    emit gridWidthChanged();
    emit axisScaleChanged();
}

void JltScriptScene::setDragActive(bool value)
{
    this->mDragActive = value;
    emit dragActiveChanged();
}

void JltScriptScene::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->fillRect(0,0,width(),height(),QBrush(QColor(54,54,54)));
    QPen pen;
    pen.setWidthF(0.1f);
    pen.setColor(QColor("aliceblue"));
    //小网格绘制
    painter->setPen(pen);
    this->drawGrid(painter,mGridWidth);
    //大网格绘制
    pen.setWidthF(0.5f);
    pen.setColor(QColor("black"));
    painter->setPen(pen);
    this->drawGrid(painter,mGridWidth*8);
    //十字坐标
    // pen.setWidth(1);
    // pen.setColor(Qt::red);
    // painter->setPen(pen);
    // painter->drawLine(mOriginPointF.x(),0,mOriginPointF.x(),height());
    // painter->drawLine(0,mOriginPointF.y(),width(),mOriginPointF.y());
}

void JltScriptScene::drawGrid(QPainter *painter,qreal interval)
{
    qreal pos = mOriginPointF.x();
    while (pos <= width())
    {
        if(pos >= 0)
        {
            painter->drawLine(pos,0,pos,height());
        }
        pos+=interval;
    }
    pos = mOriginPointF.x();
    while (pos >= 0)
    {
        if(pos >= 0)
        {
            painter->drawLine(pos,0,pos,height());
        }
        pos-=interval;
    }

    pos = mOriginPointF.y();
    while (pos <= height())
    {
        if(pos >= 0)
        {
            painter->drawLine(0,pos,width(),pos);
        }
        pos+=interval;
    }
    pos = mOriginPointF.y();
    while (pos >= 0)
    {
        if(pos >= 0)
        {
            painter->drawLine(0,pos,width(),pos);
        }
        pos-=interval;
    }
}

void JltScriptScene::mouseMove(const QPointF &position)
{
    if(mDragActive)
    {
        this->mMousePointF = position;
        this->mOriginPointF = mSaveOriginPointF + (mMousePointF - mDragPointF);
        emit originXChanged();
        emit originYChanged();
        emit originChanged(mOriginPointF);
        this->update();
    }
    else
    {
        auto error = qSqrt(qPow(position.x()-mPressedPointF.x(),2)+
                           qPow(position.y()-mPressedPointF.y(),2));
        if(error>3)
        {
            this->mDragPointF = position;
            this->mSaveOriginPointF = mOriginPointF;
            this->setDragActive(true);
        }
    }
}

void JltScriptScene::mousePress(const QPointF &position)
{
    this->mPressed = true;
    this->mPressedPointF = position;
}

void JltScriptScene::mouseRelease(const QPointF &position)
{
    if(mPressed&&!mDragActive)
    {
        emit menuOpened(position.x(),position.y());
    }
    this->mPressed = false;
    this->setDragActive(false);
}

void JltScriptScene::wheelMove(const QPointF &position,const QPointF &angleDelta)
{
    if(angleDelta.y() > 0)
    {
        if(mGridWidth>=16)
            return;
        QPointF rateF = (position-mOriginPointF)/mGridWidth;
        this->mGridWidth++;
        emit gridWidthChanged();
        this->mAxisScale = mGridWidth/16;
        emit axisScaleChanged();
        this->mOriginPointF = position - rateF*mGridWidth;
        emit originXChanged();
        emit originYChanged();
        this->update();
    }
    else if(angleDelta.y() < 0)
    {
        if(mGridWidth<=8)
            return;
        QPointF rateF = (position-mOriginPointF)/mGridWidth;
        this->mGridWidth--;
        emit gridWidthChanged();
        this->mAxisScale = mGridWidth/16;
        emit axisScaleChanged();
        this->mOriginPointF = position - rateF*mGridWidth;
        emit originXChanged();
        emit originYChanged();
        this->update();
    }
    emit wheelChanged(mGridWidth);
}

// void JltScriptPath::paint(QPainter *painter)
// {
//     painter->setRenderHint(QPainter::Antialiasing, true);
//     painter->fillRect(boundingRect(),QBrush(QColor(69,69,69)));
//     painter->setPen(Qt::blue);
//     painter->setFont(QFont("Arial", 30));
//     painter->drawText(0,0,width(),height(), Qt::AlignCenter, "JLT");

//     QPainterPath path;
//     path.moveTo(mStartF);
//     path.cubicTo(mStartF.x()+200,mStartF.y(),mEndF.x()-200,mEndF.y(),mEndF.x(),mEndF.y());
//     if(mHovered)
//     {
//         QPen pen;
//         pen.setWidth(5);
//         pen.setColor(Qt::red);
//         painter->setPen(pen);
//         painter->drawPath(path);
//     }
//     else
//     {
//         QPen pen;
//         pen.setWidth(5);
//         pen.setColor(Qt::white);
//         painter->setPen(pen);
//         painter->drawPath(path);
//     }
// }

// void JltScriptPath::hoverLeaveEvent(QHoverEvent *event)
// {
//     this->setHovered(false);
// }

// void JltScriptPath::hoverMoveEvent(QHoverEvent *event)
// {
//     QPainterPath path;
//     path.moveTo(mStartF);
//     path.cubicTo(mStartF.x()+200,mStartF.y(),mEndF.x()-200,mEndF.y(),mEndF.x(),mEndF.y());

//     qreal i = 0,minValue = 0;
//     QPointF saveF ;
//     bool firstFlag = true;
//     while (i<=1)
//     {
//         QPointF roteF = path.pointAtPercent(i);
//         qreal value = qSqrt(qPow(event->position().x()-roteF.x(),2)+qPow(event->position().y()-roteF.y(),2));
//         if(firstFlag)
//         {
//             firstFlag = false;
//             minValue = value;
//             saveF = roteF;
//         }
//         else
//         {
//             if(value < minValue)
//             {
//                 saveF = roteF;
//                 minValue = value;
//             }
//         }
//         i += 0.01f;
//     }
//     qreal len = qSqrt(qPow(event->position().x()-saveF.x(),2)+qPow(event->position().y()-saveF.y(),2));
//     if(len < 5)
//     {
//         this->setHovered(true);
//     }
//     else
//     {
//         this->setHovered(false);
//     }
// }

// void JltScriptPath::setHovered(bool value)
// {
//     if(mHovered != value)
//     {
//         this->mHovered = value;
//         this->update();
//     }
// }
