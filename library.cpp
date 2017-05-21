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
        file.write(doc.toJson());
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
        settings["token"] = NULL;
        settings["restoreToken"] = NULL;
        settings["totalSpace"] = NULL;
        settings["usedSpace"] = NULL;
        settings["userName"] = NULL;
        settings["email"] = NULL;
        settings["userPicture"] = NULL;
        settings["folderId"] = NULL;
        settings["artworkId"] = NULL;
        settings["musicId"] = NULL;
        settings["libraryId"] = NULL;
        settings["libraryURL"] = NULL;

        QJsonDocument doc =  QJsonDocument::fromJson(QString::fromStdString(settings.dump()).toUtf8());
        QFile file;
        file.setFileName(path + "/Cuarzo Player/settings.czconf");
        file.open(QIODevice::WriteOnly);
        file.write(doc.toJson());
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
    QJsonDocument doc(QJsonDocument::fromJson(lib));
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
    file.write(doc.toJson());
    file.close();
}
void Library::readSettings(){
    QFile loadFile(path + "/Cuarzo Player/settings.czconf");
    loadFile.open(QIODevice::ReadOnly);
    QByteArray lib = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(lib));
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
    file.write(doc.toJson());
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
    settings["libraryId"] = jres["libraryId"];
    settings["folderId"] = jres["folderId"];
    settings["musicId"] = jres["musicId"];
    settings["artworkId"] = jres["artworkId"];
    saveSettings();
    userInfoChanged();
}

void Library::getCloud(json cld)
{
    cloud = cld;

    for (json::iterator cloudArtist = cld["artists"].begin(); cloudArtist != cld["artists"].end(); ++cloudArtist)
    {
        for (json::iterator cloudAlbum = cloudArtist.value().begin(); cloudAlbum != cloudArtist.value().end(); ++cloudAlbum)
        {

        }
    }
}

void Library::songUploaded(json sng)
{
    for (json::iterator artist = library["artists"].begin(); artist != library["artists"].end(); ++artist)
    {
        for (json::iterator album = artist.value().begin(); album != artist.value().end(); ++album)
        {
            for (json::iterator song = album.value().begin(); song != album.value().end(); ++song)
            {
                if(song.value()["id"] == sng["id"])
                {

                    json updatedSong = song.value();

                    updatedSong["musicId"] = sng["musicId"];
                    updatedSong["downloadURL"] = sng["downloadURL"];
                    updatedSong["musicId"] = sng["musicId"];
                    updatedSong["cloud"] = true;

                    std::string artist = song.value()["artist"];
                    std::string album = song.value()["album"];
                    std::string id = QString::number((int)song.value()["id"]).toStdString();

                    library["artists"][artist][album][id] = updatedSong;

                    saveLibrary();
                    musicAddComplete();

                    return;
                }
            }
        }
    }
}

void Library::newSongAdded(int songID, int track, int year, int duration, QString artist, QString album, QString title, QString genre, QString format, bool artWork){

    songsAdded++;
    float per = 100/(float)songsToAdd*(float)songsAdded;
    percentAdded((int)per);

    qDebug()<<title;

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
    library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["artWorkId"] = NULL;
    library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["musicId"] = NULL;
    library["artists"][artist.toStdString()][album.toStdString()][QString::number(songID).toStdString()]["downloadURL"] = NULL;


    if(songsAdded == songsToAdd){
        saveLibrary();
        musicAddComplete();
    }
    else{
        FileManager *man = new FileManager(files[songsAdded]);
        connect(man,SIGNAL(newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool)),this,SLOT(newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool)));
        connect(man,SIGNAL(finished()),man,SLOT(deleteLater()));
        man->start();
    }

}

void Library::startMusicAdder(){

    files.clear();
    files = QFileDialog::getOpenFileUrls(new QWidget(),"Añade Música",path,"ALL (*.mp3 *.m4a) ;; MP3 (*.mp3) ;; M4A (*.m4a)");

    if(files.length() == 0){
        musicAddComplete();
        return;
    }

    songsToAdd = files.length();
    songsAdded = 0;

    FileManager *man = new FileManager(files[0]);
    connect(man,SIGNAL(newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool)),this,SLOT(newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool)));
    connect(man,SIGNAL(finished()),man,SLOT(deleteLater()));
    man->start();

}
