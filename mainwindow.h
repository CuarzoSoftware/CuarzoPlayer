#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include "songlist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void setDisplayInfo(QString title,QString album,QString artists,QString artwork);
    void selectedSong(QTableWidgetItem*);
public:
    Ui::MainWindow *ui;
    void displayArtists();
    void clearContent();
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private slots:
    void setTime(qint64);
    void setDuration(qint64);
    void on_addMusicButton_clicked();

    void on_listView_itemClicked(QListWidgetItem *item);

    void on_volumeSlider_valueChanged(int value);

    void on_timePosition_sliderMoved(int position);



    void on_timePosition_sliderPressed();
    void on_timePosition_sliderReleased();
};



#endif // MAINWINDOW_H
