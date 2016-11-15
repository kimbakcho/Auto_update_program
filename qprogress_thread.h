#ifndef QPROGRESS_THREAD_H
#define QPROGRESS_THREAD_H

#include <QObject>
#include <QThread>
#include <QProgressDialog>
#include <QDir>
#include <QProcess>
#include <QFileInfo>
#include <QApplication>
#include <QDateTime>
#include <QDebug>
class QProgress_thread : public QThread
{
    Q_OBJECT
public:
    explicit QProgress_thread();
     bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory);
     void update_file_logic();
     void start_update();
     QProcess Process;
     QString buildCpu;

     int update_file_count;
     int current_update_file_count;

     int getUpdate_file_count() const;
     void setUpdate_file_count(int value);

signals:
     void progress_value_update(int);
private :
     void run();

signals:

public slots:
};

#endif // QPROGRESS_THREAD_H
