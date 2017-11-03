#-------------------------------------------------
#
# Project created by QtCreator 2017-11-01T22:07:44
#
#-------------------------------------------------

QT = core
QT += serialport
QT -= gui

TARGET = cfa533screens
TEMPLATE = lib
CONFIG += staticlib

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
    dialogs/confirmation.cpp

HEADERS += \
    dialogs/confirmation.h \
    screen_interface.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../cfa533/ -lcfa533

INCLUDEPATH += $$PWD/../cfa533
DEPENDPATH += $$PWD/../cfa533

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../cfa533/libcfa533.a
