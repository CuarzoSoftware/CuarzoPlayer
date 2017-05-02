#include "opbutton.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

OpButton::OpButton(QString icon, int width, int height)
{
    setIcon(QIcon(icon));
    setIconSize(QSize(width,height));
    setStyleSheet("OpButton{background:transparent;border:none;}");
    setup();
}

OpButton::OpButton(QString txt, QString style)
{
    setText(txt);
    setStyleSheet("OpButton{background:transparent;border:none;"+style+"}");
    setup();
}
OpButton::OpButton(QIcon ico)
{
    setIcon(ico);
    setStyleSheet("OpButton{background:transparent;border:none;}");
    setup();
}

void OpButton::setup(){
    opacity = new QGraphicsOpacityEffect();
    opacity->setOpacity(0.1);
    opacity->setOpacity(1);
    setGraphicsEffect(opacity);
    connect(this,SIGNAL(pressed()),this,SLOT(active()));
    connect(this,SIGNAL(released()),this,SLOT(inactive()));
}

void OpButton::active(){
    animation = new QPropertyAnimation(this, "opacityLevel");
    animation->setDuration(100);
    animation->setStartValue(1);
    animation->setEndValue(0.5);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void OpButton::inactive(){
    animation = new QPropertyAnimation(this, "opacityLevel");
    animation->setDuration(100);
    animation->setStartValue(0.5);
    animation->setEndValue(1);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,SIGNAL(finished()),this,SLOT(reset()));
}

void OpButton::reset(){
    this->opacity = new QGraphicsOpacityEffect();
    this->opacity->setOpacity(1);
    this->setGraphicsEffect(opacity);
}

