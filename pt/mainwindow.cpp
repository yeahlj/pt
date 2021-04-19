#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qtimer.h>
#include<QTime>
#include<QFileDialog>
#include<QMouseEvent>
#include<QMessageBox>
#define PHOTO_X 15
#define PHOTO_Y 100
#define SMALL_W 60
#define SMALL_H 65
#define a 4



int sumSteps=0;
int tim=0;
int score=0;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(onTimerOut()));
    int sumSteps=0;
    int tim=0;
    ui->label_3->setText((QString::number(sumSteps)));
    ui->time_label->setText((QString::number(tim)));
    ui->score_label->setText((QString::number(score)));


    pSourceImage=NULL;
    for (int i=0;i<a;i++) {
        for (int j=0;j<a;j++) {
            pLbImage[i*a+j]=new QLabel(this);
            pLbImage[i*a+j]->setGeometry(PHOTO_X,PHOTO_Y,SMALL_W,SMALL_H);
            pLbImage[i*a+j]->move(PHOTO_X+SMALL_W*i,PHOTO_Y+SMALL_H*j);
            pLbImage[i*a+j]->setFrameShape(QFrame::Box);
        }

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!(QMessageBox::information(this,tr("quit a game"),tr("Are you sure?"),
                                  tr("Yes"),tr("No"))))
    {
        close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(pSourceImage==NULL)return;

    QPixmap tep(":/DMPhotos02.jpg");

    pLbImage[a*a-1]->setPixmap(tep);

    Random();

}

void MainWindow::on_btn_clicked()
{
    strFileName=
            QFileDialog::getOpenFileName(this,
                                         "choose picture",
                                         "/home/xp/image",
                                         "Images(*.png *.jpg)");
    if(strFileName==NULL) return;
    if(NULL!=pSourceImage)
    {
        delete pSourceImage;
        pSourceImage=NULL;
    }
    pSourceImage=new QImage(strFileName);
    if(pSourceImage==NULL)return;
    QImage tep=pSourceImage->scaled(ui->label_6->width(),
                                    ui->label_6->height());
    ui->label_6->setPixmap(QPixmap::fromImage(tep));
    cutImage();
    Random();
    moveImage();
    if(timer->isActive())
    {
        timer->stop();
    }
    timer->start(1000);
}

void MainWindow::cutImage()
{
    QImage temp=pSourceImage->scaled(SMALL_W*a,SMALL_H*a);
    for (int i=0;i<a;i++) {
        for (int j=0;j<a;j++) {
            pImage[i][j]=temp.copy(i*SMALL_W,j*SMALL_H,
                                   SMALL_W,
                                   SMALL_H);
            pLbImage[i*a+j]->setPixmap(QPixmap::fromImage(pImage[i][j]));
            pCompare[i][j]=i*a+j;
        }
    }
    QPixmap tep(":/blank.jpg");
    pLbImage[a*a-1]->setPixmap(tep);
}

void MainWindow::Random()
{
    sumSteps=0;
    ui->label_3->setText(QString::number(sumSteps));


    tim=0;
    ui->time_label->setText((QString::number(tim)));
    ui->score_label->setText((QString::number(score)));
    int x=-1;
    int y=-1;
    for (int w=0;w<a;w++) {
        for (int j=0;j<a;j++) {
            if(pCompare[w][j]==a*a-1){
                x=w;
                y=j;
                break;
            }
        }
        if(x!=-1)
            break;
    }
    if(x==-1||y==-1)
        return;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i=0;i<100;i++) {
        int ret=qrand()%4;
        switch(ret)
           {
        case 0:
            if(x<a-1)
            {
                pCompare[x][y]=pCompare[x+1][y];
                pCompare[x+1][y]=a*a-1;
                x++;
            }
            break;
        case 1:
            if(x>0)
            {
                pCompare[x][y]=pCompare[x-1][y];
                pCompare[x-1][y]=a*a-1;
                x--;
            }
            break;
        case 2:
            if(y<a-1)
            {
                pCompare[x][y]=pCompare[x][y+1];
                pCompare[x][y+1]=a*a-1;
                y++;
            }
            break;
        case 3:
            if(y>0)
            {
                pCompare[x][y]=pCompare[x][y-1];
                pCompare[x][y-1]=a*a-1;
                y--;
            }
            break;
        default:
            break;
        }
    }

}

void MainWindow::moveImage()
{
    for (int i=0;i<a;i++) {
        for (int j=0;j<a;j++) {
            int index=pCompare[i][j];
            pLbImage[index]->move(PHOTO_X+i*SMALL_W,
                                  PHOTO_Y+j*SMALL_H);
        }

    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
int num=0;
if(pSourceImage==NULL)return;
if(taskFinish())return;
if(event->button()==Qt::LeftButton||event->button()==Qt::RightButton)
{
    QPoint pressPoint=event->pos();
    if(pressPoint.x()>PHOTO_X&&pressPoint.y()>PHOTO_Y
            &&pressPoint.x()<PHOTO_X+SMALL_W*a&&pressPoint.y()<PHOTO_Y+SMALL_H*a)
    {
        int x=(pressPoint.x()-PHOTO_X)/SMALL_W;
        int y=(pressPoint.y()-PHOTO_Y)/SMALL_H;
        if(x>0&&pCompare[x-1][y]==a*a-1)
        {
            pCompare[x-1][y]=pCompare[x][y];
            pCompare[x][y]=a*a-1;
            num++;
        }
        else if(x<a-1&&pCompare[x+1][y]==a*a-1)
        {
            pCompare[x+1][y]=pCompare[x][y];
            pCompare[x][y]=a*a-1;
            num++;
        }else if(y>0&&pCompare[x][y-1]==a*a-1)
        {
            pCompare[x][y-1]=pCompare[x][y];
            pCompare[x][y]=a*a-1;
            num++;
        }else if(y<a-1&&pCompare[x][y+1]==a*a-1)
        {
            pCompare[x][y+1]=pCompare[x][y];
            pCompare[x][y]=a*a-1;
            num++;
        }
    }
}
    sumSteps+=num;
    ui->label_3->setText((QString::number(sumSteps)));
    moveImage();
    if(taskFinish()){
        timer->stop();
        sumPoint();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

}

void MainWindow::onTimerOut()
{
tim++;
ui->time_label->setText((QString::number(tim)));
}

int MainWindow::taskFinish()
{
    int y=1;
    for (int i=0;i<a;i++) {
        for (int j=0;j<a;j++) {
            if(pCompare[i][j]!=i*a+j)
            {
                y=0;
                break;
            }
        }
        if(!y)break;
    }
    return y;
}

void MainWindow::sumPoint()
{
    score=1000-tim*2-sumSteps*2;
    char buf[64]={};
    sprintf(buf,"Successful!Your score is:%d",score);
    ui->score_label->setText((QString::number(score)));
    pLbImage[a*a-1]->setPixmap(QPixmap::fromImage(pImage[a-1][a-1]));
    QMessageBox::about(this,"jiasaw",buf);
}
