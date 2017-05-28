#ifndef ARTISTSLIST_H
#define ARTISTSLIST_H

#include <QWidget>
#include <QBoxLayout>
#include <QList>
#include <QScrollArea>
#include "fader.h"
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
    Fader *f = new Fader(this);
    QString selectedArtist;
    QList<ArtistListItem*>items;
public slots:
    void setData(json,QString);
    void artistSelected(ArtistListItem*);
signals:
    void sendSelectedArtist(json data);
    void hideArtistView(int);
    void showArtistView(int);
};

#endif // ARTISTSLIST_H
