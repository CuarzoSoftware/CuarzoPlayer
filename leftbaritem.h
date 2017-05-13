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
    explicit LeftBarItem(QString _id,QString _icon,QString _text);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    Icon *icon;
    CropLabel *text;
    void setSelected(bool);
    QString id;

    void mousePressEvent(QMouseEvent *);
signals:
    void selected(QString);
public slots:
};

#endif // LEFTBARITEM_H
