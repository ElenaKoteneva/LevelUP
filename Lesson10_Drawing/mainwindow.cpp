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

    connect(ui->onOpenImage, &QPushButton::clicked, this, &MainWindow::open_image);
    connect(ui->radioButtonDefaultView, &QPushButton::clicked, this, &MainWindow::show_defalt);
    connect(ui->radioButtonBlur, &QPushButton::clicked, this, &MainWindow::show_blur);
    connect(ui->radioButtonGauss, &QPushButton::clicked, this, &MainWindow::show_gauss);
    connect(ui->radioButtonTreshold, &QPushButton::clicked, this, &MainWindow::show_threshold);
    connect(ui->radioButtonGray, &QPushButton::clicked, this, &MainWindow::show_gray);
    connect(ui->radioButtonHSV, &QPushButton::clicked, this, &MainWindow::show_HSV);
    connect(ui->radioButtonCanny, &QPushButton::clicked, this, &MainWindow::show_canny);

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::open_image()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::currentPath(), "Image(*.jpg;*.png);;ALL(*.*)");

    if (filename.length())
    {
        int index = filename.indexOf(".jpg"); // определяем, есть ли в названии строка ".txt"
        qDebug() << index;
        if (index != -1 && filename.length() - 4 == index)
        {
            QFile file(filename);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                m_src = imread(filename.toStdString(), IMREAD_COLOR);
                ui->radioButtonDefaultView->click();
                file.seek(0);
                file.close();
            }
        }
    }
}
void MainWindow::show_defalt()
{
    m_dst = m_src.clone();
    if (ui->drawing->isChecked())
    {
        drawing(m_dst);
    }
    m_proc_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_BGR888);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show default";
}

void MainWindow::show_blur()
{
    blur(m_src, m_dst, cv::Size(31,31), cv::Point(-1,-1));
    if (ui->drawing->isChecked())
    {
        drawing(m_dst);
    }
    m_proc_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_BGR888);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show blur";
};

void MainWindow::show_gauss()
{
    GaussianBlur(m_src, m_dst, cv::Size(31,31), 0, 0);
    if (ui->drawing->isChecked())
    {
        drawing(m_dst);
    }
    m_proc_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_BGR888);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show gauss";
}
void MainWindow::show_gray()
{
    cvtColor(m_src, m_dst, cv::COLOR_RGB2GRAY);
    if (ui->drawing->isChecked())
    {
        drawing(m_dst);
    }
    m_proc_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show gray";
}
void MainWindow::show_threshold()
{
    cv::cvtColor(m_src, m_dst, cv::COLOR_BGR2GRAY);
    cv::threshold(m_src, m_dst, 0, 255, 3);
    m_proc_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_Grayscale16);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show threshold";
}
void MainWindow::show_HSV()
{
    cv::cvtColor(m_src, m_dst, cv::COLOR_RGB2HSV);
    if (ui->drawing->isChecked())
    {
        drawing(m_dst);
    }
    m_proc_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_BGR888);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show HSV";
}
void MainWindow::show_canny()
{
    cv::cvtColor(m_src, m_dst, cv::COLOR_RGB2GRAY);
    cv::threshold(m_src, m_dst, 150, 255, 0);
    cv::Canny(m_src, m_dst, 100, 255);
    if (ui->drawing->isChecked())
    {
        drawing(m_dst);
    }
    m_proc_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, static_cast<int>(m_dst.step), QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show canny";
}

