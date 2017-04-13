#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QLCDNumber>

#include <windows.h>

#include "player.h"
#include "egg.h"
#include "ground.h"
#include "trap.h"
#include "ladder.h"

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
    Ui::Widget *ui;

    void paintEvent(QPaintEvent *);

    QList<QGraphicsItem *> items;  //list of usable items
    double count;   //score counter

private slots:

    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_scoreBackButton_clicked();
    void on_scoreButton_clicked();
    void on_quitButton_clicked();

    void eggDelete(QGraphicsItem *item);
};

#endif // WIDGET_H
