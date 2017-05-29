#include "artistlistitem.h"

extern QString blue;
extern QString path;

using json = nlohmann::json;

//Create an artists list item for the left bar

ArtistListItem::ArtistListItem(json _data)
{
    artistName = QString::fromStdString(_data.begin().value().begin().value()["artist"]);
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

//Set the artists info

void ArtistListItem::setData(json _data)
{
    data = _data;
    json fSong = _data.begin().value().begin().value();
    text = new CropLabel(QString::fromStdString(fSong["artist"]),"color:#888");

    if(fSong["artWork"])
    {
        icon->setPixmap(r.round(QImage(path + "/Cuarzo Player/Artwork/"+QString::fromStdString(fSong["artist"])+"/"+QString::fromStdString(fSong["album"])+".png")));
    }
    else{
        icon->setPixmap(r.round(QImage(":res/img/artWork.png")));
    }
}

void ArtistListItem::setSelected(bool selected)
{
    if(selected){
        text->setStyleSheet("color:#FFF");
        setStyleSheet("#item{background:"+blue+";border-bottom:1px solid #EEE;border-radius:0}");
    }
    else{
        text->setStyleSheet("color:#888");
        setStyleSheet("#item{background:#FFF;border-bottom:1px solid #EEE;border-radius:0}");
    }
}

void ArtistListItem::setLocation(QString location)
{
    bool local = false;
    bool cloud = false;

    for (json::iterator it = data.begin(); it != data.end(); ++it) {
        for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
            if(it2.value()["local"]){
                local = true;
            }
            if(it2.value()["cloud"]){
                cloud = true;
            }
        }
    }

    if(location == "local" && local || location == "cloud" && cloud || location == "both" && local || location == "both" && cloud ){
        show();
    }
    else{
        hide();
    }

}


void ArtistListItem::mousePressEvent(QMouseEvent*){
    selected(this);
}

