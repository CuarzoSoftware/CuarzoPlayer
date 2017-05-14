#ifndef ARTISTSLIST_H
#define ARTISTSLIST_H

#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>
#include "leftbaritem.h"
#include "artistlistitem.h"
#include "json.hpp"

using json = nlohmann::json;

class ArtistsList:public QFrame
{
    Q_OBJECT
public:
    explicit ArtistsList();
    QBoxLayout *scrollLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    QScrollArea *scroll = new QScrollArea();
    QFrame *frame = new QFrame();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
    json data;
    ArtistListItem *items[10000] = {nullptr};
public slots:
    void setData(json);
    void artistSelected(int);
signals:
    void sendSelectedArtist(json data);
};

#endif // ARTISTSLIST_H
