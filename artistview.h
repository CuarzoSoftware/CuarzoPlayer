#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>
#include "artistviewtitle.h"
#include "album.h"

class ArtistView : public QWidget
{
    Q_OBJECT
public:
    explicit ArtistView();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QScrollArea *scroll = new QScrollArea();
    QWidget *albumsFrame = new QWidget();
    QBoxLayout *albumsLayout = new QBoxLayout(QBoxLayout::TopToBottom,albumsFrame);
    ArtistViewTitle *artistViewTitle = new ArtistViewTitle();

signals:

public slots:
};

#endif // ARTISTVIEW_H
