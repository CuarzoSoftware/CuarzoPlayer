#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QFileInfo>
#include <fstream>
#include <fileref.h>
#include <QThread>
#include "filemanager.h"
#include <QFileDialog>
#include "json.hpp"

using json = nlohmann::json;

class Library:public QObject
{
    Q_OBJECT

public:
    Library();
    int songsToAdd;
    int songsAdded;
    json library;
    json settings;
    void readLibrary();
    void saveLibrary();
    void readSettings();
    void saveSettings();
public slots:
    void newSongAdded(int,int,int,int,QString,QString,QString,QString,QString,bool);
    void setUserInfo(json);
    void startMusicAdder();
signals:
    void userInfoChanged();
    void musicAddComplete();
    void percentAdded(int);
};

#endif // LIBRARY_H
