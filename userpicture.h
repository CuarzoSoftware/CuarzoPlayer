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
    UserPicture()
    {
        setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        setFixedSize(38,38);
        setStyleSheet("UserPicture{border-radius:19px;background:#FFF;border:1px solid #EEE}");
        image->setScaledContents(true);
        image->setPixmap(r.round(QImage(":res/img/google-logo.png")));
        image->setFixedSize(30,30);
        layout->setMargin(3);
        layout->addWidget(image);
    }

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QLabel *image = new QLabel();
    Pix r;
signals:

public slots:
};

#endif // USERPICTURE_H
