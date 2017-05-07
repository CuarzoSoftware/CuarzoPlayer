#include "id.h"

#include <QDebug>
ID::ID()
{
    QFile file(":res/cache/id.count");
    file.open(QIODevice::ReadOnly);
    currentID = file.readAll().toInt();
    file.close();
    qDebug() << currentID;
}

int ID::newID(){
    currentID++;
    return currentID;
}

void ID::saveID(){
    QFile file(":res/cache/id.count");
    file.open(QIODevice::WriteOnly);
    QByteArray data;
    for(int i = 0; i != sizeof(currentID); ++i)
    {
      data.append((char)(currentID&(0xFF << i) >>i));
    }
    file.write(data);
    file.close();
}
