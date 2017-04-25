#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QMediaPlayer>
#include <QDir>
#include <json.hpp>
#include <opbutton.h>

namespace Ui {
class MainWindow;
}
using json = nlohmann::json;
class MainWindow : public QMainWindow
{
    Q_OBJECT


QMediaPlayer *player = new QMediaPlayer();
QTableWidgetItem *artistSongsItems[10000];
QTableWidgetItem *artistSongItem;
QString displayedArtist,playlistArtist;
QString viewMode = "artists";
QString loop = "on";
bool shuffle = false;
json currentSongData, artistSongData, localSongsDB, playList;

QString path = QDir::homePath() + "/Music/Cuarzo Player";

public slots:
    void doubleClickedSongFromArtistView(QTableWidgetItem* model);
    void playerStateChanged(QMediaPlayer::MediaStatus state);
    void activeSongFromArtistView();
    void playBack();
    void playPause();
    void playNext();
    void loopToggle();
    void shuffleToggle();
public:
    Ui::MainWindow *ui;
    void displayArtists();
    void clearContent();
    void playSong();
    void SaveLocalSongsDB();
    OpButton *backBtn = new OpButton(":rec/images/back-button.svg",40,40);
    OpButton *playBtn = new OpButton(":rec/images/play-button.svg",40,40);
    OpButton *nextBtn = new OpButton(":rec/images/next-button.svg",40,40);
    OpButton *loopBtn = new OpButton(":rec/images/loop-on.svg",30,30);
    OpButton *shuffleBtn = new OpButton(":rec/images/shuffle-off.svg",30,30);
    void selectSongFromArtistView(QTableWidgetItem* model);
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private slots:
    void setTime(qint64);
    void on_addMusicButton_clicked();
    void on_listView_itemClicked(QListWidgetItem *item);
    void on_volumeSlider_valueChanged(int value);
    void on_timePosition_sliderReleased();
};



#endif // MAINWINDOW_H
