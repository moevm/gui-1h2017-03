#include "enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int baseX, int baseY, int patrolRange, int monsterType)
{
    movement = 1;
    this->baseX = baseX;
    this->baseY = baseY;
    this->patrolRange = patrolRange;
    this->setPos(baseX, baseY);
    if(monsterType==1){
    img = new QImage(":/pic/enemy1left.png");
    img2 = new QImage(":/pic/enemy1right.png");
    }
    else{
    img = new QImage(":/pic/enemy2left.png");
    img2 = new QImage(":/pic/enemy2right.png") ;
    }
}

QRectF Enemy::boundingRect() const
{
return QRectF(2,5,42,42);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

if(movement == -1){
    //QImage img(":/pic/enemy"+monsterType+"left.png");
    painter->drawImage(0, 0, *img);
}
else{
    //QImage img2(":/pic/enemy"+monsterType+"right.png");
    painter->drawImage(0, 0, *img2);
}
Q_UNUSED(option);
Q_UNUSED(widget);
}

void Enemy::moveEnemy(){
if(movement == 1)
{
     this->moveBy(speed,0);
} else
{
     this->moveBy(-speed,0);
}

//left interc check
if(this->x() < baseX - patrolRange)
{
    movement = 1;
    this->setX(baseX - patrolRange);
}
if(this->x() < 70){
    movement = 1;
    this->setX(70);
}
//right interc check
if(this->x() > baseX + patrolRange)
{
    movement = -1;
    this->setX(baseX + patrolRange);
}
if(this->x() + /*this->rect().width()*/50 + 20 >830)
{
    movement = -1;
    this->setX(831 - /*this->rect().width()*/50 - 20);
}
}

void Enemy::slotTimer(){

this->moveEnemy();

}

void Enemy::difficultyTimer(){
    if(this->speed > maxSpeed)this->speed = maxSpeed;
    else this->speed+=0.07;

    this->patrolRange+=20;
}

