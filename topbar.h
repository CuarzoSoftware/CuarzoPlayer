#ifndef TOPBAR_H
#define TOPBAR_H

#include <QJsonObject>
#include <QWidget>
#include <QBoxLayout>
#include "selectlist.h"

class TopBar : public QWidget
{
public:
    TopBar();
    SelectList *modeList;
    QBoxLayout *layout;

};

#endif // TOPBAR_H
