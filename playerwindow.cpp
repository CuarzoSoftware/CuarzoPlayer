#include "playerwindow.h"
#include "croplabel.h"
#include <QCloseEvent>

extern QString path;


/* -------------------------------*/
/* Creates the player main window */
/* -------------------------------*/

PlayerWindow::PlayerWindow()
{
    #ifdef Q_OS_MAC
        ObjectiveC *obc = new ObjectiveC();
        obc->Display(winId());
        delete obc;
    #endif

    QRect screen = QApplication::desktop()->screenGeometry();
    setContextMenuPolicy(Qt::NoContextMenu);
    setFocusPolicy(Qt::ClickFocus);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMinimumSize(1000,600);
    move(screen.width()/2-500,screen.height()/2-300);
    setCentralWidget(frame);
    installEventFilter(this);
    frame->setObjectName("MainFrame");
    frame->setStyleSheet("#MainFrame{background:#FFF}");
    frameLayout->setMargin(0);
    frameLayout->setSpacing(0);
    frameLayout->addWidget(topBar);
    frameLayout->addWidget(middleView);
    frameLayout->addWidget(bottomBar);

    createActions();
    createMenus();

    if(!library->settings["init"])
    {
        showLoginWindow();
    }
    else{
        setupSettings();
    }
}

/* ---------------------------------------*/
/* Save the user data when user is logged */
/* ---------------------------------------*/

void PlayerWindow::loggedIn(QString token, QString refresh)
{
    library->settings["token"] = token.toStdString();
    library->settings["restoreToken"] = refresh.toStdString();
    library->settings["init"] = true;
    library->saveSettings();
    setupSettings();
}

/* -----------------------------------------------------------------*/
/* Create connections and setup the saved setting to child elements */
/* -----------------------------------------------------------------*/

void PlayerWindow::setupSettings()
{

    fileMenu->setEnabled(true);
    accountMenu->setEnabled(true);

    if(library->settings["token"] != "NO"){

        logoutAct->setVisible(true);
        loginAct->setVisible(false);
        library->library["logged"] = true;
        topBar->modeList->show();
        topBar->addAccount->hide();
        topBar->storageBar->show();

        if(!cloudConnectionsMade)
        {
            drive = new GoogleDrive(library->settings);

            //Google Drive

            connect(middleView->artistView,SIGNAL(syncSong(json)),drive,SLOT(syncSong(json)));
            connect(middleView->artistView,SIGNAL(sendCancelSongUpload(int)),drive,SLOT(cancelSongUpload(int)));
            connect(drive,SIGNAL(songUploaded(json)),library,SLOT(songUploaded(json)));
            connect(drive,SIGNAL(songUploaded(json)),middleView->artistView,SLOT(songUploaded(json)));
            connect(drive,SIGNAL(sendUserInfo(json)),library,SLOT(setUserInfo(json)));
            connect(drive,SIGNAL(sendCloud(json)),library,SLOT(getCloud(json)));
            connect(library,SIGNAL(userInfoChanged()),this,SLOT(setUserInfo()));
            connect(drive,SIGNAL(imageReady()),this,SLOT(imageReady()));
            connect(drive,SIGNAL(sendSongUploadProgress(int,int)),middleView->artistView,SLOT(setSongUploadPercent(int,int)));

            //DELETE SONGS
            connect(library,SIGNAL(deleteFromCloud(json)),drive,SLOT(deleteSong(json)));
            connect(library,SIGNAL(deleteFromBoth(json)),drive,SLOT(deleteSong(json)));
            cloudConnectionsMade = true;
        }

        setUserInfo();
    }
    else{

        loginAct->setVisible(true);
        logoutAct->setVisible(false);
        topBar->modeList->hide();
        topBar->userPicture->image->setPixmap(QPixmap(":res/img/user.svg"));
        topBar->addAccount->show();
        topBar->storageBar->hide();
        if(!globalConnectionsMade) connect(topBar->addAccount,SIGNAL(released()),this,SLOT(showLoginWindow()));
    }

    if(!globalConnectionsMade)
    {
        //DISPLAY MODE

        connect(topBar->modeList,SIGNAL(sendSelected(QString)),this,SLOT(setLibraryLocation(QString)));
        connect(middleView->artistsList,SIGNAL(hideArtistView(int)),middleView->artistView->f,SLOT(fadeOut(int)));
        connect(middleView->artistsList,SIGNAL(showArtistView(int)),middleView->artistView->f,SLOT(fadeIn(int)));

        //ADD MUSIC

        connect(topBar->addButton,SIGNAL(released()),library,SLOT(startMusicAdder()));
        connect(topBar->addButton,SIGNAL(released()),topBar->pie,SLOT(show()));
        connect(library,SIGNAL(songAddCanceled()),topBar->pie,SLOT(hide()));
        connect(library,SIGNAL(songAddProgress(int)),topBar->pie,SLOT(setPercent(int)));
        connect(library,SIGNAL(songAddComplete()),topBar->pie,SLOT(hide()));
        connect(library,SIGNAL(songAddComplete()),this,SLOT(setLibrary()));

        //DELETE SONGS

        connect(middleView->artistView,SIGNAL(deleteSongs(QList<json>,QString)),library,SLOT(deleteSongs(QList<json>,QString)));
        connect(library,SIGNAL(deleteFromBoth(json)),middleView->artistView,SLOT(hideSong(json)));
        connect(library,SIGNAL(deleteFromLocal(json)),middleView->artistView,SLOT(changeSong(json)));

        connect(library,SIGNAL(deleteFromCloud(json)),middleView->artistView,SLOT(changeSong(json)));

        //SONGS EVENTS

        connect(middleView->artistView,SIGNAL(sendSongPlayed(json)),this,SLOT(playFromArtist(json)));
        connect(middleView->leftBar,SIGNAL(sendSelected(QString)),this,SLOT(leftItemSelected(QString)));
        connect(middleView->artistsList,SIGNAL(sendSelectedArtist(json)),this,SLOT(artistSelected(json)));

        //PLAYER EVENTS

        connect(player,SIGNAL(songPlaying(json)),bottomBar->songInfo,SLOT(setData(json)));
        connect(player,SIGNAL(songPlaying(json)),middleView->artistView,SLOT(songPlayed(json)));
        connect(player,SIGNAL(sendTimePosition(float,float)),bottomBar->timeBar,SLOT(getTimePosition(float,float)));
        connect(player,SIGNAL(sendState(bool)),bottomBar->playerButtons,SLOT(setPlay(bool)));
        connect(bottomBar->timeBar,SIGNAL(positionChanged(float)),player,SLOT(setTime(float)));
        connect(bottomBar->volumeBar->slider,SIGNAL(valueChanged(int)),player->player->audio(),SLOT(setVolume(int)));
        connect(bottomBar->playerButtons->play,SIGNAL(released()),player,SLOT(playPause()));
        connect(bottomBar->playerButtons->back,SIGNAL(released()),player,SLOT(playBack()));
        connect(bottomBar->playerButtons->next,SIGNAL(released()),player,SLOT(playNext()));
        connect(bottomBar,SIGNAL(sendShuffleMode(bool)),player,SLOT(setShuffle(bool)));
        connect(bottomBar,SIGNAL(sendLoopMode(int)),player,SLOT(setLoopMode(int)));

        globalConnectionsMade = true;
    }

    //SET SETTINGS

    bottomBar->volumeBar->slider->setValue(library->settings["volume"]);
    bottomBar->volumeBar->positionChanged(library->settings["volume"]);
    bottomBar->setLoopMode(library->settings["loop"]);
    bottomBar->setShuffleMode(library->settings["shuffle"]);
    player->settings = library->settings;

    middleView->leftBar->itemSelected("artists");

    libraryLocationSelected = "local";
    setLibrary();
    show();
}


/* ---------------------------------------- */
/* Detect when leftbar category is selected */
/* ---------------------------------------- */

void PlayerWindow::leftItemSelected(QString id)
{

    viewMode = id;

    if(id == "artists")
    {
        middleView->artistsList->show();
        middleView->artistView->show();
    }

}


/* ------------------------------------------------------- */
/* Display artist window when artist list item is selected */
/* ------------------------------------------------------- */

void PlayerWindow::artistSelected(json data)
{
    middleView->artistView->setData(data,libraryLocationSelected);

    if(!player->currentSong.is_null())
        middleView->artistView->songPlayed(player->currentSong);

}


/* ------------------------------------------ */
/* Sets the current library to child elements */
/* ------------------------------------------ */

void PlayerWindow::setLibrary()
{
    middleView->artistsList->setData(library->library["artists"],libraryLocationSelected);
}


/* ---------------------------------------------------------------- */
/* Play song and create playlist if song is played from artist view */
/* ---------------------------------------------------------------- */

void PlayerWindow::playFromArtist(json data)
{

    //Check if current song playlist is created, and create if not

    if(playingFrom != "artistView" || data["artist"] != player->currentSong["artist"])
    {
        //Read the artist songs

        json artist = library->library["artists"][QString::fromStdString(data["artist"]).toStdString()];

        //Create the artist playlist

        QList<json> list;

        for (json::iterator a = artist.begin(); a != artist.end(); ++a)
        {
            //json ar = s.sortByKey(a.value(),"track","int");

            for (json::iterator s = a.value().begin(); s != a.value().end(); ++s)
            {
                list.append(s.value());
            }
        }

        player->playList = list;
        player->setShuffle(player->shuffle);
        playingFrom = "artistView";
    }

    player->playSong(data);

}

/* ---------------------------------------- */
/* Refresh the Google Drive info if posible */
/* ---------------------------------------- */

void PlayerWindow::setUserInfo()
{
    drive->setData(library->settings);

    long used;
    long total;

    if(library->settings["usedSpace"].is_string()){
        QString a =  QString::fromStdString(library->settings["usedSpace"]);
        used = math.fromString(a);
    }
    else{
        used = library->settings["usedSpace"];
    }
    if(library->settings["totalSpace"].is_string()){
        QString b =  QString::fromStdString(library->settings["totalSpace"]);
        total = math.fromString(b);
    }
    else{
         total = library->settings["totalSpace"];
    }


    topBar->storageBar->setPercent(used,total);

}


/* Makes interface only show songs from selected location ('local', 'cloud' or 'all') */

void PlayerWindow::setLibraryLocation(QString location)
{
    libraryLocationSelected = location.toLower();
    setLibrary();
}




/* ------------------------------- */
/* When prfile image is downloaded */
/* ------------------------------- */

void PlayerWindow::imageReady()
{
    if(library->settings["userPicture"] != "")
    {
        QImage im(path + "/Cuarzo Player/User/ProfileImage.jpg");
        if(!im.isNull()){
            topBar->userPicture->image->setPixmap(p.round(im));
        }
    }
}

void PlayerWindow::quitApp()
{
    goingToExit = true;
    QApplication::exit(0);
}


/* -------*/
/* Events */
/* ------ */

bool PlayerWindow::eventFilter(QObject *, QEvent *event)
{

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if(keyEvent->key() == Qt::Key_Q && QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {

        }
    }
    return false;
}


void PlayerWindow::closeEvent(QCloseEvent *event)
{
    if(!goingToExit){
        #ifdef Q_OS_MAC
            ObjectiveC *obc = new ObjectiveC();
            obc->HideWindow();
            delete obc;
        #endif
            event->ignore();
     }
}

void PlayerWindow::createActions()
{
    addMusicAct = new QAction(tr("&Add Music"), this);
    addMusicAct->setShortcuts(QKeySequence::New);
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    loginAct = new QAction(tr("&Add Google Drive Account"),this);
    connect(loginAct, SIGNAL(triggered(bool)), this, SLOT(showLoginWindow()));

    logoutAct = new QAction(tr("Logout from Google Drive"),this);
    connect(logoutAct, SIGNAL(triggered(bool)), this, SLOT(logout()));

    exitAct = new QAction(tr("&PIC"),this);
    exitAct->setMenuRole(QAction::QuitRole);
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(quitApp()));
}

void PlayerWindow::createMenus()
{

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addMusicAct);
    fileMenu->addAction(exitAct);
    accountMenu = menuBar()->addMenu(tr("&Account"));
    accountMenu->addAction(logoutAct);
    accountMenu->addAction(loginAct);

}

void PlayerWindow::showLoginWindow()
{
    fileMenu->setEnabled(false);
    accountMenu->setEnabled(false);
    hide();
    Login *login = new Login();
    login->show();
    connect(login,SIGNAL(loggedIn(QString,QString)),this,SLOT(loggedIn(QString,QString)));
}

void PlayerWindow::logout()
{
    QMessageBox msgBox;
    msgBox.setText("You won't be able to listen to the songs stored in this cloud until you login again.");
    msgBox.setInformativeText("Do you wish to continue?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if(ret != QMessageBox::Yes) return;

    showLoginWindow();
}
