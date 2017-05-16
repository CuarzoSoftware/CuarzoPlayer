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
    json currentSong;
    json playList;
    QMediaPlayer *player = new QMediaPlayer(this);

signals:
    void songPlaying(json);
    void sendTimePosition(float,float);
public slots:
    void playSong(json);
    void setTime(float percent);
    void timeChanged(qint64 t);
};

#endif // PLAYER_H
