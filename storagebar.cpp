#include "storagebar.h"
#include <QDebug>

extern QString blue;
extern QString red;
extern QString orange;
extern QString green;

StorageBar::StorageBar()
{
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(100,20);
    setObjectName("main");
    setStyleSheet("#main{background:#999;border-radius:6px}");

    bar->setParent(this);
    bar->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    bar->setFixedSize(0,20);
    bar->setObjectName("bar");
    bar->setStyleSheet("#bar{background:"+blue+";border-top-left-radius:6px;border-bottom-left-radius:6px}");

    text->setParent(this);
    text->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    text->setFixedSize(100,20);
    text->move(10,0);
    text->setStyleSheet("color:#FFF;text-align:center;font-size:10px");
}
void StorageBar::setPercent(long used, long total){
    float per = (float)100/(float)total*(float)used;
    if(per<6){
        per = 6;
    }
    bar->setFixedWidth(per);
    text->setText(QString::number((float)used/1000000000, 'f', 1 ) + " GB / " +  QString::number(total/1000000000, 'f', 1 ) + " GB");
}
