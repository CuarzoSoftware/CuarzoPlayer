#include "playerwindow.h"
#include <QCollator>


extern QString path;


/* -------------------------------*/
/* Creates the player main window */
/* -------------------------------*/

PlayerWindow::PlayerWindow(Library *lib, QString token, QString refresh)
{

    setupUI();                          //SETUP THE MAIN WINDOW

    setupLibrary(lib,token,refresh);    //SETUP MUSIC LIBRARY

    setupViewsAndWidgets();             //SETUP VIEWS AND UI ELEMENTS

    setupTopBarMenus();                 //SETUP THE TOP MENU OPTIONS

    setupConnections();                 //SETUP SOME IMPORTANT CONNECTIONS

    setupSettings();                    //SETUP SAVED SETTINGS

}

void PlayerWindow::setupUI()
{

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
}

void PlayerWindow::setupLibrary(Library *lib, QString token, QString refresh)
{
    library = lib;
    library->set["token"] = token;
    library->set["restoreToken"] = refresh;
    library->set["init"] = true;
    library->saveSettings();
    if(token == ""){
        logged = false;
    }
    else{
        logged = true;
    }
}

void PlayerWindow::setupViewsAndWidgets()
{
    viewMode = "artists";
    refreshLibrary();
}

void PlayerWindow::setupTopBarMenus()
{
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
}

void PlayerWindow::setupConnections()
{

    //ADD MUSIC

    connect(topBar->addButton,SIGNAL(clicked(bool)),library,SLOT(startMusicAdder()));
    connect(topBar->addButton,SIGNAL(released()),topBar->pie,SLOT(show()));
    connect(library,SIGNAL(songAddCanceled()),topBar->pie,SLOT(hide()));
    connect(library,SIGNAL(songAddProgress(int)),topBar->pie,SLOT(setPercent(int)));
    connect(library,SIGNAL(songAddComplete()),topBar->pie,SLOT(hide()));
    connect(library,SIGNAL(songAddComplete()),this,SLOT(refreshLibrary()));
    connect(library,SIGNAL(deleteFromBoth(QString)),this,SLOT(deletedFromBoth(QString)));
    connect(library,SIGNAL(songDeletionEnd()),this,SLOT(songDeletionEnd()));

    //SELECTION

    connect(middleView->leftBar,SIGNAL(sendSelected(QString)),this,SLOT(leftItemSelected(QString)));


    //EDIT SONGS

    connect(tagEditor,SIGNAL(songsEdited(QVariantList)),this,SLOT(songsEdited(QVariantList)));

    if(logged){

        logoutAct->setVisible(true);
        loginAct->setVisible(false);
        //topBar->modeList->show();
        topBar->addAccount->hide();
        topBar->storageBar->show();

        //drive = new GoogleDrive(library->settings);

        //Google Drive

        /*
        connect(drive,SIGNAL(songUploaded(json)),library,SLOT(songUploaded(json)));
        connect(drive,SIGNAL(sendUserInfo(json)),library,SLOT(setUserInfo(json)));
        connect(drive,SIGNAL(sendCloud(json)),library,SLOT(getCloud(json)));
        connect(library,SIGNAL(userInfoChanged()),this,SLOT(setUserInfo()));
        connect(drive,SIGNAL(imageReady()),this,SLOT(imageReady()));


        //DELETE SONGS
        connect(library,SIGNAL(deleteFromCloud(json)),drive,SLOT(deleteSong(json)));
        connect(library,SIGNAL(deleteFromBoth(json)),drive,SLOT(deleteSong(json)));
        */

        setUserInfo();
    }
    else{

        loginAct->setVisible(true);
        logoutAct->setVisible(false);
        //topBar->modeList->hide();
        topBar->userPicture->image->setPixmap(QPixmap(":res/img/user.svg"));
        topBar->addAccount->show();
        topBar->storageBar->hide();
        connect(topBar->addAccount,SIGNAL(released()),this,SIGNAL(showLoginWindow()));
    }

    //LOGIN LOGOUT
    connect(this,SIGNAL(showLoginWindow()),this,SLOT(deleteLater()));

    //DISPLAY MODE

    //connect(topBar->modeList,SIGNAL(sendSelected(QString)),this,SLOT(setLibraryLocation(QString)));

    //PLAYER EVENTS

    connect(player,SIGNAL(songPlaying(QVariantMap)),this,SLOT(showSongPlaying(QVariantMap)));
    connect(player,SIGNAL(songPlaying(QVariantMap)),bottomBar->songInfo,SLOT(setData(QVariantMap)));
    connect(player,SIGNAL(sendTimePosition(float,float)),bottomBar->timeBar,SLOT(getTimePosition(float,float)));
    connect(player,SIGNAL(sendState(bool)),bottomBar->playerButtons,SLOT(setPlay(bool)));
    connect(bottomBar->timeBar,SIGNAL(positionChanged(float)),player,SLOT(setTime(float)));
    connect(bottomBar->volumeBar->slider,SIGNAL(valueChanged(int)),player->player->audio(),SLOT(setVolume(int)));
    connect(bottomBar->playerButtons->play,SIGNAL(released()),player,SLOT(playPause()));
    connect(bottomBar->playerButtons->back,SIGNAL(released()),player,SLOT(playBack()));
    connect(bottomBar->playerButtons->next,SIGNAL(released()),player,SLOT(playNext()));
    connect(bottomBar,SIGNAL(sendShuffleMode(bool)),player,SLOT(setShuffle(bool)));
    connect(bottomBar,SIGNAL(sendLoopMode(int)),player,SLOT(setLoopMode(int)));
    connect(middleView->artistView->artistViewTitle->shuffle,SIGNAL(released()),this,SLOT(shuffleArtist()));

}

void PlayerWindow::setupSettings()
{
    bottomBar->volumeBar->slider->setValue(library->set["volume"].toInt());
    bottomBar->volumeBar->positionChanged(library->set["volume"].toInt());
    bottomBar->setLoopMode(library->set["loop"].toInt());
    bottomBar->setShuffleMode(library->set["shuffle"].toBool());
    player->settings = library->set;
    libraryLocation = "local";
}

void PlayerWindow::refreshLibrary()
{

    if(library->songs.empty())
    {
        middleView->msg->show();
        middleView->leftBar->hide();
        middleView->artistsList->hide();
        middleView->artistView->hide();

        return;
    }
    else
    {
         middleView->msg->hide();
    }


    if(viewMode == "artists")
    {
        while(!artistListItems.empty())
        {
            artistListItems.takeLast()->deleteLater();
        }

        middleView->leftBar->hide();

        foreach (QVariant song, library->songs)
        {
            QVariantMap sng = song.toMap();
            QString id = sng["id"].toString();
            QString album = sng["album"].toString();
            QString artist = sng["artist"].toString();

            if(!existArtistListItem(artist))
            {
                ArtistListItem *item = new ArtistListItem(sng);
                if(artist == currentArtist)item->setSelected(true);
                connect(item,SIGNAL(selected(QString)),this,SLOT(artistSelected(QString)));
                artistListItems.append(item);
                middleView->artistsList->layout->addWidget(item);
            }
        }

        middleView->leftBar->show();

        if(currentArtist!="")middleView->artistView->show();
        /*
        QString key = currentArtist;
        QString from = playingFrom;
        currentArtist = playingFrom = "";
        createPlayList(key, from);
        */
    }

}


void PlayerWindow::leftItemSelected(QString id)
{

    viewMode = id;

    if(id == "artists")
    {
        middleView->artistsList->show();
    }

}


void PlayerWindow::artistSelected(QString artis)
{
    if(viewMode == "artists" && currentArtist == artis) return;

    foreach (ArtistListItem *item, artistListItems) {
       if(item->artistName == artis)
       {
           item->setSelected(true);
       }
       else
       {
           item->setSelected(false);
       }
    }

    currentArtist = artis;

    middleView->artistView->hide();

    while(!albums.empty())
    {
        albums.takeFirst()->deleteLater();
    }
    selectedAlbumSongs.clear();
    albumSongs.clear();
    albums.clear();

    foreach (QVariant song, library->songs)
    {
        QVariantMap sng = song.toMap();
        QString id = sng["id"].toString();
        QString album = sng["album"].toString();
        QString artist = sng["artist"].toString();
        bool local = sng["local"].toBool();
        bool cloud = sng["cloud"].toBool();

        if(artis != artist)continue;

        if(existAlbum(artist,album))
        {
            if(!existAlbumSong(id))
            {
                if(libraryLocation == "local" && !local) continue;
                if(libraryLocation == "cloud" && !cloud) continue;
                AlbumSong *newSong = new AlbumSong(sng,logged);
                connect(newSong,SIGNAL(songSelected(QString)),this,SLOT(albumSongSelected(QString)));
                connect(newSong,SIGNAL(songPlayed(QString)),this,SLOT(playFromArtist(QString)));
                connect(newSong,SIGNAL(showSongMenu(QString)),this,SLOT(showSongMenu(QString)));
                connect(newSong,SIGNAL(songRightClicked(QString)),this,SLOT(songRightClicked(QString)));
                albumSongs.append(newSong);
                Album *oldAlbum = getAlbum(artist,album);
                oldAlbum->songsLayout->addWidget(newSong);
                oldAlbum->songsCount++;
            }
        }
        else
        {
            if(libraryLocation == "local" && !local) continue;
            if(libraryLocation == "cloud" && !cloud) continue;
            Album *newAlbum = new Album(sng);
            AlbumSong *newSong = new AlbumSong(sng,logged);
            connect(newSong,SIGNAL(songSelected(QString)),this,SLOT(albumSongSelected(QString)));
            connect(newSong,SIGNAL(songPlayed(QString)),this,SLOT(playFromArtist(QString)));
            connect(newSong,SIGNAL(showSongMenu(QString)),this,SLOT(showSongMenu(QString)));
            connect(newSong,SIGNAL(songRightClicked(QString)),this,SLOT(songRightClicked(QString)));
            albumSongs.append(newSong);
            newAlbum->songsLayout->addWidget(newSong);
            albums.append(newAlbum);
            middleView->artistView->albumsLayout->addWidget(newAlbum);
        }
    }

    if(albums.empty()) return;
    foreach (Album *album, albums)
    {
        album->refreshSongCount();
    }
    if(existAlbumSong(player->currentSong["id"].toString()))
    {
        showSongPlaying(player->currentSong);
    }

    middleView->artistView->setData(artis,albums.length(),albumSongs.length());

    middleView->artistView->show();
}


void PlayerWindow::playFromArtist(QString SongId)
{
    QVariantMap song = getSong(SongId);
    QString artist = song["artist"].toString();
    createPlayList(artist,"artistView");
    player->playSong(song);

}

void PlayerWindow::createPlayList(QString key,QString from)
{
    if(playingFrom != "artistView" || key != player->currentSong["artist"].toString())
    {

        QVariantList playlist;
        foreach(QVariant sng,library->songs){
            QVariantMap s = sng.toMap();
            if(s["artist"].toString() == key){
                playlist.append(s);
            }
        }
        player->playList = playlist;
        player->setShuffle(player->shuffle);
        currentArtist = key;

    }
    playingFrom = from;
}

void PlayerWindow::shuffleArtist()
{
    bottomBar->setShuffleMode(true);
    createPlayList(currentArtist,"artistView");
    player->playSong(player->playList[0].toMap());
}

/* ---------------------------------------- */
/* Refresh the Google Drive info if posible */
/* ---------------------------------------- */

void PlayerWindow::setUserInfo()
{
    /*
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
    */
}


/* Makes interface only show songs from selected location ('local', 'cloud' or 'all') */

void PlayerWindow::setLibraryLocation(QString location)
{
    libraryLocation = location.toLower();

}

void PlayerWindow::imageReady()
{
    if(library->set["userPicture"].toString() != "")
    {
        QImage im(path + "/Cuarzo Player/User/ProfileImage.jpg");
        if(!im.isNull()){
            topBar->userPicture->image->setPixmap(p.round(im));
        }
    }
}

void PlayerWindow::showSongPlaying(QVariantMap songData)
{
    foreach (AlbumSong *song, albumSongs) {
       song->setPlaying(false);
    }
    getAlbumSong(songData["id"].toString())->setPlaying(true);
}

void PlayerWindow::deletedFromBoth(QString songId)
{
    /*
    foreach (QVariant song, player->playList) {
       if(song.toMap()["id"].toString() == songId){
           player->playList.removeAt(player->playList.indexOf(song));
       }
    }
    if(player->currentSong["id"].toString() == songId){
        player->play(false);
        player->player->stop();
        player->sendTimePosition(0,0);
        player->currentSong.clear();
        bottomBar->songInfo->clear();
    }
    if(existAlbumSong(songId))
    {
        albumSongs.takeAt(albumSongs.indexOf(getAlbumSong(songId)))->deleteLater();
    }
    */
}

void PlayerWindow::albumSongSelected(QString songId)
{

    if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) && !selectedAlbumSongs.empty())
    {
        int first = albumSongs.indexOf(selectedAlbumSongs[0]);
        int last  = albumSongs.indexOf(getAlbumSong(songId));
        foreach (AlbumSong *song, selectedAlbumSongs) {
            song->setSelected(false);
        }
        selectedAlbumSongs.clear();

        if(first >= last)
        {
            for(int i=first;i>=last;i--)
            {
                AlbumSong *song = albumSongs[i];
                song->setSelected(true);
                selectedAlbumSongs.append(song);
            }
        }
        else{
            for(int i=first;i<=last;i++)
            {
                AlbumSong *song = albumSongs[i];
                song->setSelected(true);
                selectedAlbumSongs.append(song);
            }
        }
    }
    else
    {
        foreach (AlbumSong *song, selectedAlbumSongs) {
            song->setSelected(false);
        }
        selectedAlbumSongs.clear();
        AlbumSong *s = getAlbumSong(songId);
        s->setSelected(true);
        selectedAlbumSongs.append(s);
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



bool PlayerWindow::existArtistListItem(QString artist)
{
    foreach(ArtistListItem *item,artistListItems)
    {
        if(item->artistName == artist) return true;
    }
    return false;
}

bool PlayerWindow::existAlbum(QString artist, QString albumName)
{
    foreach(Album *album,albums)
    {
        if(album->artist== artist && album->album== albumName) return true;
    }
    return false;
}
bool PlayerWindow::existAlbumSong(QString id)
{
    foreach(AlbumSong *song,albumSongs)
    {
        if(song->id == id) return true;
    }
    return false;
}

ArtistListItem *PlayerWindow::getArtistListItem(QString artist)
{
    foreach(ArtistListItem *item,artistListItems)
    {
        if(item->artistName == artist) return item;
    }
}

Album *PlayerWindow::getAlbum(QString artist, QString albumName)
{
    foreach(Album *album,albums)
    {
        if(album->artist== artist && album->album== albumName) return album;
    }
}
AlbumSong *PlayerWindow::getAlbumSong(QString id)
{
    foreach(AlbumSong *song,albumSongs)
    {
        if(song->id == id) return song;
    }
    qDebug()<<"Song not found";
}

QVariantMap PlayerWindow::getSong(QString id)
{
    foreach(QVariant song,library->songs)
    {
        QVariantMap map = song.toMap();
        if(map["id"].toString() == id) return map;
    }
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

void PlayerWindow::songRightClicked(QString songId)
{
    if(selectedAlbumSongs.empty()){
        showSongMenu(songId);
    }
    else{
        bool exist = false;
        foreach (AlbumSong *song, selectedAlbumSongs) {
           if(songId == song->id){
               exist = true;
           }
        }
        if(exist){

            bool local = false;
            bool both = false;
            bool cloud = false;
            bool downloading = false;
            bool uploading = false;

            songsToDelete.clear();

            foreach (AlbumSong *song, selectedAlbumSongs) {

               QVariantMap songData = getSong(song->id);
               songsToDelete.append(songData);

               if(song->uploading){
                   uploading = true;
               }
               if(song->downloading){
                   downloading = true;
               }
               if(songData["local"].toBool() && songData["cloud"].toBool()){
                   both = true;
               }
               if(songData["local"].toBool() && !songData["cloud"].toBool()){
                   local = true;
               }
               if(!songData["local"].toBool() && songData["cloud"].toBool()){
                   cloud = true;
               }
            }

            bool synching = downloading || uploading;

            SongMenu contextMenu;
            QAction action1("Edit Info");
            QAction action2("Stop Download");
            QAction action3("Stop Upload");
            QAction action4("Download");
            QAction action5("Upload");
            QAction action6("Delete from local");
            QAction action7("Delete from cloud");
            QAction action8("Delete from everywhere");

            if(!synching) contextMenu.addAction(&action1);

            if(downloading) contextMenu.addAction(&action2);

            if(uploading) contextMenu.addAction(&action3);

            if(cloud) contextMenu.addAction(&action4);

            if(local && logged) contextMenu.addAction(&action5);

            if(local) contextMenu.addAction(&action6);

            if(cloud) contextMenu.addAction(&action7);

            if(both) contextMenu.addAction(&action8);

            connect(&action1, SIGNAL(triggered()), this, SLOT(showTagEditor()));
            connect(&action2, SIGNAL(triggered()), this, SLOT(piePressed()));
            connect(&action3, SIGNAL(triggered()), this, SLOT(piePressed()));
            connect(&action4, SIGNAL(triggered()), this, SLOT(syncClicked()));
            connect(&action5, SIGNAL(triggered()), this, SLOT(syncClicked()));
            connect(&action6, SIGNAL(triggered()), this, SLOT(deleteSongsFromLocal()));
            connect(&action7, SIGNAL(triggered()), this, SLOT(deleteFromCloud()));
            connect(&action8, SIGNAL(triggered()), this, SLOT(deleteFromBoth()));

            contextMenu.exec(QPoint(QCursor::pos().x() - 40,QCursor::pos().y() - 10));

        }
        else{
            showSongMenu(songId);
        }
    }
}

void PlayerWindow::songDeletionEnd()
{
    refreshLibrary();
    QString arti = currentArtist;
    currentArtist = "";
    artistSelected(arti);
}



void PlayerWindow::showSongMenu(QString songId)
{

    AlbumSong *song = getAlbumSong(songId);
    QVariantMap songData = getSong(songId);
    songsToDelete.clear();
    songsToDelete.append(songData);

    bool local = songData["local"].toBool();
    bool cloud = songData["cloud"].toBool();
    bool downloading = song->downloading;
    bool uploading = song->uploading;
    bool synching = downloading || uploading;
    SongMenu contextMenu;
    QAction action1("Edit Info", song);
    QAction action2("Stop Download", song);
    QAction action3("Stop Upload", song);
    QAction action4("Download", song);
    QAction action5("Upload", song);
    QAction action6("Delete from local", song);
    QAction action7("Delete from cloud", song);
    QAction action8("Delete from everywhere", song);

    if(!synching) contextMenu.addAction(&action1);

    if(downloading) contextMenu.addAction(&action2);

    if(uploading) contextMenu.addAction(&action3);

    if(!local && cloud) contextMenu.addAction(&action4);

    if(!cloud && logged) contextMenu.addAction(&action5);

    if(local && !synching) contextMenu.addAction(&action6);

    if(cloud && !synching) contextMenu.addAction(&action7);

    if(cloud && local && !synching) contextMenu.addAction(&action8);

    connect(&action1, SIGNAL(triggered()), this, SLOT(showTagEditor()));
    connect(&action2, SIGNAL(triggered()), this, SLOT(piePressed()));
    connect(&action3, SIGNAL(triggered()), this, SLOT(piePressed()));
    connect(&action4, SIGNAL(triggered()), this, SLOT(syncClicked()));
    connect(&action5, SIGNAL(triggered()), this, SLOT(syncClicked()));
    connect(&action6, SIGNAL(triggered()), this, SLOT(deleteSongsFromLocal()));
    connect(&action7, SIGNAL(triggered()), this, SLOT(deleteFromCloud()));
    connect(&action8, SIGNAL(triggered()), this, SLOT(deleteFromBoth()));

    contextMenu.exec(QPoint(QCursor::pos().x() - 40,QCursor::pos().y() - 10));

    song->more->deleteLater();
    song->more = nullptr;
    song->duration->show();
}


void PlayerWindow::deleteSongsFromLocal()
{
    selectedAlbumSongs.clear();
    library->deleteSongs(songsToDelete,"local");
}

void PlayerWindow::showTagEditor()
{
    tagEditor->setData(songsToDelete);
    tagEditor->open();
}

void PlayerWindow::songsEdited(QVariantList editedSongs)
{
    foreach (QVariant song, editedSongs)
    {
       QVariantMap s = song.toMap();

       foreach(QVariant _song,library->songs)
       {
           QVariantMap _s = _song.toMap();

           if(_s["id"].toString() == s["id"].toString())
           {

               QFileInfo check_art(path + "/Cuarzo Player/Artwork/" + s["artist"].toString() + "/" + s["album"].toString() + ".jpg");

               s["artWork"] = check_art.exists();

               if(_s["artist"].toString() != s["artist"].toString()){
                   if(!QDir(path+"/Cuarzo Player/Music/" + s["artist"].toString()).exists()){
                       QDir().mkdir(path+"/Cuarzo Player/Music/" + s["artist"].toString());
                   }
               }

               if(_s["album"].toString() != s["album"].toString()){
                   if(!QDir(path+"/Cuarzo Player/Music/" + s["artist"].toString() + "/" + s["album"].toString()).exists()){
                       QDir().mkdir(path+"/Cuarzo Player/Music/" + s["artist"].toString() + "/" + s["album"].toString());
                   }
               }

               QString songFileName = QString::number(s["track"].toInt())  + " " + s["title"].toString()  + "." + s["format"].toString();
               QString destPath = path+"/Cuarzo Player/Music/" + s["artist"].toString() + "/" + s["album"].toString() + "/";

               QFileInfo check_lib( destPath + songFileName);

               bool alreadyExistName = check_lib.exists();

               int sufix = 1;


               while(alreadyExistName)
               {
                   songFileName = QString::number(s["track"].toInt()) + " " + s["title"].toString() + " " + QString::number(sufix) + "." + s["format"].toString();

                   QFileInfo check_lib(destPath + songFileName);

                   alreadyExistName = check_lib.exists();
               }


               d.rename(path + "/Cuarzo Player/Music/" + _s["artist"].toString() + "/" + _s["album"].toString() + "/" + _s["fileName"].toString() , destPath + songFileName);

               s["fileName"] = songFileName;

               library->songs[library->songs.indexOf(_song)] = s;
           }
       }
    }
    library->sortSongs();
    library->saveLibrary();
    refreshLibrary();
    QString arti = currentArtist;
    currentArtist = "";
    artistSelected(arti);
}






