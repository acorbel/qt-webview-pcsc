#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T21:30:04
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Multipass
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    control.cpp \
    mainpage.cpp

HEADERS  += mainwindow.h \
    wintypes.h \
    winscard.h \
    pcsclite.h \
    reader.h \
    control.h \
    mainpage.h

LIBS += -lpcsclite
