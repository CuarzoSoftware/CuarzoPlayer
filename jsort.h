#ifndef JSORT_H
#define JSORT_H

#include <QString>
#include "json.hpp"


using json = nlohmann::json;

class JSort
{

public:
    json sortByKey(json data, QString key, QString type){

        json array;

        if(type == "int"){

            int index = 0;

            for (json::iterator a = data.begin(); a != data.end(); ++a) {
                if(a.value()!="NULL"){
                    json first = a.value();
                    json::object_t::key_type k;

                    for (json::iterator i = data.begin(); i != data.end(); ++i) {
                        if(i.value()!="NULL"){
                            if((int)i.value()[key.toStdString()] <= (int)first[key.toStdString()]){
                                first = i.value();
                                k = i.key();

                            }
                        }
                    }
                    data[k] = "NULL";
                    array[index] = first;
                    index++;
                }
            }
        }
        return array;
    }
};

#endif // JSORT_H
