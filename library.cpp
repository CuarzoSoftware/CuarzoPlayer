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
        settings["totalSpace"] = 0;
        settings["usedSpace"] = 0;
        settings["userName"] = "";
        settings["email"] = "";
        settings["userPicture"] = NULL;
        settings["folderId"] = "";
        settings["artworkId"] = "";
        settings["musicId"] = "";
        settings["libraryId"] = "";
        settings["libraryURL"] = "";

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

    if(settings["token"].is_null()) return;

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
                    updatedSong["cloud"] = true;

                    std::string artist = song.value()["artist"];
                    std::string album = song.value()["album"];
                    std::string id = QString::number((int)song.value()["id"]).toStdString();

                    library["artists"][artist][album][id] = updatedSong;

                    saveLibrary();
                    //musicAddComplete();

                    return;
                }
            }
        }
    }
}



void Library::startMusicAdder()
{

    QList<QUrl> files;
    files = QFileDialog::getOpenFileUrls(new QWidget(),"Añade Música",path,"ALL (*.mp3 *.m4a) ;; MP3 (*.mp3) ;; M4A (*.m4a)");

    if(files.length() == 0)
    {
        songAddCanceled();
        return;
    }

    FileManager *man = new FileManager(library,files);
    connect(man,SIGNAL(songAddProgress(int)),this,SIGNAL(songAddProgress(int)));
    connect(man,SIGNAL(songAddEnd(QString)),this,SLOT(songAddEnd(QString)));
    connect(man,SIGNAL(songAddEnd(QString)),man,SLOT(quit()));
    man->start();

}

void Library::songAddEnd(QString newLibrary)
{
    library = json::parse(newLibrary.toStdString());
    saveLibrary();
    songAddComplete();
}

void Library::deleteSongs(QList<json> songs, QString from)
{
    QList<json> deleted;
    QList<json> unlocal;
    QList<json> uncloud;

    int localCount = 0;
    int cloudCount = 0;

    foreach(json song,songs)
    {
        if(song["local"]) localCount++;
        if(song["cloud"]) cloudCount++;
    }

    if(from == "local")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You are about to permanently delete " + QString::number(localCount) + " song(s) from your local library.");
        msgBox.setInformativeText("Do you wish to continue?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        if(ret != QMessageBox::Yes) return;
    }
    if(from == "cloud")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You are about to permanently delete " + QString::number(cloudCount) + " song(s) from your cloud library.");
        msgBox.setInformativeText("Do you wish to continue?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        if(ret != QMessageBox::Yes) return;
    }
    if(from == "both")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You are about to permanently delete " + QString::number(songs.length()) + " song(s) from everywhere.");
        msgBox.setInformativeText("Do you wish to continue?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        if(ret != QMessageBox::Yes) return;
    }

    foreach(json song,songs)
    {

        std::string artist = song["artist"];
        std::string album = song["album"];
        std::string id = QString::number((int)song["id"]).toStdString();

        qDebug("deleted");

        if(from == "local")
        {

            if(song["local"] && song["cloud"])
            {
                library["artists"][artist][album][id]["local"] = false;
                unlocal.append(song);
                continue;
            }

            if(song["local"])
            {
                library["artists"][artist][album].erase(id);
                deleted.append(song);
                continue;
            }

        }

        else if(from == "cloud")
        {

            if(song["local"] && song["cloud"])
            {
                library["artists"][artist][album][id]["cloud"] = false;
                uncloud.append(song);
                continue;
            }

            if(song["cloud"])
            {
                library["artists"][artist][album].erase(id);
                deleted.append(song);
                continue;
            }

        }

        else if(from == "both")
        {

            library["artists"][artist][album].erase(id);
            deleted.append(song);
            continue;
        }

    }

    saveLibrary();

    foreach(json song,unlocal)
    {
        song["local"] = false;
        deleteFromLocal(song);
        QFile file (path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + "." + QString::fromStdString(song["format"]));
        file.remove();
    }

    foreach(json song,uncloud)
    {
        song["cloud"] = false;
        deleteFromCloud(song);
    }

    foreach(json song,deleted)
    {
        deleteFromBoth(song);
        if(!song["local"]) continue;
        QFile file (path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + "." + QString::fromStdString(song["format"]));
        file.remove();
    }

}

