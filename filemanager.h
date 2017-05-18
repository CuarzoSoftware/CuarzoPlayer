#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QImage>
#include <QThread>
#include <QFile>
#include <QUrl>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <fstream>
#include <fileref.h>
#include "id.h"
#include <tag.h>
#include <id3v2tag.h>
#include <mpegfile.h>
#include <attachedpictureframe.h>

extern QString path;

class FileManager : public QThread
{
    Q_OBJECT

public:

    ID uid;
    QUrl uri;
    FileManager(QUrl ur){
        uri = ur;
    }

protected:
    void run(){

        TagLib::MPEG::File file(uri.path().toStdString().c_str());
        TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);

        QString artist, album, title, genre, format;
        int track, year, songID, duration;
        bool artWork;


        if(m_tag->artist().isEmpty()){
          artist = "Unknown";
        }
        else{
          artist = m_tag->artist().toCString();
        }

        if(m_tag->album().isEmpty()){
          album = "Unknown";
        }
        else{
          album = m_tag->album().toCString();
        }

        if(m_tag->title().isEmpty()){
          title = "Unknown";
        }
        else{
          title = m_tag->title().toCString();
        }

        track = m_tag->track();
        year = m_tag->year();
        duration = file.audioProperties()->lengthInSeconds();
        genre = QString::fromStdString(m_tag->genre().toCString());
        songID = uid.newID();
        format = "mp3";


        TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");

        if(!frameList.isEmpty()) {

            artWork = true;

            //Check if artist folder exist

            if(!QDir(path+"/Cuarzo Player/Artwork/"+artist).exists()){
                QDir().mkdir(path+"/Cuarzo Player/Artwork/"+artist);
            }

            QFileInfo check_file(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".png");
            if (!check_file.exists()) {
                TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
                QImage coverQImg;
                coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
                bool b = coverQImg.save(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".png");
            }
        }
        else{
            artWork = false;
        }

        //Check if artist folder exist

        if(!QDir(path+"/Cuarzo Player/Music/"+artist).exists()){
            QDir().mkdir(path+"/Cuarzo Player/Music/"+artist);
        }

        //Check if album folder exist

        if(!QDir(path+"/Cuarzo Player/Music/"+artist+"/"+album).exists()){
            QDir().mkdir(path+"/Cuarzo Player/Music/"+artist+"/"+album);
        }

        //Copy file


        QFile::copy(uri.path(),path+"/Cuarzo Player/Music/"+artist+"/"+album+"/"+QString::number(songID) +".mp3");
        //QString des = path+"/Cuarzo Player/Music/"+artist+"/"+album+"/"+QString::number(songID) +".mp3";

        //std::ifstream  src(uri.path().toStdString(), std::ios::binary);
        //std::ofstream  dst(des.toStdString(),   std::ios::binary);
        //dst << src.rdbuf();

        newSongAdded(songID,track,year,duration,artist,album,title,genre,format,artWork);
    }

signals:
    void newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool);
};


#endif // FILEMANAGER_H
