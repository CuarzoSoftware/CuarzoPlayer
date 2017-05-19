#include "topbar.h"


TopBar::TopBar()
{
    QJsonArray data;
    setMaximumHeight(55);
    setMouseTracking(true);
    setStyleSheet("TopBar{border:none;background:transparent;border-bottom:1px solid #DDD;}");
    data.append(QJsonObject({{"icon",":res/img/local.svg"},{"text","Local"},{"selected",true}}));
    data.append(QJsonObject({{"icon",":res/img/cloud.svg"},{"text","Cloud"},{"selected",false}}));
    data.append(QJsonObject({{"icon",":res/img/all.svg"},{"text","All"},{"selected",false}}));
    modeList = new SelectList(data);
    modeList->setFixedWidth(130);
    modeList->menu->setFixedWidth(135);
    frameLayout->setAlignment(Qt::AlignLeft);
    frameLayout->setContentsMargins(8,8,15,8);
    frameLayout->addWidget(userPicture);
    frameLayout->addWidget(storageBar);
    frameLayout->addWidget(modeList);
    frameLayout->addWidget(new QWidget(),10);
    frameLayout->addWidget(pie);
    frameLayout->addWidget(searchBar);
    frameLayout->addWidget(addButton);
    pie->hide();


}

