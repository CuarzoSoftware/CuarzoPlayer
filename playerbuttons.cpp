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
}



void PlayerButtons::setPlay(bool playing){
    if(playing){
        play->setIcon(QIcon(":res/img/pause.svg"));
    }else{
        play->setIcon(QIcon(":res/img/play.svg"));
    }
}
