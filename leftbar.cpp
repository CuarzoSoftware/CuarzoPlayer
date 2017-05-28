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
 scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded);
 scroll->setWidgetResizable( true );
 scroll->setStyleSheet("QScrollArea{border:none}");

 layout->setMargin(0);
 layout->setSpacing(0);
 layout->setAlignment(Qt::AlignTop);

 layout->addWidget(title1);
 layout->addWidget(libraryFrame);
 layout->addWidget(title2);
 layout->addWidget(playlistsFrame);

 items.append(new LeftBarItem("artists",":res/img/artists.svg","Artists"));
 items.append(new LeftBarItem("albums",":res/img/albums.svg","Albums"));
 items.append(new LeftBarItem("songs",":res/img/songs.svg","Songs"));
 items.append(new LeftBarItem("genres",":res/img/genres.svg","Genres"));


 libraryLayout->setMargin(0);
 libraryLayout->setSpacing(0);

 foreach(LeftBarItem *item,items){
     libraryLayout->addWidget(item);
     connect(item,SIGNAL(selected(QString)),this,SLOT(itemSelected(QString)));
 }

 items.append(new LeftBarItem("0",":res/img/playlist.svg","Eduardo's playlist"));
 items.append(new LeftBarItem("1",":res/img/playlist.svg","Viaje"));
 items.append(new LeftBarItem("2",":res/img/playlist.svg","Inspiración"));
 items.append(new LeftBarItem("3",":res/img/playlist.svg","Cásicos"));

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
    sendSelected(id);
    foreach(LeftBarItem *item,items){
        if(item->id != id){
            item->setSelected(false);
        }
        else{
            item->setSelected(true);
        }
    }
}
