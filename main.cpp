#include "playerwindow.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QString>
#include <QDir>


#ifdef Q_OS_MAC
    #include "objectivec.h"
#endif

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
    #ifdef Q_OS_MAC
        ObjectiveC *obc = new ObjectiveC();
        obc->Display(w);
    #endif
    w->show();
    return a.exec();
}

