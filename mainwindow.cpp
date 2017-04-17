#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.hpp"
#include <fstream>
#include <QFileDialog>
#include <fileref.h>
#include <tag.h>
#include <id3v2tag.h>
#include <mpegfile.h>
#include <attachedpictureframe.h>
#include <string>
#include <QMediaPlayer>
#include <QScrollArea>

using json = nlohmann::json;
using namespace TagLib;

json localSongsDB;
QString path = QDir::homePath() + "/Music/Cuarzo Player";
QMediaPlayer *player = new QMediaPlayer();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->addWidget(ui->topBarWidget);
    ui->searchBarInput->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->listView->setIconSize(QSize(40,40));
    //Read the songs DB

    std::ifstream readDB(path.toStdString()+"/localSongsDB.json");
    readDB >> localSongsDB;

    displayArtists();


    player->setMedia(QUrl::fromLocalFile(path+"/music/Johnny Cash/Sings The Songs That Made Him Famous/Ballad of a Teenage Queen.mp3"));
    player->setVolume(100);
    //player->play();
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(setTime(qint64)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTime(qint64 time){
    ui->timePosition->setValue(time/1000);

}


void MainWindow::displayArtists(){
    ui->listView->clear();
    for (json::iterator it = localSongsDB["artists"].begin(); it != localSongsDB["artists"].end(); ++it) {
        QListWidgetItem *item = new QListWidgetItem();

        QString artist = QString::fromStdString(it.key());
        QString album = QString::fromStdString(it.value().begin().key());
        item->setText(QString::fromStdString(it.key()));
        item->setIcon(QIcon(path+"/artwork/"+artist+"/"+album+".png"));
        ui->listView->addItem(item);
    }
}

void SaveLocalSongsDB(){
    std::ofstream db;
    db.open (path.toStdString()+"/localSongsDB.json");
    db << localSongsDB.dump();
    db.close();
}



void MainWindow::on_addMusicButton_clicked()
{
    //Open the file dialog

    QList<QUrl> files = QFileDialog::getOpenFileUrls(this,"Añade Música",QUrl(""),tr("MP3 (*.mp3)" ));

    for(int i = 0; i < files.length(); i++){

    //Read the file and ID3 tags

    TagLib::MPEG::File file(files[i].path().toStdString().c_str());
    TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);

    QString artist, album, title;
    int track, year;
    bool artWork;

    //Read the artist

    if(m_tag->artist().isEmpty()){
      artist = "Desconocido";
    }
    else{
      artist = m_tag->artist().toCString();
    }

    //Read the album

    if(m_tag->album().isEmpty()){
      album = "Desconocido";
    }
    else{
      album = m_tag->album().toCString();
    }

    //Read the title

    if(m_tag->title().isEmpty()){
      title = "Desconocido";
    }
    else{
      title = m_tag->title().toCString();
    }

    //Read the track

    track = m_tag->track();

    //Read the year

    year = m_tag->year();


    //Copy image

    TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");

    if(!frameList.isEmpty()) {

        artWork = true;

        //Check if artist folder exist

        if(!QDir(path+"/artwork/"+artist).exists()){
            QDir().mkdir(path+"/artwork/"+artist);
        }

        TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());

        QImage coverQImg;
        coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
        bool b = coverQImg.save(path+"/artwork/"+artist+"/"+album+".png");

        Q_ASSERT(b);
    }
    else{
        artWork = false;
    }

    //Check if artist folder exist

    if(!QDir(path+"/music/"+artist).exists()){
        QDir().mkdir(path+"/music/"+artist);
    }

    //Check if album folder exist

    if(!QDir(path+"/music/"+artist+"/"+album).exists()){
        QDir().mkdir(path+"/music/"+artist+"/"+album);
    }

    //Copy file

    std::ifstream  src(files[i].path().toStdString(), std::ios::binary);
    std::ofstream  dst(path.toStdString()+"/music/"+artist.toStdString()+"/"+album.toStdString()+"/"+title.toStdString()+".mp3",   std::ios::binary);

    dst << src.rdbuf();

    localSongsDB["artists"][artist.toStdString()][album.toStdString()][title.toStdString()]["title"] = title.toStdString();
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][title.toStdString()]["track"] = track;
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][title.toStdString()]["year"] = year;
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][title.toStdString()]["artwork"] = artWork;
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][title.toStdString()]["artist"] = artist.toStdString();
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][title.toStdString()]["album"] = album.toStdString();
    }


    SaveLocalSongsDB();
    displayArtists();


       /*
    MPEG::File f(argv[i]);
    f.strip(MPEG::File);
    f.

    TagLib::ID3v2::AttachedPictureFrame;

    TagLib::FileRef f(files[0].path().toStdString().c_str());
    TagLib::String artist = f.tag()->artist();
    f.tag()->setAlbum("Fillmore East");
    f.save();
    */

}

void MainWindow::on_listView_itemClicked(QListWidgetItem *item)
{
    clearContent();

    //Creates the view inside the scroll area
    QWidget *view = new QWidget();
    QBoxLayout *viewLayout = new QBoxLayout(QBoxLayout::TopToBottom,view);
    viewLayout->setAlignment(Qt::AlignTop);

    //Creates the artist name label
    QLabel *artistTitle = new QLabel(item->text());
    artistTitle->setStyleSheet("font-weight:bold;font-size:30px");
    artistTitle->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    artistTitle->setMaximumHeight(40);
    viewLayout->addWidget(artistTitle);

    for (json::iterator it = localSongsDB["artists"][item->text().toStdString()].begin(); it != localSongsDB["artists"][item->text().toStdString()].end(); ++it) {

        //The album name String
        QString albumName = QString::fromStdString(it.key());

        //Creates an album widget and layout
        QWidget *albumWidget = new QWidget();
        QBoxLayout *albumLayout = new QBoxLayout(QBoxLayout::LeftToRight,albumWidget);
        albumLayout->setAlignment(Qt::AlignTop);
        viewLayout->addWidget(albumWidget);

        //Creates the album image and attachs to the album layout
        QWidget *albumW = new QWidget();
        QBoxLayout *albumL = new QBoxLayout(QBoxLayout::TopToBottom,albumW);
        albumL->setAlignment(Qt::AlignTop);
        QLabel *albumArt = new QLabel();
        QPixmap albumImage;
        if(it.value().begin().value()["artwork"] == true){
            albumImage = QPixmap(path+"/artwork/"+item->text()+"/"+albumName+".png");
        }
        else{
            albumImage = QPixmap(":rec/images/artWork.png");
        }
        albumArt->setPixmap(albumImage);
        albumArt->setStyleSheet("max-height:200px;max-width:200px");
        albumArt->setScaledContents(true);
        albumArt->setAlignment(Qt::AlignTop);
        albumL->addWidget(albumArt);
        albumLayout->addWidget(albumW);

        //Creates the right side widget and layout and adds to the album layout
        QWidget *rightContent = new QWidget();
        QBoxLayout *rightLayout = new QBoxLayout(QBoxLayout::TopToBottom,rightContent);
        rightLayout->setSpacing(0);
        rightLayout->setMargin(10);
        rightLayout->setAlignment(Qt::AlignTop);
        albumLayout->addWidget(rightContent);

        //Creates the album name label and adds to the right layout
        QLabel *albumTitle = new QLabel(albumName);
        albumTitle->setStyleSheet("font-weight:bold;font-size:15px");
        albumTitle->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
        albumTitle->setMaximumHeight(18);
        rightLayout->addWidget(albumTitle);

        //Creates the left and right songs container
        QWidget *rightLeft = new QWidget();
        QBoxLayout *rightLeftLayout = new QBoxLayout(QBoxLayout::TopToBottom,rightLeft);
        rightLayout->addWidget(rightLeft);
        rightLayout->setAlignment(Qt::AlignRight);
        rightLeftLayout->setMargin(0);

        //Creates the left songs container
        QListWidget *leftList = new QListWidget();
        leftList->setFrameStyle(0);
        leftList->setFocusPolicy(Qt::NoFocus);
        leftList->setStyleSheet("max-width:350px");
        leftList->setSpacing(3);
        leftList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        leftList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rightLeftLayout->addWidget(leftList);


        for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {

            //Create the songs
            QListWidgetItem *song = new QListWidgetItem();
            QWidget *songItem = new QWidget();
            QBoxLayout *songItemContainer = new QBoxLayout(QBoxLayout::LeftToRight,songItem);

            songItemContainer->setMargin(0);
            songItemContainer->setAlignment(Qt::AlignLeft);

            int tr = it2.value()["track"];

            QString tra;

            if(tr < 10){
                tra = "0"+QString::number(tr);
            }
            else{
                tra = QString::number(tr);
            }

            QLabel *trackNumber = new QLabel(tra);
            trackNumber->setStyleSheet("color:#888");
            songItemContainer->addWidget(trackNumber);

            QString title = QString::fromStdString(it2.value()["title"]);
            QLabel *trackTitle = new QLabel(title);
            trackTitle->setStyleSheet("min-width:300px;color:#444;margin-right:20px");
            songItemContainer->addWidget(trackTitle);

            QToolButton *cloud = new QToolButton();
            cloud->setIcon(QIcon(":rec/images/download.png"));
            cloud->setStyleSheet("background:transparent");
            songItemContainer->addWidget(cloud);

            leftList->addItem(song);
            leftList->setItemWidget(song,songItem);

        }

    }

    ui->scroll->layout()->addWidget(view);
    view->show();
}

void MainWindow::clearContent(){
    while ( QWidget* w = ui->scroll->findChild<QWidget*>() ){
        delete w;
    }
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    player->setVolume(value);
}



void MainWindow::on_timePosition_sliderMoved(int position)
{
     player->setPosition(position*1000);
}
