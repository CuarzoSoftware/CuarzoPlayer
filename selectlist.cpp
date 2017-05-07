#include "selectlist.h"

SelectList::SelectList(QJsonArray list)
{
    size = list.size();
    for(int i = 0; i<size;i++){

        SelectListItem *item = new SelectListItem(list[i].toObject(),i);
        items[i] = item;
        connect(item,SIGNAL(itemSelected(SelectListItem*)),this,SLOT(itemSelected(SelectListItem*)));
        menu->menuLayout->addWidget(item);
    }
    setStyleSheet("SelectList{border-radius:5px;background:white;border:1px solid #D8D8D8}");
    currentText = new QLabel("Home");
    currentIcon = new Icon(":res/img/local.svg","#666",16,16);
    selectIcon = new Icon(":res/img/listArrow.svg","#666",16,16);
    layout->setContentsMargins(7,4,4,4);
    layout->addWidget(currentIcon);
    layout->addWidget(currentText);
    layout->addWidget(selectIcon);
    menu->setMaximumWidth(width());


}

void SelectList::mousePressEvent(QMouseEvent *eventPress){
    menu->move(mapToGlobal(pos()).x() - 10,mapToGlobal(pos()).y() - 10);
    menu->show();
}

void SelectList::itemSelected(SelectListItem *item){
    for(int i = 0;i<size;i++){
        items[i]->data["selected"] = false;
        items[i]->selectIcon->setColor("#FFF");
    }
    item->data["selected"] = true;
    currentText->setText(item->data["text"].toString());
    currentIcon->setUrl(item->data["icon"].toString());
    menu->hide();
}
