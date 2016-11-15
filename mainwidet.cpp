#include "mainwidet.h"
#include "ui_mainwidet.h"

Mainwidet::Mainwidet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidet)
{
    ui->setupUi(this);
    if(QSysInfo::buildCpuArchitecture() == "i386"){
        buildCpu = "32";
    }else if(QSysInfo::buildCpuArchitecture() == "x86_64") {
        buildCpu = "64";
    }
    QDir EIS_forder(qApp->applicationDirPath()+'/'+QString("EIS_%1bit").arg(buildCpu));
    if(!EIS_forder.exists()){
        EIS_forder.mkdir(QString("EIS_%1bit").arg(buildCpu));
    }

    db = QSqlDatabase::addDatabase("QMYSQL","join_update_db");
    db.setHostName("fabsv.wisol.co.kr");
    db.setPort(3306);
    db.setUserName(DBID);
    db.setPassword(DBPW);
    db.setDatabaseName("FAB");
    if(!db.open()){
       qDebug()<<db.lastError().text();
    }
    QSqlQuery query(db);
    query.exec("select * from version_manager");
    query.next();
    ui->update_content->setHtml(query.value("content").toString());
    local_version = 0;
    remote_version = 0;
    QSettings local_version_info("version_info.ini",QSettings::IniFormat);
    local_version_info.beginGroup("version_info");
    local_version = local_version_info.value("version").toInt();
    local_version_info.endGroup();

    QSettings server_version_info("\\\\fabsv.wisol.co.kr\\FabProgram\\version_info.ini",QSettings::IniFormat);
    server_version_info.beginGroup("version_info");
    remote_version = server_version_info.value("version").toInt();
    server_version_info.endGroup();

    if(local_version == remote_version){
        setStart_popup_flag(false);
        Process.startDetached(QString("EIS_%1bit\\main.exe").arg(buildCpu));
        return ;
    }else {

    }

    update_file_count = 0;
    update_check();
    if(update_file_count == 0){
        setStart_popup_flag(false);
        Process.startDetached(QString("EIS_%1bit\\main.exe").arg(buildCpu));
        return ;
    }else {
        setStart_popup_flag(true);
    }
    QProgress_thread *thread = new QProgress_thread();
    ui->progressBar->setMaximum(update_file_count);
    thread->setUpdate_file_count(update_file_count);
    connect(thread,SIGNAL(progress_value_update(int)),this,SLOT(progress_update_value(int)));
    thread->start();
}


void Mainwidet::update_check()
{
    QDir DIR_src(QString("\\\\10.20.10.230\\FabProgram\\EIS_%1bit\\").arg(buildCpu));
    QFileInfoList list_src = DIR_src.entryInfoList();
    QDir DIR_des(qApp->applicationDirPath()+'/'+QString("EIS_%1bit/").arg(buildCpu));
    QFileInfoList list_des = DIR_des.entryInfoList();
    for(int i=0;i<list_src.size();i++){
         bool havefile_flag = false;

         if(list_src.at(i).fileName() == "." || list_src.at(i).fileName() == ".."){

              continue;
         }
         for(int j=0;j<list_des.size();j++){
              if(list_src.at(i).fileName() == list_des.at(j).fileName()){
                   havefile_flag = true;
                   qint64 between = list_src.at(i).lastModified().secsTo(list_des.at(j).lastModified());
                   if(between<0){
                        if(list_src.at(i).isDir()){
                            update_file_count++;
                            //copyPath(list_src.at(i).absoluteFilePath(),list_des.at(j).absoluteFilePath(),true);
                        }else {
                            //QFile srccopyfile(list_src.at(i).absoluteFilePath());
                            //QFile removefile(list_des.at(j).absoluteFilePath());
                            update_file_count++;
                            //removefile.remove();
                            //srccopyfile.copy(list_des.at(j).absoluteFilePath());
                        }
                   }
              }
            }
            if(!havefile_flag){
                qDebug()<<list_src.at(i).fileName();
                if(list_src.at(i).fileName() == "." || list_src.at(i).fileName() == ".."){
                    continue;
                }
                if(list_src.at(i).isDir()){
                    update_file_count++;
                }else {
                    update_file_count++;
                }
            }
    }
}

bool Mainwidet::getStart_popup_flag() const
{
    return start_popup_flag;
}

void Mainwidet::setStart_popup_flag(bool value)
{
    start_popup_flag = value;
}
Mainwidet::~Mainwidet()
{
    delete ui;
}

void Mainwidet::on_confirm_btn_clicked()
{
    Process.startDetached(QString("EIS_%1bit\\main.exe").arg(buildCpu));
    close();
}

void Mainwidet::progress_update_value(int a)
{
    ui->progressBar->setValue(a);
}

void Mainwidet::on_progressBar_valueChanged(int value)
{
    if(value == update_file_count){
        ui->confirm_btn->setEnabled(true);
    }
}
