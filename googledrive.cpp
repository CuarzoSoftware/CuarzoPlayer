#include "googledrive.h"

extern QString path;

GoogleDrive::GoogleDrive(json s)
{
    setData(s);
    getUserInfo();
}

void GoogleDrive::setData(json s){
    settings = s;
}

void GoogleDrive::getUserInfo(){

    Network *network = new Network(NULL,this);
    connect(network,SIGNAL(finished(QNetworkReply*)),this,SLOT(getUserInfoRes(QNetworkReply*)));
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v2/about"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Authorization",QString("Bearer "+QString::fromStdString(settings["token"])).toUtf8());
    network->get(request);
}

void GoogleDrive::getUserInfoRes(QNetworkReply*res){

    json jres = json::parse(res->readAll().toStdString());

    if(!jres["error"].is_null()){
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

    //qDebug()<<QString::fromStdString(settings["userPicture"]);


    sendUserInfo(settings);

    if(settings["userPicture"] != ""){
       downloadProfileImage();
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

