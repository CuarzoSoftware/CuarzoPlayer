#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void displayArtists();
    void clearContent();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setTime(qint64);

    void on_addMusicButton_clicked();

    void on_listView_itemClicked(QListWidgetItem *item);

    void on_volumeSlider_valueChanged(int value);


    void on_timePosition_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
