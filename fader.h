#ifndef FADER_H
#define FADER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class Fader : public QObject{

    Q_OBJECT
public:

    QWidget *w;

    Fader(QWidget *ob){
        w = ob;
    }

public slots:



    void fadeIn(int duration){

        QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
        w->setGraphicsEffect(eff);
        QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
        a->setDuration(duration);
        a->setStartValue(0);
        a->setEndValue(1);
        a->setEasingCurve(QEasingCurve::InBack);
        a->start(QPropertyAnimation::DeleteWhenStopped);
        connect(a,SIGNAL(finished()),this,SIGNAL(endFadeIn()));

    }
    void fadeOut(int duration){
        QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
        w->setGraphicsEffect(eff);
        QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
        a->setDuration(duration);
        a->setStartValue(1);
        a->setEndValue(0);
        a->setEasingCurve(QEasingCurve::OutBack);
        a->start(QPropertyAnimation::DeleteWhenStopped);
        connect(a,SIGNAL(finished()),this,SIGNAL(endFadeOut()));
    }
signals:
    void endFadeIn();
    void endFadeOut();
};



#endif // FADER_H
