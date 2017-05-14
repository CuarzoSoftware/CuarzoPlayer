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
    connect(topBar->addButton,SIGNAL(released()),library,SLOT(addMusic()));
    connect(middleView->artistView,SIGNAL(sendSongPlayed(json)),this,SLOT(createPlayList(json)));
    connect(middleView->leftBar,SIGNAL(sendSelected(QString)),this,SLOT(leftItemSelected(QString)));
    connect(middleView->artistsList,SIGNAL(sendSelectedArtist(json)),this,SLOT(artistSelected(json)));
    connect(library,SIGNAL(musicAdded()),this,SLOT(setLibrary()));

    connect(player,SIGNAL(songPlaying(json)),bottomBar->songInfo,SLOT(setData(json)));
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
