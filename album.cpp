#include "album.h"

Album::Album()
{
    setStyleSheet("background:#FFF");
    artWork->setPixmap(p.borderRadius(QImage("/users/eduardo/mac.jpg"),12));
    artWork->setScaledContents(true);
    artWork->setMaximumSize(150,150);
    artWork->setStyleSheet("border-radius:10px;border:2px solid #EEE");
    songsNumber->setText("14 canciones");
    songsNumber->setStyleSheet("color:#888");
    albumName = new CropLabel("This Old Dog","font-size:20px;color:#444;font-weight:bold");
    albumInfo = new CropLabel("Pop - 2017","font-size:13px;color:#888");

    layout->addWidget(artWorkFrame);
    layout->addWidget(rightFrame,10);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignTop);

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
}
