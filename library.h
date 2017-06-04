#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QVariant>
#include <QMap>
#include <QVariantMap>
#include <QFileInfo>
#include <fstream>
#include <fileref.h>
#include <QThread>
#include "filemanager.h"
#include <QFileDialog>
#include <QMessageBox>

class Library:public QObject
{
    Q_OBJECT

public:
    Library();

    QVariantMap lib;
    QVariantMap set;
    QVariantList songs;

    void readLibrary();
    void saveLibrary();
    void readSettings();
    void saveSettings();
    void sortSongs();
public slots:
    void setUserInfo(QVariantMap res);
    void getCloud(QVariantMap cloudLibrary);
    void songUploaded(QVariantMap songData);
    void startMusicAdder();
    void deleteSongs(QVariantList songsToDelete, QString from);
    void songAddEnd(QVariantList newLib);
signals:
    void userInfoChanged();
    void songAddProgress(int);
    void songAddCanceled();
    void songAddComplete();
    void songDeletionEnd();

    void deleteFromCloud(QString);
    void deleteFromLocal(QString);
    void deleteFromBoth(QString);
};

#endif // LIBRARY_H
