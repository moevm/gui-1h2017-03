#ifndef EGG_H
#define EGG_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

class Egg: public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Egg();


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // EGG_H
