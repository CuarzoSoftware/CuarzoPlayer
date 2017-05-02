#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QToolBar>
#include <QBoxLayout>
#include <QLabel>
#include "songinfo.h"

class BottomBar : public QToolBar
{
public:
    BottomBar();
    QWidget *frame;
    QBoxLayout *layout;
    SongInfo *songInfo = new SongInfo();
};

#endif // BOTTOMBAR_H
