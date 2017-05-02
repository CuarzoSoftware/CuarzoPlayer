#include "bottombar.h"
#include <QBitmap>
#include <QPainter>

BottomBar::BottomBar()
{

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
