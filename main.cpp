#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QPalette pal;
   pal.setBrush((&w)->backgroundRole(), QBrush(QPixmap("D:\\backgr.jpg")));

    (&w)->setPalette(pal);
    (&w)->setAutoFillBackground(true);

    w.show();

    return a.exec();
}
