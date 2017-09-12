#ifndef DOLINEARECTAOBJECT_H
#define DOLINEARECTAOBJECT_H


#include <QGraphicsObject>

class DoLineaRectaObject : public QGraphicsObject{
    private:
        QPointF mPunto1;
        QPointF mPunto2;

    protected:
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

    public:
        DoLineaRectaObject(const QPointF &punto1, const QPointF &punto2,
                           QGraphicsItem *parent = nullptr);
};

#endif // DOLINEARECTAOBJECT_H
