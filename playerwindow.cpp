#include "playerwindow.h"
#include "croplabel.h"
#include <QApplication>


PlayerWindow::PlayerWindow()
{
    setContextMenuPolicy(Qt::NoContextMenu);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMinimumSize(1000,600);
    setLayout(mainLayout);
    mainLayout->setMargin(0);
    mainLayout->addWidget(frame);
    frame->setObjectName("MainFrame");
    frame->setStyleSheet("#MainFrame{background:#FFF}");
    frameLayout->setMargin(0);
    frameLayout->setSpacing(0);
    frameLayout->addWidget(topBar);
    frameLayout->addWidget(middleView);
    frameLayout->addWidget(bottomBar);
    setLibrary();

    //ADD MUSIC
    connect(topBar->addButton,SIGNAL(released()),library,SLOT(addMusic()));
    connect(library,SIGNAL(musicAdded()),this,SLOT(setLibrary()));

    //SONGS EVENTS
    connect(middleView->artistView,SIGNAL(sendSongPlayed(json)),this,SLOT(createPlayList(json)));
    connect(middleView->leftBar,SIGNAL(sendSelected(QString)),this,SLOT(leftItemSelected(QString)));
    connect(middleView->artistsList,SIGNAL(sendSelectedArtist(json)),this,SLOT(artistSelected(json)));

    //PLAYER EVENTS
    connect(player,SIGNAL(songPlaying(json)),bottomBar->songInfo,SLOT(setData(json)));
    connect(bottomBar->timeBar,SIGNAL(positionChanged(float)),player,SLOT(setTime(float)));
    connect(player,SIGNAL(sendTimePosition(float,float)),bottomBar->timeBar,SLOT(getTimePosition(float,float)));
    //connect(player->player,SIGNAL(buffering(int)),bottomBar->timeBar,SLOT(setLoadPosition(int)));
    connect(bottomBar->volumeBar->slider,SIGNAL(valueChanged(int)),player->player,SLOT(setVolume(int)));

}

void PlayerWindow::leftItemSelected(QString id){
    if(id == "artists"){
        middleView->artistsList->show();
        middleView->artistView->show();
    }
}
void PlayerWindow::artistSelected(json data){
    middleView->artistView->hide();
    middleView->artistView->setData(data);
    middleView->artistView->artistViewTitle->show();
    middleView->artistView->show();
}
void PlayerWindow::setLibrary(){
    middleView->artistsList->setData(library->localLibrary["artists"]);
}
void PlayerWindow::createPlayList(json data){
    player->playSong(data);
}
