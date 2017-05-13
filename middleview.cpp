#include "middleview.h"

MiddleView::MiddleView()
{
    setChildrenCollapsible(false);
    setHandleWidth(0);
    addWidget(leftBar);
    addWidget(artistsList);
    addWidget(new QWidget());
    setStyleSheet("QSplitter::handle{background-color: black;}");
}
