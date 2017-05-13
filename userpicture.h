#ifndef USERPICTURE_H
#define USERPICTURE_H

#include <QFrame>
#include <QLabel>
#include "pix.h"

class UserPicture : public QFrame
{
    Q_OBJECT
public:
    explicit UserPicture();
    QLabel *image;
signals:

public slots:
};

#endif // USERPICTURE_H
