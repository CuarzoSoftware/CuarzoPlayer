#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include "library.h"
#include "titlebar.h"
#include "topbar.h"
#include "middleview.h"
#include "bottombar.h"
#include "id.h"
#include "player.h"
#include "json.hpp"
#include "jsort.h"
#include "login.h"
#include "googledrive.h"
#include "maths.h"
#include "pix.h"

using json = nlohmann::json;


class PlayerWindow : public QWidget
{
    Q_OBJECT
public:
    QString viewMode;
    QString playingFrom;
    Maths math;
    ID id;
    JSort s;
    Pix p;
    PlayerWindow();
    GoogleDrive *drive;
    Login *login = new Login();
    Player *player = new Player();
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QWidget *frame = new QWidget();
    TitleBar *titleBar = new TitleBar();
    MiddleView *middleView = new MiddleView();
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
    Library *library = new Library();
    TopBar *topBar = new TopBar();
    BottomBar *bottomBar = new BottomBar();
    bool eventFilter(QObject *obj, QEvent *event);
public slots:
    void addMusic();
    void leftItemSelected(QString);
    void artistSelected(json data);
    void setLibrary(QString location);
    void playFromArtist(json);
    void loggedIn(QString token, QString refresh);
    void setUserInfo();
    void setupSettings();
    void imageReady();

};

#endif // PLAYERWINDOW_H
