#ifndef OPBUTTON_H
#define OPBUTTON_H

#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class OpButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(float opacityLevel READ opacityLevel WRITE setOpacityLevel)
    QPropertyAnimation *animation;

public:
    OpButton(QString,int,int);
    QGraphicsOpacityEffect *opacity;
    void setOpacityLevel (float level){
        this->opacity->setOpacity((qreal)level);
    }
    float opacityLevel(){
        return 0;
    }
signals:

private slots:
    void active();
    void inactive();
    void reset();
};

#endif // OPBUTTON_H
