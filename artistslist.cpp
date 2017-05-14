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

void ArtistsList::artistSelected(int index){
    int i = 0;
    while(items[i] != nullptr){
        items[i]->setSelected(false);
        i++;
    }
    items[index]->setSelected(true);
    sendSelectedArtist(items[index]->data);
}

void ArtistsList::setData(json _data){
    data = _data;
    int ii = 0;
    while(items[ii] != nullptr){
        delete items[ii];
        items[ii] = nullptr;
        ii++;
    }
    int i = 0;
    for (json::iterator it = _data.begin(); it != _data.end(); ++it) {
        items[i] = new ArtistListItem(i,it.value());
        layout->addWidget(items[i]);
        connect(items[i],SIGNAL(selected(int)),this,SLOT(artistSelected(int)));
        i++;
    }
}
