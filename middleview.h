#ifndef MIDDLEVIEW_H
#define MIDDLEVIEW_H

#include <QSplitter>
#include "leftbar.h"
#include "artistslist.h"
#include "artistview.h"
#include "emptymessage.h"

class MiddleView : public QSplitter
{
public:
    MiddleView();
    LeftBar *leftBar = new LeftBar();
    EmptyMessage *msg = new EmptyMessage();
};

#endif // MIDDLEVIEW_H
