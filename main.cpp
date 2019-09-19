#include "mainwindow.h"
#include "lrc.h"
#include <QApplication>
#include<stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include  <QtWidgets>
#include<QPushButton>
namespace Ui
{
class MainWindow;
}

int main(int argc, char *argv[])
{

    //创建一个无名管道 获取mplayer回应
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if(pid == 0)//子进程
    {
        //创建一个管道
        mkfifo("fifo_cmd",0666);
        //将1设备重定向到fd[1]
        dup2(fd[1], 1);
        //使用execlp启动mplayer
        execlp("mplayer","mplayer","-idle","-slave","-quiet","-input","file=./fifo_cmd",NULL);
    }
    else//父进程
    {
        DATA data;

        //ui设计
        QApplication a(argc, argv);
        MainWindow w;
        data.p_w = &w;
        data.read_fd = fd[0];
        //创建一个接受mplayer回应的线程
        pthread_t mplayer_ack;
        pthread_create(&mplayer_ack,NULL,deal_fun , &data);
        pthread_detach(mplayer_ack);

        //创建一个管道
        mkfifo("fifo_cmd",0666);
        int fifo_fd = open("fifo_cmd",O_WRONLY);
        //创建一个线程 给mplayer发送指令
        pthread_t send_mplayer;
        pthread_create(&send_mplayer,NULL,deal_fun2 , &fifo_fd);
        pthread_detach(send_mplayer);

        w.show();

        return a.exec();
    }

}
