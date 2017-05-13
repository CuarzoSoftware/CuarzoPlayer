#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T14:58:11
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuarzoPlayer
TEMPLATE = app
ICON = icon.icns

macx {

    INCLUDEPATH += $$_PRO_FILE_PWD_/lib/mac/include/taglib/
    LIBS += \
        -L/usr/local/lib \
        -L$$_PRO_FILE_PWD_/lib/mac/lib \
        -ltag\
        -lz\
        -lobjc
    LIBS += -framework Foundation
    LIBS += -framework AppKit

    OBJECTIVE_SOURCES += objectivec.mm
    HEADERS +=  objectivec.h
}
unix:!macx {

    INCLUDEPATH += $$_PRO_FILE_PWD_/lib/linux/include/taglib/

    LIBS += \
        -L/usr/local/lib \
        -L$$_PRO_FILE_PWD_/lib/linux/lib \
        -ltag\
        -lz
}

win32 {

}


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
    opbutton.cpp \
    bottombar.cpp \
    croplabel.cpp \
    playerwindow.cpp \
    songinfo.cpp \
    playerbuttons.cpp \
    timebar.cpp \
    volumebar.cpp \
    topbar.cpp \
    library.cpp \
    id.cpp \
    selectlist.cpp \
    selectlistitem.cpp \
    icon.cpp \
    menu.cpp \
    userpicture.cpp \
    storagebar.cpp \
    searchbar.cpp \
    middleview.cpp \
    titlebar.cpp \
    leftbar.cpp \
    leftbaritem.cpp \
    artistslist.cpp \
    artistlistitem.cpp


HEADERS  += \
    opbutton.h \
    bottombar.h \
    croplabel.h \
    playerwindow.h \
    songinfo.h \
    playerbuttons.h \
    timebar.h \
    volumebar.h \
    topbar.h \
    library.h \
    id.h \
    selectlist.h \
    selectlistitem.h \
    icon.h \
    menu.h \
    userpicture.h \
    storagebar.h \
    searchbar.h \
    middleview.h \
    titlebar.h \
    leftbar.h \
    leftbaritem.h \
    artistslist.h \
    artistlistitem.h



RESOURCES += \
    resources.qrc

