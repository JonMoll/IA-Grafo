#include "dolinearectaobject.h"
#include <QPainter>

DoLineaRectaObject::DoLineaRectaObject(const QPointF &punto1, const QPointF &punto2,
                                       QGraphicsItem *parent){
    mPunto1 = punto1;
    mPunto2 = punto2;
}

QRectF DoLineaRectaObject::boundingRect() const{
    const float x2 = mPunto2.x();
    const float x1 = mPunto1.x();
    const float y2 = mPunto2.y();
    const float y1 = mPunto1.y();

    return QRectF(mPunto1, QSizeF(x2-x1, y2-y1));
}

void DoLineaRectaObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                               QWidget *widget){
    painter->drawLine(mPunto1, mPunto2);
}
