#ifndef ARTISTLISTITEM_H
#define ARTISTLISTITEM_H

#include <QFrame>
#include <QBoxLayout>
#include <QLabel>
#include "croplabel.h"
#include "pix.h"

class ArtistListItem:public QFrame
{
    Q_OBJECT
public:
    ArtistListItem(QString icon,QString text,QString id);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QLabel *icon = new QLabel();
    CropLabel *text;
    QString id;
    void mousePressEvent(QMouseEvent *event);
signals:
    void selected(QString);
public slots:
    void setSelected(bool selected);
};

#endif // ARTISTLISTITEM_H
