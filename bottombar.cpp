#include "bottombar.h"

BottomBar::BottomBar()
{
    setStyleSheet("QToolBar{border:none;background:#FFF;border-top:1px solid #DDD;}");
    setMovable(false);
    frame = new QWidget();
    layout = new QBoxLayout(QBoxLayout::LeftToRight,frame);
    this->addWidget(frame);

    layout->addWidget(songInfo);
}
