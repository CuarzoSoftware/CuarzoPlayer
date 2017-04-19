#ifndef SONGLIST_H
#define SONGLIST_H

#include <QTableWidget>

class SongList : public QTableWidget
{
    Q_OBJECT

public:
    void wheelEvent(QWheelEvent* event);
};


#endif // SONGLIST_H
