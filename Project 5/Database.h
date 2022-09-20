#include <stdio.h>
#include <map>
#include <string>
#include "Relation.h"
#pragma once
using namespace std;

class Database : public map<string, Relation> {
public:
    Database();
    ~Database();
    int getSize();
private:
};