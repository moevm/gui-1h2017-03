#include "egg.h"

Egg::Egg()
{

}

QRectF Egg::boundingRect() const
{
    return QRectF(5,5,40,40);
}

void Egg::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QImage img(":/pic/egg.png");
    painter->drawImage(5, 10, img);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
