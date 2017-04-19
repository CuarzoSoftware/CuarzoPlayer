#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <fstream>




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);

    QString path = QDir::homePath() + "/Music";

    //Check if music folder exist

    if(!QDir(path).exists()){
        QDir().mkdir(path);
    }

    //Check if Cuarzo folder exist

    if(!QDir(path+"/Cuarzo Player").exists()){
        QDir().mkdir(path+"/Cuarzo Player");
    }

    //Check if artwork folder exist

    if(!QDir(path+"/Cuarzo Player/artwork").exists()){
        QDir().mkdir(path+"/Cuarzo Player/artwork");
    }

    //Check if music folder exist

    if(!QDir(path+"/Cuarzo Player/music").exists()){
        QDir().mkdir(path+"/Cuarzo Player/music");
    }

    //Check if localSongsDB.json file exist

    QFileInfo check_file(path+"/Cuarzo Player/localSongsDB.json");
    if (!check_file.exists()) {
        std::ofstream db;
        db.open (path.toStdString()+"/Cuarzo Player/localSongsDB.json");
        db << "{\"artists\":{}}";
        db.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}

