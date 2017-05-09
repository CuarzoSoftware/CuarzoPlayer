#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QFrame>
#include <QBoxLayout>
#include "library.h"
#include "titlebar.h"
#include "topbar.h"
#include "middleview.h"
#include "bottombar.h"
#include "id.h"


class PlayerWindow : public QFrame
{
    Q_OBJECT

public:
    PlayerWindow();
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QWidget *frame = new QWidget();
    TitleBar *titleBar = new TitleBar();
    MiddleView *middleView = new MiddleView();
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
    Library *library = new Library();
    TopBar *topBar = new TopBar();
    BottomBar *bottomBar = new BottomBar();
    ID id;


public slots:
    void closeWindow();
    void minimizeWindow();
    void maximizeWindow();
    void showWindow();
};

#endif // PLAYERWINDOW_H
