#include "album.h"

using json = nlohmann::json;

extern QString path;

//Creates the album

Album::Album(json data)
{
    setData(data);
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

void Album::setData(json data)
{
    if(data.begin().value()["artWork"])
    {
        artWork->setPixmap(p.borderRadius(QImage(path + "/Cuarzo Player/Artwork/" + QString::fromStdString(data.begin().value()["artist"]) + "/" + QString::fromStdString(data.begin().value()["album"]) + ".png"),12));
    }
    else{
        artWork->setPixmap(p.borderRadius(QImage(":res/img/artWork.png"),12));

    }

    albumName = new CropLabel(QString::fromStdString(data.begin().value()["album"]),"font-size:20px;color:#444;font-weight:bold");

    QString genre = QString::fromStdString(data.begin().value()["genre"]);
    QString year = QString::number((int)data.begin().value()["year"]);
    QString inf = "";

    if(genre != "")                     inf += genre;
    if(genre != NULL && year != "0")    inf += (" - " + year);
    if(genre == NULL && year != "0")    inf += year;
    if(inf != "")                       albumInfo = new CropLabel(inf ,"font-size:13px;color:#888");
    else                                albumInfo = new CropLabel("" ,"font-size:13px;color:#888"); albumInfo->hide();

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

    foreach(json jsong , list)
    {
        AlbumSong *song = new AlbumSong(jsong);
        addSong(song);
    }

    songsNumber->setText(QString::number(songs.size()) + " canciones");

    sort();
}

void Album::addSong(AlbumSong *song)
{
    songsLayout->addWidget(song);
    songs.insert(song->id,song);
}

void Album::sort()
{

    QList<AlbumSong*> sngs = songs.values();

    qSort(sngs.begin(), sngs.end(),[](AlbumSong *a, AlbumSong *b) -> bool {
        return a->data["track"] <= b->data["track"];
    });

    foreach (AlbumSong *song, sngs) {
        songsLayout->addWidget(song);
    }


}





