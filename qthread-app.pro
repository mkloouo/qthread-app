#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T12:41:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qthread-app
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
main.cpp \
ballphysics.cpp \
ballwidget.cpp \
ballcontroller.cpp \
ballwindow.cpp \
balldb.cpp

HEADERS += \
ballphysics.h \
ballwidget.h \
ballcontroller.h \
ballwindow.h \
balldb.h

FORMS += \
ballwindow.ui
