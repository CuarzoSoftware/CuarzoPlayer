/*
#include "googledrive.h"
#include <QHttpPart>
#include <QJsonDocument>

extern QString path;

GoogleDrive::GoogleDrive(QVariantMap s)
{
    settings = s;
    getUserInfo();
}



void GoogleDrive::getUserInfo(){

    Network *network = new Network(NULL,this);
    connect(network,SIGNAL(finished(QNetworkReply*)),this,SLOT(getUserInfoRes(QNetworkReply*)));
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v2/about"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Authorization",QString("Bearer "+settings["token"].toString()).toUtf8());
    network->get(request);
}

void GoogleDrive::getUserInfoRes(QNetworkReply*res){

    json jres = json::parse(res->readAll().toStdString());

    if(!jres["error"].is_null())
    {
        qDebug()<<"Token Expired";
        refreshToken("getUserInfo");
        return;
    }

    settings["totalSpace"] = jres["quotaBytesTotal"];
    settings["usedSpace"] = jres["quotaBytesUsed"];
    settings["email"] = jres["user"]["email"];
    settings["userName"] = jres["user"]["displayName"];
    if(jres["user"]["picture"].is_null()){
        settings["userPicture"] = "";
    }
    else{
        settings["userPicture"] = jres["user"]["picture"]["url"];
    }


    sendUserInfo(settings);

    if(settings["userPicture"] != ""){
       downloadProfileImage();
    }

    readFolder("","root");

}

void GoogleDrive::readFolder(QString folderId, QString callback)
{

    Network *network = new Network(callback,this);
    connect(network,SIGNAL(finished(QNetworkReply*,QString)),this,SLOT(readFolderRes(QNetworkReply*,QString)));
    QUrl url("https://www.googleapis.com/drive/v2/files/"+folderId);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Authorization",QString("Bearer "+QString::fromStdString(settings["token"])).toUtf8());
    network->get(request);

}

void GoogleDrive::readFolderRes(QNetworkReply *res, QString callback)
{

    json jres = json::parse(res->readAll().toStdString());

    //Check if token expired

    //Check if library exist on Google Drive

    if(callback == "root")
    {

        QString libraryId = NULL;

        for (json::iterator it = jres["items"].begin(); it != jres["items"].end(); ++it)
        {

            if(!it.value()["title"].is_null())
            {
                if(it.value()["title"] == "library.czlib")
                {
                    libraryId = QString::fromStdString(it.value()["id"]);
                }
            }
        }


        if(libraryId == NULL){
            qDebug()<<"Library not Found";
            createFolder("CuarzoPlayer","root", "CuarzoPlayer");
        }
        else{
            settings["libraryId"] = libraryId.toStdString();
            sendUserInfo(settings);
            qDebug()<<"Library Found";
        }
    }
}

void GoogleDrive::createFolder(QString name, QString parent, QString callback){


    Network *network = new Network(callback,this);
    connect(network,SIGNAL(finished(QNetworkReply*,QString)),this,SLOT(createFolderRes(QNetworkReply*,QString)));

    json js;
    js["name"] = name.toStdString();
    js["parents"][0] = parent.toStdString();
    js["mimeType"] = "application/vnd.google-apps.folder";

    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=UTF-8");
    request.setRawHeader("Authorization",QString("Bearer "+QString::fromStdString(settings["token"])).toUtf8());
    network->post(request,QString::fromStdString(js.dump()).toUtf8());

}

void GoogleDrive::createFolderRes(QNetworkReply*res, QString callback){
    json jres = json::parse(res->readAll().toStdString());
    if(callback == "CuarzoPlayer"){
        settings["folderId"] = jres["id"];
        createFolder("Music",QString::fromStdString(settings["folderId"]), "Music");
        qDebug()<<"Cuarzo Folder ID: "+ QString::fromStdString(settings["folderId"]);
    }
    if(callback == "Music"){
        settings["musicId"] = jres["id"];
        createFolder("Artwork",QString::fromStdString(settings["folderId"]), "Artwork");
        qDebug()<<"Music Folder ID: "+ QString::fromStdString(settings["musicId"]);

    }
    if(callback == "Artwork"){
        settings["artworkId"] = jres["id"];
        qDebug()<<"ArtWork Folder ID: "+ QString::fromStdString(settings["artworkId"]);
        updateLibrary(NULL,NULL);
        sendUserInfo(settings);
    }
}

void GoogleDrive::updateLibrary(QString id, QByteArray bin){

    Network *network = new Network(id,this);
    connect(network,SIGNAL(finished(QNetworkReply*,QString)),this,SLOT(updateLibraryRes(QNetworkReply*,QString)));

    json js;

    if(id != NULL)
        //Updates library
    {
        js["id"] = id.toStdString();
    }
    else
        //Create new library
    {
        json lib;
        lib["artists"] = {};
        lib["playlists"] = {};
        lib["folderId"] = settings["folderId"];
        lib["artworkId"] = settings["artworkId"];
        lib["musicId"] = settings["musicId"];
        lib["libraryId"] = settings["libraryId"];
        QJsonDocument doc =  QJsonDocument::fromJson(QString::fromStdString(lib.dump()).toUtf8());
        bin = doc.toBinaryData();
        cloud = lib;
    }

    js["title"] = "library.czlib";
    js["parents"][0]["id"] = settings["folderId"];
    js["mimeType"] = "text/plain";



    QByteArray boundary = "CUARZO_BOUND";

    QNetworkRequest req(QUrl("https://www.googleapis.com/upload/drive/v2/files?uploadType=multipart"));

    QByteArray data;
    data += "\r\n--"+boundary+"\r\n";
    data += "Content-Type: application/json\r\n\r\n";
    data += QString::fromStdString(js.dump()).toUtf8();
    data += "\r\n--"+boundary+"\r\n";
    data += "Content-Type: text/plain\r\n\r\n";
    data += bin;
    data += "\r\n--"+boundary+"--";

    req.setRawHeader("Authorization","Bearer " + QString::fromStdString(settings["token"]).toUtf8());
    req.setRawHeader("Content-Type","multipart/related; boundary=\""+boundary+"\"");
    req.setRawHeader("Content-Length",QString::number(data.size()).toUtf8());

    network->post(req,data);

}

void GoogleDrive::updateLibraryRes(QNetworkReply *res, QString callback)
{
    json jres = json::parse(res->readAll().toStdString());

    if(callback == NULL)
    {
        settings["libraryId"] = jres["id"];
        settings["libraryURL"] = jres["downloadUrl"];
        sendUserInfo(settings);
        sendCloud(cloud);
        qDebug()<<"Library created";
    }

}

void GoogleDrive::syncSong(json song)
{
    if(song["cloud"] == false)
    {
        uploadSong(song);
    }
}

void GoogleDrive::uploadSong(json song)
{
    Network *network = new Network(QString::number((int) song["id"]),this);
    connect(network,SIGNAL(finished(QNetworkReply*,QString)),this,SLOT(uploadSongRes(QNetworkReply*,QString)));
    json js;
    QString title = QString::number((int) song["id"]) + "." + QString::fromStdString(song["format"]);
    js["title"] = title.toStdString();
    js["parents"][0]["id"] = settings["musicId"];
    js["mimeType"] = "audio/mpeg";

    QByteArray boundary = "CUARZO_BOUND";

    QNetworkRequest req(QUrl("https://www.googleapis.com/upload/drive/v2/files?uploadType=multipart"));

    QFile file(path + "/Cuarzo Player/Music/" + QString::fromStdString(song["artist"]) + "/" + QString::fromStdString(song["album"]) + "/" + QString::number((int)song["id"]) + "." + QString::fromStdString(song["format"]));
    file.open(QIODevice::ReadOnly);
    QByteArray data;
    data += "\r\n--"+boundary+"\r\n";
    data += "Content-Type: application/json\r\n\r\n";
    data += QString::fromStdString(js.dump()).toUtf8();
    data += "\r\n--"+boundary+"\r\n";
    data += "Content-Type: audio/mpeg\r\n\r\n";
    data += file.readAll();
    data += "\r\n--"+boundary+"--";

    req.setRawHeader("Authorization","Bearer " + QString::fromStdString(settings["token"]).toUtf8());
    req.setRawHeader("Content-Type","multipart/related; boundary=\""+boundary+"\"");
    req.setRawHeader("Content-Length",QString::number(data.size()).toUtf8());

    Reply *reply = new Reply((int) song["id"],network->post(req,data));
    replies.append(reply);

    connect(reply, SIGNAL(percentReady(int,int)), this, SLOT(songUploadProgress(int,int)));

}

void GoogleDrive::uploadSongRes(QNetworkReply *res, QString songId)
{
    qDebug()<<res->errorString();

    int id = songId.toInt();

    if(res->errorString() == "Operation canceled")
    {
        for(int i= 0; i<replies.length();i++)
        {
            if(replies[i]->_id == id)
            {
                replies[i]->res->abort();
                replies.removeAt(i);
                return;
            }
        }
        return;
    }
    else if(res->errorString() != "Unknown error")
    {
        return;
    }



    json jres = json::parse(res->readAll().toStdString());
    json song;
    song["id"] = songId.toInt();
    song["musicId"] = jres["id"];
    song["downloadURL"] = jres["downloadUrl"];
    songUploaded(song);

    qDebug()<<QString::fromStdString(jres["downloadUrl"]);

}

void GoogleDrive::songUploadProgress(int percent, int id)
{
    sendSongUploadProgress(percent,id);
}

void GoogleDrive::cancelSongUpload(int id)
{
    for(int i= 0; i<replies.length();i++)
    {
        if(replies[i]->_id == id)
        {
            replies[i]->res->abort();
            replies.removeAt(i);
            return;
        }
    }
}

void GoogleDrive::deleteSong(json song)
{
    Network *network = new Network(QString::number((int) song["id"]),this);
    connect(network,SIGNAL(finished(QNetworkReply*,QString)),this,SLOT(deleteSongRes(QNetworkReply*,QString)));
    QNetworkRequest req(QUrl("https://www.googleapis.com/drive/v2/files/"+QString::fromStdString(song["musicId"])));
    req.setRawHeader("Authorization","Bearer " + QString::fromStdString(settings["token"]).toUtf8());
    network->deleteResource(req);
}

void GoogleDrive::deleteSongRes(QNetworkReply *res, QString songId)
{
    qDebug()<<"Song deleted from cloud";

    if(res->errorString() == "Unknown error")
    {
        //songDeleteComplete(song);
    }

}

void GoogleDrive::tokenRefreshed(QNetworkReply *res, QString callback){

    json jres = json::parse(res->readAll().toStdString());
    settings["token"] = jres["access_token"];

    qDebug()<<"Token Refreshed";

    if(callback == "getUserInfo"){
        getUserInfo();
    }

}

void GoogleDrive::refreshToken(QString callback){

    Network *network = new Network(callback,this);

    connect(network,SIGNAL(finished(QNetworkReply*,QString)),this,SLOT(tokenRefreshed(QNetworkReply*,QString)));

    QUrlQuery postData;
    postData.addQueryItem("refresh_token", QString::fromStdString(settings["restoreToken"]));
    postData.addQueryItem("client_id", client_id);
    postData.addQueryItem("client_secret", client_secret);
    postData.addQueryItem("grant_type", "refresh_token");

    QNetworkRequest request(QUrl("https://www.googleapis.com/oauth2/v4/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    network->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

}

void GoogleDrive::downloadProfileImage()
{
    Network *network = new Network(NULL,this);
    connect(network,SIGNAL(finished(QNetworkReply*)),this,SLOT(imageDownloaded(QNetworkReply*)));
    QNetworkRequest request(QUrl(QString::fromStdString(settings["userPicture"])));
    network->get(request);
}

void GoogleDrive::imageDownloaded(QNetworkReply *res)
{
    QFile file;
    file.setFileName(path + "/Cuarzo Player/User/ProfileImage.jpg");
    file.open(QIODevice::WriteOnly);
    file.write(res->readAll());
    file.close();
    imageReady();
}
*/
