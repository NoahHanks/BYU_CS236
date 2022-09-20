#include <stdio.h>
#include <map>
#include <string>
#include "Relation.h"

using namespace std;

class Database : public map<string, Relation> {
public:
    Database(){}
    ~Database(){}
private:
};