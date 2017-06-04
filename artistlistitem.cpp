#include "artistlistitem.h"

extern QString blue;
extern QString path;


//Create an artists list item for the left bar

ArtistListItem::ArtistListItem(QVariantMap data)
{
    setData(data);
    setAutoFillBackground(true);
    setObjectName("item");
    setStyleSheet("#item{border-bottom:1px solid #EEE;border-radius:0}");
    icon->setFixedSize(40,40);
    icon->setObjectName("Ic");
    layout->setMargin(8);
    layout->addWidget(icon);
    layout->addWidget(text);
}

//Set the artists info

void ArtistListItem::setData(QVariantMap data)
{
    artistName = data["artist"].toString();
    text = new CropLabel(data["artist"].toString(),"color:#888");

    if(data["artWork"].toBool())
    {
        icon->setStyleSheet("#Ic{border-image:url(\""+path + "/Cuarzo Player/Artwork/"+data["artist"].toString()+"/"+data["album"].toString()+".jpg"+"\"); background-position: center;border-radius:4px}");

    }
    else{
        icon->setStyleSheet("#Ic{border-image:url(\":res/img/artWork.png\"); background-position: center;border-radius:4px}");

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




void ArtistListItem::mousePressEvent(QMouseEvent*){
    selected(artistName);
}

