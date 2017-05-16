/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

// QtGui/QtWidgets
#include <QFileDialog>

#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "DualInstance.h"
#include "ui_Dual.h"

DualInstance::DualInstance(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Dual),
      _media1(0),
      _media2(0)
{
    ui->setupUi(this);

    _instance1 = new VlcInstance(VlcCommon::args(), this);
    _player1 = new VlcMediaPlayer(_instance1);
    _player1->setVideoWidget(ui->video1);

    ui->video1->setMediaPlayer(_player1);

    connect(ui->open1, SIGNAL(clicked()), this, SLOT(open1()));
    connect(ui->stop1, SIGNAL(clicked()), _player1, SLOT(stop()));

    _instance2 = new VlcInstance(VlcCommon::args(), this);
    _player2 = new VlcMediaPlayer(_instance2);
    _player2->setVideoWidget(ui->video2);

    ui->video2->setMediaPlayer(_player2);

    connect(ui->open2, SIGNAL(clicked()), this, SLOT(open2()));
    connect(ui->stop2, SIGNAL(clicked()), _player2, SLOT(stop()));

    ui->group1->setTitle("Instance 1");
    ui->group2->setTitle("Instance 2");

    setWindowTitle("Dual Instance Test");
}

DualInstance::~DualInstance()
{
    delete _media1;
    delete _player1;
    delete _media2;
    delete _player2;
    delete _instance1;
    delete _instance2;
    delete ui;
}

void DualInstance::open1()
{
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open file"),
                        QDir::homePath(),
                        tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media1 = new VlcMedia(file, true, _instance1);

    _player1->open(_media1);
}

void DualInstance::open2()
{
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open file"),
                        QDir::homePath(),
                        tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media2 = new VlcMedia(file, true, _instance2);

    _player2->open(_media2);
}
