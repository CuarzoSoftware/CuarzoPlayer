#include "searchbar.h"

SearchBar::SearchBar()
{
    setAttribute(Qt::WA_MacShowFocusRect,false);
    setFixedSize(165,25);
    setPlaceholderText("Search");
    setStyleSheet("SearchBar{border-radius:5;padding:2px;padding-left:20px;border:1px solid #CCC;}");
    icon->setParent(this);
    icon->move(6,6);
}

