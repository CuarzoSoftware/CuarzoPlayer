#ifndef SONGINFO_H
#define SONGINFO_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <pix.h>
#include "croplabel.h"
#include "json.hpp"

using json = nlohmann::json;

class SongInfo : public QWidget
{
    Q_OBJECT
public:
    SongInfo();
    Pix r;
    QBoxLayout *layout;
    QLabel *artWork;
    CropLabel *song;
    CropLabel *artist;
public slots:
    void setData(json);
};

#endif // SONGINFO_H
