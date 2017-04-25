#include "opbutton.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

OpButton::OpButton(QString icon, int width, int height)
{
    this->setStyleSheet("OpButton{background:transparent;border:none;color:red}");
    this->setIcon(QIcon(icon));
    this->opacity = new QGraphicsOpacityEffect();
    this->opacity->setOpacity(0.1);
    this->setGraphicsEffect(opacity);
    this->setIconSize(QSize(width,height));
    this->opacity->setOpacity(1);
    connect(this,SIGNAL(pressed()),this,SLOT(active()));
    connect(this,SIGNAL(released()),this,SLOT(inactive()));
}

void OpButton::active(){
    this->animation = new QPropertyAnimation(this, "opacityLevel");
    this->animation->setDuration(100);
    this->animation->setStartValue(1);
    this->animation->setEndValue(0.5);
    this->animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void OpButton::inactive(){
    this->animation = new QPropertyAnimation(this, "opacityLevel");
    this->animation->setDuration(100);
    this->animation->setStartValue(0.5);
    this->animation->setEndValue(1);
    this->animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,SIGNAL(finished()),this,SLOT(reset()));
}

void OpButton::reset(){
    this->opacity = new QGraphicsOpacityEffect();
    this->opacity->setOpacity(1);
    this->setGraphicsEffect(opacity);
}

