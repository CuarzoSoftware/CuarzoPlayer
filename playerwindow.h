#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include "library.h"
#include "topbar.h"
#include "bottombar.h"

namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = 0);
    Library *library = new Library();
    TopBar *topBar = new TopBar();
    BottomBar *bottomBar = new BottomBar();
    ~PlayerWindow();

private:
    Ui::PlayerWindow *ui;
};

#endif // PLAYERWINDOW_H
