#include "artistview.h"

using json = nlohmann::json;

//Creates the artist window

ArtistView::ArtistView()
{
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(15,0,15,0);
    layout->setSpacing(0);
    layout->addWidget(artistViewTitle);
    layout->addWidget(scroll,10);
    scroll->setStyleSheet("QScrollArea{border:none;background:transparent}");
    scroll->setWidget(albumsFrame);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setWidgetResizable( true );
    albumsFrame->setLayout(albumsLayout);
    albumsFrame->setObjectName("fram");
    albumsFrame->setStyleSheet("#fram{background:transparent}");
    albumsLayout->setMargin(15);
    albumsLayout->setSpacing(40);
}

//Sets the data and print the albums

void ArtistView::setData(json _data){

    //Cleans the previus albums

    qDeleteAll(albums);
    albums.clear();

    data = _data;

    //Create the albums

    int songsCount = 0;

    for (json::iterator it = data.begin(); it != data.end(); ++it)
    {
        Album *album = new Album(0,it.value());
        albumsLayout->addWidget(album);

        connect(album,SIGNAL(songPlayed(json)),this,SIGNAL(sendSongPlayed(json)));
        connect(album,SIGNAL(syncSong(json)),this,SLOT(sendSyncSong(json)));
        connect(album,SIGNAL(songSelected(int)),this,SLOT(songSelected(int)));
        connect(album,SIGNAL(sendCancelSongUpload(int)),this,SLOT(cancelSongUpload(int)));

        songsCount += album->songs.length();

        albums.append(album);
    }

    //Set the artist info in the top bar

    artistViewTitle->artistName->changeText(QString::fromStdString(data.begin().value().begin().value()["artist"]));
    artistViewTitle->artistInfo->changeText(QString::number(albums.length()) + " álbumes, " + QString::number(songsCount) + " canciones");
}

void ArtistView::sendSyncSong(json song)
{
    syncSong(song);
}

//Focus the selected song and unfocus the rest

void ArtistView::songSelected(int id)
{
    if(!existSong(id)) return;

    foreach(Album *album,albums)
    {
        foreach (AlbumSong *song, album->songs)
        {
            song->setSelected(false);
        }
    }

   getSongById(id)->setSelected(true);

}

void ArtistView::setSongUploadPercent(int per, int id)
{
    if(!existSong(id)) return;
    AlbumSong *song = getSongById(id);
    song->pie->show();
    song->sync->hide();
    song->pie->setPercent(per);
    return;
}

//Set the song playing icon visible

void ArtistView::songPlayed(json _data)
{
    int id = _data["id"];
    if(!existSong(id)) return;

    foreach(Album *album,albums)
    {
        foreach (AlbumSong *song, album->songs)
        {
            song->setPlaying(false);
        }
    }

   getSongById(id)->setPlaying(true);
}

//Hide the upload pie when song finishes upload

void ArtistView::songUploaded(json _data)
{
    int id = _data["id"];
    if(!existSong(id)) return;

    AlbumSong *song = getSongById(id);
    song->pie->hide();
    song->space->show();
}

void ArtistView::cancelSongUpload(int sid)
{
    sendCancelSongUpload(sid);
}

bool ArtistView::existSong(int sid)
{
    foreach(Album *album,albums)
    {
        foreach (AlbumSong *song, album->songs)
        {
            if(song->data["id"] == sid)
            {
                return true;
            }
        }
    }
    return false;
}

AlbumSong *ArtistView::getSongById(int sid)
{
    foreach(Album *album,albums)
    {
        foreach (AlbumSong *song, album->songs)
        {
            if(song->data["id"] == sid)
            {
                return song;
            }
        }
    }
}

