#include "player.h"
#include <QDebug>


extern QString path;

Player::Player()
{
    connect(player,SIGNAL(positionChanged(float)),this,SLOT(positionChanged(float)));
    connect(player,SIGNAL(end()),this,SLOT(playNext()));
}


/* Emits the current song position */

void Player::positionChanged(float position)
{
    float pos = (float)currentSong["duration"] * position;
    sendTimePosition(pos,(float)currentSong["duration"]);
}


/* Plays the selected song */

void Player::playSong(json song)
{
    currentSong = song;
    songPlaying(song);

    if(song["local"])
    {
        QString songPath = path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + "." + QString::fromStdString(song["format"]);
        player->open(new VlcMedia(songPath,true,vlc));
    }
    else
    {
        player->open(new VlcMedia("https://www.googleapis.com/drive/v3/files/"+QString::fromStdString(song["musicId"])+"?alt=media&access_token="+QString::fromStdString(settings["token"]) ,false,vlc));
    }

    play(true);
}


/* Toggle the player status */

void Player::playPause()
{
    if(player->state() == Vlc::Playing)
    {
        play(false);
    }
    else
    {
        play(true);
    }
}


/* Sets the play state */

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


/* Changes the player song position */

void Player::setTime(float percent)
{
    player->setPosition(percent);
}


/* Sets the loop mode */

void Player::setLoopMode(int mode)
{
    loopMode = mode;

}


/* Sets the shuffle mode */

void  Player::setShuffle(bool mode)
{
    shuffle = mode;

    if(mode)
    {
        qSort(playList.begin(), playList.end(),[](json a, json b) -> bool {
            int ans = QString::fromStdString(a["album"]).compare(QString::fromStdString(b["album"]));
            return (a["track"] <= b["track"] && ans == 0) || ans == -1;
        });
    }
    else{
        qSort(playList.begin(), playList.end(),[](json a, json b) -> bool {
            return qrand() % ((1 + 1) - 0) + 0;
        });
    }

}


/* Skip to the next song */

void Player::playNext()
{
    if(loopMode == 2)
    {
        playSong(currentSong);
        return;
    }

    int size = playList.length();
    int songIndex = -1;

    //Gets the current song index in playlist and its size

    foreach(json song,playList)
    {
        songIndex++;
        if(song["id"] == currentSong["id"])
        {
            break;
        }

    }

    if(songIndex == -1) return;

    if(songIndex == size - 1)
    {
        if(loopMode == 0){
            playSong(playList[0]);
            play(false);
        }
        else{
            playSong(playList[0]);
        }

    }
    else
    {
        playSong(playList[songIndex + 1]);
    }
}

/* Play previus song */

void Player::playBack(){

    if(loopMode == 2)
    {
        playSong(currentSong);
        return;
    }

    int size = playList.length();
    int songIndex = -1;

    //Gets the current song index in playlist and its size

    foreach(json song,playList)
    {
        songIndex++;
        if(song["id"] == currentSong["id"])
        {
            break;
        }
    }

    if(songIndex==0)
    {
        playSong(playList[size - 1]);
    }
    else{
        playSong(playList[songIndex - 1]);
    }

}


void Player::downloadTempSong(json song)
{
    /*
    QNetworkAccessManager *network = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files/"+QString::fromStdString(song["musicId"])+"?alt=media"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Authorization",QString("Bearer "+QString::fromStdString(settings["token"])).toUtf8());
    reply = network->get(request);
    connect(reply, SIGNAL(readyRead()),this,SLOT(setBuffer()));
    connect(reply,SIGNAL(finished()),this,SLOT(endBuffer()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProg(qint64,qint64)));
    file->setFileName("/tmp/caca.mp3");
    file->open(QIODevice::WriteOnly);
    */
}

void Player::setBuffer()
{
    /*
    file->write(reply->read(reply->bytesAvailable()));

    int pos = player->position();
    player->setMedia(QUrl::fromLocalFile("/tmp/caca.mp3"));
    player->setPosition(pos);
    play(true);
    */
}

void Player::endBuffer()
{
    /*
    file->close();
    */
}

void Player::downloadProg(qint64 per,qint64 tot)
{
    /*
    qDebug() << per;
    if(per > 100000 && player->state() != QMediaPlayer::PlayingState)
    {
        //int pos = player->position();
        //player->setMedia(QUrl::fromLocalFile("/tmp/caca.mp3"));
        //player->setPosition(pos);
        //play(true);
    }
    */

}

