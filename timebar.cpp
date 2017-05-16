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
    currentTime->setFixedWidth(30);
    remainingTime->setStyleSheet("color:#666;font-size:10px");
    remainingTime->setFixedWidth(30);


    layout->addWidget(currentTime);
    layout->addWidget(baseBar);
    layout->addWidget(remainingTime);

    baseBar->installEventFilter(this);

    timePosition = 0;
    loadPosition = 0;

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


}

void TimeBar::setTimePosition(float percent){
    timePosition = percent;
    int w = (float)baseBar->width()/1000*percent;
    currentTimeBar->setFixedWidth(w);
}
void TimeBar::getTimePosition(float c,float t){
    float per = (1000/t/1000) *c;
    setTimePosition(per);
    currentTime->setText(r.timeFromSecconds(c/1000));
    remainingTime->setText("- " + r.timeFromSecconds(t - c/1000));
}
void TimeBar::setLoadPosition(int per){
    //qDebug()<<per;
    loadPosition = per;
    float w = (float)baseBar->width()/(float)100*(float)per;
    //loadingBar->setFixedWidth((int)w);
}

bool TimeBar::eventFilter(QObject *obj, QEvent *event)
 {
    if (obj == baseBar && event->type() == QEvent::Resize) {
        setTimePosition(timePosition);
        setLoadPosition(loadPosition);
    }
    if (obj == baseBar && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
        positionChanged((float)1000/(float)baseBar->width()*(float)mEvent->localPos().x());
    }
    return false;
 }
