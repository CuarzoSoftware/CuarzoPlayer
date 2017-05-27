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

void ArtistView::menuDeleteLocalSongs()
{
    deleteSongs(selectedSongs,"local");
}

void ArtistView::menuDeleteCloudSongs()
{
    deleteSongs(selectedSongs,"cloud");
}

void ArtistView::menuDeleteBothSongs()
{
    deleteSongs(selectedSongs,"both");
}

void ArtistView::menuUploadSongs()
{

}

void ArtistView::menuDownloadSongs()
{

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
        lastSelected = -1;
        song->setSelected(true);
    }

}

void ArtistView::songRightClicked(int id)
{

    bool local = false;
    bool cloud = false;
    bool both  = false;
    bool selected = false;
    bool downloading = false;
    bool uploading = false;

    if(!existSong(id))return;

    AlbumSong *song = getSongById(id);
    selectedSongs.clear();

    if(firstSelected != -1 && lastSelected != -1)
    {
        int from = 0;
        int to = 0;
        if(firstSelected >= lastSelected)
        {
            from = lastSelected;
            to = firstSelected;
        }
        else
        {
            from = firstSelected;
            to = lastSelected;
        }
        for(int i = from; i <= to; i++)
        {
            selectedSongs.append(songs[i]->data);
            if(songs[i]->data["id"] == id) selected = true;
            if(songs[i]->data["local"] && !songs[i]->data["cloud"]) local = true;
            if(!songs[i]->data["local"] && songs[i]->data["cloud"]) cloud = true;
            if(songs[i]->data["local"]  &&  songs[i]->data["cloud"]) both = true;
            if(songs[i]->downloading) downloading = true;
            if(songs[i]->uploading) uploading = true;
        }
    }
    qDebug() <<selected;

    if(!selected)
    {
        selectedSongs.clear();
        selectedSongs.append(song->data);
        if(song->data["local"] && !song->data["cloud"]) local = true;
        if(!song->data["local"] && song->data["cloud"]) cloud = true;
        if(song->data["local"]  &&  song->data["cloud"]) both = true;
        if(song->downloading) downloading = true;
        if(song->uploading) uploading = true;
    }

    QMenu contextMenu(tr("Options"),this);

    QAction action1("Edit Info", this);
    QAction action2("Stop Download", this);
    QAction action3("Stop Upload", this);
    QAction action4("Download", this);
    QAction action5("Upload", this);
    QAction action6("Delete from local", this);
    QAction action7("Delete from cloud", this);
    QAction action8("Delete from everywhere", this);

    if(!uploading&&!downloading)contextMenu.addAction(&action1);
    if(downloading)contextMenu.addAction(&action2);
    if(uploading)contextMenu.addAction(&action3);
    if(!local && cloud && !downloading && !uploading)contextMenu.addAction(&action4);
    if(local && !cloud && !downloading && !uploading)contextMenu.addAction(&action5);
    if(cloud || both)contextMenu.addAction(&action7);
    if(local || both)contextMenu.addAction(&action6);
    if(both && !downloading && !uploading)contextMenu.addAction(&action8);


    connect(&action6, SIGNAL(triggered()), this, SLOT(menuDeleteLocalSongs()));
    connect(&action7, SIGNAL(triggered()), this, SLOT(menuDeleteCloudSongs()));
    connect(&action8, SIGNAL(triggered()), this, SLOT(menuDeleteBothSongs()));


    contextMenu.exec(QCursor::pos());
}

void ArtistView::setSongUploadPercent(int per, int id)
{
    if(!existSong(id)) return;
    AlbumSong *song = getSongById(id);
    song->uploading = true;
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
    song->sync->setIcon(QIcon(":res/img/success.svg"));
    song->sync->setColor(blue);
    song->sync->show();
    song->uploading = false;
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

