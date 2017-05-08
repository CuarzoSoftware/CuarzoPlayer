#include "storagebar.h"

extern QString blue;
extern QString red;
extern QString orange;
extern QString green;
StorageBar::StorageBar()
{
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(100,15);
    setObjectName("main");
    setStyleSheet("#main{background:#999;border-radius:4px}");


    bar->setParent(this);
    bar->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    bar->setFixedSize(40,15);
    bar->setObjectName("bar");
    bar->setStyleSheet("#bar{background:"+blue+";border-top-left-radius:4px;border-bottom-left-radius:4px}");
    //bar->move(1,1);

    text->setParent(this);
    text->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    text->setFixedSize(100,15);
    text->setText("0.1 GB de 15 GB");
    text->move(10,0);
    text->setStyleSheet("color:#FFF;text-align:center;font-size:8px");
}
