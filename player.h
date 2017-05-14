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
    QMediaPlayer *mediaPlayer = new QMediaPlayer(this);
    json playList;
signals:
    void songPlaying(json);
public slots:
    void playSong(json);
};

#endif // PLAYER_H
