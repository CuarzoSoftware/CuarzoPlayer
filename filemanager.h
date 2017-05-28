#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QImage>
#include <QThread>
#include <QFile>
#include <QList>
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
#include "json.hpp"

using json = nlohmann::json;

extern QString path;

class FileManager : public QThread
{
    Q_OBJECT

public:

    ID uid;
    QList<QUrl> urls;
    json library;
    FileManager(json oldLibrary,QList<QUrl> uris){
        library = oldLibrary;
        urls = uris;
    }

protected:
    void run(){

        int total = urls.length();
        int completed = 0;
        foreach (QUrl uri, urls)
        {
            QStringList urlParts = uri.path().split( "." );
            QString format = urlParts.last();
            QString filename = uri.fileName();

            QString artist, album, title, genre;
            int track, year, songID, duration;
            bool artWork;

            if(format == "mp3")
            {
                 TagLib::MPEG::File MP3FILE(uri.path().toStdString().c_str());
                 TagLib::ID3v2::Tag *MP3 = MP3FILE.ID3v2Tag(true);

                 if(MP3->artist().isEmpty())    artist = "Unknown";
                 else                           artist = QString::fromStdWString(MP3->artist().toWString());
                 if(MP3->album().isEmpty())     album = "Unknown";
                 else                           album = QString::fromStdWString(MP3->album().toWString());
                 if(MP3->title().isEmpty())     title = filename;
                 else                           title = QString::fromStdWString(MP3->title().toWString());
                 track = MP3->track();
                 year = MP3->year();
                 duration = MP3FILE.audioProperties()->lengthInSeconds();
                 genre = QString::fromStdWString(MP3->genre().toWString());
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
                else                           artist = QString::fromStdWString(M4A->artist().toWString());
                if(M4A->album().isEmpty())     album = "Unknown";
                else                           album = QString::fromStdWString(M4A->album().toWString());
                if(M4A->title().isEmpty())     title = filename;
                else                           title = QString::fromStdWString(M4A->title().toWString());

                track = M4A->track();
                year = M4A->year();
                duration = M4AFILE.audioProperties()->lengthInSeconds();
                genre = QString::fromStdWString(M4A->genre().toWString());
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


            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["id"] = songID;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["track"] = track;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["year"] = year;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["duration"] = duration;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["artist"] = artist.toStdString();
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["album"] = album.toStdString();
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["title"] = title.toStdString();
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["genre"] = genre.toStdString();
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["format"] = format.toStdString();
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["artWork"] = artWork;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["cloud"] = false;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["local"] = true;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["albumSynched"] = false;
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["artWorkId"] = "";
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["musicId"] = "";
            library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["downloadURL"] = "";

            completed++;

            float percent = (float)100/(float)total*(float)completed;
            songAddProgress((float)percent);
        }

        songAddEnd(QString::fromStdString(library.dump()));
        deleteLater();
    }

signals:
    void songAddProgress(int);
    void songAddEnd(QString);
};


#endif // FILEMANAGER_H
