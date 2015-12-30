#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T19:50:32
#
#-------------------------------------------------

QT       += core gui multimedia webkitwidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rockoplus
TEMPLATE = app


SOURCES += sources/main.cpp\
        sources/mainwindow.cpp \
    sources/rockosettings.cpp \
    sources/playlistloader.cpp \
    sources/song.cpp

HEADERS  += headers/mainwindow.h \
    headers/rockosettings.h \
    headers/playlistloader.h \
    headers/song.h

FORMS    += ui/mainwindow.ui



