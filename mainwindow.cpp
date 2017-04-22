#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "songlist.h"
#include "json.hpp"
#include "fileref.h"
#include "tag.h"
#include "id3v2tag.h"
#include "mpegfile.h"
#include "attachedpictureframe.h"
#include <fstream>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QMediaPlayer>
#include <QScrollArea>
#include <QPushButton>
#include <QWheelEvent>
#include <QUuid>
#include <QTime>



using json = nlohmann::json;
using namespace TagLib;

QTableWidgetItem *artistSongsItems[10000];
QTableWidgetItem *artistSongItem;
QString displayedArtist,playlistArtist;
QString viewMode = "artists";
json currentSongData, artistSongData, localSongsDB, playList;

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
    ui->displayInfo->item(0,0)->setTextColor(QColor("#000"));
    ui->displayInfo->item(1,0)->setTextColor(QColor("#444"));
    ui->displayInfo->item(2,0)->setTextColor(QColor("#888"));

    //Read the songs DB
    std::ifstream readDB(path.toStdString()+"/localSongsDB.json");
    readDB >> localSongsDB;
    displayArtists();
    player->setVolume(100);
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(setTime(qint64)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Set current a remaining song time

void MainWindow::setTime(qint64 time){
    float dur = (float)100000 / (float)player->duration() * (float)time ;
    ui->timePosition->setValue(dur);
    int seconds = (time/1000) % 60;
    int minutes = (time/60000) % 60;
    int secondsB = ((player->duration() - time)/1000) % 60;
    int minutesB = ((player->duration() - time)/60000) % 60;
    QTime cTime(0,minutes,seconds);
    QTime rTime(0,minutesB,secondsB);
    ui->currentTime->setText(cTime.toString().mid(3,5));
    ui->remainTime->setText("-"+rTime.toString().mid(3,5));
}

//Display the artists list

void MainWindow::displayArtists(){
    ui->listView->clear();
    for (json::iterator it = localSongsDB["artists"].begin(); it != localSongsDB["artists"].end(); ++it) {
        QListWidgetItem *item = new QListWidgetItem();

        QString artist = QString::fromStdString(it.key());
        QString album = QString::fromStdString(it.value().begin().key());
        item->setText(QString::fromStdString(it.key()));
        if(it.value().begin().value().begin().value()["artwork"]==true){
            item->setIcon(QIcon(path+"/artwork/"+artist+"/"+album+".png"));
        }
        else{
            item->setIcon(QIcon(":rec/images/artWork.png"));
        }

        ui->listView->addItem(item);
    }
}

//Save the current library

void SaveLocalSongsDB(){
    std::ofstream db;
    db.open (path.toStdString()+"/localSongsDB.json");
    db << localSongsDB.dump();
    db.close();
}

//Adds new music

void MainWindow::on_addMusicButton_clicked()
{
    //Open the file dialog

    QList<QUrl> files = QFileDialog::getOpenFileUrls(this,"Añade Música",QUrl(path),tr("MP3 (*.mp3)" ));

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
      artist.remove(QRegExp("[^a-zA-Z\\d\\s]"));
    }

    //Read the album

    if(m_tag->album().isEmpty()){
      album = "Desconocido";
    }
    else{
      album = m_tag->album().toCString();
      album.remove(QRegExp("[^a-zA-Z\\d\\s]"));
    }

    //Read the title

    if(m_tag->title().isEmpty()){
      title = "Desconocido";
    }
    else{
      title = m_tag->title().toCString();
      title.remove(QRegExp("[^a-zA-Z\\d\\s]"));
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

        QFileInfo check_file(path+"/artwork/"+artist+"/"+album+".png");
        if (!check_file.exists()) {
            TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());

            QImage coverQImg;
            coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
            coverQImg.save(path+"/artwork/"+artist+"/"+album+".png");
        }
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

    QFile::copy(files[i].path(), path+"/music/"+artist+"/"+album+"/"+title+".mp3");
    //std::ifstream  src(files[i].path().toStdString(), std::ios::binary);
    //std::ofstream  dst(path.toStdString()+"/music/"+artist.toStdString()+"/"+album.toStdString()+"/"+title.toStdString()+".mp3",   std::ios::binary);

   // dst << src.rdbuf();
    QString preID;
    if(track<10){
        preID = "0" + QString::number(track) ;
    }
    else{
        preID = QString::number(track) ;
    }
    QString id = preID + QUuid::createUuid().toString().mid(1,36);
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][id.toStdString()]["title"] = title.toStdString();
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][id.toStdString()]["track"] = track;
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][id.toStdString()]["year"] = year;
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][id.toStdString()]["artwork"] = artWork;
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][id.toStdString()]["artist"] = artist.toStdString();
    localSongsDB["artists"][artist.toStdString()][album.toStdString()][id.toStdString()]["album"] = album.toStdString();
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


//Display albums from selected artist

void MainWindow::on_listView_itemClicked(QListWidgetItem *item){

    //Cleans the body container
    clearContent();

    //Save the current artist name
    displayedArtist = item->text();

    //Creates the view inside the scroll area
    QWidget *view = new QWidget();
    QBoxLayout *viewLayout = new QBoxLayout(QBoxLayout::TopToBottom,view);
    viewLayout->setAlignment(Qt::AlignTop);

    //Creates the artist name label on the top
    QLabel *artistTitle = new QLabel(item->text());
    artistTitle->setStyleSheet("font-weight:bold;font-size:30px");
    artistTitle->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    artistTitle->setMaximumHeight(40);
    viewLayout->addWidget(artistTitle);

    int globalIndex = 0;

    //Loop through the artist albums
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
        rightLayout->setMargin(0);
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
        SongList *songList = new SongList();
        songList->setColumnCount(3);
        songList->setMinimumHeight(it.value().size() * 30);
        songList->setMaximumWidth(400);
        songList->setSelectionBehavior(QAbstractItemView::SelectRows);
        songList->setShowGrid(false);
        songList->setWordWrap(false);
        songList->setStyleSheet("border:none");
        songList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        songList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
        songList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        songList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        songList->horizontalHeader()->hide();
        songList->verticalHeader()->hide();
        songList->setColumnWidth(0,30);
        songList->setColumnWidth(2,30);

        //When song from list is double clicked
        connect(songList,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleClickedSongFromArtistView(QTableWidgetItem*)));

        rightLeftLayout->addWidget(songList);

        int albumIndex = 0;

        //Loop the album songs
        for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {

            //Create a song
            QTableWidgetItem *track = new QTableWidgetItem();
            QTableWidgetItem *title = new QTableWidgetItem();
            QTableWidgetItem *status = new QTableWidgetItem();

            //Set the global index
            track->setData(Qt::UserRole,QVariant(globalIndex));
            title->setData(Qt::UserRole,QVariant(globalIndex));
            status->setData(Qt::UserRole,QVariant(globalIndex));

            artistSongsItems[globalIndex] = title;
            artistSongData[globalIndex] = it2.value();
            artistSongData[globalIndex]["globalIndex"] = globalIndex;
            artistSongData[globalIndex]["albumIndex"] = albumIndex;
            songList->insertRow(songList->rowCount());

            //Set the track number
            int tr = it2.value()["track"];
            QString tra;
            if(tr < 10){
                tra = "0"+QString::number(tr);
            }
            else{
                tra = QString::number(tr);
            }
            if(displayedArtist == playlistArtist){
                if(!currentSongData.empty()){
                    if(currentSongData["globalIndex"] == globalIndex){
                         track->setIcon(QIcon(":rec/images/playingSong.png"));
                         artistSongItem = title;
                    }
                }
            }else{
                artistSongItem = NULL;
            }

            track->setText(tra);
            songList->setItem(songList->rowCount() - 1,0,track);

            //Set the song title
            QString titleText = QString::fromStdString(it2.value()["title"]);
            title->setText(titleText);

            songList->setItem(songList->rowCount() - 1,1,title);

            //Set the current song status (Download / Downloaded / Upload)
            status->setIcon(QIcon(":rec/images/download.png"));
            songList->setItem(songList->rowCount() - 1,2,status);

            globalIndex++;
            albumIndex++;
        }

    }
    ui->scroll->layout()->addWidget(view);
    view->show();
}

//Double ckicked on song from artist view mode

void MainWindow::doubleClickedSongFromArtistView(QTableWidgetItem* model){
    currentSongData = artistSongData[model->data(Qt::UserRole).toInt()];
    if(displayedArtist != playlistArtist){
        playList = artistSongData;
    }
    playlistArtist = displayedArtist;
    selectSongFromArtistView(model);
    playSong();
}

//Set selected song from artist view mode list

void MainWindow::selectSongFromArtistView(QTableWidgetItem* model){
    if(displayedArtist == playlistArtist){
        if(artistSongItem!=NULL){
            artistSongItem->tableWidget()->item(artistSongItem->row(),0)->setIcon(QIcon());
        }
        model->tableWidget()->item(model->row(),0)->setIcon(QIcon(":rec/images/playingSong.png"));
        artistSongItem = model;
    }
}

void MainWindow::playSong(){

    QString artist = QString::fromStdString(currentSongData["artist"]);
    QString album = QString::fromStdString(currentSongData["album"]);
    QString title = QString::fromStdString(currentSongData["title"]);

    player->setMedia(QUrl::fromLocalFile(path+"/music/"+artist+"/"+album+"/"+title+".mp3"));
    player->play();

    if(currentSongData["artwork"] == true){
        ui->artWork->setPixmap(QPixmap(path+"/artwork/"+artist+"/"+album+".png"));
    }
    else{
        ui->artWork->setPixmap(QPixmap(":rec/images/artWork.png"));
    }
    ui->displayInfo->item(0,0)->setText(title);
    ui->displayInfo->item(1,0)->setText(album);
    ui->displayInfo->item(2,0)->setText(artist);
}

void SongList::wheelEvent(QWheelEvent *event){
    event->ignore();
}

void MainWindow::clearContent(){
    while ( QWidget* w = ui->scroll->findChild<QWidget*>() ){
        delete w;
    }
}

void MainWindow::on_volumeSlider_valueChanged(int value){
    player->setVolume(value);
}

void MainWindow::on_timePosition_sliderReleased(){
    player->setPosition((float)player->duration() / 100000 * (float)ui->timePosition->value());
}

void MainWindow::on_playNextButton_clicked(){
    if(playList.size() == 0){
        return;
    }
    int i = (int)currentSongData["globalIndex"] + 1;
    if(viewMode == "artists"){
        if(i < (int)playList.size()){
            currentSongData = playList[i];
            selectSongFromArtistView(artistSongsItems[i]);
        }
        else{
            currentSongData = playList[0];
            selectSongFromArtistView(artistSongsItems[0]);
        }
        playSong();
    }
}
