#ifndef ICON_H
#define ICON_H

#include <QLabel>
#include <QBitmap>

class Icon : public QLabel
{
    QString color;

public:

    QImage img;

    Icon(QImage _img,QString _color, int w, int h)
    {
        img = _img;
        setScaledContents(true);
        setFixedSize(w,h);
        setColor(_color);
    }

    Icon(QString _url,QString _color, int w, int h)
    {
        color = _color;
        setScaledContents(true);
        setUrl(_url);
        setFixedSize(w,h);
    }
    Icon(QString _url,int w, int h)
    {
        setScaledContents(true);
        setUrl(_url);
        setFixedSize(w,h);
        setPixmap(QPixmap::fromImage(img));
    }
    void setColor(QString _color){
        setPixmap(QPixmap::fromImage(img));
        QPixmap newPix(pixmap()->size());
        newPix.fill( QColor(_color) );
        newPix.setMask( pixmap()->createMaskFromColor( Qt::transparent ) );
        setPixmap(newPix);
        color = _color;
    }
    void setUrl(QString _url){
        img = QImage(_url);
        setPixmap(QPixmap::fromImage(img));
        setColor(color);
    }


};

#endif // ICON_H

/*
QString color;
QImage img;

Icon(QImage _img,QString _color, int w, int h)
{
    img = _img;
    setScaledContents(true);
    setMaximumSize(w,h);
    setColor(_color);
}

Icon(QString url,QString _color, int w, int h)
{
    img = QImage(url);
    setScaledContents(true);
    setMaximumSize(w,h);
    setColor(_color);
}
void setColor(QString _color){
    QPixmap newPix = QPixmap::fromImage(img);
    newPix.fill( QColor(_color) );
    newPix.setMask( pixmap()->createMaskFromColor( Qt::transparent ) );
    setPixmap(newPix);
    color = _color;
}
void setUrl(QString url){
    img = QImage(url);
    setColor(color);
}
*/
