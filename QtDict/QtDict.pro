#-------------------------------------------------
#
# Project created by QtCreator 2019-05-13T21:23:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDict
TEMPLATE = app


SOURCES += main.cpp\
        dictwidget.cpp \
    convertwidget.cpp

HEADERS  += dictwidget.h \
    convertwidget.h

RESOURCES += \
    textfile.qrc \
    icon.qrc

CONFIG += resources_big
