#include "userpicture.h"

UserPicture::UserPicture()
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
