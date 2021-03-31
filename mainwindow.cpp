#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
extern "C" {
    #include <libavdevice/avdevice.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
}

#define FMT_NAME "avfoundation"
#define DEVICE_NAME ":1"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_audioBtn_clicked()
{
    // 获取输入格式
    AVInputFormat *fmt = av_find_input_format(FMT_NAME);
    if (!fmt) {
        qDebug() << "未能找到" << FMT_NAME << "输入格式";
        return;
    }

    qDebug() << "已找到" << FMT_NAME << "输入格式";

    // 打开设备
    // 获取上下文
    AVFormatContext *ctx = nullptr;
    int ret = avformat_open_input(&ctx, DEVICE_NAME, fmt, nullptr);
    if (ret < 0) {
        char errbuf[1024] = {0};
        av_strerror(ret, errbuf, sizeof(errbuf));
        qDebug() << "打开设备失败:" << errbuf;
        return;
    }

    qDebug() << "打开设备成功";

}
