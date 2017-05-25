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

    songs.clear();

    //Cleans the previus albums

    firstSelected = -1;
    lastSelected = -1;

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
        connect(album,SIGNAL(songRightClicked(int)),this,SLOT(songRightClicked(int)));
        connect(album,SIGNAL(deleteSong(json,QString)),this,SLOT(deleteSong(json,QString)));

        songsCount += album->songs.length();

        songs.append(album->songs);
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

    foreach (AlbumSong *song, songs)
    {
        song->setSelected(false);
    }


    AlbumSong *song = getSongById(id);
    int index = songs.indexOf(song);

    if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
    {

        if(firstSelected == -1)
        {
            firstSelected = index;
            song->setSelected(false);
        }
        else
        {
            lastSelected = index;

            if(firstSelected > lastSelected)
            {
                for(int i = lastSelected; i <= firstSelected; i++)
                {
                    songs[i]->setSelected(true);
                }
            }
            else
            {
                for(int i = firstSelected; i <= lastSelected; i++)
                {
                    songs[i]->setSelected(true);
                }
            }
        }
    }
    else{
        firstSelected = index;
        song->setSelected(true);
    }

}

void ArtistView::songRightClicked(int id)
{
    QMenu contextMenu(tr("Options"),this);

    QAction action1("Edit Info", this);
    QAction action2("Stop Download", this);
    QAction action3("Stop Upload", this);
    QAction action4("Download", this);
    QAction action5("Upload", this);

    contextMenu.addAction(&action1);
    contextMenu.addAction(&action2);
    contextMenu.addAction(&action3);
    contextMenu.addAction(&action4);
    contextMenu.addAction(&action5);

    //connect(&action2, SIGNAL(triggered()), this, SLOT(piePressed()));
    //connect(&action3, SIGNAL(triggered()), this, SLOT(piePressed()));
    //connect(&action4, SIGNAL(triggered()), this, SLOT(syncClicked()));
    //connect(&action5, SIGNAL(triggered()), this, SLOT(syncClicked()));

    //contextMenu.exec(QCursor::pos());
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

void ArtistView::deleteSong(json song, QString from)
{
    QList<json>_songs;
    _songs.append(song);
    deleteSongs(_songs,from);
}

void ArtistView::hideSong(json song)
{
    int id = song["id"];
    if(!existSong(id)) return;
    getSongById(id)->hide();
}

void ArtistView::changeSong(json song)
{
    int id = song["id"];
    if(!existSong(id)) return;
    getSongById(id)->setData(song);
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

