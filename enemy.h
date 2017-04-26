#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

class Enemy: public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Enemy();
    Enemy(int baseX, int baseY, int patrolRange, int monsterType);
    void moveEnemy();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotTimer();

private:
    int baseX, baseY, patrolRange;
    QImage *img, *img2;

    float speed = 0.8;
    volatile short movement = 0; //-1 - left move, 0 - stand, 1 - right move
};

#endif // ENEMY_H
