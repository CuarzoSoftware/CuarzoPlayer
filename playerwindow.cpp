#include "playerwindow.h"
#include "croplabel.h"
#include <QApplication>


PlayerWindow::PlayerWindow()
{

    setWindowFlags(Qt::CustomizeWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setContextMenuPolicy(Qt::NoContextMenu);
    setMinimumSize(800,400);
    setLayout(mainLayout);
    mainLayout->setMargin(0);
    mainLayout->addWidget(frame);
    frame->setObjectName("MainFrame");
    frame->setStyleSheet("#MainFrame{background:#FFF;border-radius:10px}");
    frameLayout->setMargin(0);
    frameLayout->setSpacing(0);
    frameLayout->addWidget(titleBar);
    frameLayout->addWidget(topBar);
    frameLayout->addWidget(middleView);
    frameLayout->addWidget(bottomBar);
    connect(titleBar,SIGNAL(closeWindow()),this,SLOT(closeWindow()));
    connect(titleBar,SIGNAL(minimizeWindow()),this,SLOT(minimizeWindow()));
    connect(titleBar,SIGNAL(maximizeWindow()),this,SLOT(maximizeWindow()));
}
void PlayerWindow::closeWindow(){
     QApplication::quit();
}
void PlayerWindow::maximizeWindow(){
     showMaximized();
}
void PlayerWindow::minimizeWindow(){
     showMinimized();
}
void PlayerWindow::showWindow(){
     show();
}



