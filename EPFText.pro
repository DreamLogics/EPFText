#-------------------------------------------------
#
# Project created by QtCreator 2014-04-08T15:44:30
#
#-------------------------------------------------

QT       += gui

TARGET = EPFText
TEMPLATE = lib

DEFINES += EPFTEXT_LIBRARY

include(../QOPSLib/src/QOPSLib.pri)
include(src/EPFText.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}
