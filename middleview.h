#ifndef MIDDLEVIEW_H
#define MIDDLEVIEW_H

#include "leftbar.h"
#include "artistview.h"

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

class ArtistsList : public QFrame
{
    Q_OBJECT
public:
    ArtistsList()
    {
        hide();
        setAutoFillBackground(true);
        setMinimumWidth(190);
        setFixedWidth(190);

        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor("#FFF"));
        frame->setObjectName("fr");
        frame->setPalette(pal);
        frame->setStyleSheet("#fr{border-right:1px solid #F4F4F4;border-radius: 0px;background:#FFF}");

        scrollLayout->addWidget(scroll);
        scrollLayout->setMargin(0);
        scrollLayout->setSpacing(0);
        scroll->setWidget(frame);
        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setWidgetResizable( true );
        scroll->setStyleSheet("QScrollArea{border:none}");

        layout->setMargin(0);
        layout->setSpacing(0);
        layout->setAlignment(Qt::AlignTop);

    }
    QBoxLayout *scrollLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    QScrollArea *scroll = new QScrollArea();
    QFrame *frame = new QFrame();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,frame);

};


class MiddleView : public QWidget
{
    Q_OBJECT

    public:
        QHBoxLayout *layout = new QHBoxLayout(this);
        LeftBar *leftBar = new LeftBar();
        ArtistsList *artistsList = new ArtistsList();
        EmptyMessage *msg = new EmptyMessage();
        ArtistView *artistView = new ArtistView();

        MiddleView()
        {
            layout->setMargin(0);
            layout->setSpacing(0);
            layout->setAlignment(Qt::AlignLeft);
            layout->addWidget(msg,10);
            layout->addWidget(leftBar);
            layout->addWidget(artistsList);
            layout->addWidget(artistView);

        }

};

#endif // MIDDLEVIEW_H
