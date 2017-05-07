#include <QMouseEvent>
#include "timebar.h"


TimeBar::TimeBar(QWidget *parent) : QWidget(parent)
{
    extern QString blue;

    setMinimumWidth(250);
    layout = new QBoxLayout(QBoxLayout::LeftToRight,this);

    baseBar = new QWidget();
    baseBar->setStyleSheet("background:#EEE;border-radius:1px");
    baseBar->setFixedHeight(5);
    baseBar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    baseBar->setMouseTracking(true);

    loadingBar = new QWidget(baseBar);
    loadingBar->setStyleSheet("background:#DDD;border-radius:1px");
    loadingBar->setFixedHeight(5);
    loadingBar->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    loadingBar->setFixedWidth(100);

    currentTimeBar = new QWidget(baseBar);
    currentTimeBar->setStyleSheet("background:"+blue+";border-radius:1px");
    currentTimeBar->setFixedHeight(5);
    currentTimeBar->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    currentTimeBar->setFixedWidth(50);

    currentTime->setStyleSheet("color:#666;font-size:10px");
    remainingTime->setStyleSheet("color:#666;font-size:10px");

    layout->addWidget(currentTime);
    layout->addWidget(baseBar);
    layout->addWidget(remainingTime);

    baseBar->installEventFilter(this);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


}

void TimeBar::setPosition(int percent){
    currentTimeBar->setFixedWidth(baseBar->width()/100*percent);
}

bool TimeBar::eventFilter(QObject *obj, QEvent *event)
 {
    if (obj == baseBar && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
        currentTimeBar->setFixedWidth(mEvent->localPos().x());
        positionChanged(baseBar->width()/100*currentTime->width());
    }
    return false;
 }
