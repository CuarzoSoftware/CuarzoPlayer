#ifndef USERPICTURE_H
#define USERPICTURE_H

#include <QFrame>
#include <QLabel>
#include <QBoxLayout>
#include "pix.h"

class UserPicture : public QFrame
{
    Q_OBJECT
public:
    explicit UserPicture();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QLabel *image = new QLabel();
    Pix r;
signals:

public slots:
};

#endif // USERPICTURE_H
