#include "Database.h"

Database :: Database(){}
Database :: ~Database(){}

int Database :: getSize(){
    int size = 0;
    for(map<string, Relation>::iterator it = this->begin(); it != this->end(); ++it)
        for(Tuple x : it->second.getSet())
            size++;
    return size;
}