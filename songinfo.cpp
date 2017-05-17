#include "songinfo.h"

extern QString path;

SongInfo::SongInfo()
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

void SongInfo::setData(json data){
    if(data["artWork"]){
        artWork->setPixmap(r.borderRadius(QImage(path + "/Cuarzo Player/Artwork/" + QString::fromStdString(data["artist"]) + "/" + QString::fromStdString(data["album"]) + ".png") ,10));
    }else{
        artWork->setPixmap(r.borderRadius(QImage(":res/img/artWork.png") ,10));

    }
    song->changeText(QString::fromStdString(data["title"]));
    artist->changeText(QString::fromStdString(data["artist"]));
}
