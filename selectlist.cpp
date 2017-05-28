#include "selectlist.h"

SelectList::SelectList(json list)
{
    setData(list);
    setStyleSheet("SelectList{border-radius:5px;background:white;border:1px solid #D8D8D8}");
    currentText = new QLabel("Local");
    currentIcon = new Icon(":res/img/local.svg","#666",16,16);
    selectIcon = new Icon(":res/img/listArrow.svg","#666",16,16);
    layout->setContentsMargins(7,4,4,4);
    layout->addWidget(currentIcon);
    layout->addWidget(currentText);
    layout->addWidget(selectIcon);
    menu->setMaximumWidth(width());
    setMaximumHeight(25);

}

void SelectList::mousePressEvent(QMouseEvent *eventPress){
    menu->move(mapToGlobal(QPoint(this->pos().x() - 167,this->pos().y() - 20)));
    menu->show();
}

void SelectList::itemSelected(SelectListItem *item){
    foreach(SelectListItem *it,items){
        it->data["selected"] = false;
        it->selectIcon->setColor("#FFF");
    }
    item->data["selected"] = true;
    sendSelected(QString::fromStdString(item->data["text"]));
    currentText->setText(QString::fromStdString(item->data["text"]));
    currentIcon->setUrl(QString::fromStdString(item->data["icon"]));
    menu->hide();
}

void SelectList::setData(json data)
{
    int i = 0;
    qDeleteAll(items);
    items.clear();
    for (json::iterator it = data.begin(); it != data.end(); ++it)
    {
        SelectListItem *item = new SelectListItem(it.value(),i);
        items.append(item);
        connect(item,SIGNAL(itemSelected(SelectListItem*)),this,SLOT(itemSelected(SelectListItem*)));
        menu->menuLayout->addWidget(item);
        i++;
    }
}
