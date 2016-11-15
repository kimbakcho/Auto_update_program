#ifndef MAINWIDET_H
#define MAINWIDET_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfoList>
#include <QDateTime>
#include <QProgressDialog>
#include <qprogress_thread.h>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#define DBID "EIS"
#define DBPW "wisolfab!"
#define FTPID "eis"
#define FTPPW "wisolfab!"
namespace Ui {
class Mainwidet;
}

class Mainwidet : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwidet(QWidget *parent = 0);

    int update_file_count;
    void update_check();
    QProcess Process;
    bool start_popup_flag;
    QString buildCpu;
    int local_version;
    int remote_version;
    QString update_content;
    QSqlDatabase db;
    ~Mainwidet();


    bool getStart_popup_flag() const;
    void setStart_popup_flag(bool value);

private slots:
    void on_confirm_btn_clicked();
    void progress_update_value(int a);

    void on_progressBar_valueChanged(int value);

private:
    Ui::Mainwidet *ui;
};

#endif // MAINWIDET_H
