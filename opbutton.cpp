#include "opbutton.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

OpButton::OpButton(QString icon, int width, int height)
{
    this->setStyleSheet("OpButton{background:transparent;border:none;color:red}");
    this->setIcon(QIcon(icon));
    opacity = new QGraphicsOpacityEffect();
    opacity->setOpacity(0.1);
    this->setGraphicsEffect(opacity);
    this->setIconSize(QSize(width,height));
    opacity->setOpacity(1);
    connect(this,SIGNAL(pressed()),this,SLOT(active()));
    connect(this,SIGNAL(released()),this,SLOT(inactive()));
}

void OpButton::active(){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "opacityLevel");
    animation->setDuration(100);
    animation->setStartValue(1);
    animation->setEndValue(0.5);
    animation->start();
}

void OpButton::inactive(){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "opacityLevel");
    animation->setDuration(100);
    animation->setStartValue(0.5);
    animation->setEndValue(1);
    animation->start();
}
