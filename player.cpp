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
    float pos = currentSong["duration"].toFloat() * position;
    sendTimePosition(pos,currentSong["duration"].toFloat());
}


/* Plays the selected song */

void Player::playSong(QVariantMap song)
{
    currentSong = song;
    songPlaying(currentSong);

    if(currentSong["local"].toBool())
    {
        QString songPath = path +"/Cuarzo Player/Music/"+currentSong["artist"].toString()+"/"+currentSong["album"].toString() +"/"+currentSong["fileName"].toString();
        player->open(new VlcMedia(songPath,true,vlc));
    }
    else
    {
        player->open(new VlcMedia("https://www.googleapis.com/drive/v3/files/"+song["musicId"].toString()+"?alt=media&access_token="+settings["token"].toString() ,false,vlc));
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
        if(player->seekable()){
            player->play();
        }
        else{
            if(currentSong["id"].toString() != ""){
                playSong(currentSong);
            }
            else{
                return;
            }
        }

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

        qSort(playList.begin(), playList.end(),[](QVariant a, QVariant b) -> bool {

            QString aArtist = a.toMap()["artist"].toString();
            QString bArtist = b.toMap()["artist"].toString();


            int comp = aArtist.compare(bArtist);

            if(comp<0){
                return true;
            }
            if(comp>0){
                return false;
            }
            if(comp==0){

                QString aAlbum = a.toMap()["album"].toString();
                QString bAlbum = b.toMap()["album"].toString();

                comp = aAlbum.compare(bAlbum);

                if(comp<0){
                    return true;
                }
                if(comp>0){
                    return false;
                }
                if(comp==0){

                    int aTrack =  a.toMap()["track"].toInt();
                    int bTrack =  b.toMap()["track"].toInt();

                    if(aTrack<bTrack){
                        return true;
                    }
                    if(aTrack>bTrack){
                        return false;
                    }
                    if(aTrack==bTrack){

                        QString aTitle = a.toMap()["title"].toString();
                        QString bTitle = b.toMap()["title"].toString();

                        comp = aTitle.compare(bTitle);

                        if(comp<0){
                            return true;
                        }
                        if(comp>0){
                            return false;
                        }
                        if(comp==0){
                            return false;
                        }
                    }
                }
            }
        });

    }
    else{

        qSort(playList.begin(), playList.end(),[](QVariant a, QVariant b) -> bool {
            return qrand() % ((1 + 1) - 0) + 0;
        });
    }

}


/* Skip to the next song */

void Player::playNext()
{

    if(playList.empty()) return;

    if(loopMode == 2)
    {
        playSong(currentSong);
        return;
    }

    int size = playList.length();
    int songIndex = playList.indexOf(currentSong);

    if(loopMode == 0 && songIndex == size -1)
    {
        currentSong = playList[0].toMap();
        songPlaying(currentSong);
        play(false);
        player->stop();
        sendTimePosition(0,0);
        return;
    }

    if(songIndex == size - 1)
    {
        if(loopMode == 0){
            playSong(playList[0].toMap());
            play(false);
        }
        else{
            playSong(playList[0].toMap());
        }

    }
    else
    {
        playSong(playList[songIndex + 1].toMap());
    }
}

/* Play previus song */

void Player::playBack(){

    if(playList.empty()) return;

    if(loopMode == 2)
    {
        playSong(currentSong);
        return;
    }

    int size = playList.length();
    int songIndex =  playList.indexOf(currentSong);

    if(songIndex==0)
    {
        playSong(playList[size - 1].toMap());
    }
    else{
        playSong(playList[songIndex - 1].toMap());
    }

}

