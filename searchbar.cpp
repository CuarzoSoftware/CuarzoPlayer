#include "searchbar.h"

SearchBar::SearchBar()
{
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_MacShowFocusRect, 0);
    setFixedSize(165,25);
    setClearButtonEnabled(true);
    setPlaceholderText("Search");
    setObjectName("searchBar");
    setStyleSheet("#searchBar{border-radius:5;padding:2px;padding-left:60px;border:1px solid #CCC;}");
    icon->setParent(this);
    icon->move(43,6);

}

void SearchBar::focusOutEvent(QFocusEvent *){
    animation = new QPropertyAnimation(this, "position");
    animation->setDuration(200);
    animation->setStartValue(5);
    animation->setEndValue(43);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void SearchBar::focusInEvent(QFocusEvent *){
    animation = new QPropertyAnimation(this, "position");
    connect(animation,SIGNAL(finished()),this,SLOT(focusOn()));
    animation->setDuration(200);
    animation->setStartValue(43);
    animation->setEndValue(5);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SearchBar::focusOn(){
    setSelection(0,0);
}
