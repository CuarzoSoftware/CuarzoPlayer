#ifndef TOPBAR_H
#define TOPBAR_H

#include <QJsonObject>
#include <QFrame>
#include <QBoxLayout>
#include "opbutton.h"
#include "selectlist.h"
#include "userpicture.h"
#include "storagebar.h"
#include "searchbar.h"
#include "pie.h"
#include "json.hpp"

using json = nlohmann::json;

class TopBar : public QFrame
{
    Q_OBJECT
public:
    TopBar();
    SelectList *modeList;
    QBoxLayout *frameLayout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    UserPicture *userPicture = new UserPicture();
    OpButton *addAccount = new OpButton("Add Google Drive","font-size:11px;color:#888");
    StorageBar *storageBar = new StorageBar();
    SearchBar *searchBar = new SearchBar();
    OpButton *addButton = new OpButton(":res/img/add.svg",35,35);
    Pie *pie = new Pie(0,30);
};

#endif // TOPBAR_H
