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
    //Check if library.czl file exist
    QFileInfo check_lib(path+"/Cuarzo Player/library.czl");
    if (!check_lib.exists()) {
        QString base = "{\"songs\":[],\"playlists\":[]}";
        QJsonDocument doc = QJsonDocument::fromJson(base.toUtf8());
        lib = doc.toVariant().toMap();
        songs = lib["songs"].toList();
        QFile file;
        file.setFileName(path + "/Cuarzo Player/library.czl");
        file.open(QIODevice::WriteOnly);
        file.write(doc.toBinaryData());
        file.close();
    }
    else{
        readLibrary();
    }
    //Check if settings.czconf file exist
    QFileInfo check_conf(path+"/Cuarzo Player/settings.czs");
    if (!check_conf.exists()) {

        set.insert("init",false);
        set.insert("logged",false);
        set.insert("token","");
        set.insert("restoreToken","");
        set.insert("totalSpace",0);
        set.insert("usedSpace",0);
        set.insert("userPicture","");
        set.insert("volume",100);
        set.insert("loop",0);
        set.insert("shuffle",false);
        set.insert("folderId","");
        set.insert("artworkId","");
        set.insert("musicId","");
        set.insert("libraryId","");
        set.insert("libraryURL","");

        QJsonDocument doc =  QJsonDocument::fromVariant(set);

        QFile file;
        file.setFileName(path + "/Cuarzo Player/settings.czs");
        file.open(QIODevice::WriteOnly);
        file.write(doc.toBinaryData());
        file.close();
    }
    else{
        readSettings();
    }


}



void Library::readLibrary(){
    QFile loadFile(path + "/Cuarzo Player/library.czl");
    loadFile.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromBinaryData(loadFile.readAll());
    lib = doc.toVariant().toMap();
    songs = lib["songs"].toList();
    loadFile.close();
}

void Library::saveLibrary(){
    QFile file;
    file.setFileName(path + "/Cuarzo Player/library.czl");
    file.open(QIODevice::WriteOnly);
    lib["songs"] = songs;
    QJsonDocument doc = QJsonDocument::fromVariant(lib);
    file.write(doc.toBinaryData());
    file.close();
}
void Library::readSettings(){
    QFile loadFile(path + "/Cuarzo Player/settings.czs");
    loadFile.open(QIODevice::ReadOnly);
    QJsonDocument doc(QJsonDocument::fromBinaryData(loadFile.readAll()));
    set = doc.toVariant().toMap();
    loadFile.close();
}
void Library::saveSettings(){
    QFile file;
    file.setFileName(path + "/Cuarzo Player/settings.czs");
    file.open(QIODevice::WriteOnly);
    QJsonDocument doc = QJsonDocument::fromVariant(set);
    file.write(doc.toBinaryData());
    file.close();
}

void Library::sortSongs()
{
    qSort(songs.begin(), songs.end(),[](QVariant a, QVariant b) -> bool {

        QString aArtist = a.toMap()["artist"].toString();
        QString bArtist = b.toMap()["artist"].toString();


        int comp = aArtist.compare(bArtist);

        if(comp<0){
            return true;
        }
        if(comp>0){
            return false;
        }
        if(comp==0){

            QString aAlbum = a.toMap()["album"].toString();
            QString bAlbum = b.toMap()["album"].toString();

            comp = aAlbum.compare(bAlbum);

            if(comp<0){
                return true;
            }
            if(comp>0){
                return false;
            }
            if(comp==0){

                int aTrack =  a.toMap()["track"].toInt();
                int bTrack =  b.toMap()["track"].toInt();

                if(aTrack<bTrack){
                    return true;
                }
                if(aTrack>bTrack){
                    return false;
                }
                if(aTrack==bTrack){

                    QString aTitle = a.toMap()["title"].toString();
                    QString bTitle = b.toMap()["title"].toString();

                    comp = aTitle.compare(bTitle);

                    if(comp<0){
                        return true;
                    }
                    if(comp>0){
                        return false;
                    }
                    if(comp==0){
                        return false;
                    }
                }
            }
        }
    });
}

void Library::setUserInfo(QVariantMap res){

    for(QVariantMap::const_iterator iter = res.constBegin(); iter != res.constEnd(); ++iter) {
        set[iter.key()] = iter.value();
    }

    saveSettings();
    userInfoChanged();
}

void Library::getCloud(QVariantMap cloudLibrary)
{

}

void Library::songUploaded(QVariantMap songData)
{
    foreach(QVariant song, songs)
    {
        QVariantMap sng = song.toMap();
        if(sng["id"].toString() == songData["id"].toString())
        {
            sng["musicId"] = songData["musicId"].toString();
            sng["cloud"] = true;
            songs[songs.indexOf(song)] = sng;
            break;
        }
    }
    saveLibrary();
    return;
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

    FileManager *man = new FileManager(songs,files);

    connect(man,SIGNAL(songAddProgress(int)),this,SIGNAL(songAddProgress(int)));
    connect(man,SIGNAL(songAddEnd(QVariantList)),this,SLOT(songAddEnd(QVariantList)));
    connect(man,SIGNAL(finished()),man,SLOT(quit()));

    man->start();

}

void Library::songAddEnd(QVariantList newLib)
{
    songs = newLib;
    sortSongs();
    saveLibrary();
    songAddComplete();
}


void Library::deleteSongs(QVariantList songsToDelete, QString from)
{

    QList<QString> localCount;
    QList<QString> cloudCount;

    foreach(QVariant song,songsToDelete)
    {
        QVariantMap sng = song.toMap();
        if(sng["local"].toBool()) localCount.append(sng["id"].toString());
        if(sng["cloud"].toBool()) cloudCount.append(sng["id"].toString());
    }

    if(from == "local")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You are about to permanently delete " + QString::number(localCount.length()) + " song(s) from your local library.");
        msgBox.setInformativeText("Do you wish to continue?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        if(ret != QMessageBox::Yes) return;

        foreach (QString id, localCount)
        {
            foreach (QVariant sn, songs)
            {
                QVariantMap s = sn.toMap();
                if(id == s["id"].toString())
                {
                    QFile file(path + "/Cuarzo Player/Music/"+ s["artist"].toString() + "/" + s["album"].toString() + "/" + s["fileName"].toString());
                    file.remove();
                    if(s["cloud"].toBool())
                    {
                        s["local"] = false;
                        songs[songs.indexOf(sn)] = s;
                        deleteFromLocal(id);
                    }
                    else
                    {
                        songs.removeAt(songs.indexOf(sn));
                        deleteFromBoth(id);
                    }
                }
            }
        }
    }
    if(from == "cloud")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You are about to permanently delete " + QString::number(cloudCount.length()) + " song(s) from your cloud library.");
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
        msgBox.setText("You are about to permanently delete " + QString::number(songsToDelete.length()) + " song(s) from everywhere.");
        msgBox.setInformativeText("Do you wish to continue?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        if(ret != QMessageBox::Yes) return;
    }

    saveLibrary();
    songDeletionEnd();

}

