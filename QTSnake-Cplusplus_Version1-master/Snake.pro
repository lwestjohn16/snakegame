#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T23:06:28
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app

RC_ICONS = icon.ico

SOURCES += main.cpp\
    food.cpp \
    game.cpp \
    snake.cpp

HEADERS  += \
    food.h \
    game.h \
    snake.h

FORMS    +=

DISTFILES += \
    food.png \
    snake.png \
    food1.png \
    food2.png \
    snake1.png

RESOURCES += \
    images.qrc \
    sound.qrc
