#include "artistslist.h"

ArtistsList::ArtistsList()
{

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

void ArtistsList::artistSelected(ArtistListItem* item){
    foreach(ArtistListItem *it,items)
    {
        it->setSelected(false);
    }
    item->setSelected(true);
    selectedArtist = item->artistName;
    sendSelectedArtist(item->data);
}

void ArtistsList::setData(json _data,QString location){

    qDeleteAll(items);
    items.clear();
    bool found = false;
    if(location == "local" || location == "cloud")
    {

        for (json::iterator it = _data.begin(); it != _data.end(); ++it) {
            bool hasLocalSongs = false;
            for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
                for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) {
                    if(it3.value()[location.toStdString()]){
                        hasLocalSongs = true;
                    }
                }
            }
            if(!hasLocalSongs) continue;
            ArtistListItem *item = new ArtistListItem(it.value());
            items.append(item);
            layout->addWidget(item);
            connect(item,SIGNAL(selected(ArtistListItem*)),this,SLOT(artistSelected(ArtistListItem*)));
            if(item->artistName == selectedArtist){
                item->setSelected(true);
                sendSelectedArtist(item->data);
                found = true;
            }
        }
    }
    else{
        for (json::iterator it = _data.begin(); it != _data.end(); ++it) {
            ArtistListItem *item = new ArtistListItem(it.value());
            items.append(item);
            layout->addWidget(item);
            connect(item,SIGNAL(selected(ArtistListItem*)),this,SLOT(artistSelected(ArtistListItem*)));
            if(item->artistName == selectedArtist){
                item->setSelected(true);
                sendSelectedArtist(item->data);
                found = true;
            }
        }
    }

    if(!found && items.length() == 0)
    {
        hideArtistView(256);
    }

    if(!found && items.length() != 0)
    {
        items[0]->setSelected(true);
        sendSelectedArtist(items[0]->data);
        f->fadeIn(256);
        showArtistView(256);
    }

    if(found){
        f->fadeIn(256);
        showArtistView(256);
    }


}
