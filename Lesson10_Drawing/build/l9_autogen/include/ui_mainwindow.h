/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *onOpenImage;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonDefaultView;
    QRadioButton *radioButtonBlur;
    QRadioButton *radioButtonGauss;
    QRadioButton *radioButtonTreshold;
    QRadioButton *radioButtonGray;
    QRadioButton *radioButtonHSV;
    QRadioButton *radioButtonCanny;
    QCheckBox *drawing;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(475, 363);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        onOpenImage = new QPushButton(centralwidget);
        onOpenImage->setObjectName(QString::fromUtf8("onOpenImage"));

        verticalLayout_2->addWidget(onOpenImage);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        radioButtonDefaultView = new QRadioButton(centralwidget);
        radioButtonDefaultView->setObjectName(QString::fromUtf8("radioButtonDefaultView"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(15);
        sizePolicy1.setHeightForWidth(radioButtonDefaultView->sizePolicy().hasHeightForWidth());
        radioButtonDefaultView->setSizePolicy(sizePolicy1);
        radioButtonDefaultView->setMinimumSize(QSize(0, 15));

        verticalLayout->addWidget(radioButtonDefaultView);

        radioButtonBlur = new QRadioButton(centralwidget);
        radioButtonBlur->setObjectName(QString::fromUtf8("radioButtonBlur"));

        verticalLayout->addWidget(radioButtonBlur);

        radioButtonGauss = new QRadioButton(centralwidget);
        radioButtonGauss->setObjectName(QString::fromUtf8("radioButtonGauss"));

        verticalLayout->addWidget(radioButtonGauss);

        radioButtonTreshold = new QRadioButton(centralwidget);
        radioButtonTreshold->setObjectName(QString::fromUtf8("radioButtonTreshold"));

        verticalLayout->addWidget(radioButtonTreshold);

        radioButtonGray = new QRadioButton(centralwidget);
        radioButtonGray->setObjectName(QString::fromUtf8("radioButtonGray"));

        verticalLayout->addWidget(radioButtonGray);

        radioButtonHSV = new QRadioButton(centralwidget);
        radioButtonHSV->setObjectName(QString::fromUtf8("radioButtonHSV"));

        verticalLayout->addWidget(radioButtonHSV);

        radioButtonCanny = new QRadioButton(centralwidget);
        radioButtonCanny->setObjectName(QString::fromUtf8("radioButtonCanny"));

        verticalLayout->addWidget(radioButtonCanny);

        drawing = new QCheckBox(centralwidget);
        drawing->setObjectName(QString::fromUtf8("drawing"));

        verticalLayout->addWidget(drawing);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addLayout(verticalLayout_2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(50, 50));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setScaledContents(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);


        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 475, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        onOpenImage->setText(QCoreApplication::translate("MainWindow", "Open Image", nullptr));
        radioButtonDefaultView->setText(QCoreApplication::translate("MainWindow", "Default view", nullptr));
        radioButtonBlur->setText(QCoreApplication::translate("MainWindow", "Blur", nullptr));
        radioButtonGauss->setText(QCoreApplication::translate("MainWindow", "Gauss", nullptr));
        radioButtonTreshold->setText(QCoreApplication::translate("MainWindow", "Threshold", nullptr));
        radioButtonGray->setText(QCoreApplication::translate("MainWindow", "Gray", nullptr));
        radioButtonHSV->setText(QCoreApplication::translate("MainWindow", "HSV", nullptr));
        radioButtonCanny->setText(QCoreApplication::translate("MainWindow", "Canny", nullptr));
        drawing->setText(QCoreApplication::translate("MainWindow", "Drawing", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Image", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
