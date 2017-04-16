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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addMusicButton_clicked();

    void on_listView_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
