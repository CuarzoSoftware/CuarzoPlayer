/*
#ifndef GOOGLEDRIVE_H
#define GOOGLEDRIVE_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QFile>
#include <QList>
#include "network.h"
#include "reply.h"


class GoogleDrive : public QObject
{
    Q_OBJECT
public:
    explicit GoogleDrive(QVariantMap settings);

    QList<Reply*> replies;
    QString key = "AIzaSyCQXTMwalQiq-twGJrBrnXmDFNJeGwWs0g";
    QString client_id = "677866894523-ejp2cte1mn0mnb7v7m62kiuteng6mo8v.apps.googleusercontent.com";
    QString client_secret = "QW5thR07Nwo4dfUy4oozRofU";
    QString redirect = "urn:ietf:wg:oauth:2.0:oob";
    QVariantMap settings;
    QVariantMap cloud;


signals:
    void sendUserInfo(json);
    void songUploaded(json);
    void sendCloud(json);
    void sendSongUploadProgress(int,int);
    void tokenRefreshReady();
    void imageReady();
public slots:

    void setData(json);

    void getUserInfo();
    void getUserInfoRes(QNetworkReply*res);

    void readFolder(QString folderId ,QString callback);
    void readFolderRes(QNetworkReply*res, QString callback);

    void createFolder(QString name,QString parent, QString callback);
    void createFolderRes(QNetworkReply*res, QString callback);

    void updateLibrary(QString id, QByteArray bin);
    void updateLibraryRes(QNetworkReply*res, QString callback);

    void syncSong(json song);
    void uploadSong(json song);
    void uploadSongRes(QNetworkReply*res, QString callback);
    void songUploadProgress(int percent, int id);
    void cancelSongUpload(int id);
    void deleteSong(json song);
    void deleteSongRes(QNetworkReply*res, QString callback);



    void refreshToken(QString);
    void tokenRefreshed(QNetworkReply *res, QString);
    void downloadProfileImage();
    void imageDownloaded(QNetworkReply *);
};

#endif // GOOGLEDRIVE_H
*/
