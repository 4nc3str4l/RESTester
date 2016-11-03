#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T21:20:57
#
#-------------------------------------------------

QT += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += network

TARGET = ComTester
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    highlighter.cpp

HEADERS  += mainwindow.h \
    highlighter.h

FORMS    += mainwindow.ui

win32:RC_ICONS += index.ico
