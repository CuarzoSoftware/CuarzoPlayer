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
    ArtistListItem(QVariantMap data);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QWidget *icon = new QWidget();
    CropLabel *text;
    QString artistName;
    Pix r;
    void mousePressEvent(QMouseEvent *event);
signals:
    void selected(QString);
public slots:
    void setData(QVariantMap data);
    void setSelected(bool selected);
};

#endif // ARTISTLISTITEM_H
