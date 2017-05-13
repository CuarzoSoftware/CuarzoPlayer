#ifndef MIDDLEVIEW_H
#define MIDDLEVIEW_H

#include <QSplitter>
#include "leftbar.h"

class MiddleView : public QSplitter
{
public:
    MiddleView();
    LeftBar *leftBar = new LeftBar();
};

#endif // MIDDLEVIEW_H
