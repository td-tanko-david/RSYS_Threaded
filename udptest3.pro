#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T12:55:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = udptest3
TEMPLATE = app
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    sender.cpp \
    receiver.cpp \
    mytextedit.cpp \
    keyenterreceiver.cpp \
    updater.cpp

HEADERS += \
        mainwindow.h \
    sender.h \
    receiver.h \
    mytextedit.h \
    keyenterreceiver.h \
    updater.h

FORMS += \
        mainwindow.ui
