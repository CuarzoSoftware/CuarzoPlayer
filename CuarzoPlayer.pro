#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T14:58:11
#
#-------------------------------------------------

QT       += core
QT       += multimedia
QT       += svg
QT       += network
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuarzoPlayer
TEMPLATE = app
ICON = icon.icns

macx {

    INCLUDEPATH += "../CuarzoPlayer/lib/mac/include/taglib/"
    INCLUDEPATH += "/Library/Frameworks/GStreamer.framework/Headers/"

    LIBS += \
        -L/usr/local/lib \
        -L$$_PRO_FILE_PWD_/lib/mac/lib \
        -ltag\
        -lz\
        -lobjc

    LIBS += -framework Foundation
    LIBS += -framework AppKit
    LIBS += -framework GStreamer

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
    artistlistitem.cpp \
    artistview.cpp \
    artistviewtitle.cpp \
    album.cpp \
    albumsong.cpp \
    player.cpp \
    login.cpp \
    googledrive.cpp



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
    artistlistitem.h \
    pix.h \
    artistview.h \
    artistviewtitle.h \
    album.h \
    albumsong.h \
    json.hpp \
    player.h \
    jsort.h \
    login.h \
    googledrive.h \
    network.h \
    maths.h \
    pie.h \
    filemanager.h \
    reply.h




RESOURCES += \
    resources.qrc





