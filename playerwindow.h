#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include "bottombar.h"

namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = 0);
    BottomBar *bottomBar = new BottomBar();
    ~PlayerWindow();

private:
    Ui::PlayerWindow *ui;
};

#endif // PLAYERWINDOW_H
