#include "bottombar.h"
#include <QBitmap>
#include <QPainter>

extern QString blue;
extern QString lightGray;


BottomBar::BottomBar()
{
    loopState = 1;
    shuffleState = true;
    loopButton = new OpButton(":res/img/loop.svg",27,27,blue);
    shuffleButton = new OpButton(":res/img/shuffle.svg",27,27,blue);

    connect(loopButton,SIGNAL(released()),this,SLOT(toggleLoop()));
    connect(shuffleButton,SIGNAL(released()),this,SLOT(toggleShuffle()));
    setMaximumHeight(75);

    setStyleSheet("BottomBar{border:none;background:transparent;border-top:1px solid #DDD;}");
    frameLayout->setSpacing(5);

    frameLayout->addWidget(songInfo,0);
    frameLayout->addWidget(playerButtons,0);
    frameLayout->addWidget(timeBar,1);
    frameLayout->addWidget(volumeBar,0);
    frameLayout->addWidget(loopButton,0);
    frameLayout->addWidget(shuffleButton,0);
}

void BottomBar::toggleLoop(){
    if(loopState == 0){
        loopButton->setIcon(QIcon(":res/img/loop.svg"));
        loopButton->setColor(blue);
        loopState = 1;
    }
    else if(loopState == 1){
        loopButton->setIcon(QIcon(":res/img/loop-one.svg"));
        loopButton->setColor(blue);
        loopState = 2;
    }
    else if(loopState == 2){
        loopButton->setIcon(QIcon(":res/img/loop.svg"));
        loopButton->setColor(lightGray);
        loopState = 0;
    }
    sendLoopMode(loopState);
}
void BottomBar::toggleShuffle(){
    if(!shuffleState){
        shuffleButton->setColor(blue);
        shuffleState = true;
    }
    else{
        shuffleButton->setColor(lightGray);
        shuffleState = false;
    }
    sendShuffleMode(shuffleState);
}
