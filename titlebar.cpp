#include "titlebar.h"

TitleBar::TitleBar()
{
    setMaximumHeight(32);
    installEventFilter(this);
    setAttribute(Qt::WA_Hover, true);
    layout->setAlignment(Qt::AlignLeft);
    layout->addWidget(close);
    layout->addWidget(minimize);
    layout->addWidget(maximize);
    layout->setMargin(10);
    close->setPixmap(QPixmap(":res/img/window-close.svg"));
    close->setMaximumSize(12,12);
    close->setScaledContents(true);
    close->setAttribute(Qt::WA_Hover, true);
    close->installEventFilter(this);
    minimize->setPixmap(QPixmap(":res/img/window-minimize.svg"));
    minimize->setMaximumSize(12,12);
    minimize->setScaledContents(true);
    minimize->setAttribute(Qt::WA_Hover, true);
    minimize->installEventFilter(this);
    maximize->setPixmap(QPixmap(":res/img/window-maximize.svg"));
    maximize->setMaximumSize(12,12);
    maximize->setScaledContents(true);
    maximize->setAttribute(Qt::WA_Hover, true);
    maximize->installEventFilter(this);
}

bool TitleBar::eventFilter(QObject *watched, QEvent *event){
    if(watched == close || watched == minimize || watched == maximize){
        if(event->type() == QEvent::HoverEnter){
            close->setPixmap(QPixmap(":res/img/window-close-hover.svg"));
            minimize->setPixmap(QPixmap(":res/img/window-minimize-hover.svg"));
            maximize->setPixmap(QPixmap(":res/img/window-maximize-hover.svg"));
        }
        if(event->type() == QEvent::HoverLeave){
            close->setPixmap(QPixmap(":res/img/window-close.svg"));
            minimize->setPixmap(QPixmap(":res/img/window-minimize.svg"));
            maximize->setPixmap(QPixmap(":res/img/window-maximize.svg"));
        }
    }
    if(event->type() == QEvent::MouseButtonPress){
        if(watched == close){
            close->setPixmap(QPixmap(":res/img/window-close-active.svg"));
        }
        if(watched == minimize){
            minimize->setPixmap(QPixmap(":res/img/window-minimize-active.svg"));
        }
        if(watched == maximize){
            maximize->setPixmap(QPixmap(":res/img/window-maximize-active.svg"));
        }
    }
    if(event->type() == QEvent::MouseButtonRelease){
        if(watched == close){
            close->setPixmap(QPixmap(":res/img/window-close-hover.svg"));
            closeWindow();
        }
        if(watched == minimize){
            minimize->setPixmap(QPixmap(":res/img/window-minimize-hover.svg"));
            minimizeWindow();
        }
        if(watched == maximize){
            maximize->setPixmap(QPixmap(":res/img/window-maximize-hover.svg"));
            maximizeWindow();
        }
    }
    return false;
}
