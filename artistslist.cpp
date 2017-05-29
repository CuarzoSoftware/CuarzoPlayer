#include "artistslist.h"

ArtistsList::ArtistsList()
{
    hide();
    setAutoFillBackground(true);
    setMinimumWidth(190);
    setFixedWidth(190);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor("#FFF"));
    frame->setObjectName("fr");
    frame->setPalette(pal);
    frame->setStyleSheet("#fr{border-right:1px solid #F4F4F4;border-radius: 0px;background:#FFF}");

    scrollLayout->addWidget(scroll);
    scrollLayout->setMargin(0);
    scrollLayout->setSpacing(0);
    scroll->setWidget(frame);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setWidgetResizable( true );
    scroll->setStyleSheet("QScrollArea{border:none}");

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);

}

void ArtistsList::setData(json _data){

    qDeleteAll(artists);
    artists.clear();
    for (json::iterator it = _data.begin(); it != _data.end(); ++it) {

        ArtistListItem *artist = new ArtistListItem(it.value());
        artists.insert(QString::fromStdString(it.key()),artist);
        layout->addWidget(artist);
        connect(artist,SIGNAL(selected(ArtistListItem*)),this,SLOT(artistSelected(ArtistListItem*)));


        if(artist->artistName == selectedArtist){
            artist->setSelected(true);
            sendSelectedArtist(selectedArtist);
        }
    }
}


void ArtistsList::setLocation(QString location)
{
    foreach (ArtistListItem *artist, artists) {
       artist->setLocation(location);
    }
}

void ArtistsList::artistSelected(ArtistListItem* ar){
    foreach(ArtistListItem *artist,artists)
    {
        artist->setSelected(false);
    }
    ar->setSelected(true);
    selectedArtist = ar->artistName;
    sendSelectedArtist(selectedArtist);
}

