#include "trap.h"

Trap::Trap()
{

}

QRectF Trap::boundingRect() const
{
    return QRectF(0, 0, 25, 25);
}

void Trap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QImage img(":/pic/trap.png");
    painter->drawImage(0, 0, img);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Trap::gameOverTimer(){

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                               << mapToScene(5, 5)
                                                               << mapToScene(5, 25)
                                                               << mapToScene(25, 25));
        foreach (QGraphicsItem *item, foundItems) {
            if (item == this) continue;
            emit gotOver();
        }
}

void gotOver(){

}
