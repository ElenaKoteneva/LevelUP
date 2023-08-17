#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/opencv.hpp>
//#include <opencv4/opencv2/opencv.hpp>

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
    Mat m_src, m_dst;
    VideoCapture m_video;
    //CvCapture* capture; //CAP_ANY
    VideoCapture m_cam;
    QTimer* timer;

    void drawing(Mat pic);
private slots:
    void open_video();
    void open_camera();
    void update();
};
#endif // MAINWINDOW_H
