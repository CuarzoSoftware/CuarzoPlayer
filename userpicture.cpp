#include "userpicture.h"

UserPicture::UserPicture()
{
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(38,38);
    setStyleSheet("UserPicture{border-radius:19px;background:#FFF;border:1px solid #EEE}");
    image = new QLabel(this);
    image->setScaledContents(true);
    image->setPixmap(QPixmap(":res/img/google-logo.png"));
    image->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    image->setFixedSize(32,32);
    image->move(3,3);
}
