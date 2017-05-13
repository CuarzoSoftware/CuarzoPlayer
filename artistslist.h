#ifndef ARTISTSLIST_H
#define ARTISTSLIST_H

#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>
#include "leftbaritem.h"
#include "artistlistitem.h"

class ArtistsList:public QFrame
{
    Q_OBJECT
public:
    explicit ArtistsList();
    QBoxLayout *scrollLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    QScrollArea *scroll = new QScrollArea();
    QFrame *frame = new QFrame();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
    ArtistListItem *items[10000] = {nullptr};
};

#endif // ARTISTSLIST_H
