#ifndef SELECTLIST_H
#define SELECTLIST_H

#include <QFrame>
#include <QBoxLayout>
#include <QList>
#include <QLabel>
#include "icon.h"
#include "menu.h"
#include "selectlistitem.h"
#include "json.hpp"

using json = nlohmann::json;

class SelectList : public QFrame
{
    Q_OBJECT
    Icon *currentIcon;
    Icon *selectIcon;
    QLabel *currentText;
public:
    explicit SelectList(json items);
    QList<SelectListItem*> items;
    int size;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    Menu *menu = new Menu();
    void mousePressEvent(QMouseEvent *eventPress);


signals:
    void sendSelected(QString);
public slots:
    void itemSelected(SelectListItem*);
    void setData(json);
};

#endif // SELECTLIST_H
