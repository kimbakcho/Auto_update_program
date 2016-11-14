#ifndef MAINWIDET_H
#define MAINWIDET_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfoList>
#include <QDateTime>
namespace Ui {
class Mainwidet;
}

class Mainwidet : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwidet(QWidget *parent = 0);
    QProcess Process;
    bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory);
    ~Mainwidet();

private:
    Ui::Mainwidet *ui;
};

#endif // MAINWIDET_H
