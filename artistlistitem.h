#ifndef ARTISTLISTITEM_H
#define ARTISTLISTITEM_H

#include <QFrame>
#include <QBoxLayout>
#include <QLabel>
#include "croplabel.h"
#include "pix.h"
#include "json.hpp"

using json = nlohmann::json;

class ArtistListItem:public QFrame
{
    Q_OBJECT
public:
    ArtistListItem(json _data);
    json data;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QLabel *icon = new QLabel();
    CropLabel *text;
    QString artistName;
    Pix r;
    void mousePressEvent(QMouseEvent *event);
signals:
    void selected(ArtistListItem*);
public slots:
    void setData(json _data);
    void setSelected(bool selected);
};

#endif // ARTISTLISTITEM_H
