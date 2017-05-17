#include "library.h"
#include <QDebug>


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
        library = json::parse(base.toStdString());
        QJsonDocument doc = QJsonDocument::fromJson(base.toUtf8());
        QFile file;
        file.setFileName(path + "/Cuarzo Player/library.czlib");
        file.open(QIODevice::WriteOnly);
        file.write(doc.toBinaryData());
        file.close();
    }
    else{
        readLibrary();
    }
    //Check if settings.czconf file exist
    QFileInfo check_conf(path+"/Cuarzo Player/settings.czconf");
    if (!check_conf.exists()) {

        settings["volume"] = 100;
        settings["loop"] = 0;
        settings["shuffle"] = false;
        settings["init"] = false;
        settings["logged"] = false;
        settings["token"] = "";
        settings["restoreToken"] = "";
        settings["totalSpace"] = 0;
        settings["usedSpace"] = 0;
        settings["userName"] = "";
        settings["email"] = "";
        settings["userPicture"] = "";

        QJsonDocument doc =  QJsonDocument::fromJson(QString::fromStdString(settings.dump()).toUtf8());
        QFile file;
        file.setFileName(path + "/Cuarzo Player/settings.czconf");
        file.open(QIODevice::WriteOnly);
        file.write(doc.toBinaryData());
        file.close();
    }
    else{
        readSettings();
    }
}

void Library::readLibrary(){
    QFile loadFile(path + "/Cuarzo Player/library.czlib");
    loadFile.open(QIODevice::ReadOnly);
    QByteArray lib = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromBinaryData(lib));
    QString strJson(doc.toJson(QJsonDocument::Compact));
    library = json::parse(strJson.toStdString());
    loadFile.close();
}

void Library::saveLibrary(){
    QFile file;
    file.setFileName(path + "/Cuarzo Player/library.czlib");
    file.open(QIODevice::WriteOnly);
    QString base = QString::fromStdString(library.dump());
    QJsonDocument doc = QJsonDocument::fromJson(base.toUtf8());
    file.write(doc.toBinaryData());
    file.close();
}
void Library::readSettings(){
    QFile loadFile(path + "/Cuarzo Player/settings.czconf");
    loadFile.open(QIODevice::ReadOnly);
    QByteArray lib = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromBinaryData(lib));
    QString strJson(doc.toJson(QJsonDocument::Compact));
    settings = json::parse(strJson.toStdString());
    loadFile.close();
}
void Library::saveSettings(){
    QFile file;
    file.setFileName(path + "/Cuarzo Player/settings.czconf");
    file.open(QIODevice::WriteOnly);
    QString base = QString::fromStdString(settings.dump());
    QJsonDocument doc = QJsonDocument::fromJson(base.toUtf8());
    file.write(doc.toBinaryData());
    file.close();
}

void Library::setUserInfo(json jres){
    settings["totalSpace"] = jres["totalSpace"];
    settings["usedSpace"] = jres["usedSpace"];
    settings["email"] = jres["email"];
    settings["userName"] = jres["userName"];
    settings["userPicture"] = jres["userPicture"];
    settings["toke"] = jres["token"];
    saveSettings();
    userInfoChanged();
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


    }

    saveLibrary();
    musicAdded();

}
