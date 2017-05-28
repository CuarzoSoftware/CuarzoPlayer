#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QApplication>
#include <QList>
#include "bouncyscroll.h"
#include "fader.h"
#include "artistviewtitle.h"
#include "album.h"
#include "json.hpp"


using json = nlohmann::json;

class ArtistView : public QWidget
{
    Q_OBJECT
public:
    explicit ArtistView();

    //VARIABLES
    QString libraryLocationSelected;
    QList<json> selectedSongs;
    QList<AlbumSong*> songs;
    int firstSelected = -1;
    int lastSelected = -1;
    QList<Album*> albums;
    json data;


    //ELEMENTS
    QWidget *albumsFrame = new QWidget();
    QBoxLayout *albumsLayout = new QBoxLayout(QBoxLayout::TopToBottom,albumsFrame);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    ArtistViewTitle *artistViewTitle = new ArtistViewTitle();
    BouncyScroll *scroll = new BouncyScroll();
    Fader *f = new Fader(this);



public slots:

    //CONSTRUCTORS
    void setData(json, QString);

    //MENUS
    void menuDeleteLocalSongs();
    void menuDeleteCloudSongs();
    void menuDeleteBothSongs();
    void menuDownloadSongs();
    void menuUploadSongs();


    //SONGS
    void setSongUploadPercent(int,int);
    void deleteSong(json,QString);
    AlbumSong *getSongById(int);
    void cancelSongUpload(int);
    void songRightClicked(int);
    void songSelected(int id);
    void sendSyncSong(json);
    void songUploaded(json);
    void changeSong(json);
    void songPlayed(json);
    void hideSong(json);
    bool existSong(int);

signals:

    //SONGS
    void deleteSongs(QList<json>,QString);
    void sendCancelSongUpload(int);
    void sendSongPlayed(json);
    void syncSong(json);

};

#endif // ARTISTVIEW_H
