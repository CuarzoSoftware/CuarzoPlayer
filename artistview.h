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
    void songPlayed(json song);
    void setData(json _data);
    void sendSyncSong(json song);
    void setSongUploadPercent(int per, int id);
    void songUploaded(json _data);
    void cancelSongUpload(int);


signals:
    void sendSongPlayed(json song);
    void syncSong(json song);
    void sendCancelSongUpload(int);
public slots:
};

#endif // ARTISTVIEW_H
