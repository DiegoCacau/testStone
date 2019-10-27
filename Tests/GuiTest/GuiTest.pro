QT += core gui
QT += widgets testlib
QT += networkauth
QT += multimedia

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_guitest.cpp

INCLUDEPATH += ../../
LIBS += \
       -L../../

VPATH += ../../
FORMS += \
    loggedwindow.ui \
    mainwindow.ui
SOURCES += \
    loggedwindow.cpp \
    mainwindow.cpp \
    musiclists.cpp \
    spofity.cpp

HEADERS += \
    loggedwindow.h \
    mainwindow.h \
    musiclists.h \
    secretkeys.h \
    spofity.h

