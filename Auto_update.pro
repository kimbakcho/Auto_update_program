#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T15:50:42
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Auto_update
TEMPLATE = app

RC_FILE = myapp.rc

QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO

SOURCES += main.cpp\
        mainwidet.cpp \
    qprogress_thread.cpp

HEADERS  += mainwidet.h \
    qprogress_thread.h

FORMS    += mainwidet.ui

RESOURCES += \
    res.qrc
