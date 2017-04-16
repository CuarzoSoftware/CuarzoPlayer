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

using json = nlohmann::json;
using namespace TagLib;

json localSongsDB;
QString path = QDir::homePath() + "/Music/Cuarzo Player";

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

}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->userName->setText(item->text());
}
