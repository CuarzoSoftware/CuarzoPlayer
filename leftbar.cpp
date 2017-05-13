#include "leftbar.h"

LeftBar::LeftBar()
{
 setAutoFillBackground(true);
 setFixedWidth(170);
 setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
 QPalette pal = palette();
 pal.setColor(QPalette::Background, QColor("#FAFAFA"));
 setPalette(pal);
 scrollLayout->addWidget(scroll);
 scrollLayout->setMargin(0);
 scrollLayout->setSpacing(0);
 scroll->setWidget(frame);
 scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
 scroll->setWidgetResizable( true );
 scroll->setStyleSheet("QScrollArea{border:none}");

 layout->setMargin(0);
 layout->setSpacing(0);
 layout->setAlignment(Qt::AlignTop);

 layout->addWidget(title1);
 layout->addWidget(libraryFrame);
 layout->addWidget(title2);
 layout->addWidget(playlistsFrame);

 items[0] = new LeftBarItem("artists",":res/img/artists.svg","Artists");
 items[1] = new LeftBarItem("albums",":res/img/albums.svg","Albums");
 items[2] = new LeftBarItem("songs",":res/img/songs.svg","Songs");
 items[3] = new LeftBarItem("genres",":res/img/genres.svg","Genres");


 libraryLayout->setMargin(0);
 libraryLayout->setSpacing(0);

 for(int i = 0; i<=3; i++){
     libraryLayout->addWidget(items[i]);
     connect(items[i],SIGNAL(selected(QString)),this,SLOT(itemSelected(QString)));
 }

 items[4] = new LeftBarItem("0",":res/img/playlist.svg","Eduardo's playlist");
 items[5] = new LeftBarItem("1",":res/img/playlist.svg","Viaje");
 items[6] = new LeftBarItem("2",":res/img/playlist.svg","Inspiración");
 items[7] = new LeftBarItem("3",":res/img/playlist.svg","Cásicos");

 for(int i = 4; i<=7; i++){
     playlistsLayout->addWidget(items[i]);
     connect(items[i],SIGNAL(selected(QString)),this,SLOT(itemSelected(QString)));
 }

 playlistsLayout->setMargin(0);
 playlistsLayout->setSpacing(0);

 title1->setStyleSheet("color:#AAA;font-size:10px;font-weight:bold;margin:8px");
 title2->setStyleSheet("color:#AAA;font-size:10px;font-weight:bold;margin:8px");
}

void LeftBar::itemSelected(QString id){
    int i = 0;
    while(items[i] != nullptr){
        if(items[i]->id != id){
            items[i]->setSelected(false);
        }
        i++;
    }
}
