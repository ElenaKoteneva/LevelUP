#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.|,)[0-9]{9}"), this));
    number_1 = 0;
    number_2 = 0;
    result = 0;
    str_number.clear();
    str_result.clear();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_0_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("0");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_1_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("1");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("2");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("3");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_4_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("4");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_5_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("5");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_6_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("6");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_7_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("7");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_8_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("8");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButton_9_clicked()
{
    if (!plus && !minus && !mul && !div) str_number = ui->lineEdit->text();
    str_number.append("9");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButtonPoint_clicked()
{
    str_number = ui->lineEdit->text();
    if (!str_number.contains('.')) str_number.append(".");
    ui->lineEdit->setText(str_number);
}

void MainWindow::on_pushButtonC_clicked()
{
    str_number.clear();
    str_result.clear();
    number_1 = 0;
    number_2 = 0;
    result = 0;
    ui->lineEdit->setText("");
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButtonPlus_clicked()
{
    str_number = ui->lineEdit->displayText();
    number_1 = str_number.toDouble();
    qDebug() << number_1;
    str_number.clear();
    plus = 1;
    minus = 0;
    mul = 0;
    div = 0;
}

void MainWindow::on_pushButtonMinus_clicked()
{
    number_1 = ui->lineEdit->displayText().toDouble();
    qDebug() << number_1;
    str_number.clear();
    minus = 1;
    plus = 0;
    mul = 0;
    div = 0;
}

void MainWindow::on_pushButtonMul_clicked()
{
    number_1 = ui->lineEdit->displayText().toDouble();
    qDebug() << number_1;
    str_number.clear();
    mul = 1;
    plus = 0;
    minus = 0;
    div = 0;
}

void MainWindow::on_pushButtonDiv_clicked()
{
    number_1 = ui->lineEdit->displayText().toDouble();
    qDebug() << number_1;
    str_number.clear();
    div = 1;
    plus = 0;
    minus = 0;
    mul = 0;

}
void MainWindow::on_pushButtonEqual_clicked()
{
    number_2 = str_number.toDouble();
    str_number.clear();

    if (plus) result = number_1 + number_2;
    else if (minus) result = number_1 - number_2;
    else if (mul) result = number_1 * number_2;
    else if (div) result = number_1 / number_2;


    str_result.setNum(result);
    ui->lineEdit->setText(str_result);

    number_1 = result;
    number_2 = 0;

    plus = 0;
    minus = 0;
    mul = 0;
    div = 0;
}
