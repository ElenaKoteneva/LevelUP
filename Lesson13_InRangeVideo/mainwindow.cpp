#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(25);

    ui->sliderRed->setMinimum(0);
    ui->sliderRed->setMaximum(255);
    ui->sliderGreen->setMinimum(0);
    ui->sliderGreen->setMaximum(255);
    ui->sliderBlue->setMinimum(0);
    ui->sliderBlue->setMaximum(255);

    connect(ui->onOpenVideo, &QPushButton::clicked, this, &MainWindow::openVideo);
    //connect(ui->pushButtonCamera, &QPushButton::clicked, this, &MainWindow::openCamera);
    connect(ui->sliderRed, &QSlider::valueChanged, this, &MainWindow::changeChanelRed);
    connect(ui->sliderGreen, &QSlider::valueChanged, this, &MainWindow::changeChanelGreen);
    connect(ui->sliderBlue, &QSlider::valueChanged, this, &MainWindow::changeChanelBlue);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openVideo()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::currentPath(), "Video(*.mp4;*.avi;*.wmv);;ALL(*.*)");

    if (filename.length())
    {
        int index = filename.indexOf(".mp4");
        qDebug() << index << filename.length() - 4;
        if (index != -1 && filename.length() - 4 == index)
        {
            m_video = VideoCapture(filename.toStdString());
        }
        else
        {
            qDebug() << "Check file *.mp4";
        }
    }
}
//    if (!m_video.isOpened())
//    {
//        qDebug() << "Error opening video stream or file"<< endl;
//    }
//    else
//    {
//        m_video = VideoCapture(filename.toStdString());
//    }


void MainWindow::openCamera()
{
    m_cam = VideoCapture(0);
    qDebug() << "Camera";
}


void MainWindow::update()
{
   //m_cam.read(m_src);
   if (m_video.read(m_src))
   {

       if (ui->debugInfo->isChecked())
       {
           m_src = debugInfo(m_src);
       }

       m_image = QImage(m_src.data, m_src.cols, m_src.rows, QImage::Format_BGR888);
       m_image.scaled(320, 240); // Не работает масштабирование ???
       ui->label->setPixmap(QPixmap::fromImage(m_image));

       if (ui->threshold->isChecked())
       {
           cvtColor(m_src, m_frame_HSV, cv::COLOR_BGR2HSV);
           inRange(m_frame_HSV, Scalar(m_ch_blue, m_ch_red, m_ch_green), Scalar(255,255,255), m_frame_threshold);
           m_image = QImage(m_frame_threshold.data, m_frame_threshold.cols, m_frame_threshold.rows, QImage::Format_Grayscale8);
           m_image.scaled(320, 240);
           ui->inRangeVideo->setPixmap(QPixmap::fromImage(m_image));
       }

       if (ui->HSV->isChecked())
       {
           cv::cvtColor(m_src, m_dst, cv::COLOR_BGR2HSV);
           m_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, QImage::Format_BGR888);
           ui->HSV_Video->setPixmap(QPixmap::fromImage(m_image));
       }

       if (ui->canny->isChecked())
       {
           Mat canny_img;
           Canny(m_src, m_dst, 100, 200);
           canny_img = cv::Scalar::all(0);
           m_src.copyTo(canny_img, m_dst);

           m_image = QImage(canny_img.data, canny_img.cols, canny_img.rows, QImage::Format_BGR888);
           ui->canny_video->setPixmap(QPixmap::fromImage(m_image));
       }
   }

}

Mat MainWindow::debugInfo(Mat frame)
{
    char* message;
    int frame_current = m_video.get(CAP_PROP_POS_FRAMES);

    sprintf(message,"Current frame=%d",frame_current);
    putText(frame, message, {10,50}, FONT_ITALIC, 1, {0,255,0}, 2);

    return frame;
}

void MainWindow::changeChanelRed()
{
    m_ch_red = ui->sliderRed->value();
}

void MainWindow::changeChanelGreen()
{
    m_ch_green = ui->sliderGreen->value();
}

void MainWindow::changeChanelBlue()
{
    m_ch_blue = ui->sliderBlue->value();
}
//m_image.scaled(240, 240, Qt::KeepAspectRatio);
//image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
// m_image.scaledToWidth(ui->label->width());
//imshow("src", m_src);
