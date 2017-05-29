#include "playerwindow.h"


extern QString path;


/* -------------------------------*/
/* Creates the player main window */
/* -------------------------------*/

PlayerWindow::PlayerWindow(Library *lib, QString token, QString refresh)
{

    //MAKES TITLE BAR WHITE ON MAC OS X

    #ifdef Q_OS_MAC
        ObjectiveC *obc = new ObjectiveC();
        obc->Display(winId());
        delete obc;
    #endif

    //SETUP UI

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
    show();

    //CREATES MUSIC LIBRARY

    library = lib;

    library->settings["token"] = token.toStdString();
    library->settings["restoreToken"] = refresh.toStdString();
    library->settings["init"] = true;
    library->saveSettings();

    //CREATE ELEMENTS

    artistList = new ArtistsList();
    middleView->addWidget(artistList);
    refreshLibrary();

    //CREATES MENUS ACTIONS

    addMusicAct = new QAction(tr("&Add Music"), this);
    addMusicAct->setShortcuts(QKeySequence::New);
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    loginAct = new QAction(tr("&Add Google Drive Account"),this);
    connect(loginAct, SIGNAL(triggered(bool)), this, SIGNAL(showLoginWindow()));

    logoutAct = new QAction(tr("Logout from Google Drive"),this);
    connect(logoutAct, SIGNAL(triggered(bool)), this, SLOT(logout()));

    exitAct = new QAction(tr("&PIC"),this);
    exitAct->setMenuRole(QAction::QuitRole);
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(quitApp()));

    //CREATES MENUS

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addMusicAct);
    fileMenu->addAction(exitAct);
    accountMenu = menuBar()->addMenu(tr("&Account"));
    accountMenu->addAction(logoutAct);
    accountMenu->addAction(loginAct);


    //CONNECTIONS

    //ADD MUSIC

    connect(topBar->addButton,SIGNAL(clicked(bool)),library,SLOT(startMusicAdder()));
    connect(topBar->addButton,SIGNAL(released()),topBar->pie,SLOT(show()));
    connect(library,SIGNAL(songAddCanceled()),topBar->pie,SLOT(hide()));
    connect(library,SIGNAL(songAddProgress(int)),topBar->pie,SLOT(setPercent(int)));
    connect(library,SIGNAL(songAddComplete()),topBar->pie,SLOT(hide()));
    connect(library,SIGNAL(songAddComplete()),this,SLOT(refreshLibrary()));

    //SELECTION

    connect(middleView->leftBar,SIGNAL(sendSelected(QString)),this,SLOT(leftItemSelected(QString)));
    connect(artistList,SIGNAL(sendSelectedArtist(QString)),this,SLOT(artistSelected(QString)));


    //SETUP SETTINGS

    if(albumSongs.size() == 0)
    {
        middleView->msg->show();
    }
    else{
        artistList->artistSelected(artistList->artists.values()[0]);
        artistList->show();
        middleView->leftBar->itemSelected("artists");
    }


    if(library->settings["token"] != "NO"){

        logoutAct->setVisible(true);
        loginAct->setVisible(false);
        topBar->modeList->show();
        topBar->addAccount->hide();
        topBar->storageBar->show();

        drive = new GoogleDrive(library->settings);

        //Google Drive


        connect(drive,SIGNAL(songUploaded(json)),library,SLOT(songUploaded(json)));
        connect(drive,SIGNAL(sendUserInfo(json)),library,SLOT(setUserInfo(json)));
        connect(drive,SIGNAL(sendCloud(json)),library,SLOT(getCloud(json)));
        connect(library,SIGNAL(userInfoChanged()),this,SLOT(setUserInfo()));
        connect(drive,SIGNAL(imageReady()),this,SLOT(imageReady()));


        //DELETE SONGS
        connect(library,SIGNAL(deleteFromCloud(json)),drive,SLOT(deleteSong(json)));
        connect(library,SIGNAL(deleteFromBoth(json)),drive,SLOT(deleteSong(json)));


        setUserInfo();
    }
    else{

        loginAct->setVisible(true);
        logoutAct->setVisible(false);
        topBar->modeList->hide();
        topBar->userPicture->image->setPixmap(QPixmap(":res/img/user.svg"));
        topBar->addAccount->show();
        topBar->storageBar->hide();
        connect(topBar->addAccount,SIGNAL(released()),this,SIGNAL(showLoginWindow()));
    }

    //LOGIN LOGOUT
    connect(this,SIGNAL(showLoginWindow()),this,SLOT(deleteLater()));

    //DISPLAY MODE

    connect(topBar->modeList,SIGNAL(sendSelected(QString)),this,SLOT(setLibraryLocation(QString)));






    //PLAYER EVENTS

    connect(player,SIGNAL(songPlaying(json)),this,SLOT(showSongPlaying(json)));
    connect(player,SIGNAL(sendTimePosition(float,float)),bottomBar->timeBar,SLOT(getTimePosition(float,float)));
    connect(player,SIGNAL(sendState(bool)),bottomBar->playerButtons,SLOT(setPlay(bool)));
    connect(bottomBar->timeBar,SIGNAL(positionChanged(float)),player,SLOT(setTime(float)));
    connect(bottomBar->volumeBar->slider,SIGNAL(valueChanged(int)),player->player->audio(),SLOT(setVolume(int)));
    connect(bottomBar->playerButtons->play,SIGNAL(released()),player,SLOT(playPause()));
    connect(bottomBar->playerButtons->back,SIGNAL(released()),player,SLOT(playBack()));
    connect(bottomBar->playerButtons->next,SIGNAL(released()),player,SLOT(playNext()));
    connect(bottomBar,SIGNAL(sendShuffleMode(bool)),player,SLOT(setShuffle(bool)));
    connect(bottomBar,SIGNAL(sendLoopMode(int)),player,SLOT(setLoopMode(int)));


    //SET SETTINGS

    bottomBar->volumeBar->slider->setValue(library->settings["volume"]);
    bottomBar->volumeBar->positionChanged(library->settings["volume"]);
    bottomBar->setLoopMode(library->settings["loop"]);
    bottomBar->setShuffleMode(library->settings["shuffle"]);
    player->settings = library->settings;


    libraryLocationSelected = "local";

}

void PlayerWindow::refreshLibrary()
{
    for (json::iterator it = library->library["artists"].begin(); it != library->library["artists"].end(); ++it)
    {
        if(artistViews.contains(QString::fromStdString(it.key()))){

            ArtistView *artistView = artistViews[QString::fromStdString(it.key())];

            for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
            {
                QString albumKey = QString::fromStdString(it.key())+QString::fromStdString(it2.key());

                if(artistView->albums.contains(albumKey)){

                    Album *album = albums[albumKey];

                    for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3)
                    {
                        int songId = (int)it3.value()["id"];

                        if(!album->songs.contains(songId)){
                            AlbumSong *song = new AlbumSong(it3.value());
                            album->addSong(song);
                            artistView->songs.append(song);
                            albumSongs.insert(songId,song);
                            connect(song,SIGNAL(songPlayed(json)),this,SLOT(playFromArtist(json)));
                            album->sort();
                        }

                    }
                }
                else{
                    Album *album = new Album(it2.value());
                    artistView->addAlbum(album);
                    albums.insert(albumKey,album);
                    foreach (AlbumSong *song, album->songs)
                    {
                        albumSongs.insert((int)song->data["id"],song);
                        connect(song,SIGNAL(songPlayed(json)),this,SLOT(playFromArtist(json)));
                    }

                }
            }
            artistView->sort();
        }
        else{
            ArtistView *artistView = new ArtistView(it.value());
            artistViews.insert(QString::fromStdString(it.key()),artistView);
            middleView->addWidget(artistView);

            albums.unite(artistView->albums);

            /*
            //TESTING
            connect(artistView,SIGNAL(syncSong(json)),drive,SLOT(syncSong(json)));
            connect(artistView,SIGNAL(sendCancelSongUpload(int)),drive,SLOT(cancelSongUpload(int)));

            connect(drive,SIGNAL(songUploaded(json)),artistView,SLOT(songUploaded(json)));
            connect(drive,SIGNAL(sendSongUploadProgress(int,int)),artistView,SLOT(setSongUploadPercent(int,int)));

            connect(artistView,SIGNAL(deleteSongs(QList<json>,QString)),library,SLOT(deleteSongs(QList<json>,QString)));
            connect(library,SIGNAL(deleteFromBoth(json)),artistView,SLOT(hideSong(json)));
            connect(library,SIGNAL(deleteFromLocal(json)),artistView,SLOT(changeSong(json)));

            connect(library,SIGNAL(deleteFromCloud(json)),artistView,SLOT(changeSong(json)));



            */

            foreach (AlbumSong *song, artistView->songs)
            {
                albumSongs.insert((int)song->data["id"],song);
                connect(song,SIGNAL(songPlayed(json)),this,SLOT(playFromArtist(json)));
            }
        }
    }
    artistList->hide();
    artistList->setData(library->library["artists"]);
    artistList->show();
}


void PlayerWindow::leftItemSelected(QString id)
{

    viewMode = id;

    if(id == "artists")
    {
        artistList->show();
    }

}


void PlayerWindow::artistSelected(QString artist)
{
    foreach (ArtistView *view, artistViews) {
        view->hide();
    }
    artistViews[artist]->show();
}


void PlayerWindow::setLibrary()
{
}

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

void PlayerWindow::showSongPlaying(json songData)
{
    foreach (AlbumSong *song, albumSongs) {
       song->setPlaying(false);
    }
    if(albumSongs.contains(songData["id"]))
    {
        albumSongs[songData["id"]]->setPlaying(true);
        bottomBar->songInfo->setData(songData);
    }
}


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

void PlayerWindow::quitApp()
{
    goingToExit = true;
    QApplication::exit(0);
}

