#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage m_image, m_proc_image;
    cv::Mat src;
    cv::Mat dst;
private slots:
    void open_image();
    void show_defalt();
    void show_blur();
    void show_gauss();
    void show_gray();
    void show_threshold();
    void show_HSV();
    void show_canny();
};
#endif // MAINWINDOW_H
