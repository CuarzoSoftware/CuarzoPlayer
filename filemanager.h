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
#include <mp4file.h>
#include <mp4tag.h>
#include <mp4coverart.h>
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

        QStringList urlParts = uri.path().split( "." );
        QString format = urlParts.last();

        QString artist, album, title, genre;
        int track, year, songID, duration;
        bool artWork;

        if(format == "mp3")
        {
             TagLib::MPEG::File MP3FILE(uri.path().toStdString().c_str());
             TagLib::ID3v2::Tag *MP3 = MP3FILE.ID3v2Tag(true);

             if(MP3->artist().isEmpty())    artist = "Unknown";
             else                           artist = MP3->artist().toCString();
             if(MP3->album().isEmpty())     album = "Unknown";
             else                           album = MP3->album().toCString();
             if(MP3->title().isEmpty())     title = "Unknown";
             else                           title = MP3->title().toCString();

             track = MP3->track();
             year = MP3->year();
             duration = MP3FILE.audioProperties()->lengthInSeconds();
             genre = QString::fromStdString(MP3->genre().toCString());
             songID = uid.newID();

             TagLib::ID3v2::FrameList frameList = MP3->frameList("APIC");

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
                     coverQImg.save(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".png");
                 }
             }
             else
             {
                 artWork = false;
             }
        }
        else if (format == "m4a")
        {
            TagLib::MP4::File M4AFILE(uri.path().toStdString().c_str());
            TagLib::MP4::Tag *M4A = M4AFILE.tag();

            if(M4A->artist().isEmpty())    artist = "Unknown";
            else                           artist = M4A->artist().toCString();
            if(M4A->album().isEmpty())     album = "Unknown";
            else                           album = M4A->album().toCString();
            if(M4A->title().isEmpty())     title = "Unknown";
            else                           title = M4A->title().toCString();

            track = M4A->track();
            year = M4A->year();
            duration = M4AFILE.audioProperties()->lengthInSeconds();
            genre = QString::fromStdString(M4A->genre().toCString());
            songID = uid.newID();

            TagLib::MP4::ItemListMap itemsListMap = M4A->itemListMap();
            TagLib::MP4::Item coverItem = itemsListMap["covr"];
            TagLib::MP4::CoverArtList coverArtList = coverItem.toCoverArtList();

            if(!coverArtList.isEmpty()) {

                artWork = true;

                //Check if artist folder exist

                if(!QDir(path+"/Cuarzo Player/Artwork/"+artist).exists()){
                    QDir().mkdir(path+"/Cuarzo Player/Artwork/"+artist);
                }

                QFileInfo check_file(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".png");
                if (!check_file.exists()) {
                    QImage coverQImg;
                    TagLib::MP4::CoverArt coverArt = coverArtList.front();
                    coverQImg.loadFromData((const uchar *)coverArt.data().data(),coverArt.data().size());
                    coverQImg.save(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".png");
                }
            }
            else
            {
                artWork = false;
            }
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


        QFile::copy(uri.path(),path+"/Cuarzo Player/Music/"+artist+"/"+album+"/"+QString::number(songID) + "." + format);


        newSongAdded(songID,track,year,duration,artist,album,title,genre,format,artWork);
    }

signals:
    void newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool);
};


#endif // FILEMANAGER_H
