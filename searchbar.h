#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>
#include "icon.h"

class SearchBar : public QLineEdit
{
    Q_OBJECT

public:
    SearchBar();
    Icon *icon = new Icon(":res/img/search.svg","#444",13,13);
};

#endif // SEARCHBAR_H
