#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>


std::vector<Point> pts = { {200,10}, {250,10}, {250,60}, {200,60} };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(25);

    connect(ui->onOpenVideo, &QPushButton::clicked, this, &MainWindow::open_video);
    connect(ui->pushButtonCamera, &QPushButton::clicked, this, &MainWindow::open_camera);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_camera()
{
    m_cam = VideoCapture(0);
    m_cam.read(m_src);
    ui->radioButtonDefaultView->click();
    qDebug() << "Camera";
}

void MainWindow::open_video()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::currentPath(), "Video(*.mp4;*.avi;*.wmv);;ALL(*.*)");

    if (filename.length())
    {
        int index = filename.indexOf(".wmv");
        qDebug() << index << filename.length() - 4;
        if (index != -1 && filename.length() - 4 == index)
        {
            QFile file(filename);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                m_video = cv::VideoCapture(filename.toStdString());
                m_video.read(m_src);
                ui->radioButtonDefaultView->click();
                file.seek(0);
                file.close();
            }
        }
    }
}

void MainWindow::update()
{
    m_video.read(m_src);
    //m_cam.read(m_src);
    if (!m_src.empty())
       {
           m_image = QImage(m_src.data, m_src.cols, m_src.rows, static_cast<int>(m_src.step), QImage::Format_BGR888);
           ui->label->setPixmap(QPixmap::fromImage(m_image));
       }

    if (ui->drawing->isChecked())
    {
        drawing(m_src);
    }

    if (ui->radioButtonBlur->isChecked())
    {
        blur(m_src, m_dst, cv::Size(31,31), cv::Point(-1,-1));
        m_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_BGR888);
        ui->label->setPixmap(QPixmap::fromImage(m_image));
    }
    else if (ui->radioButtonGauss->isChecked())
    {
        GaussianBlur(m_src, m_dst, cv::Size(31,31), 0, 0);
        m_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_BGR888);
        ui->label->setPixmap(QPixmap::fromImage(m_image));
    }
    else if (ui->radioButtonGray->isChecked())
    {
        cvtColor(m_src, m_dst, cv::COLOR_RGB2GRAY);
        m_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_Grayscale8);
        ui->label->setPixmap(QPixmap::fromImage(m_image));
    }
    else if (ui->radioButtonTreshold->isChecked())
    {
        cv::cvtColor(m_src, m_dst, cv::COLOR_BGR2GRAY);
        cv::threshold(m_src, m_dst, 0, 255, 3);
        m_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_Grayscale16);
        ui->label->setPixmap(QPixmap::fromImage(m_image));
    }
    else if (ui->radioButtonHSV->isChecked())
    {
        cv::cvtColor(m_src, m_dst, cv::COLOR_RGB2HSV);
        m_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_BGR888);
        ui->label->setPixmap(QPixmap::fromImage(m_image));
    }
    else if (ui->radioButtonCanny->isChecked())
    {
        Mat canny_img;
        Canny(m_src, m_dst, 100, 200);
        canny_img = cv::Scalar::all(0);
        m_src.copyTo(canny_img, m_dst);
        m_image = QImage(canny_img.data, canny_img.cols, canny_img.rows, static_cast<int>(canny_img.step), QImage::Format_BGR888);
        ui->label->setPixmap(QPixmap::fromImage(m_image));
    }
    else
    {
        m_image = QImage(m_src.data, m_src.cols, m_src.rows, static_cast<int>(m_src.step), QImage::Format_BGR888);
        ui->label->setPixmap(QPixmap::fromImage(m_image));
    }

}

void MainWindow::drawing(Mat img)
{
    line(img, {10,10}, {60,60}, {255,255,255}, 3);
    circle(img, {95,35},25,{225,255,255},3);
    rectangle(img, {130,10}, {180,60},{255,255,255},3);
    fillPoly(img, pts, Scalar{250,255,255});
    putText(img, "Line", {10,80},FONT_HERSHEY_PLAIN, 1, {0,255,0});
    putText(img, "Circlr", {70,80},FONT_HERSHEY_PLAIN, 1, {0,255,0});
    putText(img, "Rect", {130,80},FONT_HERSHEY_PLAIN, 1, {0,255,0});
    putText(img, "Fill", {190,80},FONT_HERSHEY_PLAIN, 1, {0,255,0});
}

//image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
//imshow("src", m_src);
