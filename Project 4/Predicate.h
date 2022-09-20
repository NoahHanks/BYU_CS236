#include <stdio.h>
#include <vector>
#include <string>
#include "Parameter.h"
#pragma once

using namespace std;

class Predicate {
private:
    string id;
    vector<Parameter> paramList;
public:
    Predicate();
    ~Predicate();
    Predicate(string ident);
    Predicate(string ident, vector<Parameter> pList);
    string getID();
    vector<Parameter> getParameters();
    void addParameter(Parameter param);
    string toString();
};