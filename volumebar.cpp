#include "volumebar.h"

VolumeBar::VolumeBar(QWidget *parent) : QWidget(parent)
{
    setMinimumWidth(100);
    layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    icon->setMaximumSize(20,20);
    icon->setPixmap(QPixmap(":res/img/volume-low.svg"));
    icon->setScaledContents(true);
    slider->setMaximum(100);
    slider->setMinimum(0);
    layout->addWidget(icon);
    layout->addWidget(slider);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(positionChanged(int)));
}

void VolumeBar::positionChanged(int per){
    if(per < 10){
        icon->setPixmap(QPixmap(":res/img/volume-low.svg"));
    }
    else if(per >= 10 && per<80){
        icon->setPixmap(QPixmap(":res/img/volume-medium.svg"));
    }
    else{
        icon->setPixmap(QPixmap(":res/img/volume-high.svg"));
    }
}
