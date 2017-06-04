#ifndef ROUNDPIX_H
#define ROUNDPIX_H

#include <QPixmap>
#include <QImage>
#include <QBitmap>
#include <QPainter>
#include <QDebug>

class Pix
{
public:
    QPixmap round(QImage image){
        QPixmap img = rect(image);
        QBitmap  mask(img.size());
        QPainter painter(&mask);
        mask.fill(Qt::white);
        painter.setBrush(Qt::black);
        painter.drawEllipse(QPoint(mask.width()/2, mask.height()/2), img.width()/2, img.height()/2);
        img.setMask(mask);
        return img;
    }
    QPixmap rect(QImage image){
        QImage copy;
        if(image.height() > image.width()){
            copy = image.copy( 0, (image.height()-image.width())/2, image.width(), image.width());
        }
        else{
            copy = image.copy( (image.width()-image.height())/2, 0, image.height(), image.height());
        }
        QPixmap img = QPixmap::fromImage(copy);
        return img;
    }
    QPixmap borderRadius(QImage image,int radius){
        QPixmap img = rect(image);
        QBitmap  mask(img.size());
        QPainter painter(&mask);
        mask.fill(Qt::white);
        painter.setBrush(Qt::black);
        painter.drawRoundRect(0,0,mask.width(),mask.height(),radius,radius);
        img.setMask(mask);
        return img;
    }
    QString timeFromSecconds(int secs){
        int mins = secs/60;
        int sec = secs%60;
        QString segundos;
        if(sec<10){
            segundos = "0" + QString::number(sec);
        }
        else{
            segundos = QString::number(sec);
        }
        return QString::number(mins)+":"+segundos;
    }
};



#endif // ROUNDPIX_H
