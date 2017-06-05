#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QCryptographicHash>
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
#include <tag.h>
#include <id3v2tag.h>
#include <mpegfile.h>
#include <mp4file.h>
#include <mp4tag.h>
#include <mp4coverart.h>
#include <attachedpictureframe.h>
#include "pix.h"

extern QString path;

class FileManager : public QThread
{
    Q_OBJECT

public:

    QCryptographicHash *hash3 = new QCryptographicHash(QCryptographicHash::Sha3_224);
    QList<QUrl> urls;
    QVariantList newLib;
    Pix p;
    FileManager(QVariantList oldLib,QList<QUrl> uris){
        newLib = oldLib;
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

            QString artist, album, title, genre, songId;
            int track, year, duration;
            bool artWork;

            if(format == "mp3")
            {
                 TagLib::MPEG::File MP3FILE(uri.path().toStdString().c_str());
                 TagLib::ID3v2::Tag *MP3 = MP3FILE.ID3v2Tag(true);

                 if(MP3->artist().isEmpty())    artist = "Unknown";
                 else                           artist = QString::fromStdWString(MP3->artist().toWString()).remove(QRegExp("[^a-zA-Z\\d\\s]"));
                 if(MP3->album().isEmpty())     album = "Unknown";
                 else                           album = QString::fromStdWString(MP3->album().toWString()).remove(QRegExp("[^a-zA-Z\\d\\s]"));
                 if(MP3->title().isEmpty())     title = filename;
                 else                           title = QString::fromStdWString(MP3->title().toWString()).remove(QRegExp("[^a-zA-Z\\d\\s]"));
                 track = MP3->track();
                 year = MP3->year();
                 duration = MP3FILE.audioProperties()->lengthInSeconds();
                 genre = QString::fromStdWString(MP3->genre().toWString());

                 TagLib::ID3v2::FrameList frameList = MP3->frameList("APIC");

                 if(!frameList.isEmpty()) {

                     artWork = true;

                     //Check if artist folder exist

                     if(!QDir(path+"/Cuarzo Player/Artwork/"+artist).exists()){
                         QDir().mkdir(path+"/Cuarzo Player/Artwork/"+artist);
                     }

                     QFileInfo check_file(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".jpg");
                     if (!check_file.exists()) {
                         TagLib::ID3v2::AttachedPictureFrame *coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
                         QImage coverQImg;
                         coverQImg.loadFromData((const uchar *) coverImg->picture().data(), coverImg->picture().size());
                         coverQImg = coverQImg.scaled(256,256,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                         coverQImg.save(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".jpg","jpg",100);
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
                else                           artist = QString::fromStdWString(M4A->artist().toWString()).remove(QRegExp("[^a-zA-Z\\d\\s]"));
                if(M4A->album().isEmpty())     album = "Unknown";
                else                           album = QString::fromStdWString(M4A->album().toWString()).remove(QRegExp("[^a-zA-Z\\d\\s]"));
                if(M4A->title().isEmpty())     title = filename;
                else                           title = QString::fromStdWString(M4A->title().toWString()).remove(QRegExp("[^a-zA-Z\\d\\s]"));

                track = M4A->track();
                year = M4A->year();
                duration = M4AFILE.audioProperties()->lengthInSeconds();
                genre = QString::fromStdWString(M4A->genre().toWString());

                TagLib::MP4::ItemListMap itemsListMap = M4A->itemListMap();
                TagLib::MP4::Item coverItem = itemsListMap["covr"];
                TagLib::MP4::CoverArtList coverArtList = coverItem.toCoverArtList();

                if(!coverArtList.isEmpty()) {

                    artWork = true;

                    //Check if artist folder exist

                    if(!QDir(path+"/Cuarzo Player/Artwork/"+artist).exists()){
                        QDir().mkdir(path+"/Cuarzo Player/Artwork/"+artist);
                    }

                    QFileInfo check_file(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".jpg");
                    if (!check_file.exists()) {
                        QImage coverQImg;
                        TagLib::MP4::CoverArt coverArt = coverArtList.front();
                        coverQImg.loadFromData((const uchar *)coverArt.data().data(),coverArt.data().size());
                        coverQImg = coverQImg.scaled(256,256,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                        coverQImg.save(path+"/Cuarzo Player/Artwork/"+artist+"/"+album+".jpg","jpg",100);
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


            QFile originFile( uri.path() );
            originFile.open( QIODevice::ReadOnly );
            QByteArray songData = originFile.readAll();
            hash3->addData(songData);
            songId = QString::fromStdString(hash3->result().toStdString());
            originFile.close();

            QString songFileName = QString::number(track) + " " + title + "." + format;
            QString destPath = path+"/Cuarzo Player/Music/"+artist+"/"+album+"/";

            QFileInfo check_lib(destPath + songFileName);

            bool alreadyExistName = check_lib.exists();

            int sufix = 1;

            while(alreadyExistName)
            {
                songFileName = QString::number(track) + " " + title + " " + QString::number(sufix) + "." + format;

                QFileInfo check_lib(destPath + songFileName);

                alreadyExistName = check_lib.exists();
            }

            QFile destFile(destPath + songFileName);
            destFile.open(QIODevice::WriteOnly);
            destFile.write(songData);
            destFile.close();

            QVariantMap song;

            song["id"] = songId;
            song["track"] = track;
            song["year"] = year;
            song["duration"] = duration;
            song["artist"] = artist;
            song["album"] = album;
            song["title"] = title;
            song["genre"] = genre;
            song["format"] = format;
            song["artWork"] = artWork;
            song["cloud"] = false;
            song["local"] = true;
            song["artWorkId"] = "";
            song["musicId"] = "";
            song["fileName"] = songFileName;

            newLib.append(song);

            completed++;

            float percent = (float)100/(float)total*(float)completed;
            songAddProgress((float)percent);
        }

        songAddEnd(newLib);
        deleteLater();
    }

signals:
    void songAddProgress(int);
    void songAddEnd(QVariantList);
};


#endif // FILEMANAGER_H
