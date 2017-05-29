#ifndef EMPTYMESSAGE_H
#define EMPTYMESSAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include "croplabel.h"

class EmptyMessage : public QWidget{
    Q_OBJECT
public:
    QVBoxLayout *layout = new QVBoxLayout(this);
    CropLabel *text = new CropLabel("Library Empty","font-size:40px;font-weight:bold;color:#CCC");
    EmptyMessage(){
        hide();
        layout->addWidget(text);
        text->setAlignment(Qt::AlignCenter);
    }
};

#endif
