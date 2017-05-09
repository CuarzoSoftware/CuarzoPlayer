#include "searchbar.h"

SearchBar::SearchBar()
{
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_MacShowFocusRect, 0);
    setFixedSize(165,25);
    setPlaceholderText("Search");
    setObjectName("searchBar");
    setStyleSheet("#searchBar{border-radius:5;padding:2px;padding-left:60px;border:1px solid #CCC;}");
    icon->setParent(this);
    icon->move(43,6);
}

void SearchBar::focusOutEvent(QFocusEvent *){
    anim = new QPropertyAnimation(this, "position");
    anim->setDuration(200);
    anim->setStartValue(5);
    anim->setEndValue(43);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
void SearchBar::focusInEvent(QFocusEvent *){
    anim = new QPropertyAnimation(this, "position");
    anim->setDuration(200);
    anim->setStartValue(43);
    anim->setEndValue(5);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    setFocus();
}

