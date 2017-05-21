#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
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
    json playList;
    QMediaPlayer *player = new QMediaPlayer(this);

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
    void mediaChanged(QMediaPlayer::MediaStatus);

};

#endif // PLAYER_H
