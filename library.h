#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QFileInfo>
#include <fstream>
#include "id.h"
#include <QFileDialog>
#include <fileref.h>
#include <tag.h>
#include <id3v2tag.h>
#include <mpegfile.h>
#include <attachedpictureframe.h>
#include "json.hpp"

using json = nlohmann::json;

class Library:public QObject
{
    Q_OBJECT
public:
    Library();
    ID uid;
    json library;
    json settings;
    void readLibrary();
    void saveLibrary();
    void readSettings();
    void saveSettings();
public slots:
    void addMusic();
    void setUserInfo(json);
signals:
    void userInfoChanged();
    void musicAdded();
};

#endif // LIBRARY_H
