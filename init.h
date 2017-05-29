#ifndef INIT_H
#define INIT_H

#include <QObject>
#include <QDebug>
#include "library.h"
#include "login.h"
#include "playerwindow.h"

class Init : public QObject{

    Q_OBJECT

public:

    Library *library = new Library();

    Init(){

        if(!library->settings["init"])
        {
            logOut();
        }
        else{
            loggedIn(QString::fromStdString(library->settings["token"]),QString::fromStdString(library->settings["restoreToken"]));
        }
    }

public slots:

    void loggedIn(QString token,QString refresh)
    {
        PlayerWindow *w = new PlayerWindow(library,token,refresh);
        connect(w,SIGNAL(showLoginWindow()),this,SLOT(logOut()));
    }

    void logOut()
    {
        Login *login = new Login();
        login->show();
        connect(login,SIGNAL(loggedIn(QString,QString)),this,SLOT(loggedIn(QString,QString)));
    }

};

#endif // INIT_H
