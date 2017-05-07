#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QWidget>
#include <QCoreApplication>
#include <QFrame>
#include <QBoxLayout>
#include <QMouseEvent>
#include "library.h"
#include "topbar.h"
#include "bottombar.h"
#include "id.h"

class PlayerWindow : public QWidget
{
    Q_OBJECT

public:
    PlayerWindow();
    QFrame *frame = new QFrame();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
    Library *library = new Library();
    TopBar *topBar = new TopBar();
    BottomBar *bottomBar = new BottomBar();
    ID id;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
    int resizeMode;
    QPoint *minSize = new QPoint(800,400);

};

#endif // PLAYERWINDOW_H
