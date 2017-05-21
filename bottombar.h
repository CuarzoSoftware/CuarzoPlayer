#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QBoxLayout>
#include <QLabel>
#include <QFrame>
#include "songinfo.h"
#include "playerbuttons.h"
#include "timebar.h"
#include "volumebar.h"
#include "opbutton.h"



class BottomBar : public QFrame
{
    Q_OBJECT
public:
    BottomBar();
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    SongInfo *songInfo = new SongInfo();
    PlayerButtons *playerButtons = new PlayerButtons();
    TimeBar *timeBar = new TimeBar();
    VolumeBar *volumeBar = new VolumeBar();
    OpButton *loopButton;
    OpButton *shuffleButton;
    int loopState;
    bool shuffleState;

public slots:
    void toggleLoop();
    void toggleShuffle();
    void setShuffleMode(bool);
    void setLoopMode(int);

signals:
    void sendLoopMode(int);
    void sendShuffleMode(bool);
};

#endif // BOTTOMBAR_H
