#include "croplabel.h"

CropLabel::CropLabel(QString text,QString style)
{
    _text = text;
    setText(text);
    setStyleSheet(style);
}

void CropLabel::changeText(QString text){
    _text = text;
    setText(text);
}

void CropLabel::resizeEvent( QResizeEvent * event){
    QString elidedText = this->fontMetrics().elidedText(_text, Qt::ElideRight, this->width() - 5);
    this->setText(elidedText);
}
