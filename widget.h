#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <windows.h>
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

    QGraphicsRectItem* player;
    QGraphicsScene *scene;
    QTimer *timer;

    float gravity = 1.0;
    bool onGround = false;

    Ui::Widget *ui;

private slots:

    void onTimer();

    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_scoreBackButton_clicked();
    void on_scoreButton_clicked();
    void on_quitButton_clicked();
};

#endif // WIDGET_H
