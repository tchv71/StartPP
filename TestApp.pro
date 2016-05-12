#-------------------------------------------------
#
# Project created by QtCreator 2016-05-08T12:16:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpropertywnd.cpp \
    cmfcpropertygridproperty.cpp \
    cmfcpropertygrid.cpp

HEADERS  += mainwindow.h \
    cpropertywnd.h \
    cmfcpropertygridproperty.h \
    cmfcpropertygrid.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
