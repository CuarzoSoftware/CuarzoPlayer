#include "album.h"

using json = nlohmann::json;

extern QString path;

//Creates the album

Album::Album(int _id, json _data, QString location)
{
    id = _id;
    setData(_data,location);
    artWork->setScaledContents(true);
    artWork->setMaximumSize(150,150);
    artWork->setStyleSheet("border-radius:10px;border:2px solid #EEE");
    songsNumber->setStyleSheet("color:#888");


    layout->addWidget(artWorkFrame);
    layout->addWidget(rightFrame,10);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(25);

    artWorkLayout->addWidget(artWork);
    artWorkLayout->addWidget(artWorkBottomFrame);
    artWorkLayout->addWidget(new QWidget(),10);
    artWorkLayout->setAlignment(Qt::AlignTop);
    artWorkLayout->setMargin(0);
    artWorkLayout->setSpacing(0);
    artWorkBottomLayout->setAlignment(Qt::AlignTop);
    artWorkBottomLayout->addWidget(songsNumber,10);
    artWorkBottomLayout->addWidget(shuffle);
    artWorkBottomLayout->setContentsMargins(2,8,2,8);

    rightLayout->addWidget(infoFrame);
    rightLayout->addWidget(songsFrame,10);
    rightLayout->setMargin(0);
    infoLayout->addWidget(nameFrame,10);
    //infoLayout->addWidget(sync);
    infoLayout->addWidget(more);
    infoLayout->setMargin(5);
    infoFrame->setObjectName("info");
    infoFrame->setStyleSheet("#info{border-bottom:1px solid #EEE;border-radius:0}");
    nameLayout->setMargin(0);
    nameLayout->addWidget(albumName);
    nameLayout->addWidget(albumInfo);

    songsLayout->setAlignment(Qt::AlignTop);
    songsLayout->setMargin(0);
    songsLayout->setSpacing(0);


}

//Set the albums data

void Album::setData(json _data, QString location)
{
    data = _data;
    libraryLocationSelected = location;

    //Sets the artwork

    if(data.begin().value()["artWork"])
    {
        artWork->setPixmap(p.borderRadius(QImage(path + "/Cuarzo Player/Artwork/" + QString::fromStdString(data.begin().value()["artist"]) + "/" + QString::fromStdString(data.begin().value()["album"]) + ".png"),12));
    }
    else{
        artWork->setPixmap(p.borderRadius(QImage(":res/img/artWork.png"),12));

    }

    //Set the album info

    albumName = new CropLabel(QString::fromStdString(data.begin().value()["album"]),"font-size:20px;color:#444;font-weight:bold");

    QString genre = QString::fromStdString(data.begin().value()["genre"]);
    QString year = QString::number((int)data.begin().value()["year"]);
    QString inf = "";

    if(genre != "")                     inf += genre;
    if(genre != NULL && year != "0")    inf += (" - " + year);
    if(genre == NULL && year != "0")    inf += year;
    if(inf != "")                       albumInfo = new CropLabel(inf ,"font-size:13px;color:#888");
    else                                albumInfo = new CropLabel("" ,"font-size:13px;color:#888"); albumInfo->hide();



    //Create the songs

    bool isAlbumSynched = true;

    QList<json> list;

    for (json::iterator it = data.begin(); it != data.end(); ++it)
    {
        list.append(it.value());
        if(!it.value()["cloud"] || !it.value()["local"])
        {
            isAlbumSynched = false;
        }
    }

    qSort(list.begin(), list.end(),[](json a, json b) -> bool {
        int ans = QString::fromStdString(a["album"]).compare(QString::fromStdString(b["album"]));
        return (a["track"] <= b["track"] && ans == 0) || ans == -1;
    });

    foreach(json jsong , list)
    {
        AlbumSong *song = new AlbumSong(jsong, libraryLocationSelected);
        songsLayout->addWidget(song);
        connect(song,SIGNAL(songSelected(int)),this,SLOT(sendSelectedSong(int)));
        connect(song,SIGNAL(songPlayed(json)),this,SLOT(sendPlayedSong(json)));
        connect(song,SIGNAL(syncSong(json)),this,SLOT(sendSyncSong(json)));
        connect(song,SIGNAL(cancelDownload(int)),this,SLOT(cancelSongUpload(int)));
        connect(song,SIGNAL(songRightClicked(int)),this,SIGNAL(songRightClicked(int)));
        connect(song,SIGNAL(deleteSong(json,QString)),this,SIGNAL(deleteSong(json,QString)));
        songs.append(song);
    }


    //Set the songs count info

    songsNumber->setText(QString::number(songs.length()) + " canciones");
}

//Events

void Album::sendSelectedSong(int id){
    songSelected(id);
}

void Album::sendPlayedSong(json _data){
    songPlayed(_data);
}
void Album::sendSyncSong(json _data){
    syncSong(_data);
}

void Album::cancelSongUpload(int sid)
{
    sendCancelSongUpload(sid);
}




