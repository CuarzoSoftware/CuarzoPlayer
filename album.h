#ifndef ALBUM_H
#define ALBUM_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include "croplabel.h"
#include "opbutton.h"
#include "pix.h";

extern QString blue;
extern QString path;

class Album:public QWidget
{
    Q_OBJECT
public:

    QString artist;
    QString album;
    int songsCount = 1;
    Pix p;
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

    QFrame *artWork = new QFrame();
    CropLabel *albumName;
    CropLabel *albumInfo;
    QLabel *songsNumber = new QLabel();

    OpButton *shuffle = new OpButton(":res/img/shuffle.svg",20,20,blue);
    OpButton *more = new OpButton(":res/img/more.svg",20,20,blue);

    Album(QVariantMap data)
    {
        artist = data["artist"].toString();
        album = data["album"].toString();
        albumName = new CropLabel(album,"font-size:20px;color:#444;font-weight:bold");
        if(data["artWork"].toBool())
        {
            artWork->setStyleSheet("border-image:url(\""+path + "/Cuarzo Player/Artwork/" + data["artist"].toString() + "/" + data["album"].toString() + ".jpg"+"\"); background-position: center;border-radius:6px");
        }
        else{
            artWork->setStyleSheet("border-image:url(\":res/img/artWork.png\"); background-position: center;border-radius:6px");
        }
        QString genre = data["genre"].toString();
        QString year = QString::number(data["year"].toInt());
        QString inf = "";

        if(genre != "")                     inf += genre;
        if(genre != "" && year != "0")      inf += (" - " + year);
        if(genre == "" && year != "0")      inf += year;
        if(inf != ""){
            albumInfo = new CropLabel(inf ,"font-size:13px;color:#888");
        }
        else{
            albumInfo = new CropLabel("" ,"font-size:13px;color:#888");
        }

        artWork->setFixedSize(180,180);
        songsNumber->setStyleSheet("color:#888");
        albumInfo->setFixedHeight(15);

        layout->addWidget(artWorkFrame);
        layout->addWidget(rightFrame,10);
        layout->setMargin(0);
        layout->setAlignment(Qt::AlignTop);
        layout->setSpacing(25);

        artWorkLayout->addWidget(artWork);
        artWorkLayout->addWidget(artWorkBottomFrame);
        artWorkLayout->addWidget(new QWidget(),10);
        artWorkLayout->setAlignment(Qt::AlignTop);
        artWorkLayout->setMargin(0);
        artWorkLayout->setSpacing(0);
        artWorkBottomLayout->setAlignment(Qt::AlignTop);
        artWorkBottomLayout->addWidget(songsNumber,10);
        artWorkBottomLayout->addWidget(shuffle);
        artWorkBottomLayout->setContentsMargins(2,8,2,8);

        rightLayout->addWidget(infoFrame);
        rightLayout->addWidget(songsFrame,10);
        rightLayout->setMargin(0);
        infoLayout->addWidget(nameFrame,10);
        infoLayout->addWidget(more);
        infoLayout->setMargin(5);
        infoFrame->setObjectName("info");
        infoFrame->setStyleSheet("#info{border-bottom:1px solid #EEE;border-radius:0}");
        nameLayout->setMargin(0);
        nameLayout->addWidget(albumName);
        nameLayout->addWidget(albumInfo);

        songsLayout->setAlignment(Qt::AlignTop);
        songsLayout->setMargin(0);
        songsLayout->setSpacing(0);

    }
    void refreshSongCount(){
        if(songsCount == 1)
        {
            songsNumber->setText("1 Song");
        }
        else{
            songsNumber->setText(QString::number(songsCount) + " Songs");
        }
    }
signals:
    void shuffleAlbum(QString artist,QString album);
};




#endif // ALBUM_H
