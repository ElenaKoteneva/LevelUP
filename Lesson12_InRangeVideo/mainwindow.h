#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "stdio.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace cv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage m_image;
    Mat m_src, m_dst, m_debug_info, m_frame_HSV, m_frame_threshold;
    VideoCapture m_video, m_cam;
    QTimer* timer;
    qint16 m_ch_red, m_ch_green, m_ch_blue;

    void changeChanelRed();
    void changeChanelGreen();
    void changeChanelBlue();
    Mat debugInfo(Mat frame);
private slots:
    void openVideo();
    void openCamera();
    void update();
};
#endif // MAINWINDOW_H
