#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QBuffer>
#include <QList>

#include "Common.h"
#include "Instance.h"
#include "Media.h"
#include "Audio.h"
#include "MediaPlayer.h"

#include "json.hpp"

using json = nlohmann::json;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player();
    bool shuffle = false;
    int loopMode = 0;
    QString playFrom;
    json currentSong;
    json settings;
    QList<json> playList;
    QNetworkReply *reply;
    QFile *file = new QFile();
    VlcInstance *vlc = new VlcInstance(VlcCommon::args(), this);
    VlcMediaPlayer *player = new VlcMediaPlayer(vlc);


signals:
    void songPlaying(json);
    void sendTimePosition(float,float);
    void sendState(bool);
public slots:
    void positionChanged(float position);
    void playSong(json);
    void setTime(float percent);
    void setLoopMode(int);
    void setShuffle(bool);
    void play(bool);
    void playPause();
    void playNext();
    void playBack();
    void downloadTempSong(json song);
    void setBuffer();
    void endBuffer();
    void downloadProg(qint64,qint64);

};

#endif // PLAYER_H
