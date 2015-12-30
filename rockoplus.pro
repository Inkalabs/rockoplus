#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T19:50:32
#
#-------------------------------------------------

QT       += core gui multimedia webkitwidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rockoplus
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rockosettings.cpp \
    playlistloader.cpp \
    song.cpp

HEADERS  += mainwindow.h \
    rockosettings.h \
    playlistloader.h \
    song.h

FORMS    += mainwindow.ui
