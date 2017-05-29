#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMenuBar>
#include <QMap>
#include "library.h"
#include "titlebar.h"
#include "topbar.h"
#include "middleview.h"
#include "bottombar.h"
#include "player.h"
#include "json.hpp"
#include "jsort.h"
#include "login.h"
#include "googledrive.h"
#include "maths.h"
#include "pix.h"
#include "croplabel.h"


#ifdef Q_OS_MAC
    #include "objectivec.h"
#endif

using json = nlohmann::json;

class PlayerWindow : public QMainWindow
{
    Q_OBJECT
public:

    PlayerWindow(Library*,QString,QString);

    //MENU ITEMS
    QMenu *fileMenu;
    QMenu *accountMenu;
    QAction *addMusicAct;
    QAction *loginAct;
    QAction *logoutAct;
    QAction *exitAct;

    //VARIABLES
    QString viewMode;
    QString playingFrom;
    QString libraryLocationSelected;
    QMap<QString, ArtistView*> artistViews;
    QMap<QString, Album*> albums;
    QMap<int, AlbumSong*> albumSongs;
    bool goingToExit = false;


    //UTILITIES
    Pix p;
    JSort s;
    Maths math;

    //BRAINS
    GoogleDrive *drive;
    Library *library;
    Player *player = new Player();

    //ELEMENTS
    ArtistsList *artistList;
    TopBar *topBar = new TopBar();
    QWidget *frame = new QWidget();
    TitleBar *titleBar = new TitleBar();
    BottomBar *bottomBar = new BottomBar();
    MiddleView *middleView = new MiddleView();
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::TopToBottom,frame);


    //EVENTS
    bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent(QCloseEvent * event);

public slots:

    //CONSTRUCTORS
    void setLibrary();
    void setUserInfo();
    void setLibraryLocation(QString);

    //METHODS
    void refreshLibrary();
    void playFromArtist(json);
    void logout();
    void quitApp();

    //EVENTS
    void leftItemSelected(QString);
    void artistSelected(QString);
    void imageReady();
    void showSongPlaying(json);

signals:
    void showLoginWindow();
};

#endif // PLAYERWINDOW_H
