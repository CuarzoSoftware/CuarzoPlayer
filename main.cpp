#include "playerwindow.h"
#include <QApplication>
#include <QString>
#include <QDir>

QString blue = "#2687FB";
QString lightGray = "#CCC";
QString path = QDir::homePath() + "/Music";

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);

    PlayerWindow w;
    w.show();

    return a.exec();
}

