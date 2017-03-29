#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    scene->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setVisible(false);
    ui->stopButton->setVisible(false);
    ui->scoreBackButton->setVisible(false);
    ui->scoreLabel->setVisible(false);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    player = new QGraphicsRectItem();
    player->setBrush(Qt::green);
    player->setRect(10,10,25,25);

    scene->addItem(player);
    player->setPos(10,200);

//fps timer
    timer = new QTimer();
    timer->setInterval(1000 / 100);
    timer->start();

    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    connect(ui->quitButton, SIGNAL(clicked(bool)), qApp, SLOT(quit()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onTimer()
{
    if(!ui->graphicsView->isVisible()) return;
    float speed = 4.5;

    if(GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState(0x41))
    {
         player->moveBy(-speed,0);
    }

    if(GetAsyncKeyState(VK_RIGHT)||GetAsyncKeyState(0x44))
    {
         player->moveBy(speed,0);
    }

    if(GetAsyncKeyState(VK_UP)||GetAsyncKeyState(0x57))
    {
        if(onGround)
        {
            gravity = -10;
            onGround = false;
        }
    }

//left interc check
    if(player->x() < 0)
    {
        player->setX(0);
    }
//right interc check
    if(player->x() + player->rect().width() + 20 > ui->graphicsView->width())
    {
        player->setX(ui->graphicsView->width() - player->rect().width() - 20);
    }
//roof check
    if(player->y() < 0)
    {
        player->setY(0);
        gravity = 0;
    }

    if(!onGround)
    {
//fall speed increase
        gravity += 0.4;

//ground check
        if(player->y() + gravity >= ui->graphicsView->height() - player->rect().height() - 10)
        {
            onGround = true;
            gravity = 0;
        }


        player->moveBy(0,gravity);
    }

}

void Widget::on_startButton_clicked()
{
    ui->graphicsView->setVisible(true);
    ui->startButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->stopButton->setVisible(true);
    ui->scoreButton->setVisible(false);
}

void Widget::on_stopButton_clicked()
{
    ui->graphicsView->setVisible(false);
    ui->startButton->setVisible(true);
    ui->scoreButton->setVisible(true);
    ui->quitButton->setVisible(true);
    ui->stopButton->setVisible(false);

}

void Widget::on_scoreBackButton_clicked()
{
    ui->scoreLabel->setVisible(false);
    ui->startButton->setVisible(true);
    ui->quitButton->setVisible(true);
    ui->scoreButton->setVisible(true);
    ui->scoreBackButton->setVisible(false);
}

void Widget::on_scoreButton_clicked()
{
    ui->graphicsView->setVisible(false);
    ui->startButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->scoreLabel->setVisible(true);
    ui->scoreBackButton->setVisible(true);

}


void Widget::on_quitButton_clicked()
{

}
