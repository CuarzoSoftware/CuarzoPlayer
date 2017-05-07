#include "menu.h"

Menu::Menu()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0,0,0,0));
    setPalette(pal);
    setParent(0);
    setWindowFlags(Qt::ToolTip);
    layout->addWidget(frame);
    layout->setMargin(0);
    menuLayout->setContentsMargins(0,5,0,5);
    menuLayout->setSpacing(0);
    frame->setObjectName("fram");
    frame->setStyleSheet("#fram{border-radius:5px;background:#FFF;border-color:#CCC}");
}
