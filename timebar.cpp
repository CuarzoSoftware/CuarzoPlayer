#include <QMouseEvent>
#include "timebar.h"


TimeBar::TimeBar()
{
    extern QString blue;

    setMinimumWidth(250);
    layout = new QBoxLayout(QBoxLayout::LeftToRight,this);

    baseBar = new QWidget();
    baseBar->setStyleSheet("background:#EEE;border-radius:1px");
    baseBar->setFixedHeight(5);
    baseBar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    baseBar->setMouseTracking(true);
    baseBar->installEventFilter(this);

    currentTimeBar = new QWidget(baseBar);
    currentTimeBar->setStyleSheet("background:"+blue+";border-radius:1px");
    currentTimeBar->setFixedHeight(5);
    currentTimeBar->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    currentTimeBar->setFixedWidth(50);

    currentTime->setStyleSheet("color:#666;font-size:10px");
    currentTime->setFixedWidth(30);
    remainingTime->setStyleSheet("color:#666;font-size:10px");
    remainingTime->setFixedWidth(30);


    layout->addWidget(currentTime);
    layout->addWidget(baseBar);
    layout->addWidget(remainingTime);

    baseBar->installEventFilter(this);

    timePosition = 0;

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


}

void TimeBar::setTimePosition(float percent)
{
    timePosition = percent;
    int w = (float)baseBar->width()/1000*percent;
    currentTimeBar->setFixedWidth(w);
}

void TimeBar::getTimePosition(float c,float t)
{
    float per = 1000/t*c;
    setTimePosition(per);
    currentTime->setText(r.timeFromSecconds(c));
    remainingTime->setText("- " + r.timeFromSecconds(t - c));
}


bool TimeBar::eventFilter(QObject *obj, QEvent *event)
 {
    if (obj == baseBar && event->type() == QEvent::Resize)
    {
        setTimePosition(timePosition);
    }

    if (obj == baseBar && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
        positionChanged((float)1/(float)baseBar->width()*(float)mEvent->localPos().x());
    }

    return false;
 }
