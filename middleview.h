#ifndef MIDDLEVIEW_H
#define MIDDLEVIEW_H

#include <QSplitter>
#include "leftbar.h"
#include "artistslist.h"
#include "artistview.h"

class MiddleView : public QSplitter
{
public:
    MiddleView();

    LeftBar *leftBar = new LeftBar();
    ArtistsList *artistsList = new ArtistsList();

    ArtistView *artistView = new ArtistView();
};

#endif // MIDDLEVIEW_H
