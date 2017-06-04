#ifndef LEFTBARITEM_H
#define LEFTBARITEM_H

#include <QWidget>
#include <QBoxLayout>
#include "croplabel.h"
#include "icon.h"

class LeftBarItem : public QWidget
{
    Q_OBJECT
public:
    LeftBarItem(QString _id,QString _icon,QString _text);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    Icon *icon;
    CropLabel *text;
    QString id;

    void mousePressEvent(QMouseEvent *);
signals:
    void selected(QString);
public slots:
    void setSelected(bool);
};

#endif // LEFTBARITEM_H
