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
    int trapAmount = 0;
    Trap *trap = new Trap();
    for(int i = 0;i < trapAmount; i++){
        trap = new Trap();
        trap->setPos(100+qrand()%700, ui->graphicsView->height() - 2*base->boundingRect().height());
        scene->addItem(trap);
 }

    Enemy *enemy = new Enemy(300+qrand()%450, 270, 60, qrand()%2);
    scene->addItem(enemy);
    items.append(enemy);

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
    //enemy spawn
        enemySpawnTimer = new QTimer();

        connect(timer,&QTimer::timeout,enemy,&Enemy::slotTimer);
        connect(eggTimer, &QTimer::timeout, enemy, &Enemy::difficultyTimer);
        connect(timer,&QTimer::timeout,player,&Player::slotTimer);          //player movement
        connect(player, &Player::foundEgg, this, &Widget::eggDelete);       //egg picked
        connect(player, &Player::foundTrap, this, &Widget::gameOverMsg);    //chicken catched
        connect(eggTimer, &QTimer::timeout, this, &Widget::createEgg);      //egg creation
        connect(enemySpawnTimer, &QTimer::timeout, this, &Widget::spawnEnemy);      //egg creation
}

void Widget::keyPressEvent(QKeyEvent *event){
     if(!ui->graphicsView->isVisible())return;
    switch(event->key()){
    case Qt::Key_Up:
    player->movePlayer(2);
    break;
    case Qt::Key_W:
    player->movePlayer(2);
    break;

    case Qt::Key_Left:
    player->movePlayer(-1);
    break;
    case Qt::Key_A:
    player->movePlayer(-1);
    break;

    case Qt::Key_Right:
    player->movePlayer(1);
    break;
    case Qt::Key_D:
    player->movePlayer(1);
    break;
    }
}
void Widget::keyReleaseEvent(QKeyEvent *event){
    if(!ui->graphicsView->isVisible())return;
    switch(event->key()){
    case Qt::Key_Up:
    player->movePlayer(2);
    break;
    case Qt::Key_W:
    player->movePlayer(2);
    break;

    case Qt::Key_Left:
    player->movePlayer(-1);
    break;
    case Qt::Key_A:
    player->movePlayer(-1);
    break;

    case Qt::Key_Right:
    player->movePlayer(1);
    break;
    case Qt::Key_D:
    player->movePlayer(1);
    break;
    }
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
    ui->gameOverWidget->setVisible(false);
    ui->gameModeWidget->setVisible(false);
    ui->scoreTable->setVisible(false);
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

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath()+ "/database/score.db3");
    db.open();
    connect(ui->quitButton, SIGNAL(clicked(bool)), qApp, SLOT(quit())); //quit
    count = 0;
}

void Widget::gameOverMsg(QGraphicsItem *item){
    player->decLife();
    scene->removeItem(chickenlifes.takeLast());

    if(player->getLifeCount()<1) gameOver();
    else{
        foreach (QGraphicsItem *curr, items) {
            if(curr == item){
                scene->removeItem(curr);
               // items.removeOne(item);
            }
        }
        QMediaPlayer * soundplayer = new QMediaPlayer(this);
        QMediaPlaylist * playlist = new QMediaPlaylist(soundplayer);

        soundplayer->setPlaylist(playlist);

        //int num = rand()%4+1;   //fail sound randomize
       // int radix = 10;
       // char buff[3];
        QString fileName = "qrc:/sound/Fail3";
       // fileName.append(itoa(num, buff,radix));
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
    temp->setPos(qrand()%800, qrand()%140 + 130);
    items.append(temp);
 }

 void Widget::spawnEnemy(){
     Enemy *enemy = new Enemy(300+qrand()%450, 270, 60, qrand()%2);
     scene->addItem(enemy);
     items.append(enemy);
     connect(timer,&QTimer::timeout,enemy,&Enemy::slotTimer);
     connect(eggTimer, &QTimer::timeout, enemy, &Enemy::difficultyTimer);
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
    eggTimer->start(1500);
    enemySpawnTimer->start(10000);

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
    enemySpawnTimer->stop();
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
    ui->scoreButton->setEnabled(true);
    ui->scoreTable->setVisible(false);
}

void Widget::on_scoreButton_clicked()
{
    ui->graphicsView->setVisible(false);
    ui->startButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->quitButton->setVisible(false);
    ui->scoreLabel->setVisible(true);
    ui->scoreBackButton->setVisible(true);
    ui->scoreButton->setEnabled(false);
    ui->scoreTable->setVisible(true);

    QSqlQuery query;
    query.exec("SELECT Name, Score FROM ScoreTable ORDER BY Score DESC");

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    horizontalHeader.append("Name");
    horizontalHeader.append("Score");
    model->setHorizontalHeaderLabels(horizontalHeader);
    int i = 0;

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->sort(1);
    ui->scoreTable->setModel( proxyModel );

    while (query.next()){
        item = new QStandardItem();
        item->setData(QVariant(query.value(0).toString()),Qt::DisplayRole);
        item->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 0, item);
        item = new QStandardItem();
        item->setData(QVariant(query.value(1).toInt()),Qt::DisplayRole);
        item->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 1, item);
        i++;
    }

    ui->scoreTable->setSortingEnabled(true);
    ui->scoreTable->sortByColumn(1,Qt::DescendingOrder);


    ui->scoreTable->horizontalHeader()->setDefaultSectionSize(ui->scoreTable->width()/2-1);
    ui->scoreTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->scoreTable->horizontalHeader()->setSectionsClickable(false);

    ui->scoreTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->scoreTable->verticalHeader()->setSectionsClickable(false);
    ui->scoreTable->verticalHeader()->setVisible(false);

    ui->scoreTable->setShowGrid(false);
    ui->scoreTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->scoreTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->scoreTable->setFocusPolicy(Qt::NoFocus);
    ui->scoreTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Widget::on_quitButton_clicked()
{

}

void Widget::gameOver(){
    backgroundPlayer->stop();
    QMediaPlayer * soundplayer = new QMediaPlayer(this);
    QMediaPlaylist * playlist = new QMediaPlaylist(soundplayer);

    soundplayer->setPlaylist(playlist);

    ui->gameOverWidget->setVisible(true);
    QApplication::processEvents();
    ui->overScoreLabel->setText("Your score is: " + QString::number(ui->lcdNumber->value()));

  //  int num = rand()%2+1;   // sound randomize
   // int radix = 10;
   // char buff[3];
    QString fileName = "qrc:/sound/GameOver1";
   // fileName.append(itoa(num, buff,radix));
    fileName.append(".mp3");

    playlist->addMedia(QUrl(fileName));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    soundplayer->setVolume(80);
    soundplayer->play();

    timer->stop();
    eggTimer->stop();

    disconnect(timer,&QTimer::timeout,player,&Player::slotTimer);          //player movement
    disconnect(player, &Player::foundEgg, this, &Widget::eggDelete);       //egg picked
    disconnect(player, &Player::foundTrap, this, &Widget::gameOverMsg);    //chicken catched
    disconnect(eggTimer, &QTimer::timeout, this, &Widget::createEgg);      //egg creation(test)

    QList<QGraphicsItem*> deleteList = scene->items();
    while(!deleteList.empty()){
        delete deleteList.first();
        deleteList.removeFirst();
    }

    ui->stopButton->setVisible(false);
    ui->graphicsView->setVisible(false);
}

void Widget::on_continueButton_clicked()
{
    backgroundPlayer->play();
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

void Widget::on_inputName_clicked()
{

    QSqlQuery query;
    query.prepare("INSERT INTO ScoreTable (Name, Score) "
          "VALUES (?, ?)");
    query.addBindValue(ui->nameField->text()==""?"no name":ui->nameField->text());
    query.addBindValue(ui->lcdNumber->value()==0?0:ui->lcdNumber->value());
    query.exec();


    ui->nameField->setText("");
    ui->lcdNumber->display(0);
    ui->gameOverWidget->setVisible(false);
    ui->startButton->setVisible(true);
    ui->startButton->setEnabled(true);
    ui->scoreButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->continueButton->setEnabled(false);
    ui->quitButton->setVisible(true);
    ui->lcdNumber->setVisible(false);
}

void Widget::on_nameField_returnPressed()
{
    on_inputName_clicked();
}

void Widget::on_runnerModeButton_released()
{

}
