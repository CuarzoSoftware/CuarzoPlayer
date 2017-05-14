#include "albumsong.h"
#include <QTime>
#include <QDebug>

using json = nlohmann::json;

AlbumSong::AlbumSong(json _data)
{
    setData(_data);
    setAttribute(Qt::WA_Hover);
    setObjectName("song");
    setStyleSheet("#song{border-bottom:1px solid #EEE;background:#FFF;border-radius:0px}");
    number->setStyleSheet("color:#888");
    number->setMinimumWidth(15);
    duration->setStyleSheet("color:#888");
    layout->setMargin(8);
    layout->addWidget(sync);
    layout->addWidget(number);
    layout->addWidget(status);
    layout->addWidget(name,10);
    layout->addWidget(duration);
    layout->addWidget(more);
    sync->hide();
    status->hide();
    more->hide();
}

void AlbumSong::setData(json _data){
    data = _data;
    id = data["id"];
    name = new CropLabel(QString::fromStdString(data["title"]),"color:#444");
    number->setText(QString::number((int)data["track"]));
    duration->setText(r.timeFromSecconds((int)data["duration"]));
    //qDebug()<<(int)data["duration"];
}

void AlbumSong::mousePressEvent(QMouseEvent *event){
    setSelected(true);
    songSelected(id);
}

void AlbumSong::mouseDoubleClickEvent(QMouseEvent *event){
    setPlaying(true);
    songPlayed(data);
}

void AlbumSong::setSelected(bool op)
{
    if(op){
        setStyleSheet("#song{border-bottom:1px solid transparent;background:"+blue+";border-radius:5px}");
        number->setStyleSheet("color:#FFF");
        duration->setStyleSheet("color:#FFF");
        name->setStyleSheet("color:#FFF");
        sync->setColor("#FFF");
        status->setColor("#FFF");
        more->setColor("#FFF");
    }
    else{
        setStyleSheet("#song{border-bottom:1px solid #EEE;background:transparent;border-radius:0px}");
        number->setStyleSheet("color:#888");
        duration->setStyleSheet("color:#888");
        name->setStyleSheet("color:#444");
        sync->setColor(blue);
        status->setColor(blue);
        more->setColor(blue);
    }

}

void AlbumSong::enterEvent(QEvent * event)
{
    more->show();
    duration->hide();
}

void AlbumSong::leaveEvent(QEvent * event)
{
    more->hide();
    duration->show();
}

void AlbumSong::setPlaying(bool op){

    if(op){
        number->hide();
        status->show();
    }
    else{
        number->show();
        status->hide();
    }

}
