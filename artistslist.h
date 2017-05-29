#ifndef ARTISTSLIST_H
#define ARTISTSLIST_H

#include <QWidget>
#include <QBoxLayout>
#include <QMap>
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
    QString selectedArtist;
    QMap<QString,ArtistListItem*>artists;
public slots:
    void setData(json);
    void setLocation(QString);
    void artistSelected(ArtistListItem*);
signals:
    void sendSelectedArtist(QString);
    void hideArtistView(int);
    void showArtistView(int);
};

#endif // ARTISTSLIST_H
