#include "selectlistitem.h"

extern QString blue;
SelectListItem::SelectListItem(QJsonObject _data,int _index)
{
    data = _data;
    index = _index;
    icon = new Icon(_data["icon"].toString(),"#666",16,16);
    selectIcon = new Icon(":res/img/checked.svg","#666",12,12);
    text = new CropLabel(_data["text"].toString(),"");
    if(!_data["selected"].toBool()){
        selectIcon->setColor("#FFF");
    }
    layout->addWidget(selectIcon);
    layout->addWidget(icon);
    layout->addWidget(text);
    layout->setMargin(0);
    layout->setContentsMargins(3,5,3,5);
    setAttribute(Qt::WA_Hover, true);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor("#FFF"));
    setPalette(pal);
}

void SelectListItem::enterEvent(QEvent * event){
    icon->setColor("#FFF");
    text->setStyleSheet("color:#FFF");
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(blue));
    setPalette(pal);
    if(data["selected"].toBool()){
        selectIcon->setColor("#FFF");
    }
    else{
        selectIcon->setColor(blue);
    }
}
void SelectListItem::leaveEvent(QEvent * event){
    icon->setColor("#666");
    text->setStyleSheet("color:#666");
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor("#FFF"));
    setPalette(pal);
    if(data["selected"].toBool()){
        selectIcon->setColor("#666");
    }
    else{
        selectIcon->setColor("#FFF");
    }
}

void SelectListItem::mouseReleaseEvent(QMouseEvent *eventPress){
    this->itemSelected(this);
}
