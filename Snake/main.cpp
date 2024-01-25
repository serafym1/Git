#include "mainwindow.h"
#include <QApplication>

void paint();

enum Direction{TOP,RIGHT,BUTTOM,LEFT};
Direction dir;

void logic(int x, int y, Direction dir);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
