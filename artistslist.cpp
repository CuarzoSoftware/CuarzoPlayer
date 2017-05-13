#include "artistslist.h"

ArtistsList::ArtistsList()
{
    scrollLayout->addWidget(scroll);
    scrollLayout->setMargin(0);
    scrollLayout->setSpacing(0);
    scroll->setWidget(frame);
    scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scroll->setWidgetResizable( true );
    scroll->setStyleSheet("QScrollArea{border:none}");

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);
}
