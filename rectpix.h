#ifndef PIX_H
#define PIX_H

#include <QPixmap>
#include <QImage>
#include <QBitmap>
#include <QPainter>
#include <QDebug>

class Pix
{
public:
    QPixmap round(QImage im){
        QPixmap img = rect(im);
        QBitmap  mask(img.size());
        QPainter painter(&mask);
        mask.fill(Qt::white);
        painter.setBrush(Qt::black);
        painter.drawEllipse(QPoint(mask.width()/2, mask.height()/2), img.width()/2, img.height()/2);
        img.setMask(mask);
        return img;
    }
    QPixmap rect(QImage im){
        QImage copy;
        if(im.height() > im.width()){
            copy = im.copy( 0, (im.height()-im.width())/2, im.width(), im.width());
        }
        else{
            copy = im.copy( (im.width()-im.height())/2, 0, im.height(), im.height());
        }
        QPixmap img = QPixmap::fromImage(copy);
        QBitmap  mask(img.size());
        QPainter painter(&mask);
        mask.fill(Qt::white);
        painter.setBrush(Qt::black);
        painter.drawEllipse(QPoint(mask.width()/2, mask.height()/2), img.width()/2, img.height()/2);
        img.setMask(mask);
        return img;
    }
};



#endif
