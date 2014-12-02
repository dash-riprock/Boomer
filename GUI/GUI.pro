#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T03:03:45
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

INCLUDEPATH += /home/fantasticdan/TWS/Strats/ \
               /home/fantasticdan/TWS/Strats/Boomer/ \
               /home/fantasticdan/TWS/Strats/Boomer/GUI/\
               /home/fantasticdan/TWS/Strats/Boomer/src/\
               /home/fantasticdan/TWS/Strats/Boomer/Everything/

SOURCES += main.cpp\
        mainwindow.cpp \
    market.cpp \
    strategy.cpp \
    doubleclickbutton.cpp

HEADERS  += mainwindow.h \
    market.h \
    strategy.h \
    doubleclickbutton.h

FORMS    += mainwindow.ui
