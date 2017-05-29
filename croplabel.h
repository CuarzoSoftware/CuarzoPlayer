#ifndef CROPLABEL_H
#define CROPLABEL_H

#include <QLabel>

class CropLabel : public QLabel
{
    Q_OBJECT
public:
    CropLabel(QString text,QString style)
    {
        _text = text;
        setText(text);
        setStyleSheet(style);
    }
    void changeText(QString text){
        _text = text;
        QString elidedText = this->fontMetrics().elidedText(_text, Qt::ElideRight, this->width() - 5);
        setText(elidedText);
    }

private:
    QString _text;

    void resizeEvent( QResizeEvent * event){
        QString elidedText = this->fontMetrics().elidedText(_text, Qt::ElideRight, this->width() - 5);
        this->setText(elidedText);
    }
};

#endif // CROPLABEL_H







