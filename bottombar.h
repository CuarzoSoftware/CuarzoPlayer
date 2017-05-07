#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QBoxLayout>
#include <QLabel>
#include <QToolBar>
#include "songinfo.h"
#include "playerbuttons.h"
#include "timebar.h"
#include "volumebar.h"
#include "opbutton.h"



class BottomBar : public QToolBar
{
    Q_OBJECT
public:
    BottomBar();
    QWidget *frame = new QWidget();
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::LeftToRight,frame);
    SongInfo *songInfo = new SongInfo();
    PlayerButtons *playerButtons = new PlayerButtons();
    TimeBar *timeBar = new TimeBar();
    VolumeBar *volumeBar = new VolumeBar();
    OpButton *loopButton;
    OpButton *shuffleButton;
    int shuffleState, loopState;

public slots:
    void toggleLoop();
    void toggleShuffle();
};

#endif // BOTTOMBAR_H
