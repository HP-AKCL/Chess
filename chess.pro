#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T18:36:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess_2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    board.cpp \
    stone.cpp \
    netgame.cpp

HEADERS  += widget.h \
    board.h \
    stone.h \
    netgame.h

FORMS    += widget.ui
