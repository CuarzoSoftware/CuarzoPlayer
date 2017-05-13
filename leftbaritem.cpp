#include "leftbaritem.h"

extern QString blue;

LeftBarItem::LeftBarItem(QString _id,QString _icon,QString _text)
{
    id = _id;
    setMinimumHeight(30);
    icon = new Icon(_icon,"#888",15,15);
    text = new CropLabel(_text,"font-size:11px;color:#888");
    setAutoFillBackground(true);
    layout->setMargin(0);
    layout->addWidget(icon);
    layout->addWidget(text);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor("transparent"));
    setPalette(pal);
    setContentsMargins(15,5,5,5);
}

void LeftBarItem::mousePressEvent(QMouseEvent *event){
    setSelected(true);
    selected(id);
}

void LeftBarItem::setSelected(bool selected){
    if(selected){
        icon->setColor("#FFF");
        text->setStyleSheet("font-size:11px;color:#FFF");
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(blue));
        setPalette(pal);
    }
    else{
        icon->setColor("#888");
        text->setStyleSheet("font-size:11px;color:#888");
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor("transparent"));
        setPalette(pal);
    }
}
