#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include "leftbaritem.h"

class LeftBar : public QWidget
{
    Q_OBJECT
public:
    explicit LeftBar();
    QBoxLayout *scrollLayout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QScrollArea *scroll = new QScrollArea();
    QWidget *frame = new QWidget();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
    QWidget *libraryFrame = new QWidget();
    QWidget *playlistsFrame = new QWidget();
    QBoxLayout *libraryLayout = new QBoxLayout(QBoxLayout::TopToBottom,libraryFrame);
    QBoxLayout *playlistsLayout = new QBoxLayout(QBoxLayout::TopToBottom,playlistsFrame);
    QLabel *title1 = new QLabel("Library");
    QLabel *title2 = new QLabel("Playlists");
    LeftBarItem *items[10000] = {nullptr};
signals:

public slots:
    void itemSelected(QString id);
};

#endif // LEFTBAR_H
