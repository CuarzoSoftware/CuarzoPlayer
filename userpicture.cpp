#include "userpicture.h"

UserPicture::UserPicture()
{
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(35,35);
    setStyleSheet("UserPicture{border-radius:17px;background:#FFF;border:solid 5px #000}");
    image = new QLabel(this);
    image->setScaledContents(true);
    image->setPixmap(QPixmap(":res/img/google-logo.png"));
    image->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    image->setFixedSize(31,31);
    image->move(2,2);
}
