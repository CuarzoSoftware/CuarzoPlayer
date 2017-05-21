#include "albumsong.h"
#include <QDebug>

using json = nlohmann::json;

extern QString red;
extern QString green;


//Creates the song

AlbumSong::AlbumSong(json _data)
{
    setAttribute(Qt::WA_Hover);
    setObjectName("song");
    setFixedHeight(35);
    setStyleSheet("#song{border-bottom:1px solid #EEE;background:#FFF;border-radius:0px}");
    number->setStyleSheet("color:#888");
    number->setFixedWidth(15);
    duration->setStyleSheet("color:#888");
    space->setFixedWidth(23);
    layout->setMargin(8);
    layout->addWidget(sync);
    layout->addWidget(pie);
    layout->addWidget(space);
    layout->addWidget(number);
    layout->addWidget(status);
    layout->addWidget(name,10);
    layout->addWidget(duration);
    layout->addWidget(more);
    pie->hide();
    sync->hide();
    status->hide();
    more->hide();
    space->hide();
    setData(_data);
    connect(sync,SIGNAL(pressed()),this,SLOT(syncClicked()));
    connect(pie,SIGNAL(pressed()),this,SLOT(piePressed()));
    connect(more,SIGNAL(released()),this,SLOT(showMenu()));
}

//Set the songs data

void AlbumSong::setData(json _data)
{

    data = _data;
    id = data["id"];
    name->changeText(QString::fromStdString(data["title"]));
    number->setText(QString::number((int)data["track"]));
    duration->setText(r.timeFromSecconds((int)data["duration"]));

    if(!data["local"])
    {
        sync->setIcon(QIcon(":res/img/download-border.svg"));
        sync->show();
    }
    else if(!data["cloud"])
    {
        sync->show();

    }else{

        sync->hide();

        if(!data["albumSynched"])
        {
            space->show();
        }

    }
}


//Set the focus blue color

void AlbumSong::setSelected(bool op)
{
    if(op)
    {
        setStyleSheet("#song{border-bottom:1px solid transparent;background:"+blue+";border-radius:5px}");
        number->setStyleSheet("color:#FFF");
        duration->setStyleSheet("color:#FFF");
        name->setStyleSheet("color:#FFF");
        sync->setColor("#FFF");
        status->setColor("#FFF");
        more->setColor("#FFF");
    }
    else
    {
        setStyleSheet("#song{border-bottom:1px solid #EEE;background:transparent;border-radius:0px}");
        number->setStyleSheet("color:#888");
        duration->setStyleSheet("color:#888");
        name->setStyleSheet("color:#444");
        sync->setColor(blue);
        status->setColor(blue);
        more->setColor(blue);
    }

}

//Display the playing icon

void AlbumSong::setPlaying(bool isPlaying)
{

    if(isPlaying)
    {
        number->hide();
        status->show();
    }
    else
    {
        number->show();
        status->hide();
    }

}


//Events

void AlbumSong::showMenu()
{
    QMenu contextMenu(tr("Options"),more);

    QAction action1("Edit Info", more);
    QAction action2("Stop Download", more);
    QAction action3("Stop Upload", more);
    QAction action4("Download", more);
    QAction action5("Upload", more);

    contextMenu.addAction(&action1);

    if(pie->isVisible() && data["cloud"]) contextMenu.addAction(&action2);

    if(pie->isVisible() && !data["cloud"]) contextMenu.addAction(&action3);

    if(!pie->isVisible() && data["cloud"] && !data["local"]) contextMenu.addAction(&action4);

    if(!pie->isVisible() && !data["cloud"] && data["local"]) contextMenu.addAction(&action5);

    connect(&action2, SIGNAL(triggered()), this, SLOT(piePressed()));
    connect(&action3, SIGNAL(triggered()), this, SLOT(piePressed()));
    connect(&action4, SIGNAL(triggered()), this, SLOT(syncClicked()));
    connect(&action5, SIGNAL(triggered()), this, SLOT(syncClicked()));

    contextMenu.exec(more->mapToGlobal(QPoint(50-contextMenu.width(),0)));
}

void AlbumSong::syncClicked()
{
    syncSong(data);
}

void AlbumSong::piePressed()
{
    cancelDownload(id);
    pie->hide();
    sync->show();
}


void AlbumSong::mousePressEvent(QMouseEvent *event)
{
    setSelected(true);
    songSelected(id);
}

void AlbumSong::mouseDoubleClickEvent(QMouseEvent *event)
{
    setPlaying(true);
    songPlayed(data);
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
