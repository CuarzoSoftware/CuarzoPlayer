#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "artistviewtitle.h"


class ArtistView : public QWidget
{
    Q_OBJECT
public:
    ArtistView()
    {
        hide();
        layout->setAlignment(Qt::AlignTop);
        layout->setContentsMargins(15,0,15,0);
        layout->setSpacing(0);
        layout->addWidget(artistViewTitle);
        layout->addWidget(scroll,10);
        scroll->setStyleSheet("QScrollArea{border:none;background:transparent}");
        scroll->setWidget(albumsFrame);
        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll->setWidgetResizable( true );
        albumsFrame->setLayout(albumsLayout);
        albumsFrame->setObjectName("fram");
        albumsFrame->setStyleSheet("#fram{background:transparent}");
        albumsLayout->setMargin(15);
        albumsLayout->setSpacing(40);
    }
    int songCount;
    int albumCount;
    QString artistName;
    QWidget *albumsFrame = new QWidget();
    QVBoxLayout *albumsLayout = new QVBoxLayout(albumsFrame);
    QVBoxLayout *layout = new QVBoxLayout(this);
    ArtistViewTitle *artistViewTitle = new ArtistViewTitle();
    QScrollArea *scroll = new QScrollArea();

    void setData(QString name, int albums, int songs){
        albumCount = albums;
        songCount = songs;
        artistName = name;
        artistViewTitle->artistName->changeText(name);

        QString P1,P2;

        if(albumCount == 1)
        {
            P1 = "1 album, ";
        }
        else
        {
            P1 = QString::number(albumCount) + " albums, ";
        }

        if(songCount == 1)
        {
            P2 = "1 song";
        }
        else
        {
            P2 = QString::number(songCount) + " songs";
        }

        artistViewTitle->artistInfo->changeText(P1 + P2);
    }


};

#endif // ARTISTVIEW_H
