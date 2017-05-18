#include "playerwindow.h"
#include "croplabel.h"

extern QString path;

//Creates the player main window

PlayerWindow::PlayerWindow()
{

    //Checks if is the first app launch

    if(!library->settings["init"])
    {
        login->show();
        connect(login,SIGNAL(loggedIn(QString,QString)),this,SLOT(loggedIn(QString,QString)));
    }
    else{
        setupSettings();
    }
}

//Detect when leftbar category is selected

void PlayerWindow::leftItemSelected(QString id)
{
    viewMode = id;

    if(id == "artists")
    {
        middleView->artistsList->show();
        middleView->artistView->show();
    }
}

//Display artist window when artist list item is selected

void PlayerWindow::artistSelected(json data)
{
    middleView->artistView->hide();
    middleView->artistView->setData(data);
    middleView->artistView->artistViewTitle->show();
    middleView->artistView->show();
}


//Sets the current library to child elements

void PlayerWindow::setLibrary()
{
    middleView->artistsList->setData(library->library["artists"]);
}

//Play song and create playlist if song is played from artist view

void PlayerWindow::playFromArtist(json data)
{

    //Check if current song playlist is created, and create if not

    if(playingFrom != "artistView" || data["artist"] != player->currentSong["artist"])
    {
        qDebug()<<"Playlist created";
        //Read the artist songs

        json artist = library->library["artists"][QString::fromStdString(data["artist"]).toStdString()];

        //Create the artist playlist

        json list;

        int index = 0;

        for (json::iterator a = artist.begin(); a != artist.end(); ++a)
        {
            json ar = s.sortByKey(a.value(),"track","int");

            for (json::iterator s = ar.begin(); s != ar.end(); ++s)
            {
                list[index] = s.value();
                index++;
            }
        }

        player->playList = list;
        playingFrom = "artistView";
    }

    player->playSong(data);

}

//Refresh the Google Drive info if posible

void PlayerWindow::setUserInfo()
{
    drive->setData(library->settings);

    long used;
    long total;

    QString a =  QString::fromStdString(library->settings["usedSpace"]);
    QString b = QString::fromStdString(library->settings["totalSpace"]);

    used = math.fromString(a);
    total = math.fromString(b);

    qDebug()<<total;
    qDebug()<<used;

    topBar->storageBar->setPercent(used,total);

}

//Create connections and setup the saved setting to child elements

void PlayerWindow::setupSettings()
{

    drive = new GoogleDrive(library->settings);

    setContextMenuPolicy(Qt::NoContextMenu);
    setFocusPolicy(Qt::ClickFocus);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMinimumSize(1000,600);
    setLayout(mainLayout);
    installEventFilter(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(frame);
    frame->setObjectName("MainFrame");
    frame->setStyleSheet("#MainFrame{background:#FFF}");
    frameLayout->setMargin(0);
    frameLayout->setSpacing(0);
    frameLayout->addWidget(topBar);
    frameLayout->addWidget(middleView);
    frameLayout->addWidget(bottomBar);


    //ADD MUSIC

    connect(topBar->addButton,SIGNAL(released()),library,SLOT(startMusicAdder()));
    connect(library,SIGNAL(musicAddComplete()),this,SLOT(setLibrary()));
    connect(library,SIGNAL(percentAdded(int)),topBar->pie,SLOT(setPercent(int)));

    //SONGS EVENTS

    connect(middleView->artistView,SIGNAL(sendSongPlayed(json)),this,SLOT(playFromArtist(json)));
    connect(middleView->leftBar,SIGNAL(sendSelected(QString)),this,SLOT(leftItemSelected(QString)));
    connect(middleView->artistsList,SIGNAL(sendSelectedArtist(json)),this,SLOT(artistSelected(json)));

    //PLAYER EVENTS

    connect(player,SIGNAL(songPlaying(json)),bottomBar->songInfo,SLOT(setData(json)));
    connect(player,SIGNAL(songPlaying(json)),middleView->artistView,SLOT(songPlayed(json)));
    connect(bottomBar->timeBar,SIGNAL(positionChanged(float)),player,SLOT(setTime(float)));
    connect(player,SIGNAL(sendTimePosition(float,float)),bottomBar->timeBar,SLOT(getTimePosition(float,float)));
    connect(bottomBar->volumeBar->slider,SIGNAL(valueChanged(int)),player->player,SLOT(setVolume(int)));
    connect(bottomBar->playerButtons->back,SIGNAL(released()),player,SLOT(playBack()));
    connect(bottomBar->playerButtons->next,SIGNAL(released()),player,SLOT(playNext()));
    connect(bottomBar->playerButtons,SIGNAL(setPlay(bool)),player,SLOT(play(bool)));
    connect(bottomBar,SIGNAL(sendShuffleMode(bool)),player,SLOT(setShuffle(bool)));
    connect(bottomBar,SIGNAL(sendLoopMode(int)),player,SLOT(setLoopMode(int)));

    //Google Drive

    connect(drive,SIGNAL(sendUserInfo(json)),library,SLOT(setUserInfo(json)));
    connect(library,SIGNAL(userInfoChanged()),this,SLOT(setUserInfo()));
    connect(drive,SIGNAL(imageReady()),this,SLOT(imageReady()));

    setUserInfo();
    setLibrary();
    bottomBar->volumeBar->slider->setValue(library->settings["volume"]);
    show();
}

//Save the user data when user is logged

void PlayerWindow::loggedIn(QString token, QString refresh)
{
    library->settings["token"] = token.toStdString();
    library->settings["restoreToken"] = refresh.toStdString();
    library->settings["init"] = true;
    library->saveSettings();
    setupSettings();
    delete login;
}

//When prfile image is downloaded

void PlayerWindow::imageReady()
{
    if(library->settings["userPicture"] != ""){
        topBar->userPicture->image->setPixmap(p.round(QImage(path + "/Cuarzo Player/User/ProfileImage.jpg")));
    }

}

//Events

bool PlayerWindow::eventFilter(QObject *, QEvent *event)
{

    if(event->type() == QEvent::KeyPress)
    {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if(keyEvent->key() == Qt::Key_MediaPlay)
        {
            bottomBar->playerButtons->playPause();
        }

    }
    return false;
}
