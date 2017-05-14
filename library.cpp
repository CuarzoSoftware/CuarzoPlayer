#include "library.h"
#include <QDebug>

using json = nlohmann::json;

extern QString path;

Library::Library()
{
    //Check if music folder exist
    if(!QDir(path).exists()){
        QDir().mkdir(path);
    }
    //Check if Cuarzo folder exist
    if(!QDir(path+"/Cuarzo Player").exists()){
        QDir().mkdir(path+"/Cuarzo Player");
    }
    //Check if artwork folder exist
    if(!QDir(path+"/Cuarzo Player/Artwork").exists()){
        QDir().mkdir(path+"/Cuarzo Player/Artwork");
    }
    //Check if music folder exist
    if(!QDir(path+"/Cuarzo Player/Music").exists()){
        QDir().mkdir(path+"/Cuarzo Player/Music");
    }
    //Check if library.czconf file exist
    QFileInfo id_conf(path+"/Cuarzo Player/id.count");
    if (!id_conf.exists()) {
        QFile file(path+"/Cuarzo Player/id.count");
        file.open(QIODevice::WriteOnly);
        file.write("0");
        file.close();
    }
    //Check if library.czlib file exist
    QFileInfo check_lib(path+"/Cuarzo Player/library.czlib");
    if (!check_lib.exists()) {
        QString base = "{\"artists\":{},\"playlists\":{}}";
        localLibrary = json::parse(base.toStdString());
        QJsonDocument doc = QJsonDocument::fromJson(base.toUtf8());
        QFile file;
        file.setFileName(path + "/Cuarzo Player/library.czlib");
        file.open(QIODevice::WriteOnly);
        file.write(doc.toBinaryData());
        file.close();
    }
    else{
        readLocalLibrary();
    }
    //Check if library.czconf file exist
    QFileInfo check_conf(path+"/Cuarzo Player/settings.czconf");
    if (!check_conf.exists()) {
        QJsonObject lib({{"volume",100},{"shuffle",false},{"loop","all"}});
        QJsonDocument doc(lib);
        QFile file;
        file.setFileName(path + "/Cuarzo Player/settings.czconf");
        file.open(QIODevice::WriteOnly);
        file.write(doc.toBinaryData());
        file.close();
        settings = lib;
    }
    else{
        readSettings();
    }
}

void Library::readLocalLibrary(){
    QFile loadFile(path + "/Cuarzo Player/library.czlib");
    loadFile.open(QIODevice::ReadOnly);
    QByteArray lib = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromBinaryData(lib));
    QString strJson(doc.toJson(QJsonDocument::Compact));
    localLibrary = json::parse(strJson.toStdString());
    loadFile.close();
}

void Library::saveLocalLibrary(){
    QFile file;
    file.setFileName(path + "/Cuarzo Player/library.czlib");
    file.open(QIODevice::WriteOnly);
    QString base = QString::fromStdString(localLibrary.dump());
    QJsonDocument doc = QJsonDocument::fromJson(base.toUtf8());
    file.write(doc.toBinaryData());
    file.close();
}
void Library::readSettings(){
    QFile loadFile(path + "/Cuarzo Player/settings.czconf");
    loadFile.open(QIODevice::ReadOnly);
    QByteArray lib = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromBinaryData(lib));
    settings = doc.object();
    loadFile.close();
}
void Library::saveSettings(){
    QFile file;
    file.setFileName(path + "/Cuarzo Player/settings.czconf");
    file.open(QIODevice::WriteOnly);
    QJsonDocument doc(settings);
    file.write(doc.toBinaryData());
    file.close();
}

void Library::addMusic(){

      QList<QUrl> files = QFileDialog::getOpenFileUrls(new QWidget(),"Añade Música",QUrl(""),"MP3 (*.mp3)");

      for(int i = 0; i < files.length(); i++){

      TagLib::MPEG::File file(files[i].path().toStdString().c_str());
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

      std::ifstream  src(files[i].path().toStdString(), std::ios::binary);
      std::ofstream  dst(path.toStdString()+"/Cuarzo Player/Music/"+artist.toStdString()+"/"+album.toStdString()+"/"+QString::number(songID).toStdString()+".mp3",   std::ios::binary);

      dst << src.rdbuf();


      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["id"] = songID;
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["track"] = track;
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["year"] = year;
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["duration"] = duration;
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["artist"] = artist.toStdString();
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["album"] = album.toStdString();
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["title"] = title.toStdString();
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["genre"] = genre.toStdString();
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["format"] = format.toStdString();
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["artWork"] = artWork;
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["cloud"] = false;
      localLibrary["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["local"] = true;


    }

    saveLocalLibrary();
    musicAdded();

}
