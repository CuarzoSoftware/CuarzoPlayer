#include "middleview.h"

MiddleView::MiddleView()
{
    setChildrenCollapsible(false);
    setHandleWidth(0);
    addWidget(leftBar);
    addWidget(msg);

    setStyleSheet("QSplitter::handle{background-color: black;}");
}
