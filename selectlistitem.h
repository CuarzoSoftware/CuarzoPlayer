#ifndef SELECTLISTITEM_H
#define SELECTLISTITEM_H

#include <QWidget>
#include <QBoxLayout>
#include "croplabel.h"
#include "icon.h"

#include "json.hpp"

using json = nlohmann::json;

class SelectListItem:public QWidget
{
     Q_OBJECT
public:
    SelectListItem(json data,int index);
    json data;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    int index;
    Icon *icon;
    Icon *selectIcon;
    CropLabel *text;
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
    void mouseReleaseEvent(QMouseEvent *eventPress);

signals:
    void itemSelected(SelectListItem *item);
};

#endif // SELECTLISTITEM_H
