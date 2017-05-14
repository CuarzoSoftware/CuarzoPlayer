#include "player.h"

extern QString path;
Player::Player()
{

}

void Player::playSong(json song){
    mediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + ".mp3" )));
    mediaPlayer->play();
    songPlaying(song);
}
