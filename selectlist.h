#ifndef SELECTLIST_H
#define SELECTLIST_H

#include <QFrame>
#include <QBoxLayout>
#include <QList>
#include <QLabel>
#include "icon.h"
#include "menu.h"
#include "selectlistitem.h"


class SelectList : public QFrame
{
    Q_OBJECT
public:

    Icon *currentIcon = new Icon(":res/img/local.svg","#666",16,16);
    Icon *selectIcon = new Icon(":res/img/listArrow.svg","#666",16,16);
    QLabel *currentText;
    QList<SelectListItem*> items;
    int size;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    Menu *menu = new Menu();

    SelectList(QVariantList list)
    {
        setData(list);
        setStyleSheet("SelectList{border-radius:5px;background:white;border:1px solid #D8D8D8}");
        currentText = new QLabel("Local");
        layout->setContentsMargins(7,4,4,4);
        layout->addWidget(currentIcon);
        layout->addWidget(currentText);
        layout->addWidget(selectIcon);
        menu->setMaximumWidth(width());
        setMaximumHeight(25);

    }

    void mousePressEvent(QMouseEvent *eventPress){
        menu->move(mapToGlobal(QPoint(this->pos().x() - 167,this->pos().y() - 20)));
        menu->show();
    }


signals:
    void sendSelected(QString);

public slots:

    void itemSelected(SelectListItem *item){
        foreach(SelectListItem *it,items){
            it->selected = false;
            it->selectIcon->setColor("#FFF");
        }
        item->selected = true;
        sendSelected(item->text->text());
        currentText->setText(item->text->text());
        currentIcon->setUrl(item->iconURL);
        menu->hide();
    }

    void setData(QVariantList data)
    {
        qDeleteAll(items);
        items.clear();
        foreach(QVariant it,data)
        {
            SelectListItem *item = new SelectListItem(it.toMap());
            items.append(item);
            connect(item,SIGNAL(itemSelected(SelectListItem*)),this,SLOT(itemSelected(SelectListItem*)));
            menu->menuLayout->addWidget(item);
        }
    }
};

#endif // SELECTLIST_H







