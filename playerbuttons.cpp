#include "playerbuttons.h"
#include <QBoxLayout>

PlayerButtons::PlayerButtons(QWidget *parent) : QWidget(parent)
{
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    layout->setMargin(0);
    layout->setSpacing(5);
    layout->addWidget(back);
    layout->addWidget(play);
    layout->addWidget(next);
    connect(play,SIGNAL(released()),this,SLOT(playPause()));
}



void PlayerButtons::playPause(){
    if(playing){
        playing = false;
        setPlay(false);
        play->setIcon(QIcon(":res/img/pause.svg"));
    }else{
        playing = true;
        setPlay(true);
        play->setIcon(QIcon(":res/img/play.svg"));
    }
}
