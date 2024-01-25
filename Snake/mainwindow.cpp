#include "mainwindow.h"
#include "ui_mainwindow.h"

class Snake snake;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(Timer_TimeOut_Event_Slot()));
    connect(Timer,SIGNAL(timeout()),this,SLOT(keyPressEvent(QKeyEvent*)));

    snake.x=ui->spinBox->value()*6-6*(ui->spinBox->value()%2);
    snake.y=ui->spinBox_2->value()*6-6*(ui->spinBox_2->value()%2);
    snake.tailX.push_back(snake.x);
    snake.tailY.push_back(snake.y);
    snake.counter=1;

    ui->label_2->setText("Score: " + QString::number(snake.score));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    painter.translate(20, 130);
    pen.setColor(Qt::lightGray);
    pen.setBrush(Qt::SolidPattern);
    painter.setPen(pen);

    for(int i=0; i<ui->spinBox->value(); i++){
        for(int j=0; j<ui->spinBox_2->value(); j++){
            //painter.drawRect(i*12, j*12, 10, 10);
            painter.fillRect(i*12, j*12, 10, 10, QBrush(Qt::gray, Qt::SolidPattern));
        }
    }

    for(int i=0; i<snake.tailX.size(); i++){
        painter.fillRect(snake.tailX[i]+2, snake.tailY[i]+2, 6, 6, QBrush(Qt::green, Qt::SolidPattern));
    }

    for(int i=0; i<snake.tailX.size()-1; i++){
        if(snake.tailX[i+1]-snake.tailX[i]==0){painter.fillRect(snake.tailX[i]+4, snake.tailY[i]+4, 2, snake.tailY[i+1]-snake.tailY[i], QBrush(Qt::green, Qt::SolidPattern));}
        if(snake.tailY[i+1]-snake.tailY[i]==0){painter.fillRect(snake.tailX[i]+4, snake.tailY[i]+4, snake.tailX[i+1]-snake.tailX[i], 2, QBrush(Qt::green, Qt::SolidPattern));}
    }
    if(snake.x-snake.tailX[0]==0){painter.fillRect(snake.x+4, snake.y+4, 2, snake.tailY[0]-snake.y, QBrush(Qt::green, Qt::SolidPattern));}
    if(snake.y-snake.tailY[0]==0){painter.fillRect(snake.x+4, snake.y+4, snake.tailX[0]-snake.x, 2, QBrush(Qt::green, Qt::SolidPattern));}
    // for(int i=0; i<snake.tailX.size()-1; i++){
    //     painter.drawLine(snake.tailX[i], snake.tailY[i], snake.tailX[i+1], snake.tailY[i+1]);
    // }

    painter.fillRect(snake.x, snake.y, 10, 10, QBrush(Qt::green, Qt::SolidPattern));
    painter.fillRect(snake.fruitX+2, snake.fruitY+2, 6, 6, QBrush(Qt::red, Qt::SolidPattern));

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

    snake.counter=0;
    if(e->key()==Qt::Key_Escape){
        Timer->stop();
        ui->pushButton->setDisabled(0);
        ui->spinBox_3->setDisabled(0);
        ui->spinBox->setDisabled(0);
        ui->spinBox_2->setDisabled(0);
    }
    if(e->key()==Qt::Key_W){
        if(snake.dir2!=Snake::bottom) snake.dir=Snake::top;
    }
    if(e->key()==Qt::Key_A){
        if(snake.dir2!=Snake::right) snake.dir=Snake::left;
    }
    if(e->key()==Qt::Key_S){
        if(snake.dir2!=Snake::top) snake.dir=Snake::bottom;
    }
    if(e->key()==Qt::Key_D){
        if(snake.dir2!=Snake::left) snake.dir=Snake::right;
    }
}

void MainWindow::Timer_TimeOut_Event_Slot()
{
    snake.counter=0;
    snake.dir2=snake.dir;
    switch (snake.dir)
    {
    case Snake::top:
        snake.y-=12;
        break;
    case Snake::left:
        snake.x-=12;
        break;
    case Snake::bottom:
        snake.y+=12;
        break;
    case Snake::right:
        snake.x+=12;
        break;
    }
    for(int i=0; i<snake.tailX.size();i++){
        if(snake.x==snake.tailX[i] && snake.y==snake.tailY[i]){
            QMessageBox::information(this,"Кінець", "Ви програли через удар в свій хвіст!!! Your score: "+QString::number(snake.score));
            snake.tailX.resize(0);
            snake.tailY.resize(0);
            snake.x=ui->spinBox->value()*6-6*(ui->spinBox->value()%2);
            snake.y=ui->spinBox_2->value()*6-6*(ui->spinBox_2->value()%2);
            snake.tailX.push_back(snake.x);
            snake.tailY.push_back(snake.y);
            ui->spinBox_2->setDisabled(0);
            ui->spinBox->setDisabled(0);
            ui->pushButton->setDisabled(0);
            ui->spinBox_3->setDisabled(0);
            repaint();
            Timer->stop();

        }
    }
    if(snake.x>ui->spinBox->value()*12-1 || snake.x<0 || snake.y>ui->spinBox_2->value()*12-1 || snake.y<0){
        Timer->stop();
        QString score="Ви програли через удар в стіну!!! Score: ";
        QMessageBox::information(this,"Кінець", score + QString::number(snake.score));
        ui->spinBox_3->setDisabled(0);
        ui->spinBox->setDisabled(0);
        ui->pushButton->setDisabled(0);
        ui->spinBox_2->setDisabled(0);

    }
    if(snake.x==snake.fruitX && snake.y==snake.fruitY){
        int x, y;
        bool t=true;
        while(t){
            t=false;
            x=rand()%(ui->spinBox->value());
            y=rand()%(ui->spinBox_2->value());
            for(int i=0; i<snake.tailX.size(); i++){
                if(x*12==snake.tailX[i] && y*12==snake.tailY[i]) t=true;
                if(x*12==snake.x && y*12==snake.y) t=true;
            }
        }

        snake.fruitX=x*12;
        snake.fruitY=y*12;
        snake.score++;
        snake.tailX.push_back(snake.tailX[snake.tailX.size()-1]);
        snake.tailY.push_back(snake.tailY[snake.tailY.size()-1]);
    }
    ui->label_2->setText("Score: " + QString::number(snake.score));
    repaint();
    for(int i=snake.tailX.size()-1; i>0; i--){
        snake.tailX[i]=snake.tailX[i-1];
        snake.tailY[i]=snake.tailY[i-1];
    }
    snake.tailX[0]=snake.x;
    snake.tailY[0]=snake.y;
}

void MainWindow::on_pushButton_clicked(){

    snake.x=ui->spinBox->value()*6-6*(ui->spinBox->value()%2);
    snake.y=ui->spinBox_2->value()*6-6*(ui->spinBox_2->value()%2);

    int x, y;
    x=rand()%(ui->spinBox->value());
    y=rand()%(ui->spinBox_2->value());
    snake.fruitX=x*12;
    snake.fruitY=y*12;
    qDebug()<<"start";
    Timer->setInterval(600/(ui->spinBox_3->value()));
    Timer->start();
    snake.score=0;
    ui->spinBox_3->setDisabled(1);
    ui->spinBox->setDisabled(1);
    ui->pushButton->setDisabled(1);
    ui->spinBox_2->setDisabled(1);
    ui->label_2->setText("Score: " + QString::number(snake.score));
    snake.tailX.resize(1);
    snake.tailY.resize(1);
    snake.tailX[0]=snake.x;
    snake.tailY[0]=snake.y;
    snake.counter=1;
    qDebug()<<"resize";
    snake.dir=Snake::top;

    if(ui->spinBox->value()*12+10 >= 300) QMainWindow::resize(ui->spinBox->value()*12+40, ui->spinBox_2->value()*12+180);
            else QMainWindow::resize(130, ui->spinBox_2->value()*12+180);
    repaint();
}
