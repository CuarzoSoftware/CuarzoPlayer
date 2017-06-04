#ifndef OPBUTTON_H
#define OPBUTTON_H

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class OpButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(float opacityLevel READ opacityLevel WRITE setOpacityLevel)

public:

    //VARIABLES

    int w = 0;
    int h = 0;
    QPropertyAnimation *animation;
    QGraphicsOpacityEffect *opacity;

    OpButton(QImage im, int width, int height)
    {
        w = width;
        h = height;
        setIcon(QIcon(QPixmap::fromImage(im)));
        setIconSize(QSize(width,height));
        setStyleSheet("OpButton{background:transparent;border:none;}");
        setup();
    }

    OpButton(QString icon, int width, int height, QString color)
    {
        w = width;
        h = height;
        setIcon(QIcon(icon));
        setIconSize(QSize(width,height));
        setStyleSheet("OpButton{background:transparent;border:none;}");
        setColor(color);
        setup();
    }
    OpButton(QString icon, int width, int height)
    {
        w = width;
        h = height;
        setIcon(QIcon(icon));
        setIconSize(QSize(width,height));
        setStyleSheet("OpButton{background:transparent;border:none;}");
        setup();
    }
    OpButton(QString txt, QString style)
    {
        setText(txt);
        setStyleSheet("OpButton{background:transparent;border:none;"+style+"}");
        setup();
    }



public slots:

    //METHODS

    void setOpacityLevel (float level)
    {
        this->opacity->setOpacity((qreal)level);
    }

    float opacityLevel()
    {
        return 0;
    }

    void setup()
    {
        opacity = new QGraphicsOpacityEffect();
        opacity->setOpacity(0.1);
        opacity->setOpacity(1);
        setGraphicsEffect(opacity);
        connect(this,SIGNAL(pressed()),this,SLOT(active()));
        connect(this,SIGNAL(released()),this,SLOT(inactive()));
    }

    void active()
    {
        animation = new QPropertyAnimation(this, "opacityLevel");
        animation->setDuration(100);
        animation->setStartValue(1);
        animation->setEndValue(0.5);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void inactive()
    {
        animation = new QPropertyAnimation(this, "opacityLevel");
        animation->setDuration(100);
        animation->setStartValue(0.5);
        animation->setEndValue(1);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        connect(animation,SIGNAL(finished()),this,SLOT(reset()));
    }

    void reset()
    {
        this->opacity = new QGraphicsOpacityEffect();
        this->opacity->setOpacity(1);
        this->setGraphicsEffect(opacity);
    }

    void setColor(QString color)
    {
        QPixmap m = icon().pixmap(QSize(w*2,h*2));
        QPixmap newPix(m.size());
        newPix.fill( QColor(color) );
        newPix.setMask( m.createMaskFromColor( Qt::transparent ) );
        setIcon(QIcon(newPix));
    }

};

#endif // OPBUTTON_H
