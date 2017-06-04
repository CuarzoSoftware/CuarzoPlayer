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


class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player();
    bool shuffle = false;
    int loopMode = 0;
    QString playFrom;
    QVariantMap currentSong;
    QVariantMap settings;
    QVariantList playList;
    QNetworkReply *reply;
    QFile *file = new QFile();
    VlcInstance *vlc = new VlcInstance(VlcCommon::args(), this);
    VlcMediaPlayer *player = new VlcMediaPlayer(vlc);


signals:
    void songPlaying(QVariantMap);
    void sendTimePosition(float,float);
    void sendState(bool);
public slots:
    void positionChanged(float position);
    void playSong(QVariantMap);
    void setTime(float percent);
    void setLoopMode(int);
    void setShuffle(bool);
    void play(bool);
    void playPause();
    void playNext();
    void playBack();

};

#endif // PLAYER_H
