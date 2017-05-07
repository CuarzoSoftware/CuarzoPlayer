#include "topbar.h"
#include <QLabel>

TopBar::TopBar()
{
    QJsonArray data;
    addWidget(frame);
    setMovable(false);
    setStyleSheet("TopBar{border:none;background:#FFF;border-bottom:1px solid #DDD;}");
    data.append(QJsonObject({{"icon",":res/img/local.svg"},{"text","Local"},{"selected",true}}));
    data.append(QJsonObject({{"icon",":res/img/cloud.svg"},{"text","Cloud"},{"selected",false}}));
    data.append(QJsonObject({{"icon",":res/img/all.svg"},{"text","All"},{"selected",false}}));
    modeList = new SelectList(data);
    modeList->setFixedWidth(130);
    modeList->menu->setFixedWidth(135);
    frameLayout->addWidget(modeList);
}
