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
