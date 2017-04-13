#include "ladder.h"

Ladder::Ladder()
{

}

QRectF Ladder::boundingRect() const
{
    return QRectF(0, 0, 25, 25);
}

void Ladder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QImage img(":/pic/ladder.png");
    painter->drawImage(0, 0, img);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
