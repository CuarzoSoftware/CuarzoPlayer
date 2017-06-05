#include <QApplication>
#include <QDir>
#include "init.h"

QString blue = "#2687FB";
QString red = "#FF1D25";
QString green = "#7AC943";
QString orange = "#FF931E";
QString lightGray = "#CCC";

QString path = QDir::homePath() + "/Music";


int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    a.setQuitOnLastWindowClosed(true);
    Init run;
    return a.exec();
}
