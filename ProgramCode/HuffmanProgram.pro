#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T01:05:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuffmanProgram
TEMPLATE = app


SOURCES += main.cpp\
        zgui.cpp \
    txtgrabber.cpp \
    huffman.cpp

HEADERS  += zgui.h \
    txtgrabber.h \
    huffman.h

FORMS    += zgui.ui \
    txtgrabber.ui

RESOURCES += \
    Resources/imagedirectory.qrc
