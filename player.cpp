#include "player.h"
#include <QDebug>



extern QString path;

Player::Player()
{
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(timeChanged(qint64)));
}
void Player::playSong(json song){
    currentSong = song;
    songPlaying(song);

    //VlcMedia *media = new VlcMedia("http://www.bensound.com/bensound-music/bensound-cute.mp3",false, vlc);
    player->setMedia(QUrl::fromLocalFile(path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + ".mp3"));
    player->play();
}
void Player::setTime(float percent){
    if(player->isSeekable()){
        float pos = ((float)currentSong["duration"]*percent);
        player->setPosition((qint64)pos);
    }
}

void Player::timeChanged(qint64 t){
    sendTimePosition((float)t,(float)currentSong["duration"]);
}
