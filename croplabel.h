#ifndef CROPLABEL_H
#define CROPLABEL_H

#include <QLabel>

class CropLabel : public QLabel
{
public:
    CropLabel(QString text,QString style);
private:
    QString _text;
signals:
    void resizeEvent( QResizeEvent * event);
};

#endif // CROPLABEL_H
