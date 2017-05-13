#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QMouseEvent>
#include "library.h"
#include "titlebar.h"
#include "topbar.h"
#include "middleview.h"
#include "bottombar.h"
#include "id.h"


class PlayerWindow : public QWidget
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

};

#endif // PLAYERWINDOW_H
