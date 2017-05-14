#include "artistlistitem.h"

extern QString blue;

ArtistListItem::ArtistListItem(QString _icon,QString _text,QString _id)
{
    id = _id;
    setAutoFillBackground(true);
    setObjectName("item");
    setStyleSheet("#item{border-bottom:1px solid #EEE;border-radius:0}");
    text = new CropLabel(_text,"color:#888");
    Pix r;
    icon->setPixmap(r.round(QImage(_icon)));
    icon->setFixedSize(40,40);
    icon->setScaledContents(true);
    layout->setMargin(8);
    layout->addWidget(icon);
    layout->addWidget(text);
}

void ArtistListItem::mousePressEvent(QMouseEvent *event){
    setSelected(true);
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
