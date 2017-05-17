#ifndef GOOGLEDRIVE_H
#define GOOGLEDRIVE_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include "network.h"
#include "json.hpp"

using json = nlohmann::json;

class GoogleDrive : public QObject
{
    Q_OBJECT
public:
    explicit GoogleDrive(json settings);


    QString key = "AIzaSyCQXTMwalQiq-twGJrBrnXmDFNJeGwWs0g";
    QString client_id = "677866894523-ejp2cte1mn0mnb7v7m62kiuteng6mo8v.apps.googleusercontent.com";
    QString client_secret = "QW5thR07Nwo4dfUy4oozRofU";
    QString redirect = "urn:ietf:wg:oauth:2.0:oob";
    json settings;


signals:
    void sendUserInfo(json);
    void tokenRefreshReady();
public slots:
    void setData(json);
    void getUserInfo();
    void getUserInfoRes(QNetworkReply*res);
    void refreshToken(QString);
    void tokenRefreshed(QNetworkReply *res, QString);
};

#endif // GOOGLEDRIVE_H
