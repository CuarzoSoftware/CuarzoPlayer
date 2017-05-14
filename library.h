#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
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
    json localLibrary;
    QJsonObject cloudLibrary;
    QJsonObject settings;
    void readLocalLibrary();
    void saveLocalLibrary();
    void readCloudLibrary();
    void saveCloudLibrary();
    void readSettings();
    void saveSettings();
public slots:
    void addMusic();
signals:
    void musicAdded();
};

#endif // LIBRARY_H
