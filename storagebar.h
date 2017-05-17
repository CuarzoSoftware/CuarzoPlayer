#ifndef STORAGEBAR_H
#define STORAGEBAR_H

#include <QFrame>
#include <QLabel>

class StorageBar : public QFrame
{
public:
    StorageBar();
    QFrame *bar = new QFrame();
    QLabel *text = new QLabel();
public slots:
    void setPercent(long used, long total);

};

#endif // STORAGEBAR_H
