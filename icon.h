#ifndef ICON_H
#define ICON_H

#include <QLabel>
#include <QBitmap>

class Icon : public QLabel
{
    QString color;
    QString url;

public:
    Icon(QString url,QString color, int w, int h);
    void setColor(QString color);
    void setUrl(QString url);
    void setSize();
    QString getColor();
    QString getUrl();

};

#endif // ICON_H
