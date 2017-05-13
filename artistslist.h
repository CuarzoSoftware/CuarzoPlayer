#ifndef ARTISTSLIST_H
#define ARTISTSLIST_H

#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>
#include "leftbaritem.h"

class ArtistsList
{
    Q_OBJECT
public:
    explicit ArtistsList();
    QBoxLayout *scrollLayout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QScrollArea *scroll = new QScrollArea();
    QWidget *frame = new QWidget();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
    ArtistsListItem *items[10000] = {nullptr};
};

#endif // ARTISTSLIST_H
