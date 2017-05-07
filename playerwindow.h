#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include "library.h"
#include "topbar.h"
#include "bottombar.h"
#include "id.h"

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    PlayerWindow();
    Library *library = new Library();
    TopBar *topBar = new TopBar();
    BottomBar *bottomBar = new BottomBar();
    ID id;

};

#endif // PLAYERWINDOW_H
