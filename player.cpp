#include "player.h"
#include <QDebug>


extern QString path;

Player::Player()
{
    connect(player,SIGNAL(timeChanged(int)),this,SLOT(timeChanged(int)));
}
void Player::playSong(json song){
    currentSong = song;
    songPlaying(song);

    //VlcMedia *media = new VlcMedia("http://www.bensound.com/bensound-music/bensound-cute.mp3",false, vlc);

    VlcMedia *media = new VlcMedia(path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + ".mp3",true, vlc);
    player->open(media);
}
void Player::setTime(float percent){
    float pos = ((float)currentSong["duration"]*percent);
    player->setTime((int)pos);
}

void Player::timeChanged(int t){
    sendTimePosition((float)t,player->length()/1000);
}
