#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>
#include "artistviewtitle.h"
#include "album.h"
#include "json.hpp"


using json = nlohmann::json;

class ArtistView : public QWidget
{
    Q_OBJECT
public:
    explicit ArtistView();
    json data;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QScrollArea *scroll = new QScrollArea();
    QWidget *albumsFrame = new QWidget();
    QBoxLayout *albumsLayout = new QBoxLayout(QBoxLayout::TopToBottom,albumsFrame);
    ArtistViewTitle *artistViewTitle = new ArtistViewTitle();
    Album *albums[2048] = {nullptr};

public slots:
    void songSelected(int id);
    void songPlayed(json);
    void setData(json _data);

signals:
    void sendSongPlayed(json);
public slots:
};

#endif // ARTISTVIEW_H
