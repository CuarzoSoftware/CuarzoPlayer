#ifndef ALBUMSONG_H
#define ALBUMSONG_H

#include <QFrame>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include "opbutton.h"
#include "icon.h"
#include "croplabel.h"
#include "pix.h"
#include "pie.h"


extern QString blue;
extern QString red;
extern QString green;


class AlbumSong : public QFrame
{
    Q_OBJECT
public:

    //CONSTRUCTOR
    AlbumSong(QVariantMap, bool logged);

    //VARIABLES
    bool downloading = false;
    bool uploading = false;
    bool isSelected = false;
    int bSize = 15;
    QString id;

    //UTILITIES
    Pix r;

    //ELEMENTS
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QLabel *number  = new QLabel();
    QLabel *duration = new QLabel();
    Icon *status = nullptr;
    Pie *pie = nullptr;
    OpButton *sync = nullptr;
    OpButton *more = nullptr;
    CropLabel *name = new CropLabel("","color:#444");

    //EVENTS
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:


    //SETTERS
    void setSelected(bool);
    void setPlaying(bool);
    void setData(QVariantMap);
    void setLocation(QString);

    //EVENTS
    void syncClicked();
    void piePressed();
    void morePressed();


signals:

    //EVENTS
    void songSelected(QString);
    void songPlayed(QString);
    void songRightClicked(QString);
    void showSongMenu(QString);

    //SYNC
    void syncSong(QString);

    //DOWNLOAD
    void cancelDownload(QString);


};

#endif // ALBUMSONG_H
