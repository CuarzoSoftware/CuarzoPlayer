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

    PlayerWindow *w = nullptr;

    Init(){

        if(!library->set["init"].toBool())
        {
            logOut();
        }
        else{
            loggedIn(library->set["token"].toString(),library->set["restoreToken"].toString());
        }
    }

public slots:

    void loggedIn(QString token,QString refresh)
    {
        w = new PlayerWindow(library,token,refresh);
        connect(w,SIGNAL(showLoginWindow()),this,SLOT(logOut()));
    }

    void logOut()
    {
        if(w != nullptr)
        {
            w->player->play(false);
            w->deleteLater();
        }
        Login *login = new Login();
        login->show();
        connect(login,SIGNAL(loggedIn(QString,QString)),this,SLOT(loggedIn(QString,QString)));
    }

};

#endif // INIT_H
