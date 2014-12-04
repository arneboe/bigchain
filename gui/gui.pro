#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T21:38:21
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fade.cpp \
    strobe.cpp

HEADERS  += mainwindow.h \
    fade.h \
    modeUi.h \
    strobe.h

FORMS    += mainwindow.ui \
    fade.ui \
    strobe.ui
