#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include "filework.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileWork file;

    file.writeToFileEnd("First string");
    file.writeToFileEnd("Second string");
    file.writeToFileEnd("Third string");
    file.readFileByLines();

    file.writeFileStream("Add text");
    file.readAllFileData();

    file.fileInfo();
    return a.exec();
}
