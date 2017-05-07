#ifndef ID_H
#define ID_H
#include <QFile>

class ID
{
public:
    ID();
    int currentID;
    int newID();
    void saveID();
};

#endif // ID_H
