#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(ui->graphicsView->rect());

    ui->graphicsView->setVisible(false);
    ui->stopButton->setVisible(false);
    ui->scoreBackButton->setVisible(false);
    ui->scoreLabel->setVisible(false);
    ui->lcdNumber->setVisible(false);
    this->setFixedSize(912,400);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    player = new Player();
    scene->addItem(player);

    Egg *egg = new Egg();
    egg->setPos(150,270);

    scene->addItem(egg);
    items.append(egg);
    egg = new Egg();
    egg->setPos(250,200);

    scene->addItem(egg);
    items.append(egg);
    egg = new Egg();
    egg->setPos(350,270);

    scene->addItem(egg);
    items.append(egg);

    Ground *base = new Ground();

    Trap *trap = new Trap();
    trap->setPos(430, ui->graphicsView->height() - 2*base->boundingRect().height());
    scene->addItem(trap);

    Ladder *ladder = new Ladder();
    ladder->setPos(500, ui->graphicsView->height() - 2*base->boundingRect().height());
    scene->addItem(ladder);
    ladder = new Ladder();
    ladder->setPos(500, ui->graphicsView->height() - 3*base->boundingRect().height());
    scene->addItem(ladder);

    for(int i=0; i<(ui->graphicsView->width()/base->boundingRect().width()); i++){
        base = new Ground();
        base->setPos(i*base->boundingRect().width(), ui->graphicsView->height()-base->boundingRect().height());
        scene->addItem(base);
    }

//fps timer
    timer = new QTimer();
    timer->setInterval(1000 / 100);

    connect(timer,&QTimer::timeout,player,&Player::slotTimer);
    connect(ui->quitButton, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
    connect(player, &Player::signalItemCheck, this, &Widget::eggDelete);

    count = 0;
}
void Widget::eggDelete(QGraphicsItem *item)
{
    foreach (QGraphicsItem *curr, items) {
        if(curr == item){
            scene->removeItem(curr);
            items.removeOne(item);
            delete curr;
            ui->lcdNumber->display(ui->lcdNumber->value()+1);
        }
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }

void Widget::on_startButton_clicked()
{
    timer->start();
    ui->graphicsView->setVisible(true);
    ui->startButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->stopButton->setVisible(true);
    ui->scoreButton->setVisible(false);
    ui->lcdNumber->setVisible(true);
}

void Widget::on_stopButton_clicked()
{
    timer->stop();
    ui->graphicsView->setVisible(false);
    ui->startButton->setVisible(true);
    ui->scoreButton->setVisible(true);
    ui->quitButton->setVisible(true);
    ui->stopButton->setVisible(false);
    ui->lcdNumber->setVisible(false);

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
