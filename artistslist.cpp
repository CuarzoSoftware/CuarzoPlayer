#include "artistslist.h"

ArtistsList::ArtistsList()
{
    setAutoFillBackground(true);
    setFixedWidth(170);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor("#FFF"));
    frame->setObjectName("fr");
    frame->setPalette(pal);
    frame->setStyleSheet("#fr{border-right:1px solid #F4F4F4;border-radius: 0px;background:#FFF}");

    scrollLayout->addWidget(scroll);
    scrollLayout->setMargin(0);
    scrollLayout->setSpacing(0);
    scroll->setWidget(frame);
    scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scroll->setWidgetResizable( true );
    scroll->setStyleSheet("QScrollArea{border:none}");

    items[0] = new ArtistListItem(":res/img/artWork.png","Desconocido","1");
    items[1] = new ArtistListItem(":res/img/artWork.png","Desconocido","2");
    items[2] = new ArtistListItem(":res/img/artWork.png","Desconocido","3");

    layout->addWidget(items[0]);
    layout->addWidget(items[1]);
    layout->addWidget(items[2]);

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);
}
