#include "topbar.h"
#include <QLabel>

TopBar::TopBar()
{
    setMovable(false);
    layout()->setMargin(8);
    QJsonArray data;
    data.append(QJsonObject({{"icon",":res/img/local.svg"},{"text","Local"},{"selected",true}}));
    data.append(QJsonObject({{"icon",":res/img/cloud.svg"},{"text","Cloud"},{"selected",false}}));
    data.append(QJsonObject({{"icon",":res/img/all.svg"},{"text","All"},{"selected",false}}));
    modeList = new SelectList(data);
    modeList->setFixedWidth(130);
    modeList->menu->setFixedWidth(135);
    addWidget(modeList);
}
