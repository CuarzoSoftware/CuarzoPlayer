#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QToolBar>
#include <QBoxLayout>
#include <QLabel>
#include "songinfo.h"
#include "playerbuttons.h"
#include "timebar.h"
#include "volumebar.h"
#include "opbutton.h"

class BottomBar : public QToolBar
{
public:
    BottomBar();
    QWidget *frame;
    QBoxLayout *layout;
    SongInfo *songInfo = new SongInfo();
    PlayerButtons *playerButtons = new PlayerButtons();
    TimeBar *timeBar = new TimeBar();
    VolumeBar *volumeBar = new VolumeBar();
    OpButton *loopButton = new OpButton(":res/img/loop.svg",27,27,"#2687FB");
    OpButton *shuffleButton = new OpButton(":res/img/shuffle.svg",27,27,"#2687FB");
};

#endif // BOTTOMBAR_H
