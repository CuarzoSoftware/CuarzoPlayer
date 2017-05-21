#ifndef PLAYERBUTTONS_H
#define PLAYERBUTTONS_H

#include <QWidget>
#include "opbutton.h"

class PlayerButtons : public QWidget
{
    Q_OBJECT
public:
    int size = 25;
    explicit PlayerButtons(QWidget *parent = 0);
    OpButton *back = new OpButton(":res/img/back.svg",size,size);
    OpButton *play = new OpButton(":res/img/play.svg",size,size);
    OpButton *next = new OpButton(":res/img/next.svg",size,size);
public slots:
    void setPlay(bool);
};

#endif // PLAYERBUTTONS_H
