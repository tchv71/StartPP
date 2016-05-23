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
    cmfcpropertygrid.cpp \
    StartPP/Afx/afxpropertygridctrl.cpp

HEADERS  += mainwindow.h \
    cpropertywnd.h \
    cmfcpropertygridproperty.h \
    cmfcpropertygrid.h \
    StartPP/Afx/afxcolorbar.h \
    StartPP/Afx/afxcontrolbarutil.h \
    StartPP/Afx/afxctrlcontainer.h \
    StartPP/Afx/afxdrawmanager.h \
    StartPP/Afx/afxmaskededit.h \
    StartPP/Afx/afxmenuimages.h \
    StartPP/Afx/afxpopupmenu.h \
    StartPP/Afx/afxpropertygridctrl.h \
    StartPP/Afx/afxshellmanager.h \
    StartPP/Afx/afxspinbuttonctrl.h \
    StartPP/Afx/afxtagmanager.h \
    StartPP/Afx/afxtoolbarcomboboxbutton.h \
    StartPP/Afx/afxvisualmanager.h \
    StartPP/Afx/afxwinappex.h \
    StartPP/Afx/stdafx.h \
    StartPP/Afx/afxcmn.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
