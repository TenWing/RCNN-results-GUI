#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T10:49:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RCNN-results
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        tinyxml2.cpp \
        image.cpp \
    imageloader.cpp \
    resultset.cpp \
    resultsadder.cpp \
    imagedisplayer.cpp \
    bboxdisplayer.cpp \
    imagewidget.cpp

HEADERS  += mainwindow.h \
        tinyxml2.h \
        image.h \
    imageloader.h \
    resultset.h \
    resultsadder.h \
    imagedisplayer.h \
    bboxdisplayer.h \
    imagewidget.h
