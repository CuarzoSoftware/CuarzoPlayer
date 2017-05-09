#include "playerwindow.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QString>
#include <QDir>

QString blue = "#2687FB";
QString red = "#FF1D25";
QString green = "#7AC943";
QString orange = "#FF931E";
QString lightGray = "#CCC";

QString path = QDir::homePath() + "/Music";

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    PlayerWindow *w = new PlayerWindow();
    QSystemTrayIcon *tray = new QSystemTrayIcon(QIcon(":res/img/icon.png"));
    tray->show();
    QObject::connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),w,SLOT(showWindow()));
    w->show();
    return a.exec();
}

