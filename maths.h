#ifndef MATHS_H
#define MATHS_H

#include <QString>
#include <QtMath>

class Maths
{

public:

    long fromString(QString num){
        long empty = 0;
        int potencia = 0;
        for(int i = num.length() -1 ; i >= 0;i--){
            int a = (num.at(i).toLatin1() - '0') ;
            empty += a * qPow(10, potencia);
            potencia++;
        }
        return empty;
    }

};

#endif // MATHS_H
