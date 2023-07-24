#ifndef FILEWORK_H
#define FILEWORK_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>

class FileWork
{

private:
    QFile file;
public:
    FileWork();

    FileWork(const QString &fileName);

    ~FileWork();

    void readFileByLines();

    void readAllFileData();

    void writeToFileEnd(const QByteArray &line);

    void writeFileStream(const QString &text);

    void fileInfo();
};

#endif // FILEWORK_H
