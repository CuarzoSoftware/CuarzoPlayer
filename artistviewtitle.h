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
    explicit ArtistViewTitle();

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QWidget *leftFrame = new QWidget();
    QBoxLayout *leftLayout = new QBoxLayout(QBoxLayout::TopToBottom,leftFrame);
    CropLabel *artistName = new CropLabel("","color:#444;font-size:30px;font-weight:bold");
    CropLabel *artistInfo = new CropLabel("","color:#888;font-size:15px");
    OpButton *shuffle = new OpButton(":res/img/shuffle.svg",bSize,bSize,blue);
    //OpButton *download = new OpButton(":res/img/download.svg",bSize,bSize,red);
    OpButton *sync = new OpButton(":res/img/cloud.svg",bSize,bSize,blue);
    OpButton *more = new OpButton(":res/img/more-big.svg",bSize,bSize,blue);

signals:

public slots:
};

#endif // ARTISTVIEWTITLE_H
