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

    INCLUDEPATH += "../CuarzoPlayer/lib/mac/library/libtag/include/"
    INCLUDEPATH += "../CuarzoPlayer/lib/mac/frameworks/VLCQtCore.framework/Headers/"


    LIBS += \
        -L$$_PRO_FILE_PWD_/lib/mac/library/libtag/lib \
        -L$$_PRO_FILE_PWD_/lib/mac/library/portaudio/lib \
        -ltag\
        -lportaudio\
        -lz\
        -lobjc

    LIBS += -framework Foundation
    LIBS += -framework AppKit
    LIBS += -framework VLCQtCore

    OBJECTIVE_SOURCES += objectivec.mm
    HEADERS +=  objectivec.h
}
unix:!macx {

    INCLUDEPATH += $$_PRO_FILE_PWD_/lib/linux/include/taglib/
    INCLUDEPATH += $$_PRO_FILE_PWD_/lib/linux/include/VLCQtCore/

    LIBS += \
        -L/usr/local/lib \
        -L$$_PRO_FILE_PWD_/lib/linux/lib \
        -ltag\
        -lz\
        -lVLCQtCore
}

win32 {

}


SOURCES += main.cpp\
    bottombar.cpp \
    playerwindow.cpp \
    playerbuttons.cpp \
    timebar.cpp \
    volumebar.cpp \
    library.cpp \
    menu.cpp \
    searchbar.cpp \
    titlebar.cpp \
    leftbar.cpp \
    leftbaritem.cpp \
    artistlistitem.cpp \
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
    artistlistitem.h \
    pix.h \
    artistview.h \
    artistviewtitle.h \
    album.h \
    albumsong.h \
    player.h \
    login.h \
    googledrive.h \
    network.h \
    maths.h \
    pie.h \
    filemanager.h \
    reply.h \
    init.h \
    songmenu.h \
    tageditor.h \
    tableview.h




RESOURCES += \
    resources.qrc





