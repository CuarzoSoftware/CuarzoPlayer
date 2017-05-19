#ifndef PIE_H
#define PIE_H

#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QDebug>

class Pie : public QPushButton
{
    Q_OBJECT
public:


    int siz;
    bool overlay = false;
    int savedPer;
    QColor color = Qt::gray;

    Pie(int percent, int size)
    {
        setStyleSheet("Pie{background:transparent;border:none;}");
        setAttribute(Qt::WA_Hover);
        setIconSize(QSize(size,size));
        siz = size;
        setFixedSize(size,size);
        setPercent(percent);

    }

    void setColor(QColor col){
        color = col;
        setPercent(savedPer);
    }

    void enterEvent(QEvent*)
    {
        overlay =  true;

        int si = siz*4;
        float wi = si/18;

        QImage img(QSize(si,si),QImage::Format_ARGB32);
        img.fill(Qt::transparent);

        QPainter painter(&img);
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);

        painter.drawRect(wi*6,wi*6,si-wi*12,si-wi*12);
        painter.setBrush(Qt::NoBrush);
        QPen pen(color);
        pen.setWidth(wi);
        painter.setPen(pen);
        painter.drawEllipse(wi,wi,si-wi*2,si-wi*2);
        setIcon(QIcon(QPixmap::fromImage(img)));
    }

    void leaveEvent(QEvent*)
    {
        overlay =  false;
        setPercent(savedPer);
    }
public slots:
    void setPercent(int per)
    {
        if(overlay)return;

        int si = siz*5;
        float wi = si/18;

        float grade = ((float)360/(float)100)*(float)per;

        savedPer = per;

        QImage img(QSize(si,si),QImage::Format_ARGB32);
        img.fill(Qt::transparent);

        QPainter painter(&img);
        painter.setPen(Qt::NoPen);
        painter.setBrush(color);

        painter.drawPie(QRect(wi,wi,si-wi*2,si-wi*2),90*16,-(grade*16));
        painter.setBrush(Qt::NoBrush);
        QPen pen(color);
        pen.setWidth(wi);
        painter.setPen(pen);
        painter.drawEllipse(wi,wi,si-wi*2,si-wi*2);
        setIcon(QIcon(QPixmap::fromImage(img)));


    }

};



#endif // PIE_H
