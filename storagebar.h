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
};

#endif // STORAGEBAR_H
