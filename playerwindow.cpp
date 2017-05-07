#include "playerwindow.h"
#include "croplabel.h"


PlayerWindow::PlayerWindow()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    installEventFilter(this);
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setFixedSize(800,400);
    layout->addWidget(frame);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    frame->setMouseTracking(true);
    frame->setObjectName("main");
    frame->setStyleSheet("#main{border:1px solid #EEE;border-radius:5px;background:rgba(255,255,255,0.99)}");
    frameLayout->addWidget(topBar);
    frameLayout->addWidget(bottomBar);
}

void PlayerWindow::mousePressEvent(QMouseEvent *event){

}
void PlayerWindow::mouseMoveEvent(QMouseEvent* event){
    QPoint pos = mapToGlobal(event->pos());
    int gmX = pos.x();
    int gmY = pos.x();
    int lmX = event->pos().x();
    int lmY = event->pos().y();
    if(event->buttons() != Qt::LeftButton){
        resizeMode = 0;
    }
    if(resizeMode == 1){
        if(lmX >= minSize->x()){
            setFixedWidth(lmX);
        }
        if(lmY >= minSize->y()){
            setFixedHeight(lmY);
        }
        return;
    }
    if(resizeMode == 2){
        if(lmX >= minSize->x()){
            setFixedWidth(lmX);
        }
        return;
    }
    if(resizeMode == 3){
        if(lmY >= minSize->y()){
            setFixedHeight(lmY);
        }
        return;
    }
    if(lmX>width()-7 && lmY>height()-7){
        this->setCursor(Qt::SizeFDiagCursor);
        if(event->buttons() == Qt::LeftButton){
            resizeMode = 1;
        }
    }
    else if(lmX>width()-5){
        this->setCursor(Qt::SizeHorCursor);
        if(event->buttons() == Qt::LeftButton){
            resizeMode = 2;
        }
    }
    else if(lmY>height()-5){
        this->setCursor(Qt::SizeVerCursor);
        if(event->buttons() == Qt::LeftButton){
            resizeMode = 3;
        }
    }
    else{
        this->setCursor(Qt::ArrowCursor);
    }
    bottomBar->songInfo->artist->setText(QString::number(gmX));
}
void PlayerWindow::resizeEvent(QResizeEvent* event){

}


