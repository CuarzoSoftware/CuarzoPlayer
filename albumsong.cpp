#include "albumsong.h"
#include <QDebug>

//Creates the song

AlbumSong::AlbumSong(QVariantMap data, bool logged)
{
    setAttribute(Qt::WA_Hover);
    setFixedHeight(35);
    setStyleSheet("AlbumSong{border-bottom:1px solid #EEE;border-radius:0px}");
    number->setStyleSheet("color:#888");
    number->setFixedWidth(15);
    duration->setStyleSheet("color:#888");
    layout->setMargin(8);
    if(logged){
        sync = new OpButton(":res/img/upload-border.png", bSize, bSize);
        connect(sync,SIGNAL(pressed()),this,SLOT(syncClicked()));
        layout->addWidget(sync);
    }
    layout->addWidget(number);
    layout->addWidget(name,10);
    layout->addWidget(duration);
    setData(data);
}


//Set the songs data

void AlbumSong::setData(QVariantMap data)
{
    id = data["id"].toString();
    name->changeText(data["title"].toString());
    number->setText(QString::number(data["track"].toInt()));
    duration->setText(r.timeFromSecconds((int)data["duration"].toInt()));

    if(!data["local"].toBool())
    {
        //sync->setIcon(QIcon(":res/img/download-border.svg"));
    }
    else if(!data["cloud"].toBool())
    {
        //sync->setIcon(QIcon(":res/img/upload-border.svg"));
    }
    else if(data["cloud"].toBool() && data["local"].toBool())
    {
        //sync->setIcon(QIcon(":res/img/success.svg"));
    }
}

void AlbumSong::setLocation(QString location)
{
    if(location == "local")
    {
        if(sync != nullptr)
        {
            sync->deleteLater();
            sync = nullptr;
        }
    }
    else if(location == "cloud")
    {
        //new OpButton(":res/img/upload-border.png", bSize, bSize)
    }
    else if(location == "all")
    {

    }
}


//Set the focus blue color

void AlbumSong::setSelected(bool op)
{
    if(op)
    {

        setStyleSheet("AlbumSong{border-bottom:1px solid transparent;background:"+blue+";border-radius:5px}");
        duration->setStyleSheet("color:#FFF");
        number->setStyleSheet("color:#FFF");
        name->setStyleSheet("color:#FFF");
        if(sync != nullptr)
            sync->setIcon(QIcon(":res/img/upload-border-sel.png"));
        if(pie != nullptr)
            pie->setColor(Qt::white);
        if(status != nullptr)
            status->setPixmap(QPixmap(":res/img/volume-high-sel.png"));
        if(more != nullptr)
            more->setIcon(QIcon(":res/img/more-sel.png"));
    }
    else
    {
        setStyleSheet("AlbumSong{border-bottom:1px solid #EEE;background:transparent;border-radius:0px}");
        duration->setStyleSheet("color:#888");
        number->setStyleSheet("color:#888");
        name->setStyleSheet("color:#444");
        if(sync != nullptr)
            sync->setIcon(QIcon(":res/img/upload-border.png"));
        if(pie != nullptr)
            pie->setColor(Qt::gray);
        if(status != nullptr)
            status->setPixmap(QPixmap(":res/img/volume-high.png"));
        if(more != nullptr)
            more->setIcon(QIcon(":res/img/more-small.png"));
        //if(data["local"] && !data["cloud"]) sync->setColor(blue);
        //if(!data["local"] && data["cloud"]) sync->setColor(red);
        //if(data["local"] && data["cloud"]) sync->setColor(blue);
    }
    isSelected = op;
}

//Display the playing icon

void AlbumSong::setPlaying(bool isPlaying)
{

    if(isPlaying)
    {

        if(isSelected)status = new Icon(":res/img/volume-high-sel.png",bSize, bSize);
        if(!isSelected)status = new Icon(":res/img/volume-high.png",bSize, bSize);
        layout->insertWidget(1,status);
        number->hide();
        status->show();
    }
    else
    {
        number->show();
        if(status != nullptr)
            status->hide();
            status->deleteLater();
            status = nullptr;
    }

}


//Events


void AlbumSong::syncClicked()
{
    syncSong(id);
    pie = new Pie(0,19);
    layout->insertWidget(0,pie);
}

void AlbumSong::piePressed()
{
    cancelDownload(id);
    pie->deleteLater();
    pie = nullptr;
    sync->show();
}

void AlbumSong::morePressed()
{
    showSongMenu(id);
}

void AlbumSong::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() == Qt::RightButton)
    {
        songRightClicked(id);
    }
    else
    {
        songSelected(id);
    }
}

void AlbumSong::mouseDoubleClickEvent(QMouseEvent *event)
{
    songPlayed(id);
}

void AlbumSong::enterEvent(QEvent * event)
{
    if(isSelected){
        more = new OpButton(":res/img/more-sel.png", bSize, bSize);
    }
    else
    {
        more = new OpButton(":res/img/more-small.png", bSize, bSize);
    }
    connect(more,SIGNAL(released()),this,SLOT(morePressed()));
    layout->insertWidget(layout->count()-1,more);
    duration->hide();
}

void AlbumSong::leaveEvent(QEvent * event)
{
    more->deleteLater();
    more = nullptr;
    duration->show();
}
