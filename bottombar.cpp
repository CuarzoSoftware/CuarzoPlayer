#include "bottombar.h"
#include <QBitmap>
#include <QPainter>

extern QString blue;
extern QString lightGray;


BottomBar::BottomBar()
{
    loopState = 1;
    shuffleState = 1;
    loopButton = new OpButton(":res/img/loop.svg",27,27,blue);
    shuffleButton = new OpButton(":res/img/shuffle.svg",27,27,blue);

    connect(loopButton,SIGNAL(released()),this,SLOT(toggleLoop()));
    connect(shuffleButton,SIGNAL(released()),this,SLOT(toggleShuffle()));

    setStyleSheet("QToolBar{border:none;background:#FFF;border-top:1px solid #DDD;}");
    setMovable(false);
    frame = new QWidget();
    layout = new QBoxLayout(QBoxLayout::LeftToRight,frame);
    layout->setSpacing(5);
    addWidget(frame);

    layout->addWidget(songInfo,0);
    layout->addWidget(playerButtons,0);
    layout->addWidget(timeBar,1);
    layout->addWidget(volumeBar,0);
    layout->addWidget(loopButton,0);
    layout->addWidget(shuffleButton,0);
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
}
void BottomBar::toggleShuffle(){
    if(shuffleState == 0){
        shuffleButton->setColor(blue);
        shuffleState = 1;
    }
    else{
        shuffleButton->setColor(lightGray);
        shuffleState = 0;
    }
}
