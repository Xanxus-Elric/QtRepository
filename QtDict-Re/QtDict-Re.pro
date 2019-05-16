#-------------------------------------------------
#
# Project created by QtCreator 2019-05-16T10:25:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDict-Re
TEMPLATE = app


SOURCES += main.cpp\
        maindictwidget.cpp \
    searchwidget.cpp

HEADERS  += maindictwidget.h \
    searchwidget.h

RESOURCES += \
    dictfile.qrc

CONFIG += resources_big
