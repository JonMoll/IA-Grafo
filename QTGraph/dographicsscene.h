#ifndef DOGRAPHICSSCENE_H
#define DOGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "CGraph.h"

class DoGraphicsScene : public QGraphicsScene{
    private:
        QPointF mPunto1;
        QPointF mPunto2;

    public:
        DoGraphicsScene(QObject *parent = nullptr, CGraph *my_graph = nullptr, int algoritmo = 0, int nodo_a = 0, int nodo_b = 0);
};

#endif // DOGRAPHICSSCENE_H
