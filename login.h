#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QLabel>
#include <QLineEdit>
#include "opbutton.h"
#include "croplabel.h"
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QHttpMultiPart>
#include <QNetworkRequest>
#include <QJsonDocument>

class Login : public QWidget
{
    Q_OBJECT
public:
    Login();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QLabel *logo = new QLabel();
    CropLabel *title = new CropLabel("Welcome to Cuarzo Player", "color:#666666;font-size:50px;font-weight:bold");
    CropLabel *subtitle = new CropLabel("Listen to your music anywhere\n for free", "color:#BCCBD4;font-weight:bold;font-size:25px");
    QLineEdit *code = new QLineEdit(this);
    OpButton *loginBtn = new OpButton("Login", "font-weight:bold;font-size:20px;color:#3FA8F4");
    OpButton *readyBtn = new OpButton("Continue", "font-weight:bold;font-size:20px;color:#3FA8F4");
    OpButton *skipBtn = new OpButton("Continue without Google Drive", "font-size:15px;color:#CCC");
    OpButton *backBtn = new OpButton("Go Back", "font-size:15px;color:#CCC");
    QString cod;

signals:
    void loggedIn(QString token,QString refresh);

public slots:
    void getCode();
    void cancel();
    void getToken();
    void continueWithoutLogin();
    void response(QNetworkReply*res);
};

#endif // LOGIN_H
