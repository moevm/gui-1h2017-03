        #include "player.h"

    Player::Player()
    {
       this->setPos(10,200); //base state
       this->lifes = 3;
    }

    QRectF Player::boundingRect() const
    {
        return QRectF(5,5,50,60);
    }

    void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

        if(movement == -1){
            QImage img(":/pic/chicken_left.png");
            painter->drawImage(5, 10, img);
        }

        if(movement == 1){
            QImage img2(":/pic/chicken_right.png");
            painter->drawImage(5, 10, img2);
        }
        if(movement == 0){
            QImage img3(":/pic/chicken_stand.png");
            painter->drawImage(5, 10, img3);
            }
        Q_UNUSED(option);
        Q_UNUSED(widget);
    }


    void Player::movePlayer(int direction){
        movement = 0;
        if(direction==-1)
        {
             this->moveBy(-speed,0);
             movement = -1;
        } else if(direction==1)
        {
             this->moveBy(speed,0);
             movement = 1;
        }

        if(direction==2)
        {
            if(onGround)
            {
                gravity = -4.5;
                onGround = false;
            }
        }


    //left interc check
        if(this->x() < 0)
        {
            this->setX(0);
        }

    //right interc check
        if(this->x() + /*this->rect().width()*/50 + 20 >830)
        {
            this->setX(831 - /*this->rect().width()*/50 - 20);
        }

    //roof check
        if(this->y() < 0)
        {
            this->setY(0);
            gravity = 0;
        }

        if(!onGround)
        {
    //fall speed increase
            gravity += 0.09;

    //ground check
            if(this->y() + gravity >= 316 - /*this->rect().height()*/55 - 10)
            {
                onGround = true;
                gravity = 0;
            }
            this->moveBy(0,gravity);
        }
    }

    void Player::slotTimer(){

        this->movePlayer(0);

        QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                                   << mapToScene(0, 0)
                                                                   << mapToScene(0, 56)
                                                                   << mapToScene(56, 50));
            foreach (QGraphicsItem *item, foundItems) {
                if (item == this) continue;
               if( item->boundingRect().width()==40){
                emit foundEgg(item);
                }
               if( item->boundingRect().width()==25||item->boundingRect().width()==42){
                emit foundTrap(item);
                }
            }
    }
    void foundEgg (QGraphicsItem *item){}
    void foundTrap (QGraphicsItem *item){}

    void Player::decLife(){
        --lifes;
    }
    int Player::getLifeCount(){
        return this->lifes;
    }
    void Player::setLifeCount(int lifes){
        this->lifes = lifes;
    }
