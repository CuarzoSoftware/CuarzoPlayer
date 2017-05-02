#ifndef SONGINFO_H
#define SONGINFO_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include "croplabel.h"

class SongInfo : public QWidget
{
public:
    SongInfo();
    QBoxLayout *layout;
    QLabel *artWork;
    CropLabel *song;
    CropLabel *artist;
};

#endif // SONGINFO_H
