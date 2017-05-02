#include "songinfo.h"

SongInfo::SongInfo()
{
    artWork = new QLabel();
    artWork->setPixmap(QPixmap(":res/img/artWork.png"));
    artWork->setScaledContents(true);
    artWork->setMaximumWidth(50);
    artWork->setMaximumHeight(50);
    song = new CropLabel("Strawberry Fields Forever","font-size:11px;color:#444;font-weight:bold");
    artist = new CropLabel("The Beatles","font-size:10px;color:#666");
    layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QWidget *textFrame = new QWidget();
    textFrame->setSizeIncrement(1,1);
    textFrame->setMinimumWidth(190);
    QBoxLayout *textLayout = new QBoxLayout(QBoxLayout::TopToBottom,textFrame);
    textLayout->setMargin(0);
    textLayout->setSpacing(0);
    textLayout->addWidget(song);
    textLayout->addWidget(artist);
    layout->addWidget(artWork);
    layout->addWidget(textFrame);
    layout->setMargin(0);
}
