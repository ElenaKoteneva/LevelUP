#include "filework.h"
#include <QDateTime>

FileWork::FileWork()
{
    file.setFileName("newfile.txt");
    if (!file.open(QIODevice::ReadWrite)) qDebug() << "Can not open file.";
    if (!file.exists()) qDebug() << "File does not exist.";
}

FileWork::FileWork(const QString &fileName)
{
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadWrite)) qDebug() << "Can not open file.";
    if (!file.exists()) qDebug() << "File does not exist.";
}

FileWork::~FileWork()
{
   file.close();
}

void FileWork::readFileByLines()
{
    QByteArray line;
    file.seek(0);
    while (!file.atEnd())
    {
         line = file.readLine();
         qDebug() << line;
    }
}

void FileWork::readAllFileData()
{
    QTextStream textstream(&file);
    qDebug() << "Text stream:";
    file.seek(0);
    while (!file.atEnd())

        qDebug() << textstream.readAll();
}

void FileWork::writeToFileEnd(const QByteArray &line)
{
    file.write("\n");
    file.write(line);
}

void FileWork::writeFileStream(const QString &text)
{
    QTextStream textstream(&file);
    textstream << "\n" << text;
}

void FileWork::fileInfo()
{
    QFileInfo fileInfo(file);
    qDebug() << "File Info: \n" << fileInfo.absoluteFilePath();
    qDebug() << fileInfo.birthTime().toString();
}
