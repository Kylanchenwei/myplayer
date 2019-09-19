#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSlider>
#include<QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *);
    QSlider *slider;
    QSlider *slider_volume;
    QLabel *label_min;
    QLabel *label_sec;
    QLabel *label_point;
    QLabel *label_lrc;



public slots:
    void btn_pause();
    void btn_musiclist();
    void btn_back();
    void btn_front();
    void btn_last();
    void btn_next();
    void btn_soundswitch();
    void getLrcFile();
private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void ValueChanged(int val);

private:
    Ui::MainWindow *ui;
};
typedef struct
{
    MainWindow *p_w;
    int read_fd;

}DATA;

extern void *deal_fun(void *arg);
extern void *deal_fun2(void *arg);
#endif // MAINWINDOW_H
