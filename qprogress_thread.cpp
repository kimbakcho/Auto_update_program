#include "qprogress_thread.h"

QProgress_thread::QProgress_thread()
{

}
void QProgress_thread::run()
{
    start_update();
}

bool QProgress_thread::copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory)
{
    QDir originDirectory(sourceDir);

    if (! originDirectory.exists())
    {
        return false;
    }

    QDir destinationDirectory(destinationDir);

    if(destinationDirectory.exists() && !overWriteDirectory)
    {
        return false;
    }
    else if(destinationDirectory.exists() && overWriteDirectory)
    {
        destinationDirectory.removeRecursively();
    }

    originDirectory.mkpath(destinationDir);

    foreach (QString directoryName, originDirectory.entryList(QDir::Dirs | \
                                                              QDir::NoDotAndDotDot))
    {
        QString destinationPath = destinationDir + "/" + directoryName;
        originDirectory.mkpath(destinationPath);
        copyPath(sourceDir + "/" + directoryName, destinationPath, overWriteDirectory);
    }

    foreach (QString fileName, originDirectory.entryList(QDir::Files))
    {
        QFile::copy(sourceDir + "/" + fileName, destinationDir + "/" + fileName);
    }

    /*! Possible race-condition mitigation? */
    QDir finalDestination(destinationDir);
    finalDestination.refresh();

    if(finalDestination.exists())
    {
        return true;
    }
    return false;
}

void QProgress_thread::update_file_logic()
{
    QDir DIR_src(QString("\\\\fabsv.wisol.co.kr\\FabProgram\\EIS_%1bit\\").arg(buildCpu));
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
                            copyPath(list_src.at(i).absoluteFilePath(),list_des.at(j).absoluteFilePath(),true);
                            current_update_file_count++;
                            emit progress_value_update(current_update_file_count);
                        }else {
                            QFile srccopyfile(list_src.at(i).absoluteFilePath());
                            QFile removefile(list_des.at(j).absoluteFilePath());
                            removefile.remove();
                            srccopyfile.copy(list_des.at(j).absoluteFilePath());
                            current_update_file_count++;
                            emit progress_value_update(current_update_file_count);
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
                    DIR_des.mkdir(list_src.at(i).fileName());
                    copyPath(list_src.at(i).absoluteFilePath(),DIR_des.absolutePath()+'/'+list_src.at(i).fileName(),true);
                    current_update_file_count++;
                    emit progress_value_update(current_update_file_count);
                }else {
                    QFile srccopyfile(list_src.at(i).absoluteFilePath());
                    srccopyfile.copy(DIR_des.absolutePath()+'/'+list_src.at(i).fileName());
                    current_update_file_count++;
                    emit progress_value_update(current_update_file_count);
                }
            }
        }
}


void QProgress_thread::start_update()
{
    if(QSysInfo::buildCpuArchitecture() == "i386"){
        buildCpu = "32";
    }else if(QSysInfo::buildCpuArchitecture() == "x86_64") {
        buildCpu = "64";
    }
    current_update_file_count = 0;
    update_file_logic();
}

int QProgress_thread::getUpdate_file_count() const
{
    return update_file_count;
}

void QProgress_thread::setUpdate_file_count(int value)
{
    update_file_count = value;
}


