#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "stdio.h"

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240
#define TRAP_HEIGH_OFFSET 30
#define FRAMES_PER_SEC 25


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
    Mat m_src, m_dst, cam_src, m_frame_HSV, m_frame_threshold, ipm_mat, transform_matrix, warp_inRange;
    VideoCapture m_video, m_cam;
    QTimer* timer;
    Point2f trapezoid[4], ipm_points[4];
    qint16 trap_top_line, trap_bottom_line, trap_heigh;

    void changeTopLine();
    void changeBottomLine();
    void changeTrapHeigh();
    Mat debugInfo(Mat frame);
private slots:
    void openVideo();
    void openCamera();
    void update();
};
#endif // MAINWINDOW_H
