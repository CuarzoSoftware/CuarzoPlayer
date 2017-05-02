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
    OpButton(QIcon icon);
    OpButton(QString image,int width,int height);
    OpButton(QString text,QString style);
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
    void setup();
};

#endif // OPBUTTON_H
