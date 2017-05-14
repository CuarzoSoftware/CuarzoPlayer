#include "artistlistitem.h"

extern QString blue;
extern QString path;

using json = nlohmann::json;

ArtistListItem::ArtistListItem(int _id, json _data)
{
    id = _id;
    setData(_data);
    setAutoFillBackground(true);
    setObjectName("item");
    setStyleSheet("#item{border-bottom:1px solid #EEE;border-radius:0}");
    icon->setFixedSize(40,40);
    icon->setScaledContents(true);
    layout->setMargin(8);
    layout->addWidget(icon);
    layout->addWidget(text);
}

void ArtistListItem::setData(json _data){
    data = _data;
    json fSong = _data.begin().value().begin().value();
    text = new CropLabel(QString::fromStdString(fSong["artist"]),"color:#888");

    if((bool)fSong["artWork"]){
        icon->setPixmap(r.round(QImage(path + "/Cuarzo Player/Artwork/"+QString::fromStdString(fSong["artist"])+"/"+QString::fromStdString(fSong["album"])+".png")));
    }
    else{
        icon->setPixmap(r.round(QImage(":res/img/artWork.png")));
    }
}

void ArtistListItem::mousePressEvent(QMouseEvent *event){
    selected(id);
}

void ArtistListItem::setSelected(bool selected){
    if(selected){
        text->setStyleSheet("color:#FFF");
        setStyleSheet("#item{background:"+blue+";border-bottom:1px solid #EEE;border-radius:0}");
    }
    else{
        text->setStyleSheet("color:#888");
        setStyleSheet("#item{background:#FFF;border-bottom:1px solid #EEE;border-radius:0}");
    }
}
