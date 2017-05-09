#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>
#include <QPropertyAnimation>
#include "icon.h"

class SearchBar : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(float position READ position WRITE setPosition)

public:
    bool on = false;
    SearchBar();
    Icon *icon = new Icon(":res/img/search.svg","#444",13,13);
    QPropertyAnimation *anim;
    void setPosition (float x){
        icon->move(x,6);
        this->setStyleSheet("SearchBar{border-radius:5;padding:2px;padding-left:"+QString::number(x+17)+"px;border:1px solid #CCC}");
    }
    float position(){
        return 0;
    }
    void focusOutEvent(QFocusEvent *);
    void focusInEvent(QFocusEvent *);


};

#endif // SEARCHBAR_H
