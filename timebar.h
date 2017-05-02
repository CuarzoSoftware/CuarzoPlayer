#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

class TimeBar : public QWidget
{
    Q_OBJECT
public:
    explicit TimeBar(QWidget *parent = 0);
    QBoxLayout *layout;
    QLabel *currentTime = new QLabel("00:00");
    QLabel *remainingTime = new QLabel("00:00");
    QWidget *baseBar;
    QWidget *loadingBar;
    QWidget *currentTimeBar;
    void setPosition(int percent);
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void positionChanged(int position);
public slots:

};

#endif // TIMEBAR_H
