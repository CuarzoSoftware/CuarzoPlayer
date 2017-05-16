#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <VLC/Common.h>
#include <VLC/Media.h>
#include <VLC/Instance.h>
#include <VLC/MediaPlayer.h>
#include <VLC/Audio.h>
#include "json.hpp"

using json = nlohmann::json;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player();
    json currentSong;
    json playList;
    VlcInstance *vlc = new VlcInstance(VlcCommon::args(), this);
    VlcMediaPlayer *player = new VlcMediaPlayer(vlc);
    VlcAudio *audio = new VlcAudio(player);
signals:
    void songPlaying(json);
    void sendTimePosition(float,float);
public slots:
    void playSong(json);
    void setTime(float percent);
    void timeChanged(int t);
};

#endif // PLAYER_H
