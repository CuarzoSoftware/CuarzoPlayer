#include "icon.h"

Icon::Icon(QString _url,QString _color, int w, int h)
{
    url = _url;
    color = _color;
    setScaledContents(true);
    setUrl(url);
    setMaximumSize(w,h);
}

void Icon::setColor(QString _color){
    QPixmap newPix(pixmap()->size());
    newPix.fill( QColor(_color) );
    newPix.setMask( pixmap()->createMaskFromColor( Qt::transparent ) );
    setPixmap(newPix);
    color = _color;
}
void Icon::setUrl(QString _url){
    setPixmap(QPixmap(_url));
    setColor(color);
    url = _url;
}

