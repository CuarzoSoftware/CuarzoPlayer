#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QDir>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


QMediaPlayer *player = new QMediaPlayer();
QString path = QDir::homePath() + "/Music/Cuarzo Player";

public slots:

public:
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private slots:

};



#endif // MAINWINDOW_H
