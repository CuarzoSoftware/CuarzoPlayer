#ifndef SELECTLISTITEM_H
#define SELECTLISTITEM_H

#include <QWidget>
#include <QBoxLayout>
#include <QVariantMap>
#include "croplabel.h"
#include "icon.h"

extern QString blue;

class SelectListItem : public QWidget
{
     Q_OBJECT

public:

    SelectListItem(QVariantMap data)
    {
        iconURL = data["icon"].toString();
        selected = data["selected"].toBool();
        icon = new Icon(iconURL,"#666",16,16);
        selectIcon = new Icon(":res/img/checked.svg","#666",12,12);
        text = new CropLabel(data["text"].toString(),"");
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

    QString iconURL;
    bool selected;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    Icon *icon;
    Icon *selectIcon;
    CropLabel *text;

    void enterEvent(QEvent * event){
        icon->setColor("#FFF");
        text->setStyleSheet("color:#FFF");
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(blue));
        setPalette(pal);
        if(true){
            selectIcon->setColor("#FFF");
        }
        else{
            selectIcon->setColor(blue);
        }
    }

    void leaveEvent(QEvent * event){
        icon->setColor("#666");
        text->setStyleSheet("color:#666");
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor("#FFF"));
        setPalette(pal);
        if(true){
            selectIcon->setColor("#666");
        }
        else{
            selectIcon->setColor("#FFF");
        }
    }

    void mouseReleaseEvent(QMouseEvent *eventPress){
        this->itemSelected(this);
    }

signals:
    void itemSelected(SelectListItem *item);
};

#endif // SELECTLISTITEM_H

