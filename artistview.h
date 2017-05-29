#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <QMap>
#include <QScrollArea>
#include "artistviewtitle.h"
#include "album.h"
#include "json.hpp"


using json = nlohmann::json;

class ArtistView : public QWidget
{
    Q_OBJECT
public:
    explicit ArtistView(json);

    //VARIABLES
    QList<AlbumSong*> songs;
    QMap<QString,Album*> albums;

    //ELEMENTS
    QWidget *albumsFrame = new QWidget();
    QVBoxLayout *albumsLayout = new QVBoxLayout(albumsFrame);
    QVBoxLayout *layout = new QVBoxLayout(this);
    ArtistViewTitle *artistViewTitle = new ArtistViewTitle();
    QScrollArea *scroll = new QScrollArea();


public slots:
    void addAlbum(Album*);
    void sort();
};

#endif // ARTISTVIEW_H
