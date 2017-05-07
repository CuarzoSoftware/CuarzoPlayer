#ifndef TOPBAR_H
#define TOPBAR_H

#include <QObject>
#include <QJsonObject>
#include <QToolBar>
#include "selectlist.h"

class TopBar : public QToolBar
{
public:
    TopBar();
    SelectList *modeList;
};

#endif // TOPBAR_H
