#ifndef ALBUMSONG_H
#define ALBUMSONG_H

#include <QFrame>
#include <QBoxLayout>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QMouseEvent>
#include "opbutton.h"
#include "icon.h"
#include "croplabel.h"
#include "json.hpp"
#include "pix.h"
#include "pie.h"

using json = nlohmann::json;

extern QString blue;

class AlbumSong : public QFrame
{
    Q_OBJECT
public:

    //CONSTRUCTOR
    AlbumSong(json,QString);

    //VARIABLES
    QString libraryLocationSelected;
    bool downloading = false;
    bool uploading = false;
    int bSize = 15;
    json data;
    int id;

    //UTILITIES
    Pix r;

    //ELEMENTS
    Pie *pie = new Pie(0,19);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QLabel *number  = new QLabel();
    QLabel *duration = new QLabel("caca");
    Icon *status = new Icon(":res/img/volume-high.svg",blue,bSize, bSize);
    OpButton *sync = new OpButton(":res/img/upload-border.svg", bSize, bSize, blue);
    OpButton *more = new OpButton(":res/img/more.svg", bSize, bSize, blue);
    CropLabel *name = new CropLabel("","color:#444");

    //EVENTS
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:

    //METHODS
    void showMenu();

    //SETTERS
    void setSelected(bool);
    void setPlaying(bool);
    void setData(json,QString);

    //EVENTS
    void syncClicked();
    void piePressed();

    //DELETE
    void deleteFromLocal();
    void deleteFromCloud();
    void deleteFromBoth();

signals:
    //EVENTS
    void songSelected(int);
    void songPlayed(json);
    void songRightClicked(int);

    //SYNC
    void syncSong(json);

    //DOWNLOAD
    void cancelDownload(int);

    //DELETE
    void deleteSong(json data,QString from);


};

#endif // ALBUMSONG_H
