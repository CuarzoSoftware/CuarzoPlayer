#include "middleview.h"

MiddleView::MiddleView()
{
    setChildrenCollapsible(false);
    setHandleWidth(0);
    addWidget(leftBar);
    addWidget(artistsList);
    addWidget(artistView);

    artistsList->hide();
    artistView->hide();

    setStyleSheet("QSplitter::handle{background-color: black;}");
}
