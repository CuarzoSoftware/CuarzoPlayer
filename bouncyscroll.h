#ifndef BOUNCYSCROLL_H
#define BOUNCYSCROLL_H
#include <QScrollArea>
#include <QDebug>
#include <QScrollBar>

class BouncyScroll:public QScrollArea{
    Q_OBJECT
public:
    BouncyScroll(){
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        verticalScrollBar()->setSingleStep(5);
        connect(verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(acelerate));
    }

public slots:
    void acelerate(){

    }
};

#endif // BOUNCYSCROLL_H
