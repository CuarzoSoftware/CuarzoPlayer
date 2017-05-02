#include "playerwindow.h"
#include "ui_playerwindow.h"
#include "croplabel.h"

PlayerWindow::PlayerWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
    addToolBar(Qt::BottomToolBarArea,bottomBar);
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}
