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
#include <QList>
#include "library.h"
#include "titlebar.h"
#include "topbar.h"
#include "middleview.h"
#include "bottombar.h"
#include "player.h"
#include "login.h"
//#include "googledrive.h"
#include "maths.h"
#include "pix.h"
#include "croplabel.h"
#include "album.h"
#include "albumsong.h"
#include "artistview.h"
#include "artistlistitem.h"
#include "songmenu.h"
#include "tageditor.h"

#ifdef Q_OS_MAC
    #include "objectivec.h"
#endif


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
    QString currentArtist;
    QString viewMode;
    QString playingFrom;
    QString libraryLocation;
    QList<ArtistListItem*> artistListItems;
    QList<Album*> albums;
    QList<AlbumSong*> albumSongs;
    QList<AlbumSong*> selectedAlbumSongs;
    QVariantList songsToDelete;
    bool logged;
    bool goingToExit = false;


    //UTILITIES
    Pix p;
    Maths math;
    QDir d;

    //BRAINS
   // GoogleDrive *drive;
    Library *library;
    Player *player = new Player();

    //ELEMENTS
    TopBar *topBar = new TopBar();
    QWidget *frame = new QWidget();
    TitleBar *titleBar = new TitleBar();
    TagEditor *tagEditor = new TagEditor();
    BottomBar *bottomBar = new BottomBar();
    MiddleView *middleView = new MiddleView();
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::TopToBottom,frame);


    //EVENTS
    bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent(QCloseEvent * event);

public slots:

    //CONSTRUCTORS
    void setupUI();
    void setupLibrary(Library *lib, QString token, QString refresh);
    void setupViewsAndWidgets();
    void setupTopBarMenus();
    void setupConnections();
    void setupSettings();

    void setUserInfo();
    void setLibraryLocation(QString);

    //METHODS
    void refreshLibrary();
    void playFromArtist(QString SongId);
    void logout();
    void quitApp();
    void showSongMenu(QString);
    void deleteSongsFromLocal();
    void showTagEditor();
    void songsEdited(QVariantList);


    //FINDERS
    bool existArtistListItem(QString);
    bool existAlbum(QString,QString);
    bool existAlbumSong(QString);
    ArtistListItem *getArtistListItem(QString);
    Album *getAlbum(QString,QString);
    AlbumSong *getAlbumSong(QString);
    QVariantMap getSong(QString id);

    //EVENTS
    void leftItemSelected(QString);
    void artistSelected(QString);
    void imageReady();
    void showSongPlaying(QVariantMap songData);
    void deletedFromBoth(QString);

    //SONGS
    void albumSongSelected(QString songId);
    void songRightClicked(QString songId);
    void songDeletionEnd();
    void createPlayList(QString key, QString from);
    void shuffleArtist();

signals:
    void showLoginWindow();
};

#endif // PLAYERWINDOW_H
