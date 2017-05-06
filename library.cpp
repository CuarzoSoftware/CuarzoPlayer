#include "library.h"

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
    //Check if library.czlib file exist
    QFileInfo check_lib(path+"/Cuarzo Player/library.czlib");
    if (!check_lib.exists()) {
        QJsonObject lib({{"artists",QJsonObject()},{"playlists",QJsonObject()}});
        localLibrary = lib;
        QJsonDocument doc(lib);
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
    localLibrary = doc.object();
    loadFile.close();
}

void Library::saveLocalLibrary(){
    QFile file;
    file.setFileName(path + "/Cuarzo Player/library.czlib");
    file.open(QIODevice::WriteOnly);
    QJsonDocument doc(localLibrary);
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
