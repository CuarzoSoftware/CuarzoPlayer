#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QFrame>
#include <QBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QFrame *frame = new QFrame();
    QBoxLayout *menuLayout = new QBoxLayout(QBoxLayout::TopToBottom,frame);
signals:

public slots:
};

#endif // MENU_H
