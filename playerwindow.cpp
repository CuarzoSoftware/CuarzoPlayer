#include "playerwindow.h"
#include "croplabel.h"


PlayerWindow::PlayerWindow()
{
    setStyleSheet("PlayerWindow{background:#FFF}");
    setMinimumSize(800,400);
    setUnifiedTitleAndToolBarOnMac(true);
    addToolBar(Qt::TopToolBarArea,topBar);
    addToolBar(Qt::BottomToolBarArea,bottomBar);
    setFocusPolicy(Qt::ClickFocus);
}




