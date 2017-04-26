#ifndef TRAP_H
#define TRAP_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

class Trap: public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Trap();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif
