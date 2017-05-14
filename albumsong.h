#ifndef ALBUMSONG_H
#define ALBUMSONG_H

#include <QFrame>
#include <QBoxLayout>
#include <QLabel>
#include "opbutton.h"
#include "icon.h"
#include "croplabel.h"
#include "json.hpp"
#include "pix.h"

using json = nlohmann::json;

extern QString blue;

class AlbumSong : public QFrame
{
    Q_OBJECT
    int bSize = 15;
public:
    AlbumSong(json _data);
    Pix r;
    json data;
    int id;
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QLabel *number  = new QLabel();
    QLabel *duration = new QLabel("caca");
    Icon *status = new Icon(":res/img/volume-high.svg",blue, bSize, bSize);
    OpButton *sync = new OpButton(":res/img/download-border.svg", bSize, bSize,blue);
    OpButton *more = new OpButton(":res/img/more.svg", bSize, bSize,blue);
    CropLabel *name;
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void setSelected(bool);
    void setPlaying(bool);
    void setData(json);

signals:
    void songSelected(int);
    void songPlayed(json);
};

#endif // ALBUMSONG_H