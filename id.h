#ifndef ID_H
#define ID_H
#include <QFile>

extern QString path;
class ID
{

public:
    int newID(){
        QFile file(path+"/Cuarzo Player/id.count");
        file.open(QIODevice::ReadOnly);
        int currentID = file.readAll().toInt();
        file.close();
        currentID++;
        saveID(currentID);
        return currentID;
    }
    void saveID(int currentID){
        QFile file(path+"/Cuarzo Player/id.count");
        file.open(QIODevice::WriteOnly);
        file.write(QString::number(currentID).toUtf8());
        file.close();
    }



};

#endif // ID_H
