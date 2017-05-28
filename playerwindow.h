#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMenuBar>
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

#ifdef Q_OS_MAC
    #include "objectivec.h"
#endif

using json = nlohmann::json;

class PlayerWindow : public QMainWindow
{
    Q_OBJECT
public:

    PlayerWindow();

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
    bool goingToExit = false;
    bool cloudConnectionsMade = false;
    bool globalConnectionsMade = false;

    //UTILITIES
    Pix p;
    JSort s;
    Maths math;

    //BRAINS
    GoogleDrive *drive;
    Player *player = new Player();
    Library *library = new Library();

    //ELEMENTS
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
    void setupSettings();
    void createActions();
    void createMenus();

    //METHODS
    void playFromArtist(json);
    void showLoginWindow();
    void logout();
    void quitApp();

    //EVENTS
    void loggedIn(QString token, QString refresh);
    void leftItemSelected(QString);
    void artistSelected(json data);
    void imageReady();

};

#endif // PLAYERWINDOW_H
