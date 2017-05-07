#ifndef TOPBAR_H
#define TOPBAR_H

#include <QJsonObject>
#include <QToolBar>
#include <QBoxLayout>
#include "selectlist.h"

class TopBar : public QToolBar
{
public:
    TopBar();
    SelectList *modeList;
    QWidget *frame = new QWidget();
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::LeftToRight,frame);
};

#endif // TOPBAR_H
