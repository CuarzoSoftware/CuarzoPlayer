#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QBuffer>
#include <QList>
#include "json.hpp"

#include <gst/gst.h>
#include <glib.h>

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
    QMediaPlayer *player = new QMediaPlayer(this,QMediaPlayer::StreamPlayback);
    QNetworkReply *reply;
    QBuffer *buffer = new QBuffer(this);
    QFile *file = new QFile();
    QByteArray *data = new QByteArray();

signals:
    void songPlaying(json);
    void sendTimePosition(float,float);
    void sendState(bool);
public slots:
    void playSong(json);
    void setTime(float percent);
    void timeChanged(qint64 t);
    void setLoopMode(int);
    void setShuffle(bool);
    void play(bool);
    void playPause();
    void playNext();
    void playBack();
    void downloadTempSong(json song);
    void mediaChanged(QMediaPlayer::MediaStatus);
    void setBuffer();
    void endBuffer();

};

#endif // PLAYER_H
