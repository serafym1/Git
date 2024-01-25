#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
//#include <iostream>
//#include <QTimerEvent>
//#include <QtGui/QWindow>
//#include <QtGui/QPainter>
//#include <QtGui/QResizeEvent>
//#include <QtGui/QExposeEvent>
//#include <QtGui/QBackingStore>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Key();

private:
    Ui::MainWindow *ui;
    QTimer *Timer;
     int n=1;

protected slots:


private slots:
 void on_pushButton_clicked();
 void paintEvent(QPaintEvent *event);
 void keyPressEvent(QKeyEvent *e) override;
 void Timer_TimeOut_Event_Slot();

 //void Logic();
};

class Snake{
public:
    enum eDirection{top, right, left, bottom};
    eDirection dir, dir2;
    int speed;
    int velocity;
    int score;
    int x, y;
    int fruitX, fruitY;
    QVector<int> tailX;
    QVector<int> tailY;
    int counter;
};

#endif // MAINWINDOW_H
