#ifndef SONGMENU_H
#define SONGMENU_H

#include <QMenu>

class SongMenu : public QMenu
{
    Q_OBJECT

public:

    SongMenu(){
        setAttribute(Qt::WA_Hover);
    }

    void leaveEvent(QEvent * event)
    {
        close();
    }

};

#endif // SONGMENU_H
