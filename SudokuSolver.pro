#-------------------------------------------------
#
# Project created by QtCreator 2013-11-17T23:39:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuSolver
TEMPLATE = app


SOURCES += main.cpp\
        sudokusolver.cpp \
    numberwidget.cpp \
    numberpicker.cpp \
    clickablelabel.cpp

HEADERS  += sudokusolver.h \
    numberwidget.h \
    numberpicker.h \
    clickablelabel.h

FORMS    += sudokusolver.ui

QMAKE_CXXFLAGS += -std=c++11
