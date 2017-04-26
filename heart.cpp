#include "heart.h"

Heart::Heart()
{

}

QRectF Heart::boundingRect() const
{
    return QRectF(5,5,35,46);
}

void Heart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QImage img(":/pic/heart.png");
    painter->drawImage(5, 5, img);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
