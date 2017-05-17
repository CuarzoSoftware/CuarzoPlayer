#include "artistview.h"

using json = nlohmann::json;

//Creates the artist window

ArtistView::ArtistView()
{
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(15);
    layout->setSpacing(20);
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

    int i = 0;

    while (albums[i] != nullptr)
    {
        delete albums[i];
        albums[i] = nullptr;
        i++;
    }

    data = _data;

    //Create the albums

    int albumsCount = 0;
    int songsCount = 0;

    for (json::iterator it = _data.begin(); it != _data.end(); ++it)
    {
        albums[albumsCount] = new Album(albumsCount,it.value());
        albumsLayout->addWidget(albums[albumsCount]);
        connect(albums[albumsCount],SIGNAL(songPlayed(json)),this,SIGNAL(sendSongPlayed(json)));
        connect(albums[albumsCount],SIGNAL(songSelected(int)),this,SLOT(songSelected(int)));

        for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
        {
            songsCount++;
        }

        albumsCount++;
    }

    //Set the artist info in the top bar

    artistViewTitle->artistName->changeText(QString::fromStdString(data.begin().key()));
    artistViewTitle->artistInfo->changeText(QString::number(albumsCount) + " álbumes, " + QString::number(songsCount) + " canciones");
}

//Focus the selected song and unfocus the rest

void ArtistView::songSelected(int id)
{
    int i = 0;

    while(albums[i] != nullptr)
    {
        int ii = 0;

        while(albums[i]->songs[ii] != nullptr)
        {
            albums[i]->songs[ii]->setSelected(false);

            if(albums[i]->songs[ii]->id == id)
            {
                albums[i]->songs[ii]->setSelected(true);
            }
            ii++;
        }
        i++;
    }

}

//Set the song playing icon visible

void ArtistView::songPlayed(json _data)
{
    int i = 0;

    while(albums[i] != nullptr)
    {
        int ii = 0;

        while(albums[i]->songs[ii] != nullptr)
        {
            albums[i]->songs[ii]->setPlaying(false);

            if(albums[i]->songs[ii]->id == (int)_data["id"])
            {
                albums[i]->songs[ii]->setPlaying(true);
            }
            ii++;
        }
        i++;
    }
}
