#include "artistviewtitle.h"

ArtistViewTitle::ArtistViewTitle()
{
    setObjectName("artistTitle");
    setStyleSheet("#artistTitle{border-bottom:1px solid #EEE;border-radius:0}");
    setMaximumHeight(100);
    leftLayout->addWidget(artistName);
    leftLayout->addWidget(artistInfo);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignBottom);
    layout->addWidget(leftFrame,10);
    //layout->addWidget(sync);
    layout->addWidget(shuffle);
    layout->addWidget(more);

}
