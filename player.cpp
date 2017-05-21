#include "player.h"
#include <QDebug>



extern QString path;

//Creates the media player

Player::Player()
{
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(timeChanged(qint64)));
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaChanged(QMediaPlayer::MediaStatus)));
}

//Plays the selected song

void Player::playSong(json song)
{
    currentSong = song;
    songPlaying(song);
    player->setMedia(QUrl::fromLocalFile(path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + "." + QString::fromStdString(song["format"])));
    play(true);
}

//Changes to a custom time song position if there is a song playing

void Player::setTime(float percent)
{
    if(player->isSeekable())
    {
        float pos = ((float)currentSong["duration"]*percent);
        player->setPosition((qint64)pos);
    }
}

//Emits the current song position

void Player::timeChanged(qint64 t)
{
    sendTimePosition((float)t,(float)currentSong["duration"]);

}

//Song end event

void Player::mediaChanged(QMediaPlayer::MediaStatus m)
{
    if(m == QMediaPlayer::EndOfMedia)
    {
      playNext();
    }

}

void Player::playPause()
{
    if(player->state() == QMediaPlayer::PlayingState)
    {
        play(false);
    }
    else
    {
        play(true);
    }
}

//Set the loop mode

void Player::setLoopMode(int mode)
{
    loopMode = mode;
}

//Set the shuffle mode

void  Player::setShuffle(bool mode)
{
    shuffle = mode;
}

//Toggle the play state

void Player::play(bool op)
{
    if(op)
    {
        player->play();
    }
    else
    {
        player->pause();
    }

    sendState(op);
}

//Play the next song in the playlist

void Player::playNext()
{
    int size = 0;
    int songIndex = 0;

    //Gets the current song index in playlist and its size

    for (json::iterator s = playList.begin(); s != playList.end(); ++s)
    {
        if(s.value()["id"] == currentSong["id"])
        {
            songIndex = size;
        }
        size++;
    }

    if(songIndex == size - 1)
    {
        playSong(playList[0]);
    }
    else
    {
        playSong(playList[songIndex + 1]);
    }
}
void Player::playBack(){

    int size = 0;
    int songIndex = 0;

    //Gets the current song index in playlist and its size

    for (json::iterator s = playList.begin(); s != playList.end(); ++s)
    {
        if(s.value()["id"] == currentSong["id"])
        {
            songIndex = size;
        }
        size++;
    }

    if(songIndex==0)
    {
        playSong(playList[size - 1]);
    }
    else{
        playSong(playList[songIndex - 1]);
    }

}
