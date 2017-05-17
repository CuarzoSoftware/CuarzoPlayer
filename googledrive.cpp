#include "googledrive.h"

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

    json jres = json::parse(res->readAll());

    if(!jres["error"].is_null()){
        qDebug()<<"Token Expired";
        refreshToken("getUserInfo");
        return;
    }

    settings["totalSpace"] = jres["quotaBytesTotal"];
    settings["usedSpace"] = jres["quotaBytesUsed"];
    settings["email"] = jres["user"]["email"];
    settings["userName"] = jres["name"];
    settings["userPicture"] = jres["user"]["picture"]["url"];

    sendUserInfo(settings);

}

void GoogleDrive::tokenRefreshed(QNetworkReply *res, QString callback){

    json jres = json::parse(res->readAll());
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
