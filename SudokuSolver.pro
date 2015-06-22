#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T14:33:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuSolver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    models/matrix.cpp \
    models/sudoku.cpp

HEADERS  += mainwindow.h \
    models/matrix.h \
    models/sudoku.h

FORMS    += mainwindow.ui
