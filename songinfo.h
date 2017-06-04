#ifndef SONGINFO_H
#define SONGINFO_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <pix.h>
#include "croplabel.h"

extern QString path;

class SongInfo : public QWidget
{
    Q_OBJECT
public:
    SongInfo()
    {
        setFixedWidth(180);
        artWork = new QLabel();
        artWork->setPixmap(r.borderRadius(QImage(":res/img/artWork.png"),10));
        artWork->setScaledContents(true);
        artWork->setFixedSize(50,50);
        song = new CropLabel("Song","font-size:11px;color:#444;font-weight:bold");
        artist = new CropLabel("Album","font-size:10px;color:#666");
        layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
        QWidget *textFrame = new QWidget();
        QBoxLayout *textLayout = new QBoxLayout(QBoxLayout::TopToBottom,textFrame);
        textLayout->setMargin(0);
        textLayout->setSpacing(0);
        textLayout->addWidget(song);
        textLayout->addWidget(artist);
        layout->addWidget(artWork);
        layout->addWidget(textFrame,10);
        layout->setMargin(0);
    }

    Pix r;
    QBoxLayout *layout;
    QLabel *artWork;
    CropLabel *song;
    CropLabel *artist;

public slots:
    void setData(QVariantMap data){
        if(data["artWork"].toBool()){
            artWork->setPixmap(r.borderRadius(QImage(path + "/Cuarzo Player/Artwork/" + data["artist"].toString() + "/" + data["album"].toString() + ".jpg") ,10));
        }else{
            artWork->setPixmap(r.borderRadius(QImage(":res/img/artWork.png") ,10));

        }
        song->changeText(data["title"].toString());
        artist->changeText(data["artist"].toString());
    }
    void clear(){
        artWork->setPixmap(r.borderRadius(QImage(":res/img/artWork.png") ,10));
        song->changeText("Song");
        artist->changeText("Artist");
    }
};

#endif // SONGINFO_H





