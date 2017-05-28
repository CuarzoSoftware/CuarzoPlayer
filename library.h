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
#include <QMessageBox>
#include "json.hpp"

using json = nlohmann::json;

class Library:public QObject
{
    Q_OBJECT

public:
    Library();
    json library;
    json cloud;
    json settings;
    void readLibrary();
    void saveLibrary();
    void readSettings();
    void saveSettings();
public slots:
    void setUserInfo(json);
    void getCloud(json);
    void songUploaded(json);
    void startMusicAdder();
    void deleteSongs(QList<json>,QString);
    void songAddEnd(QString);
signals:
    void userInfoChanged();
    void songAddProgress(int);
    void songAddCanceled();
    void songAddComplete();

    void deleteFromCloud(json);
    void deleteFromLocal(json);
    void deleteFromBoth(json);
};

#endif // LIBRARY_H
