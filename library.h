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


class Library
{
public:
    Library();
    QJsonObject localLibrary;
    QJsonObject cloudLibrary;
    QJsonObject settings;
    void readLocalLibrary();
    void saveLocalLibrary();
    void readCloudLibrary();
    void saveCloudLibrary();
    void readSettings();
    void saveSettings();
};

#endif // LIBRARY_H
