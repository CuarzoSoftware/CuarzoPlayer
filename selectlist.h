#ifndef SELECTLIST_H
#define SELECTLIST_H

#include <QFrame>
#include <QJsonArray>
#include <QBoxLayout>
#include <QLabel>
#include "icon.h"
#include "menu.h"
#include "selectlistitem.h"

class SelectList : public QFrame
{
    Q_OBJECT
    Icon *currentIcon;
    Icon *selectIcon;
    QLabel *currentText;
public:
    explicit SelectList(QJsonArray items);
    SelectListItem *items[1000];
    int size;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    Menu *menu = new Menu();
    void mousePressEvent(QMouseEvent *eventPress);


signals:

public slots:
    void itemSelected(SelectListItem*);
};

#endif // SELECTLIST_H
