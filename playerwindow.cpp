#include "playerwindow.h"
#include "croplabel.h"
#include <QApplication>


PlayerWindow::PlayerWindow()
{
    setContextMenuPolicy(Qt::NoContextMenu);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMinimumSize(800,400);
    setLayout(mainLayout);
    mainLayout->setMargin(0);
    mainLayout->addWidget(frame);
    frame->setObjectName("MainFrame");
    frame->setStyleSheet("#MainFrame{background:#FFF}");
    frameLayout->setMargin(0);
    frameLayout->setSpacing(0);
    frameLayout->addWidget(topBar);
    frameLayout->addWidget(middleView);
    frameLayout->addWidget(bottomBar);
}




