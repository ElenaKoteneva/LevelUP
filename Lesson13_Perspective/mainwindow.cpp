#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(FRAMES_PER_SEC);

    ui->sliderTop->setMinimum(0);
    ui->sliderTop->setMaximum(FRAME_WIDTH / 2);
    ui->sliderTop->setValue(FRAME_WIDTH / 4);
    ui->sliderTop->setEnabled(false);
    ui->sliderBottom->setMinimum(0);
    ui->sliderBottom->setMaximum(FRAME_WIDTH /  2);
    ui->sliderBottom->setValue(FRAME_WIDTH / 4);
    ui->sliderBottom->setEnabled(false);
    ui->sliderHeigh->setMinimum(0);
    ui->sliderHeigh->setMaximum(FRAME_HEIGHT - 30);
    ui->sliderHeigh->setValue((FRAME_HEIGHT - 30) / 2);
    ui->sliderHeigh->setEnabled(false);

    trap_top_line = ui->sliderTop->value();
    trap_bottom_line = ui->sliderBottom->value();
    trap_heigh = ui->sliderHeigh->value();

    ipm_points[0] = Point2f(0, 0);
    ipm_points[1] = Point2f(FRAME_HEIGHT, 0);
    ipm_points[2] = Point2f(FRAME_HEIGHT, FRAME_HEIGHT);
    ipm_points[3] = Point2f(0, FRAME_HEIGHT);

    ipm_mat = Mat(FRAME_HEIGHT, FRAME_HEIGHT, CV_8UC3);
    warp_inRange = Mat(FRAME_HEIGHT, FRAME_HEIGHT, CV_8UC3);

    connect(ui->onOpenVideo, &QPushButton::clicked, this, &MainWindow::openVideo);
    connect(ui->pushButtonCamera, &QPushButton::clicked, this, &MainWindow::openCamera);
    connect(ui->sliderTop, &QSlider::valueChanged, this, &MainWindow::changeTopLine);
    connect(ui->sliderBottom, &QSlider::valueChanged, this, &MainWindow::changeBottomLine);
    connect(ui->sliderHeigh, &QSlider::valueChanged, this, &MainWindow::changeTrapHeigh);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
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
            ui->sliderTop->setEnabled(true);
            ui->sliderBottom->setEnabled(true);
            ui->sliderHeigh->setEnabled(true);
        }
        else
        {
            qDebug() << "Check file *.mp4";
        }
    }
}

void MainWindow::openCamera()
{
    m_cam = VideoCapture(0);
    m_cam.set(cv::VideoCaptureProperties::CAP_PROP_GUID, 1);
    //ui->pushButtonCamera->setEnabled(false);
    if (!m_cam.isOpened())
    {
        qDebug() << "Could not open camera";
    }
    m_cam.set(CAP_PROP_FRAME_WIDTH, 320);
    m_cam.set(CAP_PROP_FRAME_HEIGHT, 240);
    m_video.release();
    while (true)
    {
        m_cam.read(cam_src);
        imshow("Camera(Esc-exit)", cam_src);
        char c = waitKey(25); // 25 ms
        if (c == 27) break; // Esc
    }
    m_cam.release();
    destroyWindow("Camera(Esc-exit)");
    qDebug() << "Camera";
}


void MainWindow::update()
{
    if (m_video.read(m_src))
    {
        cv::resize(m_src, m_src, Size(FRAME_WIDTH, FRAME_HEIGHT));
        m_src.copyTo(m_dst);

        if (ui->debugInfo->isChecked()) m_dst = debugInfo(m_dst);

        ui->statusbar->showMessage("Top line " + QString::number(trap_top_line) +
                                   "; Bottom line " + QString::number(trap_bottom_line) +
                                   "; Trapezoid heigh " + QString::number(trap_heigh));

        trapezoid[0] = Point2f(FRAME_WIDTH/2-trap_top_line, FRAME_HEIGHT - TRAP_HEIGH_OFFSET - trap_heigh);
        trapezoid[1] = Point2f(FRAME_WIDTH/2+trap_top_line, FRAME_HEIGHT - TRAP_HEIGH_OFFSET - trap_heigh);
        trapezoid[2] = Point2f(FRAME_WIDTH/2+trap_bottom_line, FRAME_HEIGHT - TRAP_HEIGH_OFFSET);
        trapezoid[3] = Point2f(FRAME_WIDTH/2-trap_bottom_line, FRAME_HEIGHT - TRAP_HEIGH_OFFSET);

        transform_matrix = getPerspectiveTransform(trapezoid, ipm_points);
        warpPerspective(m_dst, ipm_mat, transform_matrix, Size(FRAME_HEIGHT, FRAME_HEIGHT));

        circle(m_dst, trapezoid[0], 2, {0,255,0}, 2);
        circle(m_dst, trapezoid[1], 2, {0,255,0}, 2, LINE_8, 0);
        circle(m_dst, trapezoid[2], 2, {0,255,0}, 2, LINE_8, 0);
        circle(m_dst, trapezoid[3], 2, {0,255,0}, 2, LINE_8, 0);
        line(m_dst, trapezoid[0], trapezoid[1], Scalar(0,255,0), 2, 8);
        line(m_dst, trapezoid[1], trapezoid[2], Scalar(0,255,0), 2, 8);
        line(m_dst, trapezoid[2], trapezoid[3], Scalar(0,255,0), 2, 8);
        line(m_dst, trapezoid[3], trapezoid[0], Scalar(0,255,0), 2, 8);

        m_image = QImage(m_dst.data, m_dst.cols, m_dst.rows, QImage::Format_BGR888);
        ui->label->setPixmap(QPixmap::fromImage(m_image));

        m_image = QImage(ipm_mat.data, ipm_mat.cols, ipm_mat.rows, QImage::Format_BGR888);
        ui->Top_View_Src->setPixmap(QPixmap::fromImage(m_image));

       if (ui->threshold->isChecked())
       {
           cvtColor(m_src, m_frame_HSV, cv::COLOR_BGR2HSV);
           inRange(m_frame_HSV, Scalar(0, 0, 200), Scalar(180, 255, 255), m_frame_threshold);

           warpPerspective(m_frame_threshold, warp_inRange, transform_matrix, Size(FRAME_HEIGHT, FRAME_HEIGHT));

           m_image = QImage(m_frame_threshold.data, m_frame_threshold.cols, m_frame_threshold.rows, QImage::Format_Grayscale8);
           ui->inRangeVideo->setPixmap(QPixmap::fromImage(m_image));

           m_image = QImage(warp_inRange.data, warp_inRange.cols, warp_inRange.rows, QImage::Format_Grayscale8);
           ui->Top_View_InRange->setPixmap(QPixmap::fromImage(m_image));

       }
    }
    if (m_src.empty())
    {
        ui->statusbar->showMessage("Frame is empty. Open new video.");
        ui->sliderTop->setEnabled(false);
        ui->sliderBottom->setEnabled(false);
        ui->sliderHeigh->setEnabled(false);
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

void MainWindow::changeTopLine()
{
    trap_top_line = ui->sliderTop->value();
}

void MainWindow::changeBottomLine()
{
    trap_bottom_line = ui->sliderBottom->value();
}

void MainWindow::changeTrapHeigh()
{
    trap_heigh = ui->sliderHeigh->value();
}
