#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lrc.h"
#include<QPushButton>
#include<QLabel>
#include<QDebug>
#include<QString>
#include<QDir>
#include<QStringList>
#include<QListWidget>
#include<QSlider>
#include<QLineEdit>
#include<QPixmap>
#include<QSlider>
#include<QTimer>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>
int pause_flag = 0;
int list_flag = 0;
int sound_flag = 0;
int song_flag = 0;
int bg_flag = 0;
char **sName;
char **lName;
int tt;

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //background
    setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setBrush(backgroundRole(), QPixmap("./image/bg0.png"));
    setPalette(pal);

    //musiclist
    //QListWidget *listWidget=new QListWidget(this);
    ui->listWidget->hide();
    ui->listWidget->setGeometry(724,40,300,350);
    ui->listWidget->setStyleSheet("QListWidget{color:rgb(173,175,178); background:rgb(25,27,31);border:0px solid gray;}"
                                  "QListWidget::Item{height:30px;border:0px solid gray;padding-left:15;}"
                                  "QListWidget::Item:hover{color:rgb(255,255,255);background:transparent;border:0px solid gray;}"
                                  "QListWidget::Item:selected:active{background:#00FFFFFF;color:#FFFFFF;border-width:0;}");

    //function button
    ui->btn_last->setStyleSheet("QPushButton{border-image: url(./image/back1.png)}");
    ui->btn_next->setStyleSheet("QPushButton{border-image: url(./image/front1.png)}");
    ui->btn_back->setStyleSheet("QPushButton{border-image: url(./image/back.png)}");
    ui->btn_front->setStyleSheet("QPushButton{border-image: url(./image/front.png)}");
    ui->btn_pause->setStyleSheet("QPushButton{border-image: url(./image/pause1.png)}");
    ui->btn_musiclist->setStyleSheet("QPushButton{border-image: url(./image/ico/list.png)}");
    ui->btn_soundswitch->setStyleSheet("QPushButton{border-image: url(./image/ico/soundon.png)}");
    ui->btn_lrc->setStyleSheet("QPushButton{border-image: url(./image/ico/lrc.png)}");
    
    //slider
    slider = new QSlider(Qt::Horizontal,this);
    slider->setGeometry(112,460,800,30);
    slider->setRange(0,100);
    slider->setPageStep(10);

    slider_volume = new QSlider(Qt::Vertical,this);
    slider_volume->setGeometry(20,330,16,160);
    slider_volume->setRange(0,100);
    slider_volume->setPageStep(10);
    this->slider_volume->setSingleStep(1);
    connect(this->slider_volume,SIGNAL(valueChanged(int)),this,SLOT(ValueChanged(int)));

    //time show
    label_min = new QLabel(this);
    label_min->setGeometry(62,470,20,20);
    label_min->setStyleSheet("color:white");

    label_sec = new QLabel(this);
    label_sec->setGeometry(80,470,20,20);
    label_sec->setStyleSheet("color:white");

    label_point = new QLabel(this);
    label_point->setGeometry(72,470,5,20);
    label_point->setStyleSheet("color:white");

    label_lrc = new QLabel(this);
    label_lrc->setGeometry(270,200,400,150);
    label_lrc->setStyleSheet("color:white");

    //function event
    connect(ui->btn_pause,SIGNAL(clicked()),this,SLOT(btn_pause()));//暂停、播放按钮信号
    connect(ui->btn_musiclist,SIGNAL(clicked()),this,SLOT(btn_musiclist()));//show musiclist
    connect(ui->btn_back,SIGNAL(clicked()),this,SLOT(btn_back()));
    connect(ui->btn_front,SIGNAL(clicked()),this,SLOT(btn_front()));
    connect(ui->btn_last,SIGNAL(clicked()),this,SLOT(btn_last()));
    connect(ui->btn_next,SIGNAL(clicked()),this,SLOT(btn_next()));
    connect(ui->btn_soundswitch,SIGNAL(clicked()),this,SLOT(btn_soundswitch()));
    connect(ui->btn_lrc,SIGNAL(clicked()),this,SLOT(getLrcFile()));

    //get musiclist lyriclist
    DIR *d;
    d = opendir("./songs");
    if(d == NULL)
    {
        perror("opendir error");
    }
    struct dirent* entry;
    int i = 0;
    sName=new char *[2048];
    lName = new char *[2048];
    while ((entry=readdir(d))!=NULL)
    {
        if(entry->d_type==DT_REG)
        {
            QListWidgetItem *add_item_i = new QListWidgetItem(ui->listWidget);
            add_item_i->setText(entry->d_name);
            char str[1024]="";
            char tmp[1024]="";
            char buf[1024]="";

            //song cmd
            sprintf(str,"%s%s%s","loadfile ./songs/",entry->d_name,"\n");
            sName[i]=(char *)malloc(strlen(str) + 1);
            strcpy(sName[i],str);
            printf("%s\n",sName[i]);

            //lrc cmd
            sscanf(entry->d_name,"%[^.]",tmp);
            sprintf(buf,"%s%s%s","./lyric/",tmp,".lrc");
            lName[i]=(char *)malloc(strlen(buf) + 1);
            strcpy(lName[i],buf);
            printf("%s\n",lName[i]);

            i++;
        }
    }
    closedir(d);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void *deal_fun(void *arg)
{
    DATA *p_data =  (DATA *)arg;
    while(1)
    {
        char buf[128]="";
        read(p_data->read_fd, buf,sizeof(buf));
        //printf("buf=%s\n", buf);

        char cmd[128]="";
        sscanf(buf,"%[^=]",cmd);
        if(strcmp(cmd,"ANS_PERCENT_POSITION") == 0)//百分比
        {
            int percent_pos = 0;
            sscanf(buf,"%*[^=]=%d", &percent_pos);
            printf("\r当前的百分比为:%%%d \t", percent_pos);
            p_data->p_w->slider->setValue(percent_pos);

        }
        else if(strcmp(cmd,"ANS_TIME_POSITION") == 0)//当前时间
        {
            float time_pos = 0;
            sscanf(buf,"%*[^=]=%f", &time_pos);
            printf("当前的时间为:%02d:%02d",(int)(time_pos+0.5)/60,(int)(time_pos+0.5)%60);
            p_data->p_w->label_min->setText(QString::number((int)(time_pos+0.5)/60));
            p_data->p_w->label_sec->setText(QString::number((int)(time_pos+0.5)%60));
            p_data->p_w->label_point->setText(":");
            tt = (int)(time_pos*1000);
            printf("time = %ld",tt);
        }
        fflush(stdout);
    }
}

void *deal_fun2(void *arg)
{
    int fifo_fd = *(int *)arg ;
    //不停的给fifo_cmd发送获取当前时间以及进度
    while(1)
    {
        usleep(500*1000);//0.5秒发指令
        write(fifo_fd,"get_percent_pos\n", strlen("get_percent_pos\n"));
        usleep(500*1000);//0.5秒发指令
        write(fifo_fd,"get_time_pos\n", strlen("get_time_pos\n"));
    }
    close(fifo_fd);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,"quit\n", strlen("quit\n"));
    free(sName);
}

void MainWindow::getLrcFile()
{
}

void MainWindow::btn_pause()
{

    int fifo_fd = open("fifo_cmd",O_WRONLY);
    pause_flag++;
    if((pause_flag%2) == 0)//play
    {
        printf("play \n");
        write(fifo_fd,"pause\n", strlen("pause\n"));
        ui->btn_pause->setStyleSheet("QPushButton{border-image: url(./image/pause1.png)}");
    }
    else if((pause_flag%2) == 1)//pause
    {
        printf("pause \n");
        write(fifo_fd,"pause\n", strlen("pause\n"));
        ui->btn_pause->setStyleSheet("QPushButton{border-image: url(./image/play1.png)}");
    }
}

void MainWindow::btn_musiclist()
{

    //musiclist show
    list_flag++;
    (list_flag%2)==1 ? ui->listWidget->show(): ui->listWidget->hide();
}

void MainWindow::btn_back()
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,"seek -10\n", strlen("seek -10\n"));
}

void MainWindow::btn_front()
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,"seek 10\n", strlen("seek 10\n"));
}

void MainWindow::btn_last()
{
    bg_flag++;
    //background
    setAutoFillBackground(true);
    QPalette pal = this->palette();

    switch (bg_flag%5)
    {
    case 0:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg0.png"));
        break;
    case 1:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg1.png"));
        break;
    case 2:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg2.png"));
        break;
    case 3:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg3.png"));
        break;
    case 4:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg4.png"));
        break;
    }
    setPalette(pal);

    int fifo_fd = open("fifo_cmd",O_WRONLY);
    if(song_flag==0)
    {
        song_flag=4;
        write(fifo_fd,sName[song_flag], strlen(sName[song_flag]));
    }
    else
    {
        song_flag--;
        write(fifo_fd,sName[song_flag], strlen(sName[song_flag]));
    }
}

void MainWindow::btn_next()
{
    bg_flag++;
    //background
    setAutoFillBackground(true);
    QPalette pal = this->palette();

    switch (bg_flag%5)
    {
    case 0:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg0.png"));
        break;
    case 1:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg1.png"));
        break;
    case 2:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg2.png"));
        break;
    case 3:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg3.png"));
        break;
    case 4:
        pal.setBrush(backgroundRole(), QPixmap("./image/bg4.png"));
        break;
    }
    setPalette(pal);

    int fifo_fd = open("fifo_cmd",O_WRONLY);
    if(song_flag==4)
    {
        song_flag=0;
        write(fifo_fd,sName[song_flag], strlen(sName[song_flag]));
    }
    else
    {
        song_flag++;
        write(fifo_fd,sName[song_flag], strlen(sName[song_flag]));
    }
}

void MainWindow::btn_soundswitch()
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    sound_flag++;
    if((sound_flag%2) == 0)//0
    {
        printf("0 \n");
        write(fifo_fd,"mute 0\n", strlen("mute 0\n"));
        ui->btn_soundswitch->setStyleSheet("QPushButton{border-image: url(./image/ico/soundon.png)}");
    }
    else if((sound_flag%2) == 1)//1
    {
        printf("1 \n");
        write(fifo_fd,"mute 1\n", strlen("mute 1\n"));
        ui->btn_soundswitch->setStyleSheet("QPushButton{border-image: url(./image/ico/soundoff.png)}");
    }
}
void MainWindow::on_listWidget_clicked(const QModelIndex &index)//单击ListWidget的某一行事件触发信号函数
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    int currenRow = ui->listWidget->currentRow();//当前单击选中ListWidget控件的行号（第几行)
    switch(currenRow)
    {
    case 0:
        printf("%s\n",sName[0]);
        write(fifo_fd,sName[0],strlen(sName[0]));
        song_flag=0;
        break;
    case 1:
        printf("%s\n",sName[1]);
        write(fifo_fd,sName[1],strlen(sName[1]));
        song_flag=1;
        break;
    case 2:
        printf("%s\n",sName[2]);
        write(fifo_fd,sName[2],strlen(sName[2]));
        song_flag=2;
        break;
    case 3:
        printf("%s\n",sName[3]);
        write(fifo_fd,sName[3],strlen(sName[3]));
        song_flag=3;
        break;
    case 4:
        printf("%s\n",sName[4]);
        write(fifo_fd,sName[4],strlen(sName[4]));
        song_flag=4;
        break;
    }
}

void MainWindow::ValueChanged(int val)
{
    char cmd[16]="";
    sprintf(cmd,"%s%d%s","volume ",val," 1\n");
    printf("cmd=%s\n",cmd);
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,cmd,strlen(cmd));
    printf("valuechange=%d\n",val);
}
