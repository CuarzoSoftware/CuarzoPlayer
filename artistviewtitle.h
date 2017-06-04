#ifndef ARTISTVIEWTITLE_H
#define ARTISTVIEWTITLE_H

#include <QFrame>
#include <QBoxLayout>
#include "croplabel.h"
#include "opbutton.h"

extern QString blue;
extern QString green;
extern QString red;

class ArtistViewTitle : public QFrame
{
    Q_OBJECT

    int bSize = 30;

public:

    ArtistViewTitle()
    {
        setObjectName("artistTitle");
        setStyleSheet("#artistTitle{border-bottom:1px solid #EEE;border-radius:0}");
        setMaximumHeight(100);
        leftLayout->addWidget(artistName);
        leftLayout->addWidget(artistInfo);
        layout->setMargin(0);
        layout->setAlignment(Qt::AlignBottom);
        layout->addWidget(leftFrame,10);
        layout->addWidget(shuffle);
        layout->addWidget(more);

    }

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QWidget *leftFrame = new QWidget();
    QBoxLayout *leftLayout = new QBoxLayout(QBoxLayout::TopToBottom,leftFrame);
    CropLabel *artistName = new CropLabel("","color:#444;font-size:30px;font-weight:bold");
    CropLabel *artistInfo = new CropLabel("","color:#888;font-size:15px");
    OpButton *shuffle = new OpButton(":res/img/shuffle.svg",bSize,bSize,blue);
    OpButton *more = new OpButton(":res/img/more-big.svg",bSize,bSize,blue);

};

#endif // ARTISTVIEWTITLE_H
