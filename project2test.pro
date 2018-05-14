#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T14:49:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project2test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        start.cpp \
    choosewindow.cpp \
    solvesudokufunction.cpp \
    chooselevel.cpp \
    playsudoku.cpp \
    solvesudoku.cpp \
    difficultyclass.cpp \
    settime.cpp

HEADERS += \
        start.h \
    choosewindow.h \
    solvesudokufunction.h \
    chooselevel.h \
    playsudoku.h \
    solvesudoku.h \
    difficultyclass.h \
    settime.h

FORMS += \
        start.ui

DISTFILES += \
    su_question.txt \
    ../../if_finish_flag_172465.png

RESOURCES += \
    sudoquestion.qrc \
    image.qrc
