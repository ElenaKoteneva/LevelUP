#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

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

                m_image.load(filename);
                m_image.scaled(640, 480, Qt::KeepAspectRatio); //изменить размер, сохраняя пропорции
                //src = cv::imread(cv::samples::findFile(filename), cv::IMREADCOLOR)

                ui->radioButtonDefaultView->click();
                file.seek(0);
                file.close();
            }
        }
    }

}
void MainWindow::show_defalt()
{
    ui->label->setPixmap(QPixmap::fromImage(m_image));
    qDebug() << "Show default";
}

void MainWindow::show_blur()
{
    cv::Mat image = cv::Mat(m_image.height(), m_image.width(), CV_8UC4, m_image.bits(), m_image.bytesPerLine()).clone();
    cv::blur(image, image, cv::Size(31,31), cv::Point(-1,-1));

    m_proc_image = QImage(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_RGB32);
    cv::imshow("Blur", image);
    //ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show blur";
};

void MainWindow::show_gauss()
{
    cv::Mat image = cv::Mat(m_image.height(), m_image.width(), CV_8UC4, m_image.bits(), m_image.bytesPerLine()).clone();
    cv::GaussianBlur(image, image, cv::Size(31,31), 0, 0);
    m_proc_image = QImage(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_RGB32);
    cv::imshow("Gauss", image);
    //ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show gauss";
}
void MainWindow::show_gray()
{
    cv::Mat image = cv::Mat(m_image.height(), m_image.width(), CV_8UC4, m_image.bits(), m_image.bytesPerLine()).clone();
    cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);
    m_proc_image = QImage(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show gray";
}
void MainWindow::show_threshold()
{
    cv::Mat image = cv::Mat(m_image.height(), m_image.width(), CV_8UC4, m_image.bits(), m_image.bytesPerLine()).clone();
    //cv::cvtColor(image, image, cv::COLOR_RGB2HSV);
    cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);
    cv::threshold(image, image, 128, 255, 0);
    m_proc_image = QImage(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show threshold";
}
void MainWindow::show_HSV()
{
    cv::Mat image = cv::Mat(m_image.height(), m_image.width(), CV_8UC4, m_image.bits(), m_image.bytesPerLine()).clone();
    cv::cvtColor(image, image, cv::COLOR_RGB2HSV);
    m_proc_image = QImage(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show HSV";
}
void MainWindow::show_canny()
{
    cv::Mat image = cv::Mat(m_image.height(), m_image.width(), CV_8UC4, m_image.bits(), m_image.bytesPerLine()).clone();
    // cv::cvtColor(image, image, cv::COLOR_RGB2HSV);
    cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);
    cv::threshold(image, image, 150, 255, 0);
    cv::Canny(image, image, 100, 255);
    m_proc_image = QImage(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(m_proc_image));
    qDebug() << "Show canny";
}

