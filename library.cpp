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
    //Check if user folder exist
    if(!QDir(path+"/Cuarzo Player/User").exists()){
        QDir().mkdir(path+"/Cuarzo Player/User");
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
        settings["totalSpace"] = "";
        settings["usedSpace"] = "";
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

    std::string total = jres["totalSpace"];
    std::string used = jres["usedSpace"];

    settings["totalSpace"] = total;
    settings["usedSpace"] = used;
    settings["email"] = jres["email"];
    settings["userName"] = jres["userName"];
    settings["userPicture"] = jres["userPicture"];
    settings["token"] = jres["token"];
    saveSettings();
    userInfoChanged();
}


void Library::newSongAdded(int songID, int track, int year, int duration, QString artist, QString album, QString title, QString genre, QString format, bool artWork){

    songsAdded++;
    float per = 100/(float)songsToAdd*(float)songsAdded;
    percentAdded((int)per);

    qDebug()<<songsAdded;
    qDebug()<<songsToAdd;


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


    if(songsAdded == songsToAdd){
        saveLibrary();
        musicAddComplete();
    }

}

void Library::startMusicAdder(){

    QList<QUrl> files = QFileDialog::getOpenFileUrls(new QWidget(),"Añade Música",QUrl(""),"MP3 (*.mp3)");

    songsToAdd = files.length();
    songsAdded = 0;

    for(int i = 0; i < files.length(); i++){
        FileManager *man = new FileManager(files[i]);
        connect(man,SIGNAL(newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool)),this,SLOT(newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool)));
        connect(man,SIGNAL(finished()),man,SLOT(deleteLater()));
        man->start();
    }
}
