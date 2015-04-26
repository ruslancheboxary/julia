#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T21:09:52
#
#-------------------------------------------------

QT       += core gui

CONFIG +=  c++11
LIBS = -lm

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        ssr.cpp

HEADERS  += mainwindow.h \
        ssr.h

FORMS    += mainwindow.ui
