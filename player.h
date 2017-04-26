#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

#include <QDebug>

#include "windows.h"

class Player: public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Player();
    void movePlayer();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void decLife();
    int getLifeCount();
    void setLifeCount(int lifes);

public slots:
    void slotTimer();

signals:
     void foundEgg (QGraphicsItem *item);
     void foundTrap (QGraphicsItem *item);

private:
    int lifes;
    float gravity = 1.0;
    float speed = 2.0;
    volatile short movement = 0; //-1 - left move, 0 - stand, 1 - right move
    bool onGround = false;
};

#endif // PLAYER_H
