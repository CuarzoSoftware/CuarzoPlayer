#include "artistlistitem.h"

extern QString blue;

ArtistListItem::ArtistListItem(QString _icon,QString _text,QString _id)
{
    id = _id;
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor("#FFF"));
    setPalette(pal);
    setObjectName("item");
    setStyleSheet("#item{border-bottom:1px solid #EEE}");
    text = new CropLabel(_text,"color:#444");
    Pix r;
    icon->setPixmap(r.round(QImage("/users/eduardo/mac.jpg")));
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
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(blue));
        setPalette(pal);
    }
    else{
        text->setStyleSheet("color:#888");
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor("transparent"));
        setPalette(pal);
    }
}
