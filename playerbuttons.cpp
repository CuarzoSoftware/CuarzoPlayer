#include "playerbuttons.h"
#include <QBoxLayout>

PlayerButtons::PlayerButtons(QWidget *parent) : QWidget(parent)
{
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    layout->setMargin(0);
    layout->setSpacing(5);
    layout->addWidget(back);
    layout->addWidget(play);
    layout->addWidget(next);
}
