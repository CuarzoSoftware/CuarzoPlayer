#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QEvent>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    TitleBar();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    QLabel *close = new QLabel();
    QLabel *minimize = new QLabel();
    QLabel *maximize = new QLabel();
    bool eventFilter(QObject *watched, QEvent *event);
signals:
    void closeWindow();
    void minimizeWindow();
    void maximizeWindow();
};

#endif // TITLEBAR_H
