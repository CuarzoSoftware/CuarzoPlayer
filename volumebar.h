#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QSlider>

class VolumeBar : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeBar(QWidget *parent = 0);
    QBoxLayout *layout;
    QLabel *icon = new QLabel();
    QSlider *slider = new QSlider(Qt::Horizontal);

signals:

public slots:
    void positionChanged(int per);
};

#endif // VOLUMEBAR_H
