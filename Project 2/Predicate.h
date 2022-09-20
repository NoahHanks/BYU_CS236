#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"
#pragma once

using namespace std;

class Predicate{
private:
    string id;
    vector<Parameter> paramList;
public:
    Predicate(){
    id = "";
    paramList = vector<Parameter>();
}

~Predicate(){}

Predicate(string inputID){
    id = inputID;
    paramList = vector<Parameter>();
}

Predicate(string inputID, vector<Parameter> pList){
    id = inputID;
    paramList = pList;
}

string getID(){ return id; }
vector<Parameter> getParameters(){ return paramList; }
void addParameter(Parameter param){ paramList.push_back(param); }

string toString(){
    stringstream ss;
    ss << id << "(";
    for(int i = 0; i < (int)paramList.size(); i++)
        if(i == 0)
            ss << paramList[i].toString();
        else
            ss << "," << paramList[i].toString();
    ss << ")";
    return ss.str();
}
};