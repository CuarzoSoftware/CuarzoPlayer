#include "album.h"

using json = nlohmann::json;

extern QString path;

//Creates the album

Album::Album(int _id, json _data)
{
    id = _id;
    setData(_data);
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
    infoLayout->addWidget(sync);
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

void Album::setData(json _data)
{
    data = _data;

    //Detect if the entire albums is synched

    if(data.begin().value()["albumSynched"]){
        sync->hide();
    }

    //Sets the artwork

    if(data.begin().value()["artWork"])
    {
        artWork->setPixmap(p.borderRadius(QImage(path + "/Cuarzo Player/Artwork/" + QString::fromStdString(data.begin().value()["artist"]) + "/" + QString::fromStdString(data.begin().value()["album"]) + ".png"),12));
    }
    else{
        artWork->setPixmap(p.borderRadius(QImage(":res/img/artWork.png"),12));

    }

    //Set the album info

    albumName= new CropLabel(QString::fromStdString(data.begin().value()["album"]),"font-size:20px;color:#444;font-weight:bold");
    albumInfo = new CropLabel(QString::fromStdString(data.begin().value()["genre"]) + " - " + QString::number((int)data.begin().value()["year"]),"font-size:13px;color:#888");

    //Create the songs

    int songsCount = 0;
    json sorted = s.sortByKey(data,"track","int");

    for (json::iterator it = sorted.begin(); it != sorted.end(); ++it)
    {
        songs[songsCount] = new AlbumSong(it.value());
        songsLayout->addWidget(songs[songsCount]);
        connect(songs[songsCount],SIGNAL(songSelected(int)),this,SLOT(sendSelectedSong(int)));
        connect(songs[songsCount],SIGNAL(songPlayed(json)),this,SLOT(sendPlayedSong(json)));
        songsCount++;
    }

    //Set the songs count info

    songsNumber->setText(QString::number(songsCount) + " canciones");
}

//Events

void Album::sendSelectedSong(int id){
    songSelected(id);
}

void Album::sendPlayedSong(json _data){
    songPlayed(_data);
}


