#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QLCDNumber>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QDebug>

#include <windows.h>

#include "player.h"
#include "egg.h"
#include "ground.h"
#include "trap.h"
#include "ladder.h"
#include "heart.h"
#include "enemy.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:

    Player* player;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *eggTimer;
    Ui::Widget *ui;

    void setGameProperties(void);
    void gameOver();
    void paintEvent(QPaintEvent *);

    QList<QGraphicsItem *> items;  //list of usable items
    QList<QGraphicsItem *> chickenlifes;  //list of hearts
    double count;   //score counter

    QMediaPlayer *backgroundPlayer;
    QMediaPlaylist *backgroundPlaylist;

private slots:

    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_scoreBackButton_clicked();
    void on_scoreButton_clicked();
    void on_quitButton_clicked();

    void eggDelete(QGraphicsItem *item);
    void createEgg();
    void gameOverMsg();
    void on_continueButton_clicked();
};

#endif // WIDGET_H
