#include "Database.h"

Database :: Database(){}
Database :: ~Database(){}

int Database :: getSize(){
    int size = 0;
    for(map<string, Relation>::iterator i = this->begin(); i != this->end(); ++i)
        for(Tuple x : i->second.getSet())
            size++;
    return size;
}