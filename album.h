#ifndef ALBUM_H
#define ALBUM_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QList>
#include "croplabel.h"
#include "opbutton.h"
#include "albumsong.h"
#include "pix.h"
#include "json.hpp"
#include "jsort.h"


using json = nlohmann::json;

extern QString blue;

class Album:public QWidget
{
    Q_OBJECT
public:
    Album(int _id, json _data);
    Pix p;
    JSort s;
    int id;
    json data;
    QWidget *artWorkFrame = new QWidget();
    QWidget *artWorkBottomFrame = new QWidget();
    QWidget *nameFrame = new QWidget();
    QWidget *rightFrame = new QWidget();
    QWidget *songsFrame= new QWidget();
    QFrame *infoFrame = new QFrame();

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QBoxLayout *artWorkLayout = new QBoxLayout(QBoxLayout::TopToBottom,artWorkFrame);
    QBoxLayout *artWorkBottomLayout = new QBoxLayout(QBoxLayout::LeftToRight,artWorkBottomFrame);
    QBoxLayout *songsLayout = new QBoxLayout(QBoxLayout::TopToBottom,songsFrame);

    QBoxLayout *rightLayout = new QBoxLayout(QBoxLayout::TopToBottom,rightFrame);
    QBoxLayout *infoLayout = new QBoxLayout(QBoxLayout::LeftToRight,infoFrame);
    QBoxLayout *nameLayout = new QBoxLayout(QBoxLayout::TopToBottom,nameFrame);

    QLabel *artWork = new QLabel();
    CropLabel *albumName;
    CropLabel *albumInfo;
    QLabel *songsNumber = new QLabel();

    OpButton *shuffle = new OpButton(":res/img/shuffle.svg",20,20,blue);
    OpButton *more = new OpButton(":res/img/more.svg",20,20,blue);
    OpButton *sync = new OpButton(":res/img/sync-border.svg",20,20,blue);

    QList<AlbumSong*>songs;

signals:
    void songSelected(int);
    void songPlayed(json);
    void syncSong(json);
    void sendCancelSongUpload(int);
    void songRightClicked(int);
    void deleteSong(json,QString);

public slots:
    void sendSelectedSong(int);
    void sendPlayedSong(json);
    void setData(json);
    void sendSyncSong(json);
    void cancelSongUpload(int);
};




#endif // ALBUM_H
