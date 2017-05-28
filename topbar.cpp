#include "topbar.h"


TopBar::TopBar()
{

    setMaximumHeight(55);
    setMouseTracking(true);
    setStyleSheet("TopBar{border:none;background:transparent;border-bottom:1px solid #DDD;}");
    json data;
    data[0]["icon"] = ":res/img/local.svg";
    data[0]["text"] = "Local";
    data[0]["selected"] = true;
    data[1]["icon"] = ":res/img/cloud.svg";
    data[1]["text"] = "Cloud";
    data[1]["selected"] = false;
    data[2]["icon"] = ":res/img/all.svg";
    data[2]["text"] = "All";
    data[2]["selected"] = false;
    modeList = new SelectList(data);
    modeList->setFixedWidth(130);
    modeList->menu->setFixedWidth(135);
    frameLayout->setAlignment(Qt::AlignLeft);
    frameLayout->setContentsMargins(8,8,15,8);
    frameLayout->setSpacing(10);
    frameLayout->addWidget(userPicture);
    frameLayout->addWidget(addAccount);
    frameLayout->addWidget(storageBar);
    frameLayout->addWidget(modeList);
    frameLayout->addWidget(new QWidget(),10);
    frameLayout->addWidget(pie);
    frameLayout->addWidget(searchBar);
    frameLayout->addWidget(addButton);
    pie->hide();

}

