#-------------------------------------------------
#
# Project created by QtCreator 2014-04-08T15:44:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EPFText
TEMPLATE = app

include(../../QOPSLib/src/QOPSLib.pri)
include(../src/EPFText.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    epftextwidget.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    epftextwidget.h
