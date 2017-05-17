#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include "pix.h";

class TimeBar : public QWidget
{
    Q_OBJECT

public:

    explicit TimeBar();
    Pix r;
    QBoxLayout *layout;
    QLabel *currentTime = new QLabel("0:00");
    QLabel *remainingTime = new QLabel("0:00");
    QWidget *baseBar;
    QWidget *currentTimeBar;
    float timePosition = 0;
    bool eventFilter(QObject *obj, QEvent *event);

signals:

    void positionChanged(float);

public slots:

    void setTimePosition(float);
    void getTimePosition(float,float);

};

#endif // TIMEBAR_H
