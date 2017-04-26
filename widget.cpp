#include "widget.h"
#include "ui_widget.h"

void Widget::setGameProperties(void){
    this->player = new Player();
    scene->addItem(player);

    Heart *heart;
    for(int i = 0; i<player->getLifeCount();i++){
        heart = new Heart();
        heart->setPos(heart->boundingRect().width()*i, 0);
        scene->addItem(heart);
        chickenlifes.append(heart);
    }
    Ground *base = new Ground();

    Trap *trap = new Trap();
    trap->setPos(650, ui->graphicsView->height() - 2*base->boundingRect().height());
    scene->addItem(trap);

    Enemy *enemy = new Enemy(600, 270, 80, 1);
    scene->addItem(enemy);

    Enemy *enemy2 = new Enemy(300, 270, 120, 2);
    scene->addItem(enemy2);

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
    //egg timer
        eggTimer = new QTimer();
        connect(timer,&QTimer::timeout,enemy,&Enemy::slotTimer);
         connect(timer,&QTimer::timeout,enemy2,&Enemy::slotTimer);
        connect(timer,&QTimer::timeout,player,&Player::slotTimer);          //player movement
        connect(player, &Player::foundEgg, this, &Widget::eggDelete);       //egg picked
        connect(player, &Player::foundTrap, this, &Widget::gameOverMsg);    //chicken catched
        connect(eggTimer, &QTimer::timeout, this, &Widget::createEgg);      //egg creation(test)
}
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(ui->graphicsView->rect());

    ui->graphicsView->setVisible(false);
    ui->stopButton->setVisible(false);
    ui->continueButton->setEnabled(false);
    ui->scoreBackButton->setVisible(false);
    ui->scoreLabel->setVisible(false);
    ui->lcdNumber->setVisible(false);
    this->setFixedSize(912,400);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    backgroundPlayer = new QMediaPlayer(this);
    backgroundPlaylist = new QMediaPlaylist(backgroundPlayer);

    backgroundPlayer->setPlaylist(backgroundPlaylist);
    backgroundPlaylist->addMedia(QUrl("qrc:/sound/Backgrmusic1.mp3"));
    backgroundPlaylist->addMedia(QUrl("qrc:/sound/Backgrmusic2.mp3"));
    backgroundPlaylist->setPlaybackMode(QMediaPlaylist::Random);
    backgroundPlayer->setVolume(30);


    connect(ui->quitButton, SIGNAL(clicked(bool)), qApp, SLOT(quit())); //quit
    count = 0;
}

void Widget::gameOverMsg(){
    player->decLife();
    scene->removeItem(chickenlifes.takeLast());

    if(player->getLifeCount()<1)gameOver();
    else{
        QMediaPlayer * soundplayer = new QMediaPlayer(this);
        QMediaPlaylist * playlist = new QMediaPlaylist(soundplayer);

        soundplayer->setPlaylist(playlist);

        int num = rand()%4+1;   //fail sound randomize
        int radix = 10;
        char buff[3];
        QString fileName = "qrc:/sound/Fail";
        fileName.append(itoa(num, buff,radix));
        fileName.append(".mp3");

        playlist->addMedia(QUrl(fileName));
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        soundplayer->setVolume(80);
        soundplayer->play();
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->setPos(10, 250);
    }
}

void Widget::eggDelete(QGraphicsItem *item)
{
    foreach (QGraphicsItem *curr, items) {
        if(curr == item){
            QMediaPlayer * player = new QMediaPlayer(this);
            QMediaPlaylist * playlist = new QMediaPlaylist(player);

            player->setPlaylist(playlist);
            playlist->addMedia(QUrl("qrc:/sound/Hit.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            player->setVolume(80);
            player->play();

            scene->removeItem(curr);
            items.removeOne(item);
            ui->lcdNumber->display(ui->lcdNumber->value()+1);
            //delete sound player and playlist(will be later in Widget destructor)
        }
    }
}

 void Widget::createEgg(){
    Egg *temp = new Egg();
    scene->addItem(temp);
    temp->setPos(qrand()%500, qrand()%90 + 180);
    items.append(temp);
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
    backgroundPlayer->play();

    setGameProperties();

    timer->start();
    eggTimer->start(1000);
    ui->graphicsView->setVisible(true);
    ui->startButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->continueButton->setEnabled(true);
    ui->quitButton->setVisible(false);
    ui->stopButton->setVisible(true);
    ui->scoreButton->setVisible(false);
    ui->lcdNumber->setVisible(true);
}

void Widget::on_stopButton_clicked()
{
    backgroundPlayer->pause();
    timer->stop();
    eggTimer->stop();
    ui->graphicsView->setVisible(false);
    ui->startButton->setVisible(true);
    ui->startButton->setEnabled(false);
    ui->continueButton->setVisible(true);
    ui->scoreButton->setVisible(true);
    ui->quitButton->setVisible(true);
    ui->stopButton->setVisible(false);
    ui->lcdNumber->setVisible(false);

}

void Widget::on_scoreBackButton_clicked()
{
    ui->scoreLabel->setVisible(false);
    ui->startButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->quitButton->setVisible(true);
    ui->scoreButton->setVisible(true);
    ui->scoreBackButton->setVisible(false);
}

void Widget::on_scoreButton_clicked()
{
    ui->graphicsView->setVisible(false);
    ui->startButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->scoreLabel->setVisible(true);
    ui->scoreBackButton->setVisible(true);

}

void Widget::on_quitButton_clicked()
{

}

void Widget::gameOver(){
    backgroundPlayer->stop();
    QMediaPlayer * soundplayer = new QMediaPlayer(this);
    QMediaPlaylist * playlist = new QMediaPlaylist(soundplayer);

    soundplayer->setPlaylist(playlist);

    int num = rand()%2+1;   //fail sound randomize
    int radix = 10;
    char buff[3];
    QString fileName = "qrc:/sound/GameOver";
    fileName.append(itoa(num, buff,radix));
    fileName.append(".mp3");

    playlist->addMedia(QUrl(fileName));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    soundplayer->setVolume(80);
    soundplayer->play();

    timer->stop();
    eggTimer->stop();
    QString endMsg = "Game over. \n Score: " + QString::number(ui->lcdNumber->value());
    QMessageBox::about(this, "Game Over", endMsg);

    disconnect(timer,&QTimer::timeout,player,&Player::slotTimer);          //player movement
    disconnect(player, &Player::foundEgg, this, &Widget::eggDelete);       //egg picked
    disconnect(player, &Player::foundTrap, this, &Widget::gameOverMsg);    //chicken catched
    disconnect(eggTimer, &QTimer::timeout, this, &Widget::createEgg);      //egg creation(test)

    QList<QGraphicsItem*> deleteList = scene->items();
    while(!deleteList.empty()){
        delete deleteList.first();
        deleteList.removeFirst();
    }

    ui->graphicsView->setVisible(false);
    ui->startButton->setVisible(true);
    ui->startButton->setEnabled(true);
    ui->scoreButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->continueButton->setEnabled(false);
    ui->quitButton->setVisible(true);
    ui->stopButton->setVisible(false);
    ui->lcdNumber->setVisible(false);
    ui->lcdNumber->display(0);
}

void Widget::on_continueButton_clicked()
{
    timer->start();
    eggTimer->start(1000);
    ui->graphicsView->setVisible(true);
    ui->continueButton->setVisible(false);
    ui->startButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->stopButton->setVisible(true);
    ui->scoreButton->setVisible(false);
    ui->lcdNumber->setVisible(true);
}
