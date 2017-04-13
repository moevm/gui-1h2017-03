#include "ground.h"

Ground::Ground()
{

}

QRectF Ground::boundingRect() const
{
    return QRectF(0, 0, 25, 25);
}

void Ground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QImage img(":/pic/ground.png");
    painter->drawImage(0, 0, img);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
