#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T11:34:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zoltar
TEMPLATE = app


SOURCES += main.cpp\
    managers/gamemanager.cpp \
    states/mainmenustate.cpp \
    states/gamestate.cpp \
    states/gameoverstate.cpp

HEADERS  += \
    managers/gamemanager.h \
    states/mainmenustate.h \
    states/gamestate.h \
    data/riddle.h \
    states/gameoverstate.h

RESOURCES += \
    resources.qrc
